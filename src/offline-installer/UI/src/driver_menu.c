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


/****  Driver menu ********************************************************/
char *driverMenuOps[] = {
    "Install amdgpu Driver",
    SKIPPABLE_MENU_ITEM,
    "    amdgpu Driver Version",
    SKIPPABLE_MENU_ITEM,
    "    amdgpu Driver Blacklist",
    "    amdgpu Driver Start on install",
    SKIPPABLE_MENU_ITEM,
    "<ADVANCED>",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *driverMenuDesc[] = {
    "Enable/Disable amdgpu Driver install.",
    " ",
    "Set Version of amdgpu Driver for installation.",
    " ",
    "Prevents amdgpu Driver from loading on boot.",
    "Starts amdgpu Driver immediately after installation.",
    " ",
    "Advanced Menu Options",
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

/****  Driver help menu ***************************************************/
char *driverMenuHelpOps[] = {
    "amdgpu Install Driver",
    "amdgpu Driver        Version",
    "Set Video,Render     Group",
    "amdgpu Driver        Blacklist",
    "amdgpu Driver        Start on install",
    "",
    (char*)NULL
};

char *driverMenuHelpDesc[] = {
    "Include the amdgpu Driver in the creation of           offline installer.",
    "amdgpu Driver version for Driver source                packages.",
    "If enabled, adds current user to the video group to    access GPU resources.",
    "Prevents the amdgpu Driver from automatically starting on boot after installing it (useful for debug).",
    "Starts the amdgpu Driver after it is installed. This   option is typically used for OS installs that do not   have an enabled upstream driver already included.",
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
char **advancedDriverMenuOps = NULL;
char **advancedDriverMenuDesc = NULL;

MENU_PROP advancedDriverMenuProps = {0};
ITEMLIST_PARAMS advancedDriverMenuItems = {0};

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

/****  Driver Version Options Menu *****************************************/
MENU_PROP driverMenuVersionProps = {0};
ITEMLIST_PARAMS driverMenuVersionItems = {0};
char driverMenuVersionOps[MAX_MENU_ITEMS][MAX_MENU_ITEM_NAME] = {0};
char driverMenuVersionDesc[MAX_MENU_ITEMS][MAX_MENU_ITEM_NAME] = {0};
MENU_DATA menuDriverVersion = {0};

void process_driver_menu(MENU_DATA *pMenuData);

// help menu
void create_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// driver version menu
void create_driver_menu_version_window(WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_driver_menu_version_window();
void do_driver_menu_version();
void read_driver_version_file();

// advanced driver menu
void create_sub_menu_advanced_driver_menu_window(MENU_DATA *pDriverMenu, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void create_advanced_driver_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);
void advanced_driver_menu_draw();

// advanced driver menu events
void process_advanced_driver_menu();
void process_advanced_driver_help_menu(MENU_DATA *pMenuData);
void process_advanced_driver_menu_kernel_form();
void do_advanced_driver_menu();

// advanced driver menu bool functions
bool is_advanced_kernel_picker_available(MENU_DATA *pMenuData);
bool is_kernel_header_valid(MENU_DATA *pMenuData, char*kernel_version, bool is_rhck);


// menu draw/config
void driver_menu_toggle_grey_items(MENU_DATA *pMenuData);
void driver_menu_draw(MENU_DATA *pMenuData);
void driver_menu_submenu_draw(MENU_DATA *pMenuData);


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
    
    // Init the rocm version index for the driver versions menu and read the driver version file
    pConfig->driver_config.driver_rocm_index = -1;
    read_driver_version_file();

    // driver version sub-menu
    create_driver_menu_version_window(pMenuData->pMenuWindow, pConfig);

    // advanced sub-menu
    create_sub_menu_advanced_driver_menu_window(pMenuData, pMenuWindow, pConfig);

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = driver_menu_draw;

    // Set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_driver_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, BLUE);
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);     // space before <HELP>
    menu_set_item_select(pMenuData, DRIVER_MENU_ITEM_ADVANCED_MENU_INDEX, false);    // <ADVANCED> menu item
    driver_menu_toggle_grey_items(pMenuData);

}

void destroy_driver_menu_window(MENU_DATA *pMenuData)
{
    destroy_driver_menu_version_window();

    // driver menu
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);

    // advanced driver menu
    destroy_menu(&menuAdvancedDriverHelpMenu);
    destroy_menu(&menuAdvancedDriver);

    memset(&menuAdvancedDriverHelpMenu, 0, sizeof(menuAdvancedDriverHelpMenu));
    memset(&menuAdvancedDriver, 0, sizeof(menuAdvancedDriver));

    if (advancedDriverMenuOps) free(advancedDriverMenuOps);
    if (advancedDriverMenuDesc) free(advancedDriverMenuDesc);
}

void driver_menu_draw(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;

    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_INSTALL_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->install_driver);
    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_BLACKLIST_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->blacklist_driver);
    menu_info_draw_bool(pMenuData, DRIVER_MENU_ITEM_START_DRIVER_ROW, DRIVER_MENU_FORM_COL, pDriverConfig->start_driver);

    if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC)
    {
        if (pDriverConfig->install_driver)
        {
            mvwprintw(pMenuWindow, DRIVER_MENU_ITEM_DRIVER_VER_ROW, DRIVER_MENU_FORM_COL, "%s %s", pDriverConfig->driver_version, pDriverConfig->driver_rocm_version);
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
    
    bool enable = false;

    if (pDriverConfig->install_driver)
    {
        if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC) 
        {
            enable = true;

            // if enabling driver and rocm install enabled, then init the driver version to the rocm version (if set)
            if (!is_rocm_version_empty() && pRocmConfig->install_rocm)
            {
                set_driver_version_menu(get_rocm_version_index_by_name());
            }
        }
    }
    else if (!enable)
    {
        // reset to defaults
        pDriverConfig->blacklist_driver = false;
        pDriverConfig->start_driver = false;
        clear_str(pDriverConfig->user_selected_kernel);

        if (pRocmConfig->install_rocm)
        {
            // if toggling driver disable, reset driver if installing rocm
            reset_driver_version_menu();
        }
        else
        {
            // if toggling driver disable, reset driver and rocm version if not installing rocm
            reset_driver_version_menu();
            reset_rocm_version_menu(pRocmConfig);
        }
    }

    // Ensures sub options are properly set as selectable/unselectable based on user settings.
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
            // switch to the driver version sub-menu
            unpost_menu(pMenu);
            do_driver_menu_version();
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

    // Create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, driverMenuHelpOps, driverMenuHelpDesc); 
}

// ---------------------------ADVANCED OPTIONS FUNCTIONS START--------------------------

void print_kernel_header_check(MENU_DATA *pMenuData, bool is_rhck)
{
    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    advanced_driver_menu_draw(pMenuData);
    char kernelHeader[LARGE_CHAR_SIZE];
        
    int y = WARN_ERR_START_Y - 6;
    clear_text(pMenuData, y, WARN_ERR_START_X, MENU_SEL_START_Y);
    clear_menu_err_msg(pMenuData);

    size_t kernel_string_length;

    if (is_rhck)
    {
        kernel_string_length = strlen(pDriverConfig->user_selected_rhck_kernel);
    }
    else
    {
        kernel_string_length = strlen(pDriverConfig->user_selected_kernel);
    }
    
    if (kernel_string_length > (size_t)0)
    {
        mvwprintw(pMenuData->pMenuWindow, y, WARN_ERR_START_X, "Checking...");
        wrefresh(pMenuData->pMenuWindow);
        
        if (is_rhck)
        {
            if (is_kernel_header_valid(pMenuData, pDriverConfig->user_selected_rhck_kernel, is_rhck))
            {
                pDriverConfig->user_selected_rhck_kernel_validity_status = eKERNEL_STATUS_VALID;
                sprintf(kernelHeader, "%s is available.", pDriverConfig->user_selected_rhck_kernel);
                print_path_validation_msg_success(pMenuData, kernelHeader);
            }
            else
            {
                pDriverConfig->user_selected_rhck_kernel_validity_status = eKERNEL_STATUS_INVALID;
                sprintf(kernelHeader, "%s is not available.", pDriverConfig->user_selected_rhck_kernel);
                print_path_validation_msg_failure(pMenuData, kernelHeader);
            }
        }
        else
        {
            if (is_kernel_header_valid(pMenuData, pDriverConfig->user_selected_kernel, is_rhck))
            {
                pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_VALID;
                 sprintf(kernelHeader, "%s is available.", pDriverConfig->user_selected_kernel);
                print_path_validation_msg_success(pMenuData, kernelHeader);
            }
            else
            {
                pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_INVALID;
                sprintf(kernelHeader, "%s is not available.", pDriverConfig->user_selected_kernel);
                print_path_validation_msg_failure(pMenuData, kernelHeader);
            }
        }
    }

    // Deletes the Checking... text
    clear_text(pMenuData, y, WARN_ERR_START_X, y+1);
}

void process_kernel_version_menu_item()
{
    if (!is_advanced_kernel_picker_available(&menuAdvancedDriver))
    {
        print_menu_msg(&menuAdvancedDriver, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, YELLOW, "Ubuntu, Debian, RHEL and SLES only");
    }
}

void create_sub_menu_advanced_driver_menu_window(MENU_DATA *pDriverMenu, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{   
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;

    advancedDriverMenuOps = calloc(ADVANCED_DRIVER_MENU_MAX_ITEMS, sizeof(char*));
    advancedDriverMenuDesc = calloc(ADVANCED_DRIVER_MENU_MAX_ITEMS, sizeof(char*));

    int item_count = 0;

    if (is_ol(pDriverMenu))
    {
        advancedDriverMenuOps[0] = "UEK version";
        advancedDriverMenuOps[1] = "RHCK version";
        advancedDriverMenuOps[2] = SKIPPABLE_MENU_ITEM;
        advancedDriverMenuOps[3] = "<HELP>";
        advancedDriverMenuOps[4] = "<DONE>";

        advancedDriverMenuDesc[0] = "Set UEK kernel version for driver installation on target system. If not set,       the host kernel version is used.";
        advancedDriverMenuDesc[1] = "Set RHCK kernel version for driver installation on target system. Leave this       field empty if there is no RHCK kernel on the target system.";

        advancedDriverMenuDesc[2] = SKIPPABLE_MENU_ITEM;
        advancedDriverMenuDesc[3] = DEFAULT_VERBOSE_HELP_WINDOW_MSG;
        advancedDriverMenuDesc[4] = "Exit to Main Menu";

        item_count = 5;
    } 
    else 
    {
            advancedDriverMenuOps[0] = "Kernel version";
            advancedDriverMenuOps[1] = SKIPPABLE_MENU_ITEM;
            advancedDriverMenuOps[2] = "<HELP>";
            advancedDriverMenuOps[3] = "<DONE>";

            advancedDriverMenuDesc[0] = "Set kernel version for driver installation on target system. If not set, the       host kernel version is used.";
            advancedDriverMenuDesc[1] = SKIPPABLE_MENU_ITEM;
            advancedDriverMenuDesc[2] = DEFAULT_VERBOSE_HELP_WINDOW_MSG;
            advancedDriverMenuDesc[3] = "Exit to Main Menu";

            item_count = 4;
    }

    advancedDriverMenuProps = (MENU_PROP) {
        .pMenuTitle = "Advanced Driver Options",
        .pMenuControlMsg = "<DONE> to exit : Enter key to toggle selection",
        .numLines = item_count,
        .numCols = MAX_MENU_ITEM_COLS,
        .starty = DRIVER_MENU_ITEM_START_Y,
        .startx = DRIVER_MENU_ITEM_START_X,
        .numItems = item_count + 1
        };

    advancedDriverMenuItems = (ITEMLIST_PARAMS) {
        .numItems           = item_count + 1,
        .pItemListTitle     = "Advanced Driver Install Settings:",
        .pItemListChoices   = advancedDriverMenuOps,
        .pItemListDesp      = advancedDriverMenuDesc,
    };

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

    pMenuData->clearErrMsgAfterUpOrDownKeyPress = true;
    
    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, BLUE);

    if (!is_advanced_kernel_picker_available(pMenuData))
    {
        menu_set_item_select(pMenuData, ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX, false); // Kernel/UEK Version field
    }

    if (is_ol(pMenuData))
    {
        menu_set_item_select(pMenuData, ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX, true); // RHCK version field
    }
    
    // Use this to determine to ensure we only print 'Ubuntu only' warning message
    // the first time we draw the advanced menu
    pMenuData->isFirstTimeOpeningMenu = true;

    set_item_userptr(items[ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX], process_kernel_version_menu_item);

    strcpy(pMenuData->pFormList.formControlMsg, DEFAULT_FORM_CONTROL_MSG);
    
    pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_CHECKING;

    pDriverConfig->user_selected_rhck_kernel_validity_status = eKERNEL_STATUS_CHECKING;

    // create a form for kernel version for user to enter
    create_form(pMenuData, pMenuWindow, DRIVER_MENU_NUM_FORM_FIELDS, DRIVER_MENU_FORM_FIELD_WIDTH, DRIVER_MENU_FORM_FIELD_HEIGHT,
        ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL);

    // run function that checks if user selected kernel is valid or not
    set_form_userptr(pMenuData->pFormList.pForm, process_advanced_driver_menu_kernel_form);
    
    set_field_buffer(pMenuData->pFormList.field[ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX], 0, pConfig->kernelVersion);
    if (is_ol(pMenuData)) {
        // Fill RHCK Kernel field with RHCK kernel installed on OL system (if any)
        set_field_buffer(pMenuData->pFormList.field[ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX], 0, pConfig->rhckKernelVersion);
    }
    
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
    OFFLINE_INSTALL_CONFIG *offlineConfig = pMenuData->pConfig;

    if (is_user_selected_kernel())
    {
        switch(pDriverConfig->user_selected_kernel_validity_status)
        {
            case eKERNEL_STATUS_CHECKING:
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                break;
            case eKERNEL_STATUS_VALID:
                wattron(pMenuData->pMenuWindow, GREEN);
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                wattroff(pMenuData->pMenuWindow, GREEN);
                break;
            case eKERNEL_STATUS_INVALID:
                wattron(pMenuData->pMenuWindow, RED);
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_kernel);
                wattroff(pMenuData->pMenuWindow, RED);
                break;
            default:
                break;
        }
    }
    else
    {
        mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW, ADVANCED_DRIVER_MENU_FORM_COL, "%s", offlineConfig->kernelVersion);
    }

    if (is_user_selected_rhck_kernel())
    {
        switch(pDriverConfig->user_selected_rhck_kernel_validity_status)
        {
            case eKERNEL_STATUS_CHECKING:
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW+1, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_rhck_kernel);
                break;
            case eKERNEL_STATUS_VALID:
                wattron(pMenuData->pMenuWindow, GREEN);
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW+1, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_rhck_kernel);
                wattroff(pMenuData->pMenuWindow, GREEN);
                break;
            case eKERNEL_STATUS_INVALID:
                wattron(pMenuData->pMenuWindow, RED);
                mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW+1, ADVANCED_DRIVER_MENU_FORM_COL, "%s", pDriverConfig->user_selected_rhck_kernel);
                wattroff(pMenuData->pMenuWindow, RED);
                break;
            default:
                break;
        }
    }
    else
    {
        mvwprintw(pMenuData->pMenuWindow, ADVANCED_DRIVER_MENU_FORM_ROW+1, ADVANCED_DRIVER_MENU_FORM_COL, "%s", offlineConfig->rhckKernelVersion);
    }

    menu_draw(pMenuData);

    if (pMenuData->isFirstTimeOpeningMenu)
    {
        if (!is_advanced_kernel_picker_available(pMenuData))
        {
            print_menu_msg(pMenuData, DEBUG_ERR_START_Y, WARN_ERR_START_X, YELLOW, "Ubuntu, Debian, SLES, RHEL and OL supported.");
        }
        pMenuData->isFirstTimeOpeningMenu = false;
    }
}

// Process "ENTER" key event when user selects specific kernel version
void process_advanced_driver_menu_kernel_form(int fieldNum)
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;
    MENU *pMenu = pMenuData->pMenu;
    FORM *pForm = pMenuData->pFormList.pForm;

    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;
    // OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;

    bool is_rhck = false;

    // show only the required field and set it to current
    set_current_field(pForm, pMenuData->pFormList.field[fieldNum]);
    
    post_form(pForm);
    post_menu(pMenu);

    // When user presses enter, you have to re-draw menu, otherwise part of it gets cut off.
    advanced_driver_menu_draw(pMenuData);
    print_form_control_msg(pMenuData);

    // Switch to form control loop for entering data into given form field
    form_loop(pMenuData, false);

    unpost_form(pForm);
    unpost_menu(pMenu);

    if (fieldNum == ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX)
    {
        // store the user selected kernel on exit
        strcpy(pDriverConfig->user_selected_kernel, field_buffer(pForm->field[ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX], 0));
        remove_end_spaces(pDriverConfig->user_selected_kernel, DRIVER_MENU_FORM_FIELD_WIDTH);

        char *newline = strchr(pDriverConfig->user_selected_kernel, '\n');
        if (newline) *newline = '\0';

        if (is_field_empty(pDriverConfig->user_selected_kernel))
        {
            clear_str(pDriverConfig->user_selected_kernel);
        }

        pDriverConfig->user_selected_kernel_validity_status = eKERNEL_STATUS_CHECKING;

        print_kernel_header_check(pMenuData, is_rhck);
    }
    else if (fieldNum == ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX)
    {   
        is_rhck = true;

        // store the user selected kernel on exit
        strcpy(pDriverConfig->user_selected_rhck_kernel, field_buffer(pForm->field[ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX], 0));
        remove_end_spaces(pDriverConfig->user_selected_rhck_kernel, DRIVER_MENU_FORM_FIELD_WIDTH);

        char *newline = strchr(pDriverConfig->user_selected_rhck_kernel, '\n');
        if (newline) *newline = '\0';

        if (is_field_empty(pDriverConfig->user_selected_rhck_kernel))
        {
            clear_str(pDriverConfig->user_selected_rhck_kernel);
        }

        pDriverConfig->user_selected_rhck_kernel_validity_status = eKERNEL_STATUS_CHECKING;

        print_kernel_header_check(pMenuData, is_rhck);
    }   
}

void process_advanced_driver_help_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    unpost_menu(pMenu);

    // draw help menu window and borders
    wclear(menuAdvancedDriverHelpMenu.pMenuWindow);
    menu_draw(&menuAdvancedDriverHelpMenu);

    int is_error_reading_verbose_help_file;

    if (is_ol(pMenuData))
    {
        is_error_reading_verbose_help_file = display_help_scroll_window(&menuAdvancedDriverHelpMenu, "./rocm_menus/advanced_driver_help_ol.txt");
    }
    else
    {
        is_error_reading_verbose_help_file = display_help_scroll_window(&menuAdvancedDriverHelpMenu, "./rocm_menus/advanced_driver_help.txt");
    }
    
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

    if (index == ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX || index == ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX)
    {
        FORM *pForm = pMenuData->pFormList.pForm;
        if (pForm)
        {
            // switch to the form for kernel version
            unpost_menu(pMenu);

            void (*ptrFormFnc)(int);

            ptrFormFnc = form_userptr(pForm);
            if (NULL != ptrFormFnc)
            {
                ptrFormFnc(index);
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

bool is_user_selected_rhck_kernel()
{
    MENU_DATA *pMenuData = &menuAdvancedDriver;

    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    return strlen(pDriverConfig->user_selected_rhck_kernel) > (size_t)0;
}

bool is_advanced_kernel_picker_available(MENU_DATA *pMenuData)
{
    return (is_ubuntu(pMenuData) || is_debian(pMenuData) || is_rhel(pMenuData) || is_sles(pMenuData) || is_ol(pMenuData));
}

bool is_kernel_header_valid(MENU_DATA *pMenuData, char *kernel_version, bool is_rhck)
{
    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;
    return ((is_ubuntu(pMenuData) && is_ubuntu_kernel_header_valid(pDriverConfig->user_selected_kernel)) || 
            (is_debian(pMenuData) && is_debian_kernel_header_valid(pDriverConfig->user_selected_kernel)) || 
            (is_rhel(pMenuData) && is_rhel_kernel_header_valid(pDriverConfig->user_selected_kernel))    ||
            (is_sles(pMenuData) && is_sles_kernel_header_valid(pDriverConfig->user_selected_kernel))    || 
            (is_ol(pMenuData) && is_ol_kernel_header_valid(kernel_version, is_rhck)));
}

/**************** DRIVER VERSION MENU **************************************************************************/

void driver_menu_submenu_draw(MENU_DATA *pMenuData)
{
    wclear(pMenuData->pMenuWindow);
    menu_draw(pMenuData);
}

void read_driver_version_file()
{
    int item_count, item_desc_count;
    
    char *itemFile = "./driver_menus/driver_versions";
    char *itemDescFile = "./driver_menus/driver_versions_desc";

    // Read the item file
    item_count = read_file_for_items(itemFile, driverMenuVersionOps);
    if (item_count == -1) 
    {
        exit_error("Failed to read driver version file.");
    }

    // make sure the driver items match the rocm versions available
    if (ROCM_VERS_COLS != item_count)
    {
        exit_error("ROCM_VERS_COLS != item_count");
    }

    // Read the item description file
    item_desc_count = read_file_for_items(itemDescFile, driverMenuVersionDesc);
    if (item_desc_count == -1) 
    {
        exit_error("Failed to read driver version desc file.");
    }

    // make sure the driver items match the rocm versions available
    if (ROCM_VERS_COLS != item_desc_count)
    {
        exit_error("ROCM_VERS_COLS != item_desc_count");
    }
}

void create_driver_menu_version_window(WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    char *driverMenuVersionOpsPtrs[MAX_MENU_ITEMS] = {0};
    char *driverMenuVersionDescPtrs[MAX_MENU_ITEMS] = {0};

    DRIVER_MENU_CONFIG *pDriverConfig = &pConfig->driver_config;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;

    int driver_rocm_index = pDriverConfig->driver_rocm_index;
    bool createMenu = false;
    
    // Check if the driver version needs creation
    if (!menuDriverVersion.pMenu)
    {
        createMenu = true;
    }

    int *rocmVersionRow = get_rocm_version_matrix(pRocmConfig->rocm_distro_index);

    // setup and create the driver version menu
    if (createMenu) 
    {
        int rocm_ver_indx = 0;   // enabled rocm version menu item index
        int driver_ver_indx = 0; // index in "full" driver menu list (read from file)

        // populate the driver version items list for each col (rocm version) enabled
        for (int i = 0; i < ROCM_VERS_COLS; i++)
        {
            if (rocmVersionRow[i] == 1)
            {
                driverMenuVersionOpsPtrs[rocm_ver_indx] = driverMenuVersionOps[i];
                driverMenuVersionDescPtrs[rocm_ver_indx] = driverMenuVersionDesc[i];
                rocm_ver_indx++;
            }
            driver_ver_indx++;
        }

        // add a menu item for "space"
        strcpy(driverMenuVersionOps[driver_ver_indx], " ");
        strcpy(driverMenuVersionDesc[driver_ver_indx], " ");
        driverMenuVersionOpsPtrs[rocm_ver_indx] = driverMenuVersionOps[driver_ver_indx];
        driverMenuVersionDescPtrs[rocm_ver_indx] = driverMenuVersionDesc[driver_ver_indx];
        driver_ver_indx++;
        rocm_ver_indx++;

        // add a menu items for "DONE"
        strcpy(driverMenuVersionOps[driver_ver_indx], "<DONE>");
        strcpy(driverMenuVersionDesc[driver_ver_indx], " Exit to Driver Options Menu");
        driverMenuVersionOpsPtrs[rocm_ver_indx] = driverMenuVersionOps[driver_ver_indx];
        driverMenuVersionDescPtrs[rocm_ver_indx] = driverMenuVersionDesc[driver_ver_indx];
        driver_ver_indx++;
        rocm_ver_indx++;

        int numItems = rocm_ver_indx + 1;   // number of enable rocm versions for driver + NULL

        driverMenuVersionProps = (MENU_PROP) {
            .pMenuTitle = "Driver Version Configuration",
            .pMenuControlMsg = "<DONE> to exit : Space/Enter to select/unselect component. Up/Down to scroll.",
            .numLines = numItems - 1,
            .numCols = MAX_MENU_ITEM_COLS,
            .starty = ROCM_MENU_ITEM_START_Y,
            .startx = 4,
            .numItems = numItems
        };

        driverMenuVersionItems = (ITEMLIST_PARAMS) {
            .numItems           = numItems,
            .pItemListTitle     = "Select driver you wish to package in the offline installer:",
            .pItemListChoices   = driverMenuVersionOpsPtrs,
            .pItemListDesp      = driverMenuVersionDescPtrs
        };

        // Create the driver version Sub-Menu
        create_menu(&menuDriverVersion, pMenuWindow, &driverMenuVersionProps, &driverMenuVersionItems, pConfig);
        menuDriverVersion.enableMultiSelection = false;
        menuDriverVersion.isMenuItemsSelectable = true;

        // Set pointer to draw menu function when window is resized
        menuDriverVersion.drawMenuFunc = driver_menu_submenu_draw;

        // Make the menu multi valued
        menu_opts_off(menuDriverVersion.pMenu, O_ONEVALUE);

        // set items to non-selectable for the menu
        set_menu_fore(menuDriverVersion.pMenu, COLOR_PAIR(8));

        // Disable items from being selectable
        set_menu_grey(menuDriverVersion.pMenu, COLOR_PAIR(5));
    }

    // Check if the new driver version needs a pre-selected version
    if (pRocmConfig->install_rocm)
    {
        // if rocm install is enabled and a version set, then set driver version in the new menu
        if (!is_rocm_version_empty())
        {
            driver_rocm_index = get_driver_version_index_by_name();
            set_menu_item_select_to_index(&menuDriverVersion, driver_rocm_index);
            pDriverConfig->driver_rocm_index = driver_rocm_index;
        }
    }
    else
    {
        // if rocm is not being installed, but the driver version is set, the set the driver version in the new menu
        if (!is_driver_version_empty())
        {
            driver_rocm_index = get_driver_version_index_by_name();
            set_menu_item_select_to_index(&menuDriverVersion, driver_rocm_index);
            pDriverConfig->driver_rocm_index = driver_rocm_index;
        }
    }
}

void destroy_driver_menu_version_window()
{
    destroy_menu(&menuDriverVersion);

    memset(&menuDriverVersion, 0, sizeof(menuDriverVersion));
}

// Parses ROCm version from a string in format "name - ROCm x.y amdgpu release" or "name - ROCm x.y.z amdgpu release"
bool parse_driver_rocm_version(const char *input_str, char *output_str, size_t max_len)
{
    if (!input_str || !output_str || max_len <= 0)
    {
        return false;
    }
    
    strcpy(output_str, " : ");
    
    // Find "ROCm "
    const char *rocm_start = strstr(input_str, "ROCm ");
    if (!rocm_start)
    {
        return false;
    }
    
    // Find " amdgpu" after ROCm to determine the end
    const char *rocm_end = strstr(rocm_start, " amdgpu");
    if (!rocm_end)
    {
        return false;
    }
    
    // Calculate the length of the ROCm version string
    int rocm_len = rocm_end - rocm_start;
    
    // Check if it fits in the output buffer (including existing " : " and null terminator)
    if ((strlen(" : ") + rocm_len) >= max_len)
    {
        return false;
    }
    
    // Append the ROCm version string to " : "
    strncat(output_str, rocm_start, rocm_len);
    
    return true;
}

void set_driver_version_name(int index)
{
    DRIVER_MENU_CONFIG *pDriverConfig;
    ITEM **items;

    char rocm_version[DEFAULT_CHAR_SIZE];

    if ( NULL == menuDriverVersion.pMenu )
    {
        return;
    }

    pDriverConfig = &menuDriverVersion.pConfig->driver_config;
    items = menuDriverVersion.itemList[0].items;

    // update the driver version and driver rocm version names
    strcpy(pDriverConfig->driver_version, item_name(items[index]));

    if (parse_driver_rocm_version(item_description(items[index]), rocm_version, sizeof(rocm_version)))
    {
        strcpy(pDriverConfig->driver_rocm_version, rocm_version);
    }
}

void clear_driver_version_name()
{
    DRIVER_MENU_CONFIG *pDriverConfig;

    if ( NULL == menuDriverVersion.pMenu )
    {
        return;
    }

    pDriverConfig = &menuDriverVersion.pConfig->driver_config;

    // clear the driver version and driver rocm version names
    clear_str(pDriverConfig->driver_version);
    clear_str(pDriverConfig->driver_rocm_version);

}

void update_driver_version_config()
{
    MENU_DATA *pMenuData = &menuDriverVersion;
    int i;

    if ( NULL == pMenuData->pMenu )
    {
        return;
    }

    MENU *pMenu = pMenuData->pMenu;
    ITEM **items = pMenuData->itemList[0].items;

    ROCM_MENU_CONFIG *pRocmConfig = &pMenuData->pConfig->rocm_config;

    clear_driver_version_name();

    // check for any selected items in the menu
    for(i = 0; i < item_count(pMenu); ++i)
    {
        if(item_value(items[i]) == TRUE)
        {
            set_driver_version_name(i);
            break;
        }
    }

    // update the driver version string if there are any selections
    if (!is_driver_version_empty())
    {
        // if installing rocm, update the version to match the driver version
        if (pRocmConfig->install_rocm)
        {
            set_rocm_versions_menu(i);
        }
    }
}

void reset_driver_version_menu()
{
    ITEM **items;

    if (menuDriverVersion.pMenu)
    {
        // reset the driver version item selections
        items = menu_items(menuDriverVersion.pMenu);

        for (int i = 0; i < item_count(menuDriverVersion.pMenu); i++)
        {
            if (item_value(items[i]) == TRUE)
            {
                set_item_value(items[i], false);
            }

            delete_menu_item_selection_mark(&menuDriverVersion, items[i]);
        }

        menuDriverVersion.itemSelections = 0;

        // clear the driver version
        clear_driver_version_name();
    }
}

void do_driver_menu_version()
{
    MENU *pMenu = menuDriverVersion.pMenu;

    driver_menu_submenu_draw(&menuDriverVersion);

    // driver version menu loop
    menu_loop(&menuDriverVersion);

    // Update the driver version config on exit
    update_driver_version_config();

    unpost_menu(pMenu);

    wclear(menuDriverVersion.pMenuWindow);
}

bool is_driver_version_empty()
{
    DRIVER_MENU_CONFIG *pDriverConfig;

    if (menuDriverVersion.pMenu)
    {
        pDriverConfig = &(menuDriverVersion.pConfig)->driver_config;

        return strlen(pDriverConfig->driver_version) == 0;
    }

    return false;
}

int get_driver_version_index_by_name()
{
    DRIVER_MENU_CONFIG *pDriverConfig = &(menuDriverVersion.pConfig)->driver_config;
    int index = -1;

    ITEM **items = menuDriverVersion.itemList[0].items;
    int numItems = menuDriverVersion.itemList[0].numItems - 1;

    // find the index in the current driver version menu items for the set driver_version string
    for (int i = 0; i < numItems; i++)
    {
        if (strcmp(item_name(items[i]), pDriverConfig->driver_version) == 0)
        {
            index = i;
            break;
        }
    }

    return index;
}

void set_driver_version_menu(int index)
{
    // Set the driver version menu to item (version) given at index

    DRIVER_MENU_CONFIG *pDriverConfig;

    if (index < 0 || index >= DRIVER_ROCM_NUM_VERS)
    {
        exit_error("Invalid index for driver version menu.");
    }

    if (menuDriverVersion.pMenu)
    {
        pDriverConfig = &menuDriverVersion.pConfig->driver_config;

        // reset the driver version menu items
        reset_driver_version_menu(pDriverConfig);
        
        // set the driver version to the item at index
        set_driver_version_name(index);
        set_menu_item_select_to_index(&menuDriverVersion, index);

        pDriverConfig->driver_rocm_index = index;
    }
}
