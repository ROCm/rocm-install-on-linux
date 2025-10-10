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
#include "rocm_menu.h"
#include "help_menu.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


// For public version of the app
// ROCm Main Menu Setup
char *rocmMenuMainOp[] = {
    "Install ROCm",
    SKIPPABLE_MENU_ITEM,
    "   ROCm Version",
    "   ROCm Components",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *rocmMenuMainDesc[] = {
    "Enable/Disable ROCm install.",
    SKIPPABLE_MENU_ITEM,
    "Set ROCm Version to install.",
    "Configure ROCm Components to install.",
    SKIPPABLE_MENU_ITEM,
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};

// verbose help menu variables
// Spaces added/deleted from HelpOps and HelpDesc to ensure whole words aren't
// cut off between lines when displaying help menu.
char *rocmHelpMenuMainOp[] = {
    "Install ROCm",
    "ROCm Version",
    "ROCm Components",
    SKIPPABLE_MENU_ITEM,
    (char*)NULL,
};

char *rocmHelpMenuMainDesc[] = {
    "Include ROCm packages in the creation of the           offline installer",
    "The specific ROCm version to source packages for       creating the offline installer.",
    "List of specific groups of ROCm packages (components)  for creating the offline installer.",
    " ",
    (char*)NULL,
};

MENU_PROP rocmMenuMainProps  = {
    .pMenuTitle = "ROCm Options",
    .pMenuControlMsg = "<DONE> to exit",
    .numLines = ARRAY_SIZE(rocmMenuMainOp) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = ROCM_MENU_ITEM_START_Y,
    .startx = ROCM_MENU_ITEM_START_X,
    .numItems = ARRAY_SIZE(rocmMenuMainOp)
};

ITEMLIST_PARAMS rocmMenuMainItems = {
    .numItems           = (ARRAY_SIZE(rocmMenuMainOp)),
    .pItemListTitle     = "ROCm Install Settings:",
    .pItemListChoices   = rocmMenuMainOp,
    .pItemListDesp      = rocmMenuMainDesc
};

char *rocmVersionsNameIndexMapping[] = {
    "6.1",
    "6.1.1",
    "6.1.2",
    "6.1.3",
    "6.2",
    "6.2.1",
    "6.2.2",
    "6.2.4",
    "6.3",
    "6.3.1",
    "6.3.2",
    "6.3.3",
    "6.4",
    "6.4.1",
    "6.4.2",
    "6.4.3",
    "7.0",
    "7.0.1",
    "7.0.2",
    (char*)NULL,
};

char *rocmVersionsDescIndexMapping[] = {
    "Install ROCm 6.1",
    "Install ROCm 6.1.1",
    "Install ROCm 6.1.2",
    "Install ROCm 6.1.3",
    "Install ROCm 6.2",
    "Install ROCm 6.2.1",
    "Install ROCm 6.2.2",
    "Install ROCm 6.2.4",
    "Install ROCm 6.3",
    "Install ROCm 6.3.1",
    "Install ROCm 6.3.2",
    "Install ROCm 6.3.3",
    "Install ROCm 6.4",
    "Install ROCm 6.4.1",
    "Install ROCm 6.4.2",
    "Install ROCm 6.4.3",
    "Install ROCm 7.0",
    "Install ROCm 7.0.1",
    "Install ROCm 7.0.2",
    (char*)NULL,
};

char *distroOSVersionsIndexMapping[] = {
    "ubuntu20.04",
    "ubuntu22.04",
    "ubuntu24.04",
    "rhel8.9",
    "rhel8.10",
    "rhel9.2",
    "rhel9.3",
    "rhel9.4",
    "rhel9.5",
    "rhel9.6",
    "rhel10.0",
    "sles15.5",
    "sles15.6",
    "sles15.7",
    "ol8.10",
    "ol9.5",
    "ol9.6",
    "ol10.0",
    "debian12",
    "debian13",
    "rocky9.6",
    (char*)NULL,
};


// Each column corresponds to a specific rocm version specified in array rocmVersionsDescIndexMapping
// First column maps to 6.0.1, second maps to 6.0.2,..., third to 6.0.3 and so on...
int rocmVersionsMatrix[ROCM_VERS_ROWS][ROCM_VERS_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}, // Ubuntu 20.04 
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // Ubuntu 22.04 
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // Ubuntu 24.04 
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}, // rhel 8.9
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // rhel 8.10
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // rhel 9.2
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}, // rhel 9.3    
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // rhel 9.4
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0}, // rhel 9.5
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}, // rhel 9.6
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // rhel 10.0
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}, // sles 15.5
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0}, // sles 15.6
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1}, // sles 15.7
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1}, // oracle linux 8.10 
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0}, // oracle linux 9.5
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1}, // oracle linux 9.6
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // oracle linux 10.0
    {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1}, // debian 12
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // debian 13
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1}, // rocky 9.6
};

char **rocmVersions = NULL;
char **rocmVersionsDesc = NULL;

MENU_PROP rocmMenuVersionProps = {0};
ITEMLIST_PARAMS rocmMenuVersionItems = {0};

MENU_PROP rocmHelpMenuMainProps  = {
    .pMenuTitle = "ROCm Options Help",
    .pMenuControlMsg = DEFAULT_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = ROCM_MENU_ITEM_START_Y,
    .startx = ROCM_MENU_ITEM_START_X,
    .numItems = 0
};

ITEMLIST_PARAMS rocmHelpMenuMainItems = {
    .numItems           = 0,
    .pItemListTitle     = "ROCm Install Settings Description:",
    .pItemListChoices   = NULL,
    .pItemListDesp      = NULL
};

MENU_PROP rocmUsecasesHelpMenuMainProps  = {
    .pMenuTitle = "ROCm Components Help",
    .pMenuControlMsg = DEFAULT_SCROLLABLE_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = ROCM_MENU_ITEM_START_Y,
    .startx = ROCM_MENU_ITEM_START_X,
    .numItems = 0
};

ITEMLIST_PARAMS rocmUsecasesHelpMenuMainItems = {
    .numItems           = 0,
    .pItemListTitle     = "ROCm Components Description:",
    .pItemListChoices   = NULL,
    .pItemListDesp      = NULL
};

void process_rocm_menu(MENU_DATA *pMenuData);
void create_rocm_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);
void update_is_rocm_deselected_status(MENU_DATA *pMenuData, bool isRocmStackSelected);

// sub-menus - usecases
void create_rocm_menu_usecase_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void create_rocm_usecases_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);
void destroy_rocm_menu_usecase_window();
void do_rocm_menu_usecase();
void process_rocm_usecase_menu();
void process_rocm_help_menu_usecase();

void update_rocm_usecase_config();
void clear_rocm_usecases_menu();
bool check_usecase_for_version_chg();

// sub-menus - version
void create_rocm_menu_version_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_rocm_menu_version_window();
void process_rocm_version_menu();

bool is_rocm_version_empty();


// menu draw/config
void rocm_menu_toggle_grey_items(MENU_DATA *pMenuData, bool enable);
void rocm_menu_draw(MENU_DATA *pMenuData);
void rocm_menu_submenu_draw(MENU_DATA *pMenuData);

// helper functions to determine if specific usecases enabled/disabled
bool is_mutlimediasdk_enabled(const char *ROCMVersion);

// enable/disabling rocm usecases depending on rocm version settings
void disable_rocm_usecases_for_rocm_version_selected();

// enable/disable rocm versions depending on OS distro
int getRocmVersionOpsArray(char *rocmMenuVersionOps[], char *rocmMenuVersionDesc[], OFFLINE_INSTALL_CONFIG *pConfig);

MENU_DATA menuROCMUsecase = {0};
MENU_DATA menuROCMVersion = {0};

MENU_DATA menuHelpROCMUsecase = {0};
MENU_PROP rocmMenuUsecaseProps = {0};
ITEMLIST_PARAMS rocmMenuUseCaseItems = {0};
char rocmMenuUsecaseOps[MAX_MENU_ITEMS][MAX_MENU_ITEM_NAME] = {0};
char rocmMenuUsecaseDesc[MAX_MENU_ITEMS][MAX_MENU_ITEM_NAME] = {0};


/**************** ROCM MENU **********************************************************************************/

void create_rocm_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create the Main ROCm options menu
    create_menu(pMenuData, pMenuWindow, &rocmMenuMainProps, &rocmMenuMainItems, pConfig);

    // create verbose help menu
    pMenuData->pHelpMenu = calloc(1, sizeof(MENU_DATA));
    if (pMenuData->pHelpMenu)
    {
        create_rocm_help_menu_window(pMenuData->pHelpMenu, pMenuWindow);
    }

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = rocm_menu_draw;

     // Set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_rocm_menu);

    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);  // space before done
    rocm_menu_toggle_grey_items(pMenuData, false);
    menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, false); // rocm usecases menu

    // create the versions sub-menu
    create_rocm_menu_version_window(&menuROCMVersion, pMenuWindow, pConfig);
}

void create_rocm_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &rocmHelpMenuMainProps, &rocmHelpMenuMainItems, NULL);
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, rocmHelpMenuMainOp, rocmHelpMenuMainDesc);
}

void destroy_rocm_menu_window(MENU_DATA *pMenuData)
{
    destroy_rocm_menu_usecase_window();
    destroy_rocm_menu_version_window();
    destroy_help_menu(pMenuData->pHelpMenu);

    destroy_menu(pMenuData);

    if (rocmVersions) free(rocmVersions);
    if (rocmVersionsDesc) free(rocmVersionsDesc);
}

void rocm_menu_draw(MENU_DATA *pMenuData)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;
    ROCM_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->rocm_config;

    char drawName[DEFAULT_CHAR_SIZE];

    menu_info_draw_bool(pMenuData, ROCM_MENU_ITEM_INSTALL_ROCM_ROW, ROCM_MENU_FORM_COL, pConfig->install_rocm);

    if (pConfig->install_rocm)
    {
        mvwprintw(pMenuWindow, ROCM_MENU_ITEM_VERSION_ROW, ROCM_MENU_FORM_COL, "%s", pConfig->rocm_versions);
    }
    else
    {
        wmove(pMenuWindow, ROCM_MENU_ITEM_USECASES_ROW, ROCM_MENU_FORM_COL);
        wclrtoeol(pMenuWindow);
        wmove(pMenuWindow, ROCM_MENU_ITEM_VERSION_ROW, ROCM_MENU_FORM_COL);
        wclrtoeol(pMenuWindow);
    }

    field_trim(pConfig->rocm_usescases, drawName, ROCM_MENU_USECASES_WIDTH);
    mvwprintw(pMenuWindow, ROCM_MENU_ITEM_USECASES_ROW, ROCM_MENU_FORM_COL, "%s", drawName);

    menu_draw(pMenuData);
}

void rocm_menu_submenu_draw(MENU_DATA *pMenuData)
{
    wclear(pMenuData->pMenuWindow);
    menu_draw(pMenuData);
}

void rocm_menu_toggle_grey_items(MENU_DATA *pMenuData, bool enable)
{
    ROCM_MENU_CONFIG *pRocmConfig = &pMenuData->pConfig->rocm_config;
    DRIVER_MENU_CONFIG *pDriverConfig = &pMenuData->pConfig->driver_config;

    if (enable)
    {
        // enable all driver option fields
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, pRocmConfig->rocm_version_selected);
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_VERSIONS_INDEX, true);
    }
    else
    {
        // disable all driver option fields
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, false);
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_VERSIONS_INDEX, false);

        // reset to defaults
        reset_rocm_usecases_menu();

        if (!pDriverConfig->install_driver)
        {
            reset_rocm_version_menu(pRocmConfig);
        }
    }
}

void rocm_menu_update_state(MENU_DATA *pMenuData)
{
    // Check global state and update the rocm menu
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;

    // only update if there is a state change
    if (!pConfig->configChg)
    {
        return;
    }

    // only update if installing the rocm
    if (!pRocmConfig->install_rocm)
    {
        return;
    }

    // Check for updates to the current installer type
    if (is_repo_public(pMenuData))
    {
        // PUBLIC: usecase, version numbwr

        // enable the ROCm usecase and versions number item
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, pConfig->rocm_config.rocm_version_selected);
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_VERSIONS_INDEX, true);
    }

    // Update rocm usecase
    disable_rocm_usecases_for_rocm_version_selected();
    update_rocm_usecase_config();
}

void do_rocm_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    wclear(pMenuData->pMenuWindow);

    bool isRocmStackSelected = is_specific_usecase_selected(pMenuData, ROCM_USECASE);

    // draw the ROCm menu contents
    rocm_menu_draw(pMenuData);

    // ROCm menu loop
    menu_loop(pMenuData);

    update_is_rocm_deselected_status(pMenuData, isRocmStackSelected);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the ROCm main menu
void process_rocm_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;

    ITEM *pCurrentItem = current_item(pMenu);

    int index = item_index(pCurrentItem);

    DEBUG_UI_MSG(pMenuData, "ROCM Menu: %d, itemlist %d", index, pMenuData->curItemListIndex);

    bool isSelectable = item_opts(pCurrentItem) == O_SELECTABLE;

    if (index == ROCM_MENU_ITEM_INSTALL_ROCM_INDEX)
    {
        pRocmConfig->install_rocm = !pRocmConfig->install_rocm;
        rocm_menu_toggle_grey_items(pMenuData, pRocmConfig->install_rocm);
        menu_info_draw_bool(pMenuData, ROCM_MENU_ITEM_INSTALL_ROCM_ROW, ROCM_MENU_FORM_COL, pRocmConfig->install_rocm);

        pConfig->configChg = true;
        rocm_menu_update_state(pMenuData);
        pConfig->configChg = false;
    }
    else if (index == ROCM_MENU_ITEM_VERSIONS_INDEX)
    {
        if (pRocmConfig->install_rocm)
        {
            if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC)
            {
                // switch to the version sub-menu
                unpost_menu(pMenu);

                do_rocm_menu_version();

                if (pRocmConfig->rocm_version_selected)
                {
                    menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, true);
                }
            }
        }
    }
    else if (index == ROCM_MENU_ITEM_USECASES_INDEX)
    {
        if (pRocmConfig->install_rocm)
        {
            if (isSelectable)
            {
                // switch to the usecases sub-menu
                unpost_menu(pMenu);

                create_rocm_menu_usecase_window(&menuROCMUsecase, pMenuData->pMenuWindow, pConfig);
                do_rocm_menu_usecase();
            }
        }
    }
    else
    {
        DEBUG_UI_MSG(pMenuData, "Unknown item index");
    }

    rocm_menu_draw(pMenuData);
}

void update_is_rocm_deselected_status(MENU_DATA *pMenuData, bool isRocmStackSelected)
{
    ROCM_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->rocm_config;
    if (isRocmStackSelected && !is_specific_usecase_selected(pMenuData, ROCM_USECASE))
    {
        pConfig->is_rocm_usecase_deselected = true;
    }
    else
    {
        pConfig->is_rocm_usecase_deselected = false;
    }
}


/**************** ROCM USECASE MENU **************************************************************************/

void create_rocm_menu_usecase_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;
    ROCM_USECASES_TYPE rocm_usecases_type;

    int i, item_count, item_desc_count;
    char *itemFile;
    char *itemDescFile;
    char *rocmMenuUsecaseOpsPtrs[MAX_MENU_ITEMS];
    char *rocmMenuUsecaseDescPtrs[MAX_MENU_ITEMS];

    // set the usecase type based on the current rocm version
    rocm_usecases_type = get_usecase_type_for_version();
    if( rocm_usecases_type == eROCM_USECASES_TYPE_V1 )
    {
        itemFile = "./rocm_menus/rocm_comp_v1";
        itemDescFile = "./rocm_menus/rocm_comp_v1_desc";
    }
    else if( rocm_usecases_type == eROCM_USECASES_TYPE_V2 )
    {
        itemFile = "./rocm_menus/rocm_comp_v2";
        itemDescFile = "./rocm_menus/rocm_comp_v2_desc";
    }
    else
    {
        return;
    }

    // check if for a change in type
    if (rocm_usecases_type == pRocmConfig->rocm_usecases_type)
    {
        // no version/usecase change
        return;
    }

    // if switching usecase type reset and destroy the current usecase menu
    if ( (rocm_usecases_type != pRocmConfig->rocm_usecases_type) && (pRocmConfig->rocm_usecases_type != eROCM_USECASES_TYPE_NONE) )
    {
        reset_rocm_usecases_menu();
        destroy_rocm_menu_usecase_window();
    }

    // Read the item file
    item_count = read_file_for_items(itemFile, rocmMenuUsecaseOps);
    if (item_count == -1) 
    {
        fprintf(stderr, "Failed to read file.\n");
        return;
    }

    // Read the item description file
    item_desc_count = read_file_for_items(itemDescFile, rocmMenuUsecaseDesc);
    if (item_desc_count == -1) 
    {
        fprintf(stderr, "Failed to read file.\n");
        return;
    }

    // ensure the item and item_desc are the same
    if (item_count != item_desc_count) 
    {
        fprintf(stderr, "Item count mismatch\n");
        return;
    }

    // setup and create the usecase menu
    if (item_count != 0) 
    {
        // set the config rocm usecase type
        pRocmConfig->rocm_usecases_type = rocm_usecases_type;

        for (int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            rocmMenuUsecaseOpsPtrs[i] = rocmMenuUsecaseOps[i];
            rocmMenuUsecaseDescPtrs[i] = rocmMenuUsecaseDesc[i];
        }

        i = item_count;

        // set the menu item names to the rocm paths found
        strcpy(rocmMenuUsecaseOps[i], " ");
        strcpy(rocmMenuUsecaseDesc[i++], " ");

        strcpy(rocmMenuUsecaseOps[i], "<HELP>");
        strcpy(rocmMenuUsecaseDesc[i++], DEFAULT_VERBOSE_HELP_WINDOW_MSG);

        strcpy(rocmMenuUsecaseOps[i], "<DONE>");
        strcpy(rocmMenuUsecaseDesc[i++], " Exit to ROCm Options Menu");

        int numItems = i + 1;

        rocmMenuUsecaseProps = (MENU_PROP) {
            .pMenuTitle = "ROCm Component Configuration",
            .pMenuControlMsg = "<DONE> to exit : Space/Enter to select/unselect component. Up/Down to scroll.",
            .numLines = numItems - 1,
            .numCols = MAX_MENU_ITEM_COLS,
            .starty = ROCM_MENU_ITEM_START_Y,
            .startx = 4,
            .numItems = numItems
        };

        rocmMenuUseCaseItems = (ITEMLIST_PARAMS) {
            .numItems           = numItems,
            .pItemListTitle     = "Select which component(s) you wish to package in the offline installer:",
            .pItemListChoices   = rocmMenuUsecaseOpsPtrs,
            .pItemListDesp      = rocmMenuUsecaseDescPtrs
        };

        // Create the ROCm Sub-Menu
        create_menu(&menuROCMUsecase, pMenuWindow, &rocmMenuUsecaseProps, &rocmMenuUseCaseItems, pConfig);
        menuROCMUsecase.isMenuItemsSelectable = true;   // items are selectable

        // Set pointer to draw menu function when window is resized
        menuROCMUsecase.drawMenuFunc = rocm_menu_submenu_draw;

        // Make the menu multi valued
        menu_opts_off(pMenuData->pMenu, O_ONEVALUE);

        // set items to non-selectable for the menu
        set_menu_fore(pMenuData->pMenu, COLOR_PAIR(8));

        // Disable items from being selectable
        set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));

        // Set user pointer for 'ENTER' events
        set_menu_userptr(menuROCMUsecase.pMenu, process_rocm_usecase_menu);

        // create the usecases help menu
        create_rocm_usecases_help_menu_window(&menuHelpROCMUsecase, pMenuWindow);

        ITEM **items = menu_items(pMenuData->pMenu);
        // function that will draw scrollable help menu from the rocm_usecase.md file
        set_item_userptr(items[pMenuData->itemList[0].helpItemIndex], process_rocm_help_menu_usecase);

        // set the useptr specific to a usecase
        if( rocm_usecases_type != eROCM_USECASES_TYPE_V2 )
        {
            set_item_userptr(items[ROCM_USECASES_MENU_ITEM_MULTIMEDIASDK_INDEX], process_rocm_usecase_menu);
        }

         pMenuData->clearErrMsgAfterUpOrDownKeyPress = true;
    }
}

void create_rocm_usecases_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &rocmUsecasesHelpMenuMainProps, &rocmUsecasesHelpMenuMainItems, NULL);
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);
}

void destroy_rocm_menu_usecase_window()
{
    destroy_help_menu(menuHelpROCMUsecase.pHelpMenu);
    destroy_menu(&menuROCMUsecase);

    memset(&menuROCMUsecase, 0, sizeof(menuROCMUsecase));
    memset(rocmMenuUsecaseOps, 0, sizeof(rocmMenuUsecaseOps));
    memset(rocmMenuUsecaseDesc, 0, sizeof(rocmMenuUsecaseDesc));
}

void do_rocm_menu_usecase()
{
    MENU *pMenu = menuROCMUsecase.pMenu;

    disable_rocm_usecases_for_rocm_version_selected();
    rocm_menu_submenu_draw(&menuROCMUsecase);

    // ROCm menu loop
    menu_loop(&menuROCMUsecase);

    // Update the ROCm usecase config on exit
    update_rocm_usecase_config();

    unpost_menu(pMenu);

    // Need this to clear the X that's added when user selects rocm usecases
    // when navigating back to he rocm options menu.
    wclear(menuROCMUsecase.pMenuWindow);
}

// process when user scrolls to specific usecase via key up/down keys
void process_rocm_usecase_menu()
{
    MENU *pMenu = menuROCMUsecase.pMenu;
    ITEM *pCurrentItem = current_item(pMenu);
    const char *highlightedUsecase = item_name(pCurrentItem);

    ROCM_MENU_CONFIG *rocm_config = &(menuROCMUsecase.pConfig)->rocm_config;

    char *selectedROCMVersion = rocm_config->rocm_versions;

    bool isMultimediasdkEnabled = is_mutlimediasdk_enabled(selectedROCMVersion);

    if (strcmp(highlightedUsecase, "multimediasdk") == 0)
    {
        if (!isMultimediasdkEnabled)
        {
            print_menu_warning_msg(&menuROCMUsecase, WARN_ERR_START_Y, WARN_ERR_START_X, "not supported on ROCm version %s", selectedROCMVersion);
        }
    }
}

void process_rocm_help_menu_usecase()
{
    MENU *pMenu = menuROCMUsecase.pMenu;
    char *pHelpFile;

    unpost_menu(pMenu);
    rocm_menu_submenu_draw(&menuHelpROCMUsecase);

    ROCM_MENU_CONFIG *pRocmConfig = &menuROCMUsecase.pConfig->rocm_config;

    if (pRocmConfig->rocm_usecases_type == eROCM_USECASES_TYPE_V1)
    {
        pHelpFile = "./rocm_menus/rocm_comp_v1_help";
    }
    else if (pRocmConfig->rocm_usecases_type == eROCM_USECASES_TYPE_V2)
    {
        pHelpFile = "./rocm_menus/rocm_comp_v2_help";
    }
    else
    {
        fprintf(stderr, "Error: Invalid type %d", pRocmConfig->rocm_usecases_type);
        exit(1);
    }

    int is_error_reading_verbose_help_file = display_help_scroll_window(&menuHelpROCMUsecase, pHelpFile);
    if (is_error_reading_verbose_help_file == -1)
    {
        wgetch(menuROCMUsecase.pMenuWindow);
    }

    // Show the rocm usecase menu right after user exits from the help menu
    rocm_menu_submenu_draw(&menuROCMUsecase);
}

void update_rocm_usecase_config()
{
    MENU_DATA *pMenuData = &menuROCMUsecase;
    int i;

    if ( NULL == pMenuData->pConfig )
    {
        return;
    }

    MENU *pMenu = pMenuData->pMenu;
    ITEM **items = pMenuData->itemList[0].items;

    ROCM_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->rocm_config;

    pConfig->rocm_usescases[0] = '\0';

    for(i = 0; i < item_count(pMenu); ++i)
    {
        if(item_value(items[i]) == TRUE)
        {
            strcat(pConfig->rocm_usescases, item_name(items[i]));
            strcat(pConfig->rocm_usescases, ",");
        }
    }

    pConfig->rocm_usescases[strlen(pConfig->rocm_usescases)-1] = '\0';
}

void reset_rocm_usecases_menu()
{
    ROCM_MENU_CONFIG *pRocmConfig;

    if (menuROCMUsecase.pMenu)
    {
        pRocmConfig = &menuROCMUsecase.pConfig->rocm_config;

        // reset the usecase item selections
        ITEM **items = menu_items(menuROCMUsecase.pMenu);

        for (int i = 0; i < item_count(menuROCMUsecase.pMenu); i++)
        {
            if (item_value(items[i]) == TRUE)
            {
                set_item_value(items[i], false);
            }

            delete_menu_item_selection_mark(&menuROCMUsecase, items[i]);
        }

        menuROCMUsecase.itemSelections = 0;

        // clear the usecases
        clear_str(pRocmConfig->rocm_usescases);
    }
}

void clear_rocm_usecases_menu()
{
    MENU_DATA *pMenuData = &menuROCMUsecase;

    for (int i = 0; i < pMenuData->itemList[0].numItems; i++)
    {
        menu_set_item_select(pMenuData, i, true);
    }
}

ROCM_USECASES_TYPE get_usecase_type_for_version()
{
    ROCM_MENU_CONFIG *pRocmConfig;
    ROCM_USECASES_TYPE rocm_usecases_type;

    if (NULL == menuROCMVersion.pMenu)
    {
        return eROCM_USECASES_TYPE_NONE;
    }

    pRocmConfig = &menuROCMVersion.pConfig->rocm_config;

    // return the current usecase type based on the current rocm version selected
    if( strcmp(pRocmConfig->rocm_versions, "6.4.1") > 0 )
    {
        rocm_usecases_type = eROCM_USECASES_TYPE_V2;
    }
    else
    {
        rocm_usecases_type = eROCM_USECASES_TYPE_V1;
    }

    return rocm_usecases_type;
}


bool check_usecase_for_version_chg()
{
    ROCM_MENU_CONFIG *pRocmConfig;
    ROCM_USECASES_TYPE current_usecase;

    if (NULL == menuROCMUsecase.pMenu)
    {
        return false;
    }

    pRocmConfig = &menuROCMUsecase.pConfig->rocm_config;

    // get the usescase type for the current version
    current_usecase = get_usecase_type_for_version();
    
    if ( current_usecase == pRocmConfig->rocm_usecases_type )
    {
        // version change does not require usecase change
        return false;
    }

    // version change requires usecase change
    return true;
}

void update_rocm_usecase_string(char *rocm_usecases)
{
    OFFLINE_INSTALL_CONFIG *pConfig = menuROCMUsecase.pConfig;
    char temp[LARGE_CHAR_SIZE] = {0};
    char *tok;

    int first = 1;

    // no updates for non-meta package usecase (amdgpu-install)
    if (get_usecase_type_for_version() < eROCM_USECASES_TYPE_V2)
    {
        return;
    }

    // Copy the input usecases
    char usecases_copy[LARGE_CHAR_SIZE];
    strncpy(usecases_copy, rocm_usecases, LARGE_CHAR_SIZE - 1);
    usecases_copy[LARGE_CHAR_SIZE - 1] = '\0';
    
    tok = strtok(usecases_copy, ",");
    while (tok != NULL) 
    {
        // Check for rocm-graphcis, rocm-workstation, dkms and replace with the correct packages
        if (strcmp(tok, "dkms") == 0)
        {
            tok = "amdgpu-dkms";
        }
        else if (strcmp(tok, "rocm-hip-runtime-dev") == 0)
        {
            if ( pConfig->distroType != eDISTRO_TYPE_DEB )
            {
                tok = "rocm-hip-runtime-devel";
            }
        }

        // Append the token to temp
        if (first)
        {
            first = 0;
            snprintf(temp, sizeof(temp), "%s", tok);
        }
        else
        {
            strncat(temp, ",", sizeof(temp) - strlen(temp) - 1);
            strncat(temp, tok, sizeof(temp) - strlen(temp) - 1);
        }

        tok = strtok(NULL, ",");
    }

    // Copy back the updated string
    strncpy(rocm_usecases, temp, LARGE_CHAR_SIZE - 1);
    rocm_usecases[LARGE_CHAR_SIZE - 1] = '\0';
}


/**************** ROCM VERSION MENU ***************************************************************************/

void create_rocm_menu_version_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create dynamic rocm versions sub menu
    rocmVersions = calloc(ROCM_VERS_MENU_MAX_SIZE, sizeof(char*));
    rocmVersionsDesc = calloc(ROCM_VERS_MENU_MAX_SIZE, sizeof(char*));
    
    int numItems = getRocmVersionOpsArray(rocmVersions, rocmVersionsDesc, pConfig) + 1;

    rocmMenuVersionProps = (MENU_PROP) {
        .pMenuTitle = "ROCm Version Configuration",
        .pMenuControlMsg = "<DONE> to exit : Space/Enter to select/unselect version. Up/Down to scroll.",
        .numLines = numItems - 1,
        .numCols = MAX_MENU_ITEM_COLS,
        .starty = ROCM_MENU_ITEM_START_Y,
        .startx = ROCM_MENU_USECASES_ITEM_START_X,
        .numItems = numItems
    };

    rocmMenuVersionItems = (ITEMLIST_PARAMS) {
        .numItems           = numItems,
        .pItemListTitle     = "Select which version you wish to package in the offline installer:",
        .pItemListChoices   = rocmVersions,
        .pItemListDesp      = rocmVersionsDesc
    };


    // Create the ROCm Version Sub-Menu
    create_menu(pMenuData, pMenuWindow, &rocmMenuVersionProps, &rocmMenuVersionItems, pConfig);
    pMenuData->enableMultiSelection = false;
    pMenuData->isMenuItemsSelectable = true;

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = rocm_menu_submenu_draw;

    // Make the menu multi valued
    menu_opts_off(pMenuData->pMenu, O_ONEVALUE);

    // set items to non-selectable for the menu
    set_menu_fore(pMenuData->pMenu, COLOR_PAIR(8));

    set_menu_userptr(pMenuData->pMenu, process_rocm_version_menu);

    // Disable items from being selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(3));
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 3, false);  // space before done
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 2, false);  // done
}

void destroy_rocm_menu_version_window()
{
    destroy_menu(&menuROCMVersion);
}

void update_rocm_version_config()
{
    int i;

    MENU *pMenu = menuROCMVersion.pMenu;
    ITEM **items = menuROCMVersion.itemList[0].items;

    ROCM_MENU_CONFIG *pConfig = &(menuROCMVersion.pConfig)->rocm_config;

    pConfig->rocm_versions[0] = '\0';

    for(i = 0; i < item_count(pMenu); ++i)
    {
        if(item_value(items[i]) == TRUE)
        {
            strcat(pConfig->rocm_versions, item_name(items[i]));
            strcat(pConfig->rocm_versions, ",");
            pConfig->rocm_version_selected = true;
        }
    }

    // if user deselects rocm version
    if (is_rocm_version_empty())
    {
        pConfig->rocm_version_selected = false;
    }

    pConfig->rocm_versions[strlen(pConfig->rocm_versions)-1] = '\0';

    // check if the newly set version requires a reset to the usecase
    if (check_usecase_for_version_chg())
    {
        reset_rocm_usecases_menu();
    }
}

void do_rocm_menu_version()
{
    MENU_DATA *pMenuData = &menuROCMVersion;
    MENU *pMenu = pMenuData->pMenu;
    ROCM_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->rocm_config;

    rocm_menu_submenu_draw(pMenuData);

    // ROCm menu loop
    menu_loop(pMenuData);

    // Update the ROCm version config on exit
    update_rocm_version_config(pMenuData);

    // Update the ROCm usecase config on exit
    // Have to do this as some usecases are disabled for some specific
    // rocm versions
    disable_rocm_usecases_for_rocm_version_selected();
    update_rocm_usecase_config();

    if (pConfig->rocm_version_selected && pConfig->install_rocm)
    {
        menu_set_item_select(pMenuData, ROCM_MENU_ITEM_USECASES_INDEX, true);
    }

    unpost_menu(pMenu);

    // Need this to clear the X that's added when user selects rocm version
    // when navigating back to he rocm options menu.
    wclear(pMenuData->pMenuWindow);
}

void reset_rocm_version_menu(ROCM_MENU_CONFIG *pRocmConfig)
{
    // reset the version item selections
    ITEM **items = menu_items(menuROCMVersion.pMenu);

    for (int i = 0; i < item_count(menuROCMVersion.pMenu); i++)
    {
        if (item_value(items[i]) == TRUE)
        {
            set_item_value(items[i], false);
        }

        delete_menu_item_selection_mark(&menuROCMVersion, items[i]);
    }

    menuROCMVersion.itemSelections = 0;

    // clear the version
    clear_str(pRocmConfig->rocm_versions);

    // deselect version
    pRocmConfig->rocm_version_selected = false;
}

// multimedia supported on all rocm versions except 5.7.3 and 6.2+
bool is_mutlimediasdk_enabled(const char *ROCMVersion)
{
    bool is_supported = true;
    if ( strcmp(ROCMVersion, "5.7.3") == 0 ||
        strcmp(ROCMVersion, "6.2") > 0 || strcmp(ROCMVersion, "6.2") == 0 )
    {
        is_supported = false;
    }

    return is_supported;
}

bool is_rocm_version_empty()
{
    ROCM_MENU_CONFIG *pConfig = &(menuROCMVersion.pConfig)->rocm_config;

    return strlen(pConfig->rocm_versions) == 0;

}


// Example of param *usecase value is: "multimediasdk,"

// This function is used to concatenate a string of the names of all
// usecases user has selected that is disabled for a rocm version
// user wants to select.

// Eg. User selects rocm 6.1 and then selects usecases asan and multimediasdk.
// User then selects rocm version 5.7.3. When user does that, we display
// a warning message saying
// WARNING: multimediasdk,asan are not supported on 5.7.3.

// This function generates the "multimediasdk,asan," part
int concatenate_disabled_rocm_usecase_string(bool isUsecaseSelected, const char *usecase,
                                             bool isUsecaseEnabled, char *disabledUsecases, int disableUsecasesCount)
{
    if (isUsecaseSelected && !isUsecaseEnabled)
    {
        strcat(disabledUsecases, usecase);
        disableUsecasesCount++;
    }

    return disableUsecasesCount;
}

void process_rocm_version_menu()
{
    MENU *pMenu = menuROCMVersion.pMenu;

    int disabledUsecasesCount = 0;
    bool isMultimediasdkSelected = is_specific_usecase_selected(&menuROCMVersion, "multimediasdk");

    char disabledUsecases[DEFAULT_CHAR_SIZE];
    char printDisabledUsecases[DEFAULT_CHAR_SIZE];
    memset(disabledUsecases, '\0', DEFAULT_CHAR_SIZE);
    memset(printDisabledUsecases, '\0', DEFAULT_CHAR_SIZE);

    ITEM *pCurrentItem = current_item(pMenu);
    const char *selectedROCMVersion = item_name(pCurrentItem);

    bool isMultimediasdkEnabled = is_mutlimediasdk_enabled(selectedROCMVersion);

    disabledUsecasesCount = concatenate_disabled_rocm_usecase_string(isMultimediasdkSelected,"multimediasdk,",
                                              isMultimediasdkEnabled,disabledUsecases, disabledUsecasesCount );

    if (strlen(disabledUsecases) > 0)
    {
        strncpy(printDisabledUsecases, disabledUsecases, strlen(disabledUsecases)-1);
        const char *verb = (disabledUsecasesCount > 1) ? "are" : "is";
        print_menu_warning_msg(&menuROCMVersion, WARN_ERR_START_Y, WARN_ERR_START_X, "%s %s not supported on %s.", printDisabledUsecases, verb, selectedROCMVersion);
    }
}

void disable_rocm_usecases_for_rocm_version_selected()
{
    MENU_DATA *pMenuData = &menuROCMUsecase;

    if ( NULL == pMenuData->pConfig )
    {
        return;
    }

    ITEM **items = menu_items(pMenuData->pMenu);
    ROCM_MENU_CONFIG *pRocmConfig = &(pMenuData->pConfig)->rocm_config;

    // only usecase version type 1 has usecases disabled
    if (pRocmConfig->rocm_usecases_type >= eROCM_USECASES_TYPE_V2)
    {
        return;
    }

    char *selectedROCMVersion = pRocmConfig->rocm_versions;

    clear_rocm_usecases_menu();

    bool isMultimediasdkEnabled = is_mutlimediasdk_enabled(selectedROCMVersion);

    if (!isMultimediasdkEnabled)
    {
        TOGGLE_FALSE( (pMenuData->itemSelections), (item_index(items[ROCM_USECASES_MENU_ITEM_MULTIMEDIASDK_INDEX])) );
    }

    menu_set_item_select(pMenuData, ROCM_USECASES_MENU_ITEM_MULTIMEDIASDK_INDEX, isMultimediasdkEnabled);
}

/**************** HELPER FUNCTIONS *****************************************************************************/

int getDistroOSVerionIndex(char *distroOSVersion)
{
    int size = (int) ARRAY_SIZE(distroOSVersionsIndexMapping) - 1;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(distroOSVersion, distroOSVersionsIndexMapping[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

int getRocmVersionOpsArray(char *rocmMenuVersionOps[], char *rocmMenuVersionDesc[], OFFLINE_INSTALL_CONFIG *pConfig)
{
    int index = 0;
    char distroOSVersion[DEFAULT_CHAR_SIZE];

    sprintf(distroOSVersion, "%s%s",pConfig->distroID, pConfig->distroVersion);

    int rocmVersionIndex = getDistroOSVerionIndex(distroOSVersion);
    // if rocmVersionIndex is -1, then it means the OS it ran on isn't added to
    // the array distroOSVersionsIndexMapping
    if (rocmVersionIndex == -1)
    {
        printf("Unable to get rocm version index for current distro: %s\n", distroOSVersion);
        return -1;
    }

    for (int i = 0; i < (int) ARRAY_SIZE(rocmVersionsMatrix[rocmVersionIndex]); i++)
    {
        if (rocmVersionsMatrix[rocmVersionIndex][i] == 1)
        {
            rocmMenuVersionOps[index] = rocmVersionsNameIndexMapping[i];
            rocmMenuVersionDesc[index] = rocmVersionsDescIndexMapping[i];

            index++;
        }
    }

    // Add the last 3 rows which contain a gap between the menu items and
    // the <DONE> button, the <DONE> button and the NULL ending character.
    rocmMenuVersionOps[index] = SKIPPABLE_MENU_ITEM;
    rocmMenuVersionDesc[index] = SKIPPABLE_MENU_ITEM;

    index++;

    rocmMenuVersionOps[index] = "<DONE>";
    rocmMenuVersionDesc[index] = "Exit to main ROCm options menu";

    index++;
    rocmMenuVersionOps[index] = (char*)NULL;

    return index;
}
