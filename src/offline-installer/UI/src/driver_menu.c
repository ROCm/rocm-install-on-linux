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
#include "driver_menu.h"
#include "rocm_menu.h"
#include "help_menu.h"
#include "utils.h"


// Driver/amdgpu Setup
char *driverMenuOps[] = {
    "Install amdgpu Driver",
    SKIPPABLE_MENU_ITEM,
    "    amdgpu Driver ROCm Version",
    SKIPPABLE_MENU_ITEM,
    "    Set Video,Render Group",
    "    Blacklist amdgpu driver",
    "    Start amdgpu driver on install",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *driverMenuDesc[] = {
    "Enable/Disable amdgpu driver install.",
    " ",
    "Set ROCm Version of amdgpu driver for installation.",
    " ",
    "Adds the current user to the render and video groups.",
    "Prevents amdgpu driver from loading on boot.",
    "Starts amdgpu driver immediately after installation.",
    " ",
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};

MENU_PROP driverMenuProps = {
    .pMenuTitle = "Driver Options",
    .pMenuControlMsg = "<DONE> to exit : Enter key to toggle selection",
    .numLines = ARRAY_SIZE(driverMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = DRIVER_MENU_ITEM_START_Y,
    .startx = DRIVER_MENU_ITEM_START_X,
    .numItems = ARRAY_SIZE(driverMenuOps)
};

ITEMLIST_PARAMS driverMenuItems = {
    .numItems           = (ARRAY_SIZE(driverMenuOps)),
    .pItemListTitle     = "Driver Install Settings:",
    .pItemListChoices   = driverMenuOps,
    .pItemListDesp      = driverMenuDesc
};

// verbose help menu variables
// Spaces added/deleted from HelpOps and HelpDesc to ensure whole words aren't
// cut off between lines when displaying help menu.
char *driverMenuHelpOps[] = {
    "amdgpu Install   Driver",
    "amdgpu Driver    ROCm Version",
    "Set Video,Render Group",
    "Blacklist amdgpu driver",
    "Start amdgpu     driver on install",
    "",
    (char*)NULL
};

char *driverMenuHelpDesc[] = {
    "Include the amdgpu driver in the creation of           offline installer.",
    "amdgpu driver ROCm version for driver source           packages.",
    "If enabled, adds current user to the video group to    access GPU resources.",
    "Prevents the amdgpu driver from automatically starting on boot after installing it (useful for debug).",
    "Starts the amdgpu driver after it is installed. This   option is typically used for OS installs that do not   have an enabled upstream driver already included.",
    "",
    (char*)NULL
};

MENU_PROP driverMenuHelpProps = {
    .pMenuTitle = "Driver Options Help",
    .pMenuControlMsg = DEFAULT_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = DRIVER_MENU_ITEM_START_Y,
    .startx = DRIVER_MENU_ITEM_START_X,
    .numItems = 0
};

ITEMLIST_PARAMS driverMenuHelpItems = {
    .numItems           = 0,
    .pItemListTitle     = "Driver Features Description:",
    .pItemListChoices   = NULL,
    .pItemListDesp      = NULL
};


void process_driver_menu(MENU_DATA *pMenuData);

// sub-menus
void create_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);


// menu draw/config
void driver_menu_toggle_grey_items(MENU_DATA *pMenuData);
void driver_menu_draw(MENU_DATA *pMenuData);


void create_driver_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create the Main Driver options menu
    create_menu(pMenuData, pMenuWindow, &driverMenuProps, &driverMenuItems, pConfig);

    // create verbose help menu
    pMenuData->pHelpMenu = calloc(1, sizeof(MENU_DATA));
    if (pMenuData->pHelpMenu)
    {
        create_driver_help_menu_window(pMenuData->pHelpMenu, pMenuWindow);
    }

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = driver_menu_draw;

    // Set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_driver_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);     // space before <HELP>
    driver_menu_toggle_grey_items(pMenuData);

}

void destroy_driver_menu_window(MENU_DATA *pMenuData)
{
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);
}

void driver_menu_draw(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;
  
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_INSTALL_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->install_driver);
    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_GRP_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->set_group);
    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->blacklist_driver);
    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->start_driver);


    if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC)
    {
        if (pDriverConfig->install_driver)
        {
            mvwprintw(pMenuWindow, DRIVER_MENU_ITEM_DRIVER_VER_ROW, DRIVER_MENU_FORM_COL, "%s", pRocmConfig->rocm_versions);
        }
        else
        {
            wmove(pMenuWindow, DRIVER_MENU_ITEM_DRIVER_VER_ROW, DRIVER_MENU_FORM_COL);
            wclrtoeol(pMenuWindow);
        }
    }

    menu_draw(pMenuData);
}

void driver_menu_opts_toggle_grey_items(MENU_DATA *pMenuData)
{
    
    ROCM_MENU_CONFIG *pRocmConfig = &pMenuData->pConfig->rocm_config;
    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    // Only enable the 3 driver opts if install_driver is true and user has selected
    // a rocm version
    bool enable = pDriverConfig->install_driver && pRocmConfig->rocm_version_selected;

    // enable/disable all driver option fields
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_GRP_INDEX, enable);
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, enable);
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_INDEX, enable);
    
    if (!enable)
    {
        // reset to defaults
        pDriverConfig->set_group = false;
        pDriverConfig->blacklist_driver = false;
        pDriverConfig->start_driver = false;
        if (!pRocmConfig->install_rocm)
        {
            reset_rocm_version_menu(pRocmConfig);
        }

    }
}

void driver_menu_toggle_grey_items(MENU_DATA *pMenuData)
{
    DRIVER_MENU_CONFIG *pDriverConfig = &(pMenuData->pConfig)->driver_config;

    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_DRIVER_VER_INDEX, pDriverConfig->install_driver);
    driver_menu_opts_toggle_grey_items(pMenuData);
}

void driver_menu_update_state(MENU_DATA *pMenuData)
{
    // Check global state and update the driver menu

    UNUSED(pMenuData);
}

void do_driver_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;


    driver_menu_toggle_grey_items(pMenuData);

    // draw the Driver menu contents
    driver_menu_draw(pMenuData);

    // Driver menu loop
    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the Driver main menu
void process_driver_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;
    
    ITEM *pCurrentItem = current_item(pMenu);

    int index = item_index(pCurrentItem);

    DEBUG_UI_MSG(pMenuData, "Driver menu: item %d", index);

    bool isSelectable = item_opts(pCurrentItem) == O_SELECTABLE;

    if (!isSelectable) return;
    

    if (index == DRIVER_MENU_ITEM_INSTALL_DRIVER_INDEX)
    {
        pDriverConfig->install_driver = !pDriverConfig->install_driver;
        driver_menu_toggle_grey_items(pMenuData);
        menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_INSTALL_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->install_driver);
        if (!pDriverConfig->install_driver && is_specific_usecase_selected(pMenuData, "workstation"))
        {
            print_menu_warning_msg(pMenuData, "workstation is not supported when install driver is set to no");
        }
        else 
        {
            clear_menu_err_msg(pMenuData);
        }
        
        pConfig->configChg = true;
        driver_menu_update_state(pMenuData);
        pConfig->configChg = false;
    }
    else if (index == DRIVER_MENU_ITEM_DRIVER_VER_INDEX && pDriverConfig->install_driver)
    {
        {
            unpost_menu(pMenu);

            do_rocm_menu_version();

            // User may deselect rocm version, so driver opts must be disabled
            // before re-drawing the menu
            driver_menu_toggle_grey_items(pMenuData);

            driver_menu_draw(pMenuData);
        }
    }
    else if (index == DRIVER_MENU_ITEM_GRP_INDEX)
    {
        if (pDriverConfig->install_driver)
        {
            pDriverConfig->set_group = !pDriverConfig->set_group;
            menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_GRP_ROW, DRIVER_MENU_FORM_COL,pDriverConfig->set_group);
        }
    }
    else if (index == DRIVER_MENU_ITEM_BLACKLIST_INDEX)
    {
        // only allow blacklisting if installing the driver and not start driver
        if (pDriverConfig->install_driver && !pDriverConfig->start_driver)
        {
            pDriverConfig->blacklist_driver = !pDriverConfig->blacklist_driver;

            // if enabling blacklisting, disable start driver
            if (pDriverConfig->blacklist_driver)
            {
                pDriverConfig->start_driver = false;
                menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->start_driver);
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_INDEX, false);
            }
            else
            {
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_INDEX, true);
            }

            menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->blacklist_driver);
        }
    }
    else if (index == DRIVER_MENU_ITEM_START_DRIVER_INDEX)
    {
        // only allow start driver if installing the driver and not blacklisting
        if (pDriverConfig->install_driver && !pDriverConfig->blacklist_driver)
        {
            pDriverConfig->start_driver = !pDriverConfig->start_driver;

            // if enabling start driver, disable blacklisting
            if (pDriverConfig->start_driver)
            {
                pDriverConfig->blacklist_driver = false;
                menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, DRIVER_MENU_FORM_COL, pDriverConfig->blacklist_driver);
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, false);
            }
            else
            {
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, true);
            }

            menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->start_driver);
        }
    }

    driver_menu_draw(pMenuData);
}

void create_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &driverMenuHelpProps, &driverMenuHelpItems, NULL);

    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, driverMenuHelpOps, driverMenuHelpDesc); 
}
