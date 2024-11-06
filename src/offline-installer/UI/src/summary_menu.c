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
#include "summary_menu.h"
#include "help_menu.h"
#include "create_menu.h"
#include <math.h>
#include "utils.h"
#include <string.h>


char *targetSystemInfoOps[] = {
    "OS",
    "Kernel",
    (char *)NULL
};

char *targetSystemInfoValues[] = {
    "",
    "",
    (char *)NULL
};

char *summaryConfigOps[] = {
    "Installer Input",
    "Repo Type",
    "Dependency Type",
    "Installer Name",
    "Installer Path",
    (char* )NULL
};

char *summaryConfigValues[] = {
    "",
    "",
    "",
    "",
    "",
    "",
    (char* )NULL
};

char *summaryRocmOps[] = {
    "ROCm Version",
    "ROCm Components",
    (char *)NULL
};

char *summaryRocmValues[] = {
    "",
    "",
    (char *)NULL
};

char *summaryDriverOps[] = {
    "amdgpu Install Driver",
    "amdgpu Driver ROCm Version",
    "Set Video,render group",
    "Blacklist amdgpu driver",
    "Start amdgpu driver on install",
    (char *)NULL
};

char *summaryDriverValues[] = {
    "",
    "",
    "",
    "",
    "",
    (char *)NULL
};

char *summaryExtraOps[] = {
    "rocminfo",
    "rocm-smi",
    (char *)NULL
};

char *summaryExtraValues[] = {
    "",
    "",
    (char *)NULL
};

// Summary Menu Setup
char *summaryMenuOps[] = {
    "<Next Page>",
    SKIPPABLE_MENU_ITEM,
    "<RETURN>",
    "<ACCEPT>",
    (char*)NULL,
};

char *summaryMenuDesc[] = {
    "Next summary page",
    SKIPPABLE_MENU_ITEM,
    "Return to Main Menu",
    "Create offline installer",
    (char*)NULL,
};

MENU_PROP summaryMenuProps = {
    .pMenuTitle = "Offline Installer Configuration",
    .pMenuControlMsg = "",
    .numLines = ARRAY_SIZE(summaryMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = SUMMARY_MENU_ITEM_START_Y,
    .startx = SUMMARY_MENU_ITEM_START_X, 
    .numItems = ARRAY_SIZE(summaryMenuOps)
};

ITEMLIST_PARAMS summaryMenuItems = {
    .numItems           = ARRAY_SIZE(summaryMenuOps),
    .pItemListTitle     = "",
    .pItemListChoices   = summaryMenuOps,
    .pItemListDesp      = summaryMenuDesc
};

char install_name_trim[DEFAULT_CHAR_SIZE];
char install_loc_trim[DEFAULT_CHAR_SIZE];

void process_summary_menu(MENU_DATA *pMenuData);
void process_summary_item(MENU_DATA *pMenuData);

// menu draw
void draw_summary_page(MENU_DATA *pMenuData);
void summary_menu_draw(MENU_DATA *pMenuData);
char* bool_to_yes_no(bool value);
int print_multiline_string(WINDOW *pMenuWindow, char *text, int startx, int starty, int width);
void resize_and_reposition_summary_subwindow(MENU_DATA *pMenuData);

// page draw
void draw_next_page(MENU_DATA *pMenuData);
void draw_prev_page(MENU_DATA *pMenuData);

// repo-public prereqs
bool is_repo_public_opt_missing(OFFLINE_INSTALL_CONFIG *pConfig, char *opt);
bool is_repo_public_prereqs_fulfilled(MENU_DATA *pMenuData);


// all installer input types
bool is_miscellaneous_opt_missing(OFFLINE_INSTALL_CONFIG *pConfig, char *opt);
bool is_miscellaneous_prereqs_fulfilled(MENU_DATA *pMenuData);
bool is_opt_valid(OFFLINE_INSTALL_CONFIG *pConfig, char *opt);

void create_summary_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    int numItems;

    create_menu(pMenuData, pMenuWindow, &summaryMenuProps, &summaryMenuItems, pConfig);

    pMenuData->pMenuSubWindow = derwin(pMenuData->pMenuWindow, SUMMARY_SUBWIN_NUM_LINES, SUMMARY_SUBWIN_WIDTH_COLS, SUMMARY_SUBWIN_START_Y , SUMMARY_SUBWIN_START_X);

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = summary_menu_draw;

    numItems = summaryMenuItems.numItems;
    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, numItems - 2, false); // Disable <ACCEPT> button by default
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // default value of doneItemIndex is set to the last value of summaryMenuItems in create_menu
    // but we want it to be the second last item
    pMenuData->itemList[0].doneItemIndex = numItems - 3;
    pMenuData->itemList[0].helpItemIndex = -1;
    pMenuData->itemList[0].createOfflineInstallerItemIndex = numItems - 2;

    set_menu_userptr(pMenuData->pMenu, process_summary_menu);

    // process_summary_item function highlights the <RETURN> menu item red,
    // highlights the <ACCEPT> item to green (if applicable) and 
    // highlights the <NEXT PAGE> bold when cursor is on either of these items.
    ITEM **items = menu_items(pMenuData->pMenu);
    set_item_userptr(items[SUMMARY_MENU_ITEM_NEXT_PAGE_INDEX], process_summary_item);    // Next Page
    set_item_userptr(items[numItems - 2], process_summary_item);    // Accept
    set_item_userptr(items[numItems - 3], process_summary_item);    // Return
}

void destroy_summary_menu_window(MENU_DATA *pMenuData)
{
    delwin(pMenuData->pMenuSubWindow);
    destroy_menu(pMenuData);
}

void summary_menu_draw(MENU_DATA *pMenuData)
{
    wclear(pMenuData->pMenuWindow);

    // Flip order because we want to overwrite the default menu item title name w/
    // that menu_draw writes w/ the text "Target: pMenuData->pConfig->distroName"
    // from draw_summary_page
    menu_draw(pMenuData);   
    draw_summary_page(pMenuData);
}

void do_summary_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    pMenuData->currentSummaryPageIndex = 0;

    summary_menu_draw(pMenuData);

    // Summary menu loop
    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// return value is last row used for printing the string text
int print_multiline_string(WINDOW *pMenuWindow, char *text, int startx, int starty, int width)
{
    if (strlen(text) <= (size_t)width)
    {
        mvwprintw(pMenuWindow, starty, startx, "%s", text);
        return starty + 1;
    }
    else 
    {
        char *substring = calloc(1, sizeof(char *) * (width + 1));
        if (!substring)
        {
            return starty;
        }

        int height = calculate_text_height(text, width);
        int startIndex = 0;
        int lineWidth = width;

        for (int i = 0; i < height; i++)
        {   
            strncpy(substring, text + startIndex, lineWidth);
            
            // if we have < width characters left to print, then readjust
            // lineWidth to be value of the remaining characters left to print
            if (startIndex + width > (int)strlen(text))
            {
                lineWidth = (int)strlen(text) - startIndex;
            }
            startIndex += lineWidth;
            mvwprintw(pMenuWindow, starty, startx, "%s", substring);
            
            memset(substring, 0, (size_t)width);
            starty++;
        }
        
        free(substring);
    }

    return starty;
}

int print_sub_menu_summary_options(MENU_DATA *pMenuData, WINDOW *pMenuWindow, char **menuSummaryOp, char *menuSummaryTitle, char **menuSummaryValue, int opStartx, int starty, int valueStartx, int valueWidth)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;

    char *opt = menuSummaryOp[0];
    char *optValue;
    int i = 0;
    bool isOptMissingIfPublicRepo, isOptMissing, isOptValid;

    wattron(pMenuWindow, A_UNDERLINE);

    // Menu option title
    mvwprintw(pMenuWindow, starty, opStartx, "%s", menuSummaryTitle);
    wattroff(pMenuWindow, A_UNDERLINE);
    starty += 2;

    while (opt)
    {
        isOptValid = is_opt_valid(pConfig, opt);
        isOptMissingIfPublicRepo = is_repo_public(pMenuData) && is_repo_public_opt_missing(pConfig, opt);
        isOptMissing = isOptMissingIfPublicRepo || is_miscellaneous_opt_missing(pConfig, opt);

        if (isOptMissing)
        {
            wattron(pMenuWindow, COLOR_PAIR(1));
            optValue = "*Required*";
        }
        else
        {
            optValue = menuSummaryValue[i];
        }

        if (!isOptValid)
        {
            wattron(pMenuWindow, COLOR_PAIR(1));
        }

        wattron(pMenuWindow, A_BOLD);

        // menu summary option
        mvwprintw(pMenuWindow, starty,opStartx, "%s", opt);
        wattroff(pMenuWindow, A_BOLD);

        // menu summary value
        starty = print_multiline_string(pMenuWindow, optValue, valueStartx, starty, valueWidth);
       
        if (isOptMissing || !isOptValid)
        {
            wattroff(pMenuWindow, COLOR_PAIR(1));
        }
        
        i++;
        opt = menuSummaryOp[i]; 
    }

    return starty;
}


// checks if all prereqs required when user selects repo-public is fulfilled
bool is_repo_public_prereqs_fulfilled(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;

    bool ret = true;

    if (pConfig->rocm_config.install_rocm)
    {
        if (strlen(pConfig->rocm_config.rocm_versions) == 0)
        {
            ret &= false;
        }

        if (strlen(pConfig->rocm_config.rocm_usescases) == 0)
        {
            ret &= false;
        }
    }

    if (pConfig->driver_config.install_driver)
    {
        if (strlen(pConfig->rocm_config.rocm_versions) == 0)
        {
            ret &= false;
        }
    }
    
    return ret;
}

// checks if specific option hasn't been filled by the user
bool is_repo_public_opt_missing(OFFLINE_INSTALL_CONFIG *pConfig, char *opt)
{
    bool ret = false;

    if ( (strcmp(opt, "ROCm Version") == 0) && pConfig->rocm_config.install_rocm)
    {
        ret |= (strlen(pConfig->rocm_config.rocm_versions) == 0);
    }

    if ( (strcmp(opt, "amdgpu Driver ROCm Version") == 0) && pConfig->driver_config.install_driver)
    {
        ret |= (strlen(pConfig->rocm_config.rocm_versions) == 0);
    }

    return ret;
}

bool is_miscellaneous_prereqs_fulfilled(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    bool ret = true;

    // Check if a valid installer location is set
    if (!pConfig->create_confg.is_installer_loc_valid)
    {
        ret &= false;
    }

    // Check that either rocm or the driver is being installed
    if (!pConfig->rocm_config.install_rocm && !pConfig->driver_config.install_driver)
    {
        ret &= false;
    }

    return ret;
}

bool is_miscellaneous_opt_missing(OFFLINE_INSTALL_CONFIG *pConfig, char *opt)
{
    // if installing rocm, check that a usecase is set
    if ( (strcmp(opt, "ROCm Components") == 0) && (pConfig->rocm_config.install_rocm) )
    {   
        return (strlen(pConfig->rocm_config.rocm_usescases) == 0) ? true : false;
    }

    return false;
}

bool is_opt_valid(OFFLINE_INSTALL_CONFIG *pConfig, char *opt)
{
    if (strcmp(opt, "Installer Path") == 0)
    {
        if (!pConfig->create_confg.is_installer_loc_valid)
        {
            return false;
        }
    }

    return true;
}

int draw_target_option_summary_page(MENU_DATA *pMenuData)
{
    int starty = COLS_SUMMARY_MENU_STARTY;
    WINDOW *pMenuSubWindow = pMenuData->pMenuSubWindow;
    OFFLINE_INSTALL_CONFIG *pOfflineConfigs = pMenuData->pConfig;
    UNUSED(pOfflineConfigs);

    wattron(pMenuSubWindow, A_BOLD);
    mvwprintw(pMenuSubWindow, starty, COL1_SUMMARY_MENU_OP_STARTX, "%s", "Target Installer");
    wattroff(pMenuSubWindow, A_BOLD);
    char *distroName = calloc(1, sizeof(pOfflineConfigs->distroName) + sizeof(pOfflineConfigs->kernelVersion) + 4);
    sprintf(distroName, "%s : %s", pOfflineConfigs->distroName, pOfflineConfigs->kernelVersion);
    starty = print_multiline_string(pMenuSubWindow, distroName, COL2_SUMMARY_MENU_VALUE_STARTX, starty, COL2_SUMMARY_MENU_VALUE_WIDTH);

    starty += 1;
    return starty;
}

void draw_page_number(MENU_DATA *pMenuData)
{
    mvwprintw(pMenuData->pMenuWindow, SUMMARY_MENU_ITEM_START_Y, SUMMARY_PAGE_NUM_STARTX, "Page %d/3", pMenuData->currentSummaryPageIndex + 1);
}

int draw_create_config_summary_page(MENU_DATA *pMenuData)
{
    int starty;
    WINDOW *pMenuSubWindow = pMenuData->pMenuSubWindow;
    OFFLINE_INSTALL_CONFIG *pOfflineConfigs = pMenuData->pConfig;

    wclear(pMenuData->pMenuSubWindow);

    // Target Installer
    targetSystemInfoValues[0] = pOfflineConfigs->distroName;
    targetSystemInfoValues[1] = pOfflineConfigs->kernelVersion;
    starty = print_sub_menu_summary_options(pMenuData,pMenuSubWindow,targetSystemInfoOps, "Target Installer", targetSystemInfoValues, COL1_SUMMARY_MENU_OP_STARTX, COLS_SUMMARY_MENU_STARTY, COL2_SUMMARY_MENU_VALUE_STARTX, COL2_SUMMARY_MENU_VALUE_WIDTH);
    
    // Create Configuration
    summaryConfigValues[0] = createMenuInstallTypes[pOfflineConfigs->installerType].installer_input;
    summaryConfigValues[1] = createMenuRepoTypes[pOfflineConfigs->installerRepoType].repo_name;
    summaryConfigValues[2] = createMenuDLTypes[pOfflineConfigs->create_confg.currentInstallDLType].download_dep_name;
    summaryConfigValues[3] = pOfflineConfigs->create_confg.installer_name_with_extension;
    summaryConfigValues[4] = pOfflineConfigs->create_confg.installer_out_location;


    // Add a line between target installer and create configration info
    starty++;

    int endy = print_sub_menu_summary_options(pMenuData,pMenuSubWindow,summaryConfigOps, "Create Configuration", summaryConfigValues, COL1_SUMMARY_MENU_OP_STARTX, starty, COL2_SUMMARY_MENU_VALUE_STARTX, COL2_SUMMARY_MENU_VALUE_WIDTH);
    draw_page_number(pMenuData);

    wrefresh(pMenuData->pMenuSubWindow);
    return endy;
}

void draw_driver_summary_page(MENU_DATA *pMenuData)
{
    int starty = COLS_SUMMARY_MENU_STARTY;
    WINDOW *pMenuSubWindow = pMenuData->pMenuSubWindow;
    OFFLINE_INSTALL_CONFIG *pOfflineConfigs = pMenuData->pConfig;

    wclear(pMenuData->pMenuSubWindow);

    // Driver
    summaryDriverValues[0] = bool_to_yes_no(pOfflineConfigs->driver_config.install_driver);
    if (pOfflineConfigs->driver_config.install_driver)
    {
        summaryDriverValues[1] = pOfflineConfigs->rocm_config.rocm_versions;
    }
    else
    {
        summaryDriverValues[1] = "N/A";
    }
    summaryDriverValues[2] = bool_to_yes_no(pOfflineConfigs->driver_config.set_group);
    summaryDriverValues[3] = bool_to_yes_no(pOfflineConfigs->driver_config.blacklist_driver);
    summaryDriverValues[4] = bool_to_yes_no(pOfflineConfigs->driver_config.start_driver);
    
    print_sub_menu_summary_options(pMenuData, pMenuSubWindow,summaryDriverOps, "Driver", summaryDriverValues, COL1_SUMMARY_MENU_OP_STARTX, starty, COL2_SUMMARY_DRIVER_MENU_VALUE_STARTX, COL2_SUMMARY_DRIVIER_MENU_VALUE_WIDTH);
    draw_page_number(pMenuData);

    wrefresh(pMenuData->pMenuSubWindow);
}

void draw_rocm_and_extras_summary_page(MENU_DATA *pMenuData)
{
    int starty = COLS_SUMMARY_MENU_STARTY;
    WINDOW *pMenuSubWindow = pMenuData->pMenuSubWindow;
    OFFLINE_INSTALL_CONFIG *pOfflineConfigs = pMenuData->pConfig;

    wclear(pMenuData->pMenuSubWindow);
    
    // ROCm
    if (is_repo_public(pMenuData))
    {
        summaryRocmOps[0] = "ROCm Version";
        if (pOfflineConfigs->rocm_config.install_rocm)
        {
            summaryRocmValues[0] = pOfflineConfigs->rocm_config.rocm_versions;
        }
        else
        {
            summaryRocmValues[0] = "N/A";
        }
    } 
    else
    {
        summaryRocmValues[0] = "N/A";
        summaryRocmOps[0] = "ROCm Version";
    }

    if (pOfflineConfigs->rocm_config.install_rocm)
    {
        summaryRocmValues[1] = pOfflineConfigs->rocm_config.rocm_usescases;
    }
    else
    {
        summaryRocmValues[1] = "N/A";
    }

    starty = print_sub_menu_summary_options(pMenuData, pMenuSubWindow,summaryRocmOps, "ROCm", summaryRocmValues, COL1_SUMMARY_MENU_OP_STARTX, starty, COL2_SUMMARY_MENU_VALUE_STARTX, COL2_SUMMARY_MENU_VALUE_WIDTH);

    starty += 2;

    // Extra
    summaryExtraValues[0] = bool_to_yes_no(pOfflineConfigs->extras_config.rocminfo_install);
    summaryExtraValues[1] = bool_to_yes_no(pOfflineConfigs->extras_config.rocmsmi_install);
    
    print_sub_menu_summary_options(pMenuData, pMenuSubWindow,summaryExtraOps, "Extra", summaryExtraValues, COL1_SUMMARY_MENU_OP_STARTX, starty, COL2_SUMMARY_MENU_VALUE_STARTX, COL2_SUMMARY_MENU_VALUE_WIDTH);
    draw_page_number(pMenuData);

    wrefresh(pMenuData->pMenuSubWindow);
} 

void draw_summary_page(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    int currentMenuOptIndex = pMenuData->currentSummaryPageIndex;

    resize_and_reposition_summary_subwindow(pMenuData);
    
    if (currentMenuOptIndex == 0)
    {
        draw_create_config_summary_page(pMenuData);
    }
    else if (currentMenuOptIndex == 1)
    {
        draw_rocm_and_extras_summary_page(pMenuData);
    }
    else if (currentMenuOptIndex == 2)
    {
        draw_driver_summary_page(pMenuData);
    }

    if (!pConfig->rocm_config.install_rocm && !pConfig->driver_config.install_driver)
    {
        print_menu_err_msg(pMenuData, "No ROCm or Driver install selected");
    }
}

char* bool_to_yes_no(bool value)
{
    return value ? "yes" : "no";
}

 // process "ENTER" key events from the Create Offline Installer menu
void process_summary_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    ITEM *pCurrentItem = current_item(pMenu);
    int curMenuItemIndex = item_index(pCurrentItem);
    
    if (curMenuItemIndex == pMenuData->itemList->createOfflineInstallerItemIndex)
    {
        pMenuData->isCreateInstaller = true;
    }
    // Next Page
    else if (curMenuItemIndex == 0 )
    {
        draw_next_page(pMenuData);
    }
}

void summary_menu_update_state(MENU_DATA *pMenuData)
{
    bool all_prereqs_met = true;
    int numItems = pMenuData->itemList->numItems;

    if (!is_miscellaneous_prereqs_fulfilled(pMenuData))
    {
        all_prereqs_met = false;
    }
    // Check for updates to the current installer type
    else if (is_repo_public(pMenuData) && !is_repo_public_prereqs_fulfilled(pMenuData))
    {
        all_prereqs_met = false;
    }
    // Set status of <ACCEPT> button to all_prepreqs_met
    menu_set_item_select(pMenuData, numItems - 2, all_prereqs_met);
}

void process_summary_item(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    ITEM *pCurrentItem = current_item(pMenu);
    int numItems = pMenuData->itemList->numItems;

    DEBUG_UI_MSG(pMenuData, "item userptr: item index %d", item_index(pCurrentItem));

    if (item_index(pCurrentItem) == numItems - 3)
    {
        // set "RETURN" to red
        set_menu_fore(pMenuData->pMenu, COLOR_PAIR(6));
    }
    else if (item_index(pCurrentItem) == numItems - 2)
    {
        // set "ACCEPT" to green
        set_menu_fore(pMenuData->pMenu, COLOR_PAIR(4) | A_REVERSE);
    }
    else
    {
        // highlight <NEXT PAGE> and <PREV PAGE> bold
        set_menu_fore(pMenuData->pMenu, COLOR_PAIR(3) | A_BOLD);
    }
}

void draw_next_page(MENU_DATA *pMenuData)
{   
    int currentSummaryPageIndex = pMenuData->currentSummaryPageIndex;
    
    if (currentSummaryPageIndex == 2)
    {
        // go back to the first page
        currentSummaryPageIndex = 0;
    }
    else
    {
        currentSummaryPageIndex++;
    }

    pMenuData->currentSummaryPageIndex = currentSummaryPageIndex;
    switch(currentSummaryPageIndex)
    {
        case 0:
            draw_create_config_summary_page(pMenuData);
            break;
        case 1:
            draw_rocm_and_extras_summary_page(pMenuData);
            break;
        case 2:
            draw_driver_summary_page(pMenuData);
            break;
    }
}

void draw_prev_page(MENU_DATA *pMenuData)
{   
    int currentSummaryPageIndex = pMenuData->currentSummaryPageIndex;
    
    if (currentSummaryPageIndex == 0)
    {
        return;
    }
    else
    {
        currentSummaryPageIndex--;
        pMenuData->currentSummaryPageIndex = currentSummaryPageIndex;
        if (currentSummaryPageIndex == 0)
        {
            draw_create_config_summary_page(pMenuData);
        }
        else if (currentSummaryPageIndex == 1)
        {
            draw_rocm_and_extras_summary_page(pMenuData);
        }
    }
}

void resize_and_reposition_summary_subwindow(MENU_DATA *pMenuData)
{
    WINDOW *pMenuSubWindow = pMenuData->pMenuSubWindow;
    wresize(pMenuSubWindow, SUMMARY_SUBWIN_NUM_LINES, SUMMARY_SUBWIN_WIDTH_COLS);
    mvderwin(pMenuSubWindow, SUMMARY_SUBWIN_START_Y, SUMMARY_SUBWIN_START_X);
}
