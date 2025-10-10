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
#include "extras_menu.h"
#include "help_menu.h"


// Extras Menu Setup
char *extrasMenuOps[] = {
    "rocminfo",
    "rocm-smi",
    "amd-smi",
    "rocm-validation-suite",
    "rocdecode",
    "rocjpeg",
    "rdc",
    SKIPPABLE_MENU_ITEM,
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *extrasMenuDesc[] = {
    "Add rocminfo as extra installer package",
    "Add rocm-smi as extra installer package",
    "Add amd-smi as extra installer package",
    "Add rocm-validation-suite as extra installer package",
    "Add rocdecode as extra installer package",
    "Add rocjpeg as extra installer package",
    "Add rdc as extra installer package",
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
    "amd-smi",
    "rocm-validation-suite",
    "rocdecode",
    "rocjpeg",
    "rdc",
    SKIPPABLE_MENU_ITEM,
    (char*)NULL,
};

char *extrasMenuHelpDesc[] = {
    "rocminfo gives information about the HSA system        attributes and agents.",
    "rocm-smi acts as a command line interface for          manipulating and monitoring the amdgpu kernel.",
    "amd-smi (AMD System Management Interface)              library offers a unified tool for managing and monitoring GPUs, particularly in high-performance computing environments.",
    "rocm-validation-suite is a tool for validation         of ROCm.",
    "rocdecode is a high performance video decode           SDK for AMD GPUs.",
    "rocjpeg is a high performance JPEG decode              SDK for AMD GPUs.",
    "rdc (ROCM Data Center Tool) simplifies                 administration ",
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

MENU_DATA menuHelpExtras = {0};

void process_extras_menu(MENU_DATA *pMenuData);

void process_extras_menu_item(MENU_DATA *pMenuData);

void process_extras_help_menu(MENU_DATA *pMenuData);

// sub-menus
void create_extras_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// menu draw
void extras_menu_draw(MENU_DATA *pMenuData);

bool is_rocdecode_supported(MENU_DATA *pMenuData);
bool is_rocjpeg_supported(MENU_DATA *pMenuData);

void create_extras_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    // Create the Main Extras options menu
    create_menu(pMenuData, pMenuWindow, &extrasMenuProps, &extrasMenuItems, pConfig);

    // create verbose help menu
    create_extras_help_menu_window(&menuHelpExtras, pMenuWindow);

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = extras_menu_draw;

    ITEM **items = menu_items(pMenuData->pMenu);

    // function that will draw scrollable help menu
    set_item_userptr(items[pMenuData->itemList[0].helpItemIndex], process_extras_help_menu);

    // Set user pointers for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_extras_menu);

    // Set user pointers for arrow up and down events
    set_item_userptr(items[EXTRAS_MENU_ITEM_ROCDECODE_INDEX], process_extras_menu_item);
    set_item_userptr(items[EXTRAS_MENU_ITEM_ROCJPEG_INDEX], process_extras_menu_item);

    menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_INDEX, is_rocdecode_supported(pMenuData));
    menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_INDEX, is_rocjpeg_supported(pMenuData));

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

    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMINFO_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocmsmi_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_AMDSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->amdsmi_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RVS_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocm_validation_suite_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocdecode_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocjpeg_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RDC_ROW, EXTRAS_MENU_FORM_COL, pConfig->rdc_install);

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
        pConfig->amdsmi_install = true;
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCMINFO_INDEX, false);
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCMSMI_INDEX, false);
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_AMDSMI_INDEX, false);
    }
    else if (pRocmConfig->is_rocm_usecase_deselected)
    {
        pConfig->rocminfo_install = false;
        pConfig->rocmsmi_install = false;
        pConfig->amdsmi_install = false;
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCMINFO_INDEX, true);
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCMSMI_INDEX, true);
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_AMDSMI_INDEX, true);

        // Need to reset back to false
        pRocmConfig->is_rocm_usecase_deselected = false;
    }
    
    // check for rvs support (6.0+)
    if ( strcmp(pRocmConfig->rocm_versions, "5.7.3") == 0 )
    {
        pConfig->rocm_validation_suite_install = false;
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_RVS_INDEX, false);
    }
    else
    {
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_RVS_INDEX, true);
    }

    if (is_rocdecode_supported(pMenuData))
    {
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_INDEX, true);
        clear_menu_err_msg(pMenuData);
    }
    else
    {
        pConfig->rocdecode_install = false;
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_INDEX, false);
    }

    if (is_rocjpeg_supported(pMenuData))
    {
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_INDEX, true);
        clear_menu_err_msg(pMenuData);
    }
    else
    {
        pConfig->rocjpeg_install = false;
        menu_set_item_select(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_INDEX, false);
    }

    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMINFO_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocmsmi_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_AMDSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->amdsmi_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RVS_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocm_validation_suite_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocdecode_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocjpeg_install);
    menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RDC_ROW, EXTRAS_MENU_FORM_COL, pConfig->rdc_install);
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

void process_extras_help_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    unpost_menu(pMenu);

    // draw help menu window and borders
    wclear(menuHelpExtras.pMenuWindow);
    menu_draw(&menuHelpExtras);

    int is_error_reading_verbose_help_file = display_help_scroll_window(&menuHelpExtras, "./rocm_menus/extras_help.txt");
    if (is_error_reading_verbose_help_file == -1)
    {
        wgetch(pMenuData->pMenuWindow);
    }

    // Clear window before redrawing extras menu.
    wclear(pMenuData->pMenuWindow);
    // Show the extras menu right after user exits from the help menu
    extras_menu_draw(pMenuData);
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
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMINFO_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocminfo_install);
        }
        else if (index == 1)
        {
            pConfig->rocmsmi_install = !pConfig->rocmsmi_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCMSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocmsmi_install);
        }
        else if (index == 2)
        {
            pConfig->amdsmi_install = !pConfig->amdsmi_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_AMDSMI_ROW, EXTRAS_MENU_FORM_COL, pConfig->amdsmi_install);
        }
        else if (index == 3)
        {
            pConfig->rocm_validation_suite_install = !pConfig->rocm_validation_suite_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RVS_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocm_validation_suite_install);
        }
        else if (index == 4) 
        {
            pConfig->rocdecode_install = !pConfig->rocdecode_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCDECODE_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocdecode_install);

        }
        else if (index == 5)
        {
            pConfig->rocjpeg_install = !pConfig->rocjpeg_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_ROCJPEG_ROW, EXTRAS_MENU_FORM_COL, pConfig->rocjpeg_install);
        }
        else if (index == 6)
        {
            pConfig->rdc_install = !pConfig->rdc_install;
            menu_info_draw_bool(pMenuData, EXTRAS_MENU_ITEM_RDC_ROW, EXTRAS_MENU_FORM_COL, pConfig->rdc_install);

        }
    }

    extras_menu_draw(pMenuData);
}

void create_extras_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{    
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &extrasMenuHelpProps, &extrasMenuHelpItems, NULL);
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);
}

// only supported on rocm 6.1+
bool is_rocdecode_supported(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;

    
    return strcmp(pRocmConfig->rocm_versions, "6.1") >= 0;
}

// only supported on rocm 6.3+
bool is_rocjpeg_supported(MENU_DATA *pMenuData)
{
    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    ROCM_MENU_CONFIG *pRocmConfig = &pConfig->rocm_config;


    return strcmp(pRocmConfig->rocm_versions, "6.3") >= 0;
}

void process_extras_menu_item(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    ITEM *pCurrentItem = current_item(pMenu);
    int curMenuItemIndex = item_index(pCurrentItem);

    if (curMenuItemIndex == EXTRAS_MENU_ITEM_ROCDECODE_INDEX)
    {
        if (!is_rocdecode_supported(pMenuData))
        {
            print_menu_warning_msg(pMenuData, WARN_ERR_START_Y, WARN_ERR_START_X, "rocdecode only supported on ROCm 6.1+");
        }
    }
    else if (curMenuItemIndex == EXTRAS_MENU_ITEM_ROCJPEG_INDEX)
    {
        if (!is_rocjpeg_supported(pMenuData))
        {
            print_menu_warning_msg(pMenuData, WARN_ERR_START_Y, WARN_ERR_START_X, "rocjpeg only supported on ROCm 6.3+");
        }
    }
}
