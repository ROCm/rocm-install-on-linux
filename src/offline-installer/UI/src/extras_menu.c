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
#include "extras_menu.h"
#include "help_menu.h"


// Extras Menu Setup
char *extrasMenuOps[] = {
    "rocminfo",
    "rocm-smi",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *extrasMenuDesc[] = {
    "Add rocminfo as extra installer package",
    "Add rocm-smi as extra installer package",
    " ",
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};


MENU_PROP extrasMenuProps = {
    .pMenuTitle = "Extra Packages",
    .pMenuControlMsg = "<DONE> to exit : Enter key to toggle selection",
    .numLines = ARRAY_SIZE(extrasMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = EXTRAS_MENU_ITEM_START_Y,
    .startx = EXTRAS_MENU_ITEM_START_X, 
    .numItems = ARRAY_SIZE(extrasMenuOps)
};

ITEMLIST_PARAMS extrasMenuItems = {
    .numItems           = (ARRAY_SIZE(extrasMenuOps)),
    .pItemListTitle     = "Extra Install Packages:",
    .pItemListChoices   = extrasMenuOps,
    .pItemListDesp      = extrasMenuDesc
};

// verbose help menu variables
// Spaces added/deleted from HelpOps and HelpDesc to ensure whole words aren't
// cut off between lines when displaying help menu.
char *extrasMenuHelpOps[] = {
    "rocminfo",
    "rocm-smi",
    SKIPPABLE_MENU_ITEM,
    (char*)NULL,
};

char *extrasMenuHelpDesc[] = {
    "rocminfo gives information about the HSA system        attributes and agents.",
    "rocm-smi acts as a command line interface for          manipulating and monitoring the amdgpu kernel.",
    " ",
    (char*)NULL,
};

MENU_PROP extrasMenuHelpProps = {
    .pMenuTitle = "Extra Packages Help",
    .pMenuControlMsg = DEFAULT_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = EXTRAS_MENU_ITEM_START_Y,
    .startx = EXTRAS_MENU_ITEM_START_X, 
    .numItems = 0
};

ITEMLIST_PARAMS extrasMenuHelpItems = {
    .numItems           = 0,
    .pItemListTitle     = "Extra Install Packages Description:",
    .pItemListChoices   = 0,
    .pItemListDesp      = 0
};


void process_extras_menu(MENU_DATA *pMenuData);

// sub-menus
void create_extras_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// menu draw
void extras_menu_draw(MENU_DATA *pMenuData);

void create_extras_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create the Main Extras options menu
    create_menu(pMenuData, pMenuWindow, &extrasMenuProps, &extrasMenuItems, pConfig);

    // create verbose help menu
    pMenuData->pHelpMenu = calloc(1, sizeof(MENU_DATA));
    if (pMenuData->pHelpMenu)
    {
        create_extras_help_menu_window(pMenuData->pHelpMenu, pMenuWindow);
    }

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = extras_menu_draw;

    // Set user pointers for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_extras_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);    // space before help
}

void destroy_extras_menu_window(MENU_DATA *pMenuData)
{
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);
}

void extras_menu_draw(MENU_DATA *pMenuData)
{
    EXTRAS_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->extras_config;

    menu_draw(pMenuData);

    menu_info_draw_bool(pMenuData, 5, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
    menu_info_draw_bool(pMenuData, 6, EXTRAS_MENU_FORM_COL, pConfig->rocmsmi_install);
}

void extras_menu_update_state(MENU_DATA *pMenuData)
{
    // Check global state and update the extras menu
    ROCM_MENU_CONFIG *pRocmConfig = &pMenuData->pConfig->rocm_config;
    EXTRAS_MENU_CONFIG *pConfig = &pMenuData->pConfig->extras_config;

    if (is_specific_usecase_selected(pMenuData, ROCM_USECASE)) 
    {
        pConfig->rocmsmi_install = true;
        pConfig->rocminfo_install = true;
        menu_set_item_select(pMenuData, 0, false);
        menu_set_item_select(pMenuData, 1, false);
    }
    else if (pRocmConfig->is_rocm_usecase_deselected)
    {
        pConfig->rocminfo_install = false;
        pConfig->rocmsmi_install = false;        
        menu_set_item_select(pMenuData, 0, true);
        menu_set_item_select(pMenuData, 1, true);

        // Need to reset back to false
        pRocmConfig->is_rocm_usecase_deselected = false;
    }

    menu_info_draw_bool(pMenuData, 5, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
    menu_info_draw_bool(pMenuData, 6, EXTRAS_MENU_FORM_COL, pConfig->rocmsmi_install);
}

void do_extras_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    wclear(pMenuData->pMenuWindow);

    // draw the extras menu contents
    extras_menu_draw(pMenuData);

    // Extras menu loop
    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the Extra packages main menu
void process_extras_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    EXTRAS_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->extras_config;
    
    ITEM *pCurrentItem = current_item(pMenu);

    int index = item_index(pCurrentItem);

    DEBUG_UI_MSG(pMenuData, "Extras menu: item %d", index);

    bool isSelectable = item_opts(pCurrentItem) == O_SELECTABLE;

    if (isSelectable)
    {
        if (index == 0)
        {
            pConfig->rocminfo_install = !pConfig->rocminfo_install;
            menu_info_draw_bool(pMenuData, 5, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
        }
        else if (index == 1)
        {
            pConfig->rocmsmi_install = !pConfig->rocmsmi_install;
            menu_info_draw_bool(pMenuData, 6, EXTRAS_MENU_FORM_COL,pConfig->rocmsmi_install);
        }
    }

    extras_menu_draw(pMenuData);
}

void create_extras_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &extrasMenuHelpProps, &extrasMenuHelpItems, NULL);

    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, extrasMenuHelpOps, extrasMenuHelpDesc); 
}
