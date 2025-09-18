/* ************************************************************************
 * Copyright (c) 2024-2025 Advanced Micro Devices, Inc. All rights reserved.
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

// Driver menu

// Driver/amdgpu Setup
char *driverMenuOps[] = {
    "Install amdgpu Driver",
    SKIPPABLE_MENU_ITEM,
    "    amdgpu Driver ROCm Version",
    SKIPPABLE_MENU_ITEM,
    "    Blacklist amdgpu driver",
    "    Start amdgpu driver on install",
    SKIPPABLE_MENU_ITEM,
    "<ADVANCED>",
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
    "Prevents amdgpu driver from loading on boot.",
    "Starts amdgpu driver immediately after installation.",
    " ",
    "Advanced Menu Options"
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

// Driver help menu
char *driverMenuHelpOps[] = {
    "amdgpu Install Driver",
    "amdgpu Driver ROCm   Version",
    "Set Video,Render     Group",
    "Blacklist amdgpu     Driver",
    "Start amdgpu         Driver on install",
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

// Advanced Driver Options Menu
char *advancedDriverMenuOps[] = {
    "Kernel version",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *advanedDriverMenuDesc[] = {
    "Set kernel version for driver installation on target system. If not set, host      kernel version is used.",
    " ",
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};

MENU_PROP advancedDriverMenuProps = {
    .pMenuTitle = "Advanced Driver Options",
    .pMenuControlMsg = "<DONE> to exit : Enter key to toggle selection",
    .numLines = ARRAY_SIZE(advancedDriverMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = DRIVER_MENU_ITEM_START_Y,
    .startx = DRIVER_MENU_ITEM_START_X,
    .numItems = ARRAY_SIZE(advancedDriverMenuOps)
};

ITEMLIST_PARAMS advancedDriverMenuItems = {
    .numItems           = (ARRAY_SIZE(advancedDriverMenuOps)),
    .pItemListTitle     = "Advanced Driver Install Settings:",
    .pItemListChoices   = advancedDriverMenuOps,
    .pItemListDesp      = advanedDriverMenuDesc
};

MENU_PROP advancedDriverHelpMenuProps = {
    .pMenuTitle = "Advanced Driver Options Help",
    .pMenuControlMsg = DEFAULT_SCROLLABLE_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = DRIVER_MENU_ITEM_START_Y,
    .startx = DRIVER_MENU_ITEM_START_X,
    .numItems = 0
};

ITEMLIST_PARAMS advancedDriverHelpMenuItems = {
    .numItems           = 0,
    .pItemListTitle     = "Advanced Driver Install Settings Description:",
    .pItemListChoices   = NULL,
    .pItemListDesp      = NULL
};

MENU_DATA menuAdvancedDriver = {0};
MENU_DATA menuAdvancedDriverHelpMenu = {0};

void process_driver_menu(MENU_DATA *pMenuData);

// sub-menus
void create_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);
void advanced_driver_menu_draw();

// advanced driver menu
void create_sub_menu_advanced_driver_menu_window(WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void create_advanced_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// advanced driver menu events
void process_advanced_driver_menu();
void process_advanced_driver_help_menu(MENU_DATA *pMenuData);
void process_advanced_driver_menu_kernel_form();
void do_advanced_driver_menu();


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

    // advanced sub-menu
    create_sub_menu_advanced_driver_menu_window(pMenuWindow, pConfig);

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = driver_menu_draw;

    // Set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_driver_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);     // space before <HELP>
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_ADVANCED_MENU_INDEX, false);    // <ADVANCED> menu item
    driver_menu_toggle_grey_items(pMenuData);

}

void destroy_driver_menu_window(MENU_DATA *pMenuData)
{
    // driver menu
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);

    // advanced driver menu
    destroy_menu(&menuAdvancedDriverHelpMenu);
    destroy_menu(&menuAdvancedDriver);

    memset(&menuAdvancedDriverHelpMenu, 0, sizeof(menuAdvancedDriverHelpMenu));
    memset(&menuAdvancedDriver, 0, sizeof(menuAdvancedDriver));
}

void driver_menu_draw(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;
  
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_INSTALL_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->install_driver);
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
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;

    // Only enable the 3 driver opts if install_driver is true and user has selected
    // a rocm version
    bool enable = false;

    if (pDriverConfig->install_driver)
    {
        if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC) 
        {
            enable = pRocmConfig->rocm_version_selected;
        }
    }
    else if (!enable)
    {
        // reset to defaults
        pDriverConfig->blacklist_driver = false;
        pDriverConfig->start_driver = false;
        clear_str(pDriverConfig->user_selected_kernel);

        if (!pRocmConfig->install_rocm)
        {
            reset_rocm_version_menu(pRocmConfig);
        }
    }

    // Ensures sub options are properly set as selectable/unselectable based
    // on user settings.
    if (pDriverConfig->blacklist_driver || pDriverConfig->start_driver) 
    {
        if (pDriverConfig->blacklist_driver)
        {
            menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_INDEX, false);
        }
        else if (pDriverConfig->start_driver) 
        {
            menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, false);
        }
    }
    else
    {   
        // enable/disable all driver option fields
        menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, enable);
        menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_INDEX, enable);
        menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_ADVANCED_MENU_INDEX, enable);
    }
}

void driver_menu_toggle_grey_items(MENU_DATA *pMenuData)
{
    DRIVER_MENU_CONFIG *pDriverConfig = &(pMenuData->pConfig)->driver_config;
    bool enable = pDriverConfig->install_driver;
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_DRIVER_VER_INDEX, enable);
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

    wclear(pMenuData->pMenuWindow);

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
            print_menu_warning_msg(pMenuData, WARN_ERR_START_Y, WARN_ERR_START_X, "workstation is not supported when install driver is set to no");
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
                menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->blacklist_driver);
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, false);
            }
            else
            {
                menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_INDEX, true);
            }

            menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->start_driver);
        }
    }
    else if (index == DRIVER_MENU_ITEM_ADVANCED_MENU_INDEX)
    {
        unpost_menu(pMenu);
        do_advanced_driver_menu();
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

// ---------------------------ADVANCED OPTIONS FUNCTIONS START--------------------------

void print_kernel_header_check(MENU_DATA *pMenuData)
{
    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    advanced_driver_menu_draw(pMenuData);
    char kernelHeader[LARGE_CHAR_SIZE];
        
    int y = WARN_ERR_START_Y - 6;
    clear_text(pMenuData, y, WARN_ERR_START_X, MENU_SEL_START_Y);
    clear_menu_err_msg(pMenuData);
    
    if (strlen(pDriverConfig->user_selected_kernel) > (size_t)0)
    {
        mvwprintw(pMenuData->pMenuWindow, y, WARN_ERR_START_X, "Checking...");
        wrefresh(pMenuData->pMenuWindow);

        if (is_ubuntu_kernel_header_valid(pDriverConfig->user_selected_kernel))
        {
            pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_VALID;
        }
        else
        {
            pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_INVALID;
        }
    
        if (pDriverConfig->user_selected_kernel_validity_status == eKERNEL_STATUS_VALID)
        {
            sprintf(kernelHeader, "%s is available.", pDriverConfig->user_selected_kernel);
            print_path_validation_msg_success(pMenuData, kernelHeader);
        }
        else
        {
            sprintf(kernelHeader, "%s is not available.", pDriverConfig->user_selected_kernel);
            print_path_validation_msg_failure(pMenuData, kernelHeader);
        }
    }

    // Deletes the Checking... text
    clear_text(pMenuData, y, WARN_ERR_START_X, y+1);
}

void process_kernel_version_menu_item()
{
    if (!is_ubuntu(&menuAdvancedDriver))
    {
        print_menu_msg(&menuAdvancedDriver, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, YELLOW, "Ubuntu only");
    }
}

void create_sub_menu_advanced_driver_menu_window(WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{   
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;
    create_menu(pMenuData, pMenuWindow, &advancedDriverMenuProps, &advancedDriverMenuItems, pConfig);
    
    // create verbose help menu
    create_advanced_driver_help_menu_window(&menuAdvancedDriverHelpMenu, pMenuData->pMenuWindow);
    
    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = advanced_driver_menu_draw;

    ITEM **items = menu_items(pMenuData->pMenu);

     // set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_advanced_driver_menu);

    // function that will draw scrollable help menu
    set_item_userptr(items[pMenuData->itemList[0].helpItemIndex], process_advanced_driver_help_menu);

    // create a form for kernel version for user to enter
    create_form(pMenuData, pMenuWindow, DRIVER_MENU_NUM_FORM_FIELDS, DRIVER_MENU_FORM_FIELD_WIDTH, DRIVER_MENU_FORM_FIELD_HEIGHT,
        ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL);

    // run function that checks if user selected kernel is valid or not
    set_form_userptr(pMenuData->pFormList.pForm, process_advanced_driver_menu_kernel_form);

    pMenuData->clearErrMsgAfterUpOrDownKeyPress = true;
    
    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));

    if (!is_ubuntu(pMenuData)) {
        menu_set_item_select(pMenuData, ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX, false); // rocm usecases menu
    }

    // Use this to determine to ensure we only print 'Ubuntu only' warning message
    // the first time we draw the advanced menu
    pMenuData->isFirstTimeOpeningMenu = true;

    set_item_userptr(items[ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX], process_kernel_version_menu_item);

    strcpy(pMenuData->pFormList.formControlMsg, DEFAULT_FORM_CONTROL_MSG);
    
    pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_CHECKING;
    
    set_field_buffer(pMenuData->pFormList.field[0], 0, pConfig->kernelVersion);
}

void create_advanced_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &advancedDriverHelpMenuProps, &advancedDriverHelpMenuItems, NULL);

    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);
}

void advanced_driver_menu_draw()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;

    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    if (is_user_selected_kernel())
    {
        switch(pDriverConfig->user_selected_kernel_validity_status)
        {
            case eKERNEL_STATUS_CHECKING:
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                break;
            case eKERNEL_STATUS_VALID:
                wattron(pMenuData->pMenuWindow, COLOR_PAIR(4));
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                wattroff(pMenuData->pMenuWindow, COLOR_PAIR(4));
                break;
            case eKERNEL_STATUS_INVALID:
                wattron(pMenuData->pMenuWindow, COLOR_PAIR(1));
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                wattroff(pMenuData->pMenuWindow, COLOR_PAIR(1));
                break;
            default:
                break;
        }
    }
    
    menu_draw(pMenuData);

    if (pMenuData->isFirstTimeOpeningMenu)
    {
        if (!is_ubuntu(pMenuData))
        {
            print_menu_msg(pMenuData, DEBUG_ERR_START_Y, WARN_ERR_START_X, YELLOW, "Ubuntu only");
        }
        pMenuData->isFirstTimeOpeningMenu = false;

    }
}

// Process "ENTER" key event when user selects specific kernel version
void process_advanced_driver_menu_kernel_form()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    MENU *pMenu = pMenuData->pMenu;
    FORM *pForm = pMenuData->pFormList.pForm;

    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    post_form(pForm);

    post_menu(pMenu);

    // When user presses enter, you have to re-draw menu, otherwise part of it
    // gets cut off.
    advanced_driver_menu_draw(pMenuData);

    print_form_control_msg(pMenuData);

    // Switch to form control loop for entering data into given form field
    form_loop(pMenuData, false);

    unpost_form(pForm);
    unpost_menu(pMenu);

    // store the ROCm build number on exit
    strcpy(pDriverConfig->user_selected_kernel, field_buffer(pForm->field[0], 0));
    remove_end_spaces(pDriverConfig->user_selected_kernel, DRIVER_MENU_FORM_FIELD_WIDTH);

    char *newline = strchr(pDriverConfig->user_selected_kernel, '\n');
    if (newline) *newline = '\0';

    if (is_field_empty(pDriverConfig->user_selected_kernel))
    {
        clear_str(pDriverConfig->user_selected_kernel);
    }

    pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_CHECKING;

    print_kernel_header_check(pMenuData);
}

void process_advanced_driver_help_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    unpost_menu(pMenu);

    // draw help menu window and borders
    wclear(menuAdvancedDriverHelpMenu.pMenuWindow);
    menu_draw(&menuAdvancedDriverHelpMenu);

    int is_error_reading_verbose_help_file = display_help_scroll_window(&menuAdvancedDriverHelpMenu, "./rocm_menus/advanced_driver_help.txt");
    if (is_error_reading_verbose_help_file == -1)
    {
        wgetch(pMenuData->pMenuWindow);
    }

    // Clear window before redrawing extras menu.
    wclear(pMenuData->pMenuWindow);
    
    // Show the extras menu right after user exits from the help menu
    advanced_driver_menu_draw(pMenuData);
}

void do_advanced_driver_menu()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    MENU *pMenu = pMenuData->pMenu;

    wclear(pMenuData->pMenuWindow);

    advanced_driver_menu_draw();

    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the Advanced Driver sub-menu
void process_advanced_driver_menu()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    MENU *pMenu = pMenuData->pMenu;

    ITEM *pCurrentItem = current_item(pMenu);

    int index = item_index(pCurrentItem);

    DEBUG_UI_MSG(pMenuData, "Driver menu: item %d", index);

    bool isSelectable = item_opts(pCurrentItem) == O_SELECTABLE;

    if (!isSelectable) return;

    if (index == ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX)
    {
        FORM *pForm = pMenuData->pFormList.pForm;
        if (pForm)
        {
            // switch to the form for kernel version
            unpost_menu(pMenu);

            void (*ptrFormFnc)(MENU_DATA*);

            ptrFormFnc = form_userptr(pForm);
            if (NULL != ptrFormFnc)
            {
                ptrFormFnc((MENU_DATA*)pMenuData);
            }
            else
            {
                DEBUG_UI_MSG(pMenuData, "No user ptr for form");
            }
        }
    }

    advanced_driver_menu_draw(pMenuData);
}

bool is_user_selected_kernel()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;

    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    return strlen(pDriverConfig->user_selected_kernel) > (size_t)0;
}

// ---------------------------ADVANCED OPTIONS FUNCTIONS END--------------------------