/* ************************************************************************
 * Copyright (C) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
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
#include "post_menu.h"
#include "help_menu.h"


// Post Menu Setup
char *postMenuOps[] = {
    "Set GPU access permissions:",
    "    Add video,render group",
    "    Add udev rule",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *postMenuDesc[] = {
    "GPU access permissions",
    "Add current user to the video,render group for GPU access",
    "Add all users for GPU access",
    " ",
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};


MENU_PROP postMenuProps = {
    .pMenuTitle = "Post-Install Options",
    .pMenuControlMsg = "<DONE> to exit : Enter key to toggle selection",
    .numLines = ARRAY_SIZE(postMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = POST_MENU_ITEM_START_Y,
    .startx = POST_MENU_ITEM_START_X, 
    .numItems = ARRAY_SIZE(postMenuOps)
};

ITEMLIST_PARAMS postMenuItems = {
    .numItems           = (ARRAY_SIZE(postMenuOps)),
    .pItemListTitle     = "Post-Install:",
    .pItemListChoices   = postMenuOps,
    .pItemListDesp      = postMenuDesc
};

// verbose help menu variables
// Spaces added/deleted from HelpOps and HelpDesc to ensure whole words aren't
// cut off between lines when displaying help menu.
char *postMenuHelpOps[] = {
    "GPU Access Permissions",
    "    Current User",
    "    All Users"
    SKIPPABLE_MENU_ITEM,
    SKIPPABLE_MENU_ITEM,
    (char*)NULL,
};

char *postMenuHelpDesc[] = {
    " ",
    "Add the current user to the video,render group         for access to GPU resources.",
    "Grant GPU access to all users on the system via        udev rules.",
    "Note, this is an option for system admins.",
    (char*)NULL,
};

MENU_PROP postMenuHelpProps = {
    .pMenuTitle = "Post Install Help",
    .pMenuControlMsg = DEFAULT_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = POST_MENU_ITEM_START_Y,
    .startx = POST_MENU_ITEM_START_X, 
    .numItems = 0
};

ITEMLIST_PARAMS postMenuHelpItems = {
    .numItems           = 0,
    .pItemListTitle     = "Post Install Description:",
    .pItemListChoices   = 0,
    .pItemListDesp      = 0
};


void process_post_menu(MENU_DATA *pMenuData);

// sub-menus
void create_post_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// menu draw
void post_menu_draw(MENU_DATA *pMenuData);

MENU_DATA menuPost = {0};

void create_post_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create the post install options menu
    create_menu(pMenuData, pMenuWindow, &postMenuProps, &postMenuItems, pConfig);

    pMenuData->pHelpMenu = calloc(1, sizeof(MENU_DATA));
    if (pMenuData->pHelpMenu)
    {
        create_post_help_menu_window(pMenuData->pHelpMenu, pMenuWindow);
    }

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = post_menu_draw;

    // Set user pointers for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_post_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);    // space before help
}

void destroy_post_menu_window(MENU_DATA *pMenuData)
{
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);
}

void post_menu_draw(MENU_DATA *pMenuData)
{
    POST_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->post_config;

    menu_draw(pMenuData);

    menu_info_draw_bool(pMenuData, POST_MENU_ITEM_CUR_USER_ROW, POST_MENU_FORM_COL, pConfig->current_user_grp);
    menu_info_draw_bool(pMenuData, POST_MENU_ITEM_ALL_USER_ROW, POST_MENU_FORM_COL, pConfig->all_user_grp);
}

void do_post_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    wclear(pMenuData->pMenuWindow);

    // draw the post install menu contents
    post_menu_draw(pMenuData);

    // post install menu loop
    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the Extra packages main menu
void process_post_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    POST_MENU_CONFIG *pPostConfig = &pConfig->post_config;
    
    ITEM *pCurrentItem = current_item(pMenu);

    int index = item_index(pCurrentItem);

    DEBUG_UI_MSG(pMenuData, "post menu: item %d", index);

    bool isSelectable = item_opts(pCurrentItem) == O_SELECTABLE;

    if (isSelectable)
    {
        if (index == POST_MENU_ITEM_CUR_USER_INDEX)
        {
            pPostConfig->current_user_grp = !pPostConfig->current_user_grp;
            menu_info_draw_bool(pMenuData, POST_MENU_ITEM_CUR_USER_ROW, POST_MENU_FORM_COL, pPostConfig->current_user_grp);
        
            if (pPostConfig->current_user_grp)
            {
                // disable udev and set to false
                pPostConfig->all_user_grp = false;
                menu_info_draw_bool(pMenuData, POST_MENU_ITEM_ALL_USER_ROW, POST_MENU_FORM_COL, pPostConfig->all_user_grp);
                menu_set_item_select(pMenuData, POST_MENU_ITEM_ALL_USER_INDEX, false);
            }
            else
            {
                // enable udev
                menu_set_item_select(pMenuData, POST_MENU_ITEM_ALL_USER_INDEX, true);
            }
        
        }
        else if (index == POST_MENU_ITEM_ALL_USER_INDEX)
        {
            pPostConfig->all_user_grp = !pPostConfig->all_user_grp;
            menu_info_draw_bool(pMenuData, POST_MENU_ITEM_ALL_USER_ROW, POST_MENU_FORM_COL, pPostConfig->all_user_grp);

            if (pPostConfig->all_user_grp)
            {
                // disable user and set to false
                pPostConfig->current_user_grp = false;
                menu_info_draw_bool(pMenuData, POST_MENU_ITEM_CUR_USER_ROW, POST_MENU_FORM_COL, pPostConfig->current_user_grp);
                menu_set_item_select(pMenuData, POST_MENU_ITEM_CUR_USER_INDEX, false);
            }
            else
            {
                // enable user
                menu_set_item_select(pMenuData, POST_MENU_ITEM_CUR_USER_INDEX, true);
            }
        }
    }

    post_menu_draw(pMenuData);
}

void create_post_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &postMenuHelpProps, &postMenuHelpItems, NULL);

    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, postMenuHelpOps, postMenuHelpDesc); 
}
