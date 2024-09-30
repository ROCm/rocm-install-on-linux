/* ************************************************************************
 * Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop-
 * ies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM-
 * PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNE-
 * CTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * ************************************************************************ */
#include "menu_data.h"
#include "help_menu.h"
#include "utils.h"


int create_menu(MENU_DATA *pMenuData,  WINDOW *pMenuWin, MENU_PROP *pProperties, ITEMLIST_PARAMS *pItemListParams, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Set the menu window
    pMenuData->pMenuWindow = pMenuWin;
    
    pMenuData->enableMultiSelection = true;

    pMenuData->pMenuProps = pProperties;

    // Set the menu title, control message and configuration structure
    strcpy(pMenuData->menuTitle, pProperties->pMenuTitle);
    strcpy(pMenuData->menuControlMsg, pProperties->pMenuControlMsg);
    
    pMenuData->pConfig = pConfig;

    // Create items - main item list (index 0)
    add_menu_items(pMenuData, 0, pItemListParams);
    pMenuData->curItemListIndex = 0;

    // set the menu format
    set_menu_format(pMenuData->pMenu, MAX_MENU_ITEMS, 1);

    // Create menu for the primary item list (0)
    pMenuData->pMenu = new_menu((ITEM**)pMenuData->itemList[0].items);

    // set the default menu item colours (while with black backgroud)
    set_menu_fore(pMenuData->pMenu, COLOR_PAIR(3) | A_BOLD);

    // Set menu mark to the string
    set_menu_mark(pMenuData->pMenu, " > ");

    // Disable menu descriptions
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // Set main window and sub window
    set_menu_win(pMenuData->pMenu, pMenuWin);
    set_menu_sub(pMenuData->pMenu, derwin(pMenuWin, pProperties->numLines, pProperties->numCols,  pProperties->starty,  pProperties->startx));
    
    return 0;
}

int add_menu_items(MENU_DATA *pMenuData, int itemListIndex, ITEMLIST_PARAMS *pItemListParams)
{
    int i;
    int numItems;

    if (itemListIndex >= MAX_NUM_ITEM_LIST)
    {
        print_menu_err_msg(pMenuData, "Exceed item lists");
        return -1;
    }

    numItems = pItemListParams->numItems;

    pMenuData->itemList[itemListIndex].numItems = numItems;
    pMenuData->itemList[itemListIndex].items = (ITEM**)calloc(numItems, sizeof(ITEM*));

    int itemListTitleLen = strlen(pItemListParams->pItemListTitle);

    if (itemListTitleLen >= MAX_MENU_ITEM_COLS)
    {
        itemListTitleLen = MAX_MENU_ITEM_COLS;
    }

    strncpy(pMenuData->itemList[itemListIndex].itemTitle, pItemListParams->pItemListTitle, (size_t) itemListTitleLen);
    
    // only to be used in the summary page before creating offline installer
    pMenuData->itemList[itemListIndex].createOfflineInstallerItemIndex = -1;

    if (NULL != pMenuData->itemList[itemListIndex].items)
    {
        for(i = 0; i < numItems; ++i)
        {
            pMenuData->itemList[itemListIndex].items[i] = new_item(pItemListParams->pItemListChoices[i], pItemListParams->pItemListDesp[i]);
        }

        pMenuData->itemList[itemListIndex].doneItemIndex = numItems - 2;      // done item is the last item
        pMenuData->itemList[itemListIndex].helpItemIndex = numItems - 3;      // help item is the second last item
    }
    else
    {
        print_menu_err_msg(pMenuData, "Failed to allocate item list");
        return -1;
    }
    
    return 0;
}

void destroy_menu(MENU_DATA *pMenuData)
{
    int i;
    int itemListIndex;

    // Unpost and free all the memory taken up
    unpost_menu(pMenuData->pMenu);

    //for (itemListIndex = 0; i < NUM_ITEM_LIST; ++itemListIndex)
    for (itemListIndex = 0; itemListIndex < MAX_NUM_ITEM_LIST; itemListIndex++)
    {
        if (NULL != pMenuData->itemList[itemListIndex].items)
        {
            for(i = 0; i < pMenuData->itemList[itemListIndex].numItems; ++i)
            {
                free_item(pMenuData->itemList[itemListIndex].items[i]);
            }
        }
    }

    free_menu(pMenuData->pMenu);
}

bool is_skippable_menu_item(ITEM* item)
{
    const char *name = item_name(item);
    return (strcmp(name, SKIPPABLE_MENU_ITEM) == 0) ? true : false;
}

void skip_menu_item_down_if_skippable(MENU *pMenu)
{
    if (is_skippable_menu_item(current_item(pMenu)))
    {
        menu_driver(pMenu, REQ_DOWN_ITEM);
    }
}

void skip_menu_item_up_if_skippable(MENU *pMenu)
{
    if (is_skippable_menu_item(current_item(pMenu)))
    {
        menu_driver(pMenu, REQ_UP_ITEM);
    }
}

bool is_menu_item_help_item_index(MENU_DATA *pMenuData, int listIndex, ITEM *item)
{
    return pMenuData->itemList[listIndex].helpItemIndex == item_index(item);
}

bool is_menu_item_done_item_index(MENU_DATA *pMenuData, int listIndex, ITEM *item)
{
    return pMenuData->itemList[listIndex].doneItemIndex == item_index(item);
}

void menu_loop(MENU_DATA *pMenuData)
{
    int c;
    int done = 0;
    int listIndex = pMenuData->curItemListIndex;

    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    MENU *pMenu = pMenuData->pMenu;
    ITEM *pCurrentItem;

    void (*p)(MENU_DATA*);
    void (*drawFunc)(MENU_DATA*);
    
    // Menu loop
    while( done == 0 )
    {   
        pCurrentItem = current_item(pMenu);

        c = wgetch(pMenuWindow);
        
        switch(c)
        {	
            case KEY_RESIZE: // Terminal window resize
                if (should_window_be_resized(pMenuWindow, WIN_NUM_LINES,WIN_WIDTH_COLS))
                {
                    reset_window_before_resizing(pMenuData);
                    
                    drawFunc = pMenuData->drawMenuFunc;
                    drawFunc(pMenuData); 
                }   

                p = item_userptr(pCurrentItem);
                if (NULL != p)
                {
                    p((MENU_DATA*)pMenuData);
                }
                break;

            case KEY_DOWN:
                menu_driver(pMenu, REQ_DOWN_ITEM);

                skip_menu_item_down_if_skippable(pMenu);
                
                pCurrentItem = current_item(pMenu);

                if (pMenuData->clearErrMsgAfterUpOrDownKeyPress)
                {
                    clear_menu_err_msg(pMenuData);
                }

                print_menu_item_selection(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X);

                // Don't want to run userptr function when user navigates to 
                // <HELP> menu item in rocm components menu.
                if (is_menu_item_help_item_index(pMenuData,listIndex, pCurrentItem)) continue;
                
                p = item_userptr(pCurrentItem);
                if (NULL != p)
                {
                    p((MENU_DATA*)pMenuData);
                }
                
                break;

            case KEY_UP:
                menu_driver(pMenu, REQ_UP_ITEM);

                skip_menu_item_up_if_skippable(pMenu);

                pCurrentItem = current_item(pMenu);

                if (pMenuData->clearErrMsgAfterUpOrDownKeyPress)
                {
                    clear_menu_err_msg(pMenuData);
                }

                print_menu_item_selection(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X);

                // Don't want to run userptr function when user navigates to 
                // <HELP> menu item in rocm components menu.
                if (is_menu_item_help_item_index(pMenuData,listIndex, pCurrentItem)) continue;
        
                p = item_userptr(pCurrentItem);
                if (NULL != p)
                {
                    p((MENU_DATA*)pMenuData);
                }

                break;
            
            case ' ':
                // Don't do anything if item isn't selectable.
                if (item_opts(pCurrentItem) != O_SELECTABLE) continue;
                
                // Space bar selection only enabled for menus where isMenuItemSelectable
                // is true.
                if (!pMenuData->isMenuItemsSelectable) continue;

                // Prevents users from trying to select the <DONE> and <HELP> menu items.
                if (is_menu_item_done_item_index(pMenuData, listIndex, pCurrentItem) || 
                    is_menu_item_help_item_index(pMenuData, listIndex, pCurrentItem))
                {
                    continue;   
                }

                // Clears warning messages at the very bottom of the window.
                clear_menu_err_msg(pMenuData);

                // Deselect all other items if multiselection is disabled and the 
                // new item is not currently selected.
                if ( (!pMenuData->enableMultiSelection) && ((item_value(pCurrentItem) == FALSE)) )
                {
                    ITEM **items = menu_items(pMenu);
                    
                    for (int i = 0; i < item_count(pMenu); i++) 
                    {
                        if (item_value(items[i]) == TRUE) 
                        {
                            set_item_value(items[i], false);
                        }

                        delete_menu_item_selection_mark(pMenuData, items[i]);
                    }

                    pMenuData->itemSelections = 0;
                }           

                // update the item selection bitfield
                TOGGLE_BIT( (pMenuData->itemSelections), (item_index(pCurrentItem)) );

                menu_driver(pMenu, REQ_TOGGLE_ITEM);

                if (item_value(pCurrentItem))
                {
                    add_menu_item_selection_mark(pMenuData, pCurrentItem);
                }
                else
                {
                    delete_menu_item_selection_mark(pMenuData, pCurrentItem);
                }

                p = menu_userptr(pMenu);
                if (NULL != p)
                {
                    p((MENU_DATA*)pMenuData);
                }                
                
                break;

            case 's':
                print_menu_selections(pMenuData);
                break;

            case 10:    // Enter
                if ( item_index(pCurrentItem) == pMenuData->itemList[listIndex].doneItemIndex )
                {
                    done = 1;
                }
                else
                {   // When user clicks '<ACCEPT>' in the summary menu
                    if (item_index(pCurrentItem) == pMenuData->itemList[0].createOfflineInstallerItemIndex)
                    {
                        if (item_opts(pCurrentItem) == O_SELECTABLE)
                        {
                            done = 1;
                        }
                        
                        // If you don't add the continue here, it will execute
                        // process_create_offline_installer 
                        else
                        {
                            continue;
                        }
                    }

                    if (is_menu_item_help_item_index(pMenuData, 0, pCurrentItem))
                    {
                        if (pMenuData->pHelpMenu)
                        {
                            MENU_DATA *helpMenu = (MENU_DATA *)pMenuData->pHelpMenu;
                            unpost_menu(pMenu); 
                            do_help_menu(helpMenu);
                        }
                    }

                    // call the menu data processor
                    p = menu_userptr(pMenu);
                    if (NULL != p)
                    {
                        p((MENU_DATA*)pMenuData);
                    }
                    else
                    {
                        DEBUG_UI_MSG(pMenuData, "No user ptr for form");
                    }

                    p = item_userptr(pCurrentItem);
                    if (NULL != p)
                    {
                        p((MENU_DATA*)pMenuData);
                    }
                }
                break;
        }

        wrefresh(pMenuWindow);
    }
}

void menu_draw(MENU_DATA *pMenuData)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    MENU *pMenu = pMenuData->pMenu;

    int curItemListIndex = pMenuData->curItemListIndex;

    // resizes pMenuWindow and subwindow that displays menu items to its original
    // size in case user resized terminal window
    resize_and_reposition_window_and_subwindow(pMenuData, WIN_NUM_LINES, WIN_WIDTH_COLS);

    print_menu_title(pMenuData, MENU_TITLE_Y, MENU_TITLE_X, WIN_WIDTH_COLS, pMenuData->menuTitle, COLOR_PAIR(2));
    print_menu_item_title(pMenuData,  ITEM_TITLE_Y, ITEM_TITLE_X, pMenuData->itemList[curItemListIndex].itemTitle, COLOR_PAIR(9));
    
    print_menu_item_selection(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X);
    print_menu_control_msg(pMenuData);

    box(pMenuWindow, 0, 0);

    post_menu(pMenu);

    // redraw and currently selected items (if any)
    if (pMenuData->itemSelections)
    {
        ITEM **items = menu_items(pMenu);
        
        for(int i = 0; i < pMenuData->itemList[0].numItems; ++i)
        {
            if ( ((pMenuData->itemSelections) & (1 << i)) && (item_opts(items[i]) == O_SELECTABLE) )
            {
                set_item_value(items[i], true);
                add_menu_item_selection_mark(pMenuData, items[i]);
            }
        }
    }

    print_version(pMenuData);
}

void menu_info_draw_bool(MENU_DATA *pMenuData, int starty, int startx, bool val)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    wmove(pMenuWindow, starty, 0);

    if (val)
    {
        wattron(pMenuWindow, COLOR_PAIR(4));
        mvwprintw(pMenuWindow, starty, startx, "%s", "yes ");
        wattroff(pMenuWindow, COLOR_PAIR(4));
    }
    else
    {
        wattron(pMenuWindow, COLOR_PAIR(1));
        mvwprintw(pMenuWindow, starty, startx, "%s", "no ");
        wattroff(pMenuWindow, COLOR_PAIR(1));
    }
}

void menu_set_item_select(MENU_DATA *pMenuData, int itemIndex, bool enable_select)
{
    if (enable_select)
    {
        item_opts_on(pMenuData->itemList[0].items[itemIndex], O_SELECTABLE);
    }
    else
    {
        item_opts_off(pMenuData->itemList[0].items[itemIndex], O_SELECTABLE);
    }
}

void print_menu_title(MENU_DATA *pMenuData, int starty, int startx, int width, char *string, chtype color)
{
    int length, x, y;
    float temp;

    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    getyx(pMenuWindow, y, x);
    if(startx != 0)
    {
        x = startx;
    }

    if(starty != 0)
    {
        y = starty;
    }

    if(width == 0)
    {
        width = WIN_WIDTH_COLS;
    }

    length = strlen(string);
    temp = (width - length)/ 2;

    x = startx + (int)temp;

    wmove(pMenuWindow, y, 0);
    wclrtoeol(pMenuWindow);

    mvwhline(pMenuWindow, 2, 2, ACS_HLINE, WIN_WIDTH_COLS - 4);

    wattron(pMenuWindow, color | A_BOLD);
    mvwprintw(pMenuWindow, y, x, "%s", string);
    wattroff(pMenuWindow, color | A_BOLD);
}

void print_menu_item_title(MENU_DATA *pMenuData, int starty, int startx, char *string, chtype color)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    wmove(pMenuWindow, starty, 0);
    wclrtoeol(pMenuWindow);

    wattron(pMenuWindow, color);
    mvwprintw(pMenuWindow, starty, startx, "%s", string);
    wattroff(pMenuWindow, color);
}

void print_border_around_item_description(WINDOW *pMenuWindow, int starty)
{   
    mvwaddch(pMenuWindow, starty, WIN_WIDTH_COLS-1, ACS_VLINE);
    mvwaddch(pMenuWindow, starty+1, 0, ACS_VLINE);
    mvwaddch(pMenuWindow, starty+1, WIN_WIDTH_COLS-1, ACS_VLINE);
}

void remove_menu_item_selection_description(MENU_DATA *pMenuData, int starty, int startx)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    wmove(pMenuWindow, starty, startx);
    wclrtoeol(pMenuWindow);

    wmove(pMenuWindow, starty+1, 0);
    wclrtoeol(pMenuWindow);

    print_border_around_item_description(pMenuWindow, starty);
}

// For situation where you want to modify the item description at the bottom
// depending on what option user select
// eg user is either selecting 'full' or 'minimum' in 'dependency download type'
// in create configuration menu and you want the item description to show
// a description for either 'full' or 'minimum'
void print_menu_item_selection_opt(MENU_DATA *pMenuData, int starty, int startx, const char *description)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    
    wmove(pMenuWindow, starty, startx);
    wclrtoeol(pMenuWindow);

    wmove(pMenuWindow, starty+1, 0);
    wclrtoeol(pMenuWindow);

#if ENABLE_MENU_DEBUG
    MENU *pMenu = pMenuData->pMenu;
    ITEM *pItem = current_item(pMenu);
    mvwprintw(pMenuWindow, starty, startx, "%d: name %s: %s", 
        item_index(pItem) + 1,  
        item_name(pItem), 
        description);
#else
    mvwprintw(pMenuWindow, starty, startx, "* %s", description);
#endif // ENABLE_MENU_DEBUG

    print_border_around_item_description(pMenuWindow, starty);
}

void print_menu_item_selection(MENU_DATA *pMenuData, int starty, int startx)
{
    ITEM *pItem = current_item(pMenuData->pMenu);
    
    print_menu_item_selection_opt(pMenuData, starty, startx, item_description(pItem));
}

void print_menu_selections(MENU_DATA *pMenuData)
{
    char temp[DEFAULT_CHAR_SIZE];
    ITEM **items;
    int i;

    MENU *pMenu = pMenuData->pMenu;

    temp[0] = '\0';

    items = menu_items(pMenu);
	
    for(i = 0; i < item_count(pMenu); ++i)
    {
        if(item_value(items[i]) == TRUE)
        {
            strcat(temp, item_name(items[i]));
            strcat(temp, " ");
        }
    }

    DEBUG_UI_MSG(pMenuData, "Selections = %s : itemSelections 0x%x", temp, pMenuData->itemSelections);
}

void print_version(MENU_DATA *pMenuData)
{
    mvwprintw(pMenuData->pMenuWindow, 28, 72, "v%s-%s", OFFLINE_VERSION, ROCM_VERSION);
}

void print_menu_warning_msg(MENU_DATA *pMenuData, int y, int x, const char *fmt, ...)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if(len < 0) return;

    // format the string
    char string[len + 1];

    va_start(args, fmt);
    vsnprintf(string, len + 1, fmt, args);
    va_end(args);

    wmove(pMenuWindow, y, x);
    wclrtoeol(pMenuWindow);
    wattron(pMenuWindow, COLOR_PAIR(10));
    mvwprintw(pMenuWindow, y, x, "WARNING: %s", string);
    wattroff(pMenuWindow, COLOR_PAIR(10));

    print_border_around_item_description(pMenuWindow, y-1);
    print_version(pMenuData);
}

void print_menu_err_msg(MENU_DATA *pMenuData, const char *fmt, ...)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    int x = DEBUG_ERR_START_X;
    int y = DEBUG_ERR_START_Y;

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if(len < 0) return;

    // format the string
    char string[len + 1];

    va_start(args, fmt);
    vsnprintf(string, len + 1, fmt, args);
    va_end(args);

    wmove(pMenuWindow, y, x);
    wclrtoeol(pMenuWindow);
    
    wattron(pMenuWindow, COLOR_PAIR(1));
    mvwprintw(pMenuWindow, y, x, "ERROR: %s", string);
    wattroff(pMenuWindow, COLOR_PAIR(1));

    print_border_around_item_description(pMenuWindow, y-1);
    print_version(pMenuData);
}

void clear_menu_err_msg(MENU_DATA *pMenuData)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    
    wmove(pMenuWindow, DEBUG_ERR_START_Y, DEBUG_ERR_START_X);
    wclrtoeol(pMenuWindow);
    print_border_around_item_description(pMenuWindow, DEBUG_ERR_START_Y-1);
    print_version(pMenuData);
}

void print_menu_dbg_msg(MENU_DATA *pMenuData, const char *fmt, ...)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    int x = DEBUG_ERR_START_X;
    int y = DEBUG_ERR_START_Y;

    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if(len < 0) return;

    // format the string
    char string[len + 1];

    va_start(args, fmt);
    vsnprintf(string, len + 1, fmt, args);
    va_end(args);

    wmove(pMenuWindow, y, x);
    wclrtoeol(pMenuWindow);

    mvwprintw(pMenuWindow, y, x, "DEBUG: %s", string);
}

void print_menu_control_msg(MENU_DATA *pMenuData)
{
    move(WIN_NUM_LINES + 5, 0);
    clrtoeol();

    mvprintw(WIN_NUM_LINES + 5, 0, "%s", pMenuData->menuControlMsg);
    refresh();
}

bool print_url_check(MENU_DATA *pMenuData, char *url)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    
#if ENABLE_MENU_DEBUG
    mvwprintw(pMenuWindow, 21, 1, "%s", url);
#endif

    if ( check_url(url) != 0 )
    {
        wattron(pMenuWindow, COLOR_PAIR(1));
        mvwprintw(pMenuWindow, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, "* Invalid URL");
        wattroff(pMenuWindow, COLOR_PAIR(1));
        return false;
    }
    
    wattron(pMenuWindow, COLOR_PAIR(4));
    mvwprintw(pMenuWindow, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, "* Valid URL  ");
    wattroff(pMenuWindow, COLOR_PAIR(4));
    
    return true;
}

int create_form(MENU_DATA *pMenuData, WINDOW *pMenuWin, int numFields, int width, int height, int starty, int startx)
{ 
    int i;
    int rows, cols;

    if (numFields >= MAX_NUM_FORM_FIELDS)
    {
        return -1;
    }

    for (i = 0; i < numFields; i++)
    {
         //                                                        row,     col
        pMenuData->pFormList.field[i] = new_field(height, width, starty+i,  startx,  0, 0);     // initial line-by-line (can be moved)

        field_opts_off(pMenuData->pFormList.field[i], O_AUTOSKIP);  // don't skip to the next field with filled
        field_opts_off(pMenuData->pFormList.field[i], O_BLANK);     // don't delete entire field if a character is added in the first position

        field_opts_off(pMenuData->pFormList.field[i], O_STATIC);             // enable dynamic fields
        set_max_field(pMenuData->pFormList.field[i], MAX_FORM_FIELD_WIDTH);  // set the max field width for the dynamic field
    }

    pMenuData->pFormList.pForm = new_form(pMenuData->pFormList.field);
    pMenuData->pFormList.numFields = numFields;

    scale_form(pMenuData->pFormList.pForm, &rows, &cols);

    set_form_win(pMenuData->pFormList.pForm, pMenuWin);
    set_form_sub(pMenuData->pFormList.pForm, derwin(pMenuWin,  rows, cols, 0, 0));

    return 0;
}

void destroy_form(MENU_DATA *pMenuData)
{
    int i;

    unpost_form(pMenuData->pFormList.pForm);

    for (i = 0; i < pMenuData->pFormList.numFields; i++)
    {
        free_field(pMenuData->pFormList.field[i]);
    }

    free_form(pMenuData->pFormList.pForm);
}

void form_loop(MENU_DATA *pMenuData, bool enableNextField)
{
    int c, x;
    int done = 0;

    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    FORM *pForm = pMenuData->pFormList.pForm;

    curs_set(1);

    // move to the end of the field (default values if already set)
    form_driver(pMenuData->pFormList.pForm, REQ_END_LINE);

    wrefresh(pMenuWindow);

    // Form loop
    while( done == 0 )
    {
        c = wgetch(pMenuWindow);

        DEBUG_UI_MSG(pMenuData, "Hit : %c or %d : currentFieldIndex %d", c, c, field_index(current_field(pForm)));
        switch(c)
	    {
            case KEY_DOWN:
                if (enableNextField)
                {
                    // Go to next field
                    form_driver(pForm, REQ_NEXT_FIELD);
                    form_driver(pForm, REQ_END_LINE);
                }
                break;

	        case KEY_UP:
                if (enableNextField)
                {
                    // Go to previous field
                    form_driver(pForm, REQ_PREV_FIELD);
                    form_driver(pForm, REQ_END_LINE);
                }
                break;

            case KEY_BACKSPACE:
            case 8:
            case 127:
                x = getcurx(pMenuWindow);
                
                FIELD *pCurrentField = current_field(pForm);
                // don't run REQ_DEL_PREV if cursor is at the beginning of the field
                // due to ncurses behaviour that changes cmd REQ_DEL_PREV into
                // REQ_PREV_FIELD when on the first char.
                // workaround of setting option O_BS_OVERLOAD off doesn't work.
                if (x > pCurrentField->fcol ) 
                {
                    form_driver(pForm, REQ_DEL_PREV);
                }

                break;

            case CTRL('D'):
                DEBUG_UI_MSG(pMenuData, "Ctrl-D");
                form_driver(pForm, REQ_CLR_FIELD);
                break;

            case 10: //Enter
                form_driver(pForm, REQ_NEXT_FIELD);
                form_driver(pForm, REQ_PREV_FIELD);

                done = 1;

                break;
                
            case KEY_DC:
                form_driver(pForm, REQ_DEL_CHAR);
                break;
                
            case KEY_LEFT:
                form_driver(pForm, REQ_LEFT_CHAR);
                break;
                
            case KEY_RIGHT:
                form_driver(pForm, REQ_RIGHT_CHAR);
                break;
                
            default:	
                form_driver(pForm, c);
                break;
        }
    }

    curs_set(0);
}

void print_form_control_msg(MENU_DATA *pMenuData)
{
    move(WIN_NUM_LINES + 5, 0);
    clrtoeol();

    mvprintw(WIN_NUM_LINES + 5, 0, "%s", pMenuData->pFormList.formControlMsg);
    refresh();
}

bool should_window_be_resized(WINDOW *pMenuWindow, int y, int x)
{
    int menuWindowX, menuWindowY;
    getmaxyx(pMenuWindow, menuWindowY, menuWindowX);

    if (menuWindowX < x || menuWindowY < y)
    {
        return false;
    }

    return true;
}

void resize_and_reposition_window_and_subwindow(MENU_DATA *pMenuData, int y, int x)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    MENU_PROP *pProperties = pMenuData->pMenuProps;
    WINDOW *pSubMenuWindow = menu_sub(pMenuData->pMenu); // displays menu items

    wresize(pMenuWindow, y, x);
    
    // resize and resposition pSubMenuWindow relative to parent window
    wresize(pSubMenuWindow, pProperties->numLines, pProperties->numCols);
    mvderwin(pSubMenuWindow, pProperties->starty, pProperties->startx);
}

void reset_window_before_resizing(MENU_DATA *pMenuData)
{
    unpost_menu(pMenuData->pMenu);
    clear();
    endwin();
}

bool is_repo_public(MENU_DATA *pMenuData)
{
    return pMenuData->pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC;   
}

bool is_specific_usecase_selected(MENU_DATA *pMenuData, char *usecase) 
{
    ROCM_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->rocm_config;
    char *copy = calloc(1, sizeof(pConfig->rocm_usescases));
    if (!copy)
    {
        return false;
    }
    strcpy(copy, pConfig->rocm_usescases);
    char *p = strtok (copy, ",");

    // split rocm_usecases char string into a string array using , as delimiter
    char *rocm_usecases_array[DEFAULT_CHAR_SIZE];
    int i = 0;

    while (p != NULL)
    {
        rocm_usecases_array[i] = p;
        p = strtok (NULL, ",");
        i++;
    }

    while(i > 0)
    {
        // subtract first as value of i is 1 greater than last index in
        // rocm_usecases_array
        i--;
        if (strcmp(rocm_usecases_array[i], usecase) == 0)
        {
            free(copy);
            return true;
        }   
    }
    free(copy);
    return false;
}

void add_menu_item_selection_mark(MENU_DATA *pMenuData, ITEM *pCurrentItem)
{
    WINDOW *pSubMenuWindow = menu_sub(pMenuData->pMenu); 
    mvwprintw(pMenuData->pMenuWindow, getpary(pSubMenuWindow) + item_index(pCurrentItem), 2, "X");
}

void delete_menu_item_selection_mark(MENU_DATA *pMenuData, ITEM *pCurrentItem)
{
    WINDOW *pSubMenuWindow = menu_sub(pMenuData->pMenu);
    mvwprintw(pMenuData->pMenuWindow, getpary(pSubMenuWindow) + item_index(pCurrentItem), 2, " ");
}

int display_scroll_window(char *filename, char *query_string, char *query_pass, char *query_fail)
{
    WINDOW *win;

    int done = 0;
    int ret = -1;

    char **lines = NULL;
    char *line = NULL;
    size_t line_length = 0;
    ssize_t read;

    int start_line = 0;
    int num_lines = 0;
    int c;

    int max_win_lines = WIN_NUM_LINES - 3;

    int query_line = max_win_lines + 1;
    char query[DISPLAY_SCROLL_WINDOW_QUERY_SIZE];
    memset(query, '\0', sizeof(query));

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return -1;
    }

    win = newwin(WIN_NUM_LINES, WIN_WIDTH_COLS, WIN_START_Y, WIN_START_X);

    scrollok(win, TRUE);
    keypad(win, TRUE);
    curs_set(1);

    // Read in all the lines making up the file
    while ((read = getline(&line, &line_length, file)) != -1) 
    {
        lines = realloc(lines, (num_lines + 1) * sizeof(char*));
        lines[num_lines] = line;

        line = NULL;
        line_length = 0;
        
        num_lines++;
    }
    free(line);
    fclose(file);

    // adjust for single page files
    if (num_lines < max_win_lines)
    {
        max_win_lines = num_lines + 1;
    }

    // Draw the contents of the file line-by-line
    while( done == 0 )
    {
        // Display all the lines of text up until the size of the window
        for (int i = 0; i < max_win_lines - 1; i++) 
        {
            mvwprintw(win, i+1, 1, lines[start_line + i], "%s");
        }
        
        mvwhline(win, query_line-1, 1, ACS_HLINE, WIN_WIDTH_COLS - 1);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, query_line, 1, "%s (%s/%s) : %s", query_string, query_pass, query_fail, query);
        wattroff(win, COLOR_PAIR(2));

        wrefresh(win);

        c = wgetch(win);
        switch (c) 
        {
            case KEY_DOWN:
                if (start_line < num_lines - (max_win_lines-1))
                {
                    start_line++;
                }
                break;
            case KEY_UP:
                if (start_line > 0) 
                {
                    start_line--;
                }
                break;
            
            case 10:    // Enter
                if (strcmp(query, query_pass) == 0)
                {
                    done = 1;
                    ret = 0;
                }
                else if (strcmp(query, query_fail) == 0)
                {
                    done = 1;
                }
                break;

            case KEY_BACKSPACE:
                memset(query, '\0', sizeof(query));
                wmove(win, query_line, 1);
                wclrtoeol(win);
                break;

            default:
                if (strlen(query) < 16)
                {
                    strncat(query, (char*)&c, 1);
                }
                break;
        }
    };

    delwin(win);
    curs_set(0);

    for (int i = 0; i < num_lines; i++) 
    {
        free(lines[i]);
    }
    free(lines);

    return ret;
}

int display_help_scroll_window(MENU_DATA *pMenuData, char *filename)
{
    WINDOW *win;

    int done = 0;

    char **lines = NULL;
    char *line = NULL;
    size_t line_length = 0;
    ssize_t read;

    int start_y = ITEM_TITLE_Y + 1;
    int start_line = 0;
    int num_lines = start_y;
    int c;

    int max_win_lines = WIN_NUM_LINES - 4;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        print_menu_err_msg(pMenuData, "Failed to open file %s. Press any key to exit this menu.", filename);
        return -1;
    }

    help_menu_draw(pMenuData);
    win = pMenuData->pMenuWindow;

    scrollok(win, TRUE);
    keypad(win, TRUE);
    curs_set(0);

    // Read in all the lines making up the file
    while ((read = getline(&line, &line_length, file)) != -1) 
    {
        lines = realloc(lines, (num_lines + 1) * sizeof(char*));
        lines[num_lines] = line;

        line = NULL;
        line_length = 0;
        
        num_lines++;
    }
    free(line);
    fclose(file);

    // adjust for single page files
    if (num_lines < max_win_lines)
    {
        max_win_lines = num_lines + 1;
    }

    // Draw the contents of the file line-by-line
    while( done == 0 )
    {
        // Display all the lines of text up until the size of the window
        for (int i = start_y; i < max_win_lines - 1; i++) 
        {
            mvwprintw(win, i+1, 1, lines[start_line + i], "%s");
        } 
        
        box(win, 0, 0);

        wrefresh(win);

        c = wgetch(win);
        switch (c) 
        {
            case KEY_DOWN:
                if (start_line < num_lines - (max_win_lines-1))
                {
                    start_line++;
                }
                break;
            case KEY_UP:
                if (start_line > 0) 
                {
                    start_line--;
                }
                break;

            default:
                done = 1;
        }
    };

    for (int i = start_y; i < num_lines; i++) 
    {  
        free(lines[i]);
    }
    free(lines);

    return 0;
}
