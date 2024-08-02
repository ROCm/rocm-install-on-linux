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
#include "create_menu.h"
#include "help_menu.h"
#include "utils.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


// Create Config Menu Setup
char *createMenuOps[] = {
    "Installer Input",
    "Repo Type",
    " ",
    "Dependency Download Type",
    " ",
    "Installer Name",
    "Installer Path",
    " ",
    "<HELP>",
    "<DONE>",
    (char*)NULL,
};

char *createMenuDesc[] = {
    CREATE_MENU_ITEM_INSTALLER_INPUT_PUBLIC_DESC,
    "Repository URL used for sourcing packages.",
    " ",
    CREATE_MENU_ITEM_DEP_DOWNLOAD_FULL_DESC,
    " ",
    "Output name for the created offline installer. A .run extension will be added to   the filename.",
    "Output location for the created offline installer",
    " ",
    DEFAULT_VERBOSE_HELP_WINDOW_MSG,
    "Exit to Main Menu",
    (char*)NULL,
};

MENU_PROP createMenuProps = {
    .pMenuTitle = "Create Install Options",
    .pMenuControlMsg = "<DONE> to exit : Enter key to select/toggle",
    .numLines = ARRAY_SIZE(createMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = CREATE_MENU_ITEM_START_Y,
    .startx = CREATE_MENU_ITEM_START_X, 
    .numItems = ARRAY_SIZE(createMenuOps)
};

ITEMLIST_PARAMS createMenuItems = {
    .numItems           = (ARRAY_SIZE(createMenuOps)),
    .pItemListTitle     = "Installer Create Settings:",
    .pItemListChoices   = createMenuOps,
    .pItemListDesp      = createMenuDesc
};

INSTALL_TYPE_PROP createMenuInstallTypes[eINSTALL_TYPE_MAX] = {
    { .installer_input_type = eINSTALL_TYPE_REPO_PUBLIC,   .installer_input = "repo-public"},
};

INSTALL_DL_PROP createMenuDLTypes[eDL_TYPE_MAX] = {
    { .download_dep_type = eDL_TYPE_FULL, .download_dep_name = "full"},
    { .download_dep_type = eDL_TYPE_MIN,   .download_dep_name = "minimum"}
};

INSTALL_REPO_PROP createMenuRepoTypes[eREPO_TYPE_MAX] = {
    { .repo_type = eREPO_TYPE_RADEON,           .repo_name = "repo.radeon.com"},
};

// verbose help menu variables
// Spaces added/deleted from HelpOps and HelpDesc to ensure whole words aren't
// cut off between lines when displaying help menu.
char *createMenuHelpOps[] = {
    "Installer Input",
    "Repo Type",
    "Dependency       Download Type",
    "Installer Name",
    "Installer Path",
    "",
    (char *)NULL
};

char *createMenuHelpDesc[] = {
    "repo-public provides packages from repo.radeon.com.",
    "Repository URL used for sourcing packages.",
    "Mode of how package dependencies are downloaded.       'full' recursively downloads package dependencies      regardless of the current packages installed on the    host system. 'minimum' downloads package dependencies  based on the current host configuration. Minimum       assumes the host = target system for offline install.",
    "Output name for the created offline installer.",
    "Output location for the created offline installer.",
    "",
    (char*)NULL,
};

MENU_PROP createMenuHelpProps = {
    .pMenuTitle = "Create Install Options Help",
    .pMenuControlMsg = DEFAULT_VERBOSE_HELP_CONTROL_MSG,
    .numLines = 0,
    .numCols = MAX_MENU_ITEM_COLS,
    .starty = CREATE_MENU_ITEM_START_Y,
    .startx = CREATE_MENU_ITEM_START_X, 
    .numItems = 0
};


ITEMLIST_PARAMS createMenuHelpItems = {
    .numItems           = 0,
    .pItemListTitle     = "Installer Create Settings Description:",
    .pItemListChoices   = NULL,
    .pItemListDesp      = NULL
};

void process_create_menu(MENU_DATA *pMenuData);
void process_create_menu_item(MENU_DATA *pMenuData);

// sub-menus
void create_config_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow);

// forms
void process_create_menu_form(MENU_DATA *pMenuData, int fieldNum);

// menu draw/config
char *get_home_directory();
void create_menu_toggle_grey_items(MENU_DATA *pMenuData, bool enable);
void create_menu_draw(MENU_DATA *pMenuData);


void create_config_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig)
{
    CREATE_MENU_CONFIG *pCreateConfig = &pConfig->create_confg;

    // create verbose help menu
    pMenuData->pHelpMenu = calloc(1, sizeof(MENU_DATA));
    if (pMenuData->pHelpMenu)
    {
        create_config_help_menu_window(pMenuData->pHelpMenu, pMenuWindow);
    }

    // Create the Main create options menu
    create_menu(pMenuData, pMenuWindow, &createMenuProps, &createMenuItems, pConfig);

    // Set pointer to draw menu function when window is resized
    pMenuData->drawMenuFunc = create_menu_draw;

    // Set user pointer for 'ENTER' events
    set_menu_userptr(pMenuData->pMenu, process_create_menu);

    // Initialize the menu config settings
    pConfig->installerRepoType = eREPO_TYPE_RADEON;
    pCreateConfig->currentInstallDLType = eDL_TYPE_FULL;
    sprintf(pCreateConfig->installer_name, "%s", CREATE_MENU_DEFAULT_INSTALLER_NAME);
    sprintf(pCreateConfig->installer_name_with_extension, "%s.run", CREATE_MENU_DEFAULT_INSTALLER_NAME);

    sprintf(pCreateConfig->installer_out_location, "%s", get_home_directory());
    pCreateConfig->is_installer_loc_valid = true;   // home directory is valid

    ITEM **items = menu_items(pMenuData->pMenu);
    // Prints item description for option user selects for dependency download type
    set_item_userptr(items[CREATE_MENU_ITEM_DEP_DOWNLOAD_INDEX], process_create_menu_item);    
   
    // set items to non-selectable
    set_menu_grey(pMenuData->pMenu, COLOR_PAIR(5));
    menu_set_item_select(pMenuData, CREATE_MENU_ITEM_INSTALLER_INPUT_INDEX, false);  // installer input
    menu_set_item_select(pMenuData, CREATE_MENU_ITEM_REPO_TYPE_INDEX, false);  // repo
    menu_set_item_select(pMenuData, 2, false);  // space after repo
    menu_set_item_select(pMenuData, 4, false);  // space after dep
    menu_set_item_select(pMenuData, pMenuData->itemList[0].numItems - 4, false);  // space before <HELP>

    // create a form for user input
    create_form(pMenuData, pMenuWindow, CREATE_MENU_NUM_FORM_FIELDS, CREATE_MENU_FORM_FIELD_WIDTH, CREATE_MENU_FORM_FIELD_HEIGHT, 
            CREATE_MENU_FORM_ROW, CREATE_MENU_FORM_COL);

    strcpy(pMenuData->pFormList.formControlMsg, DEFAULT_FORM_CONTROL_MSG);

    // Initialize form field names and associated config settings
    set_form_userptr(pMenuData->pFormList.pForm, process_create_menu_form);

    set_field_buffer(pMenuData->pFormList.field[0], 0, CREATE_MENU_DEFAULT_INSTALLER_NAME);
    set_field_buffer(pMenuData->pFormList.field[1], 0, pCreateConfig->installer_out_location);
    
}

void destroy_config_menu_window(MENU_DATA *pMenuData)
{
    destroy_help_menu(pMenuData->pHelpMenu);
    destroy_menu(pMenuData);
}

void create_menu_draw(MENU_DATA *pMenuData)
{
    WINDOW *pMenuWindow = pMenuData->pMenuWindow;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    CREATE_MENU_CONFIG *pCreateConfig = &pConfig->create_confg;

    char drawName[256];

    // draw the installer input type/repo
    wmove(pMenuWindow, CREATE_MENU_ITEM_INSTALLER_INPUT_ROW, CREATE_MENU_FORM_COL);
    wclrtoeol(pMenuWindow);
    wattron(pMenuWindow, COLOR_PAIR(4));
    mvwprintw(pMenuWindow, CREATE_MENU_ITEM_INSTALLER_INPUT_ROW, CREATE_MENU_FORM_COL, "%s", createMenuInstallTypes[pConfig->installerType].installer_input);
    wattroff(pMenuWindow, COLOR_PAIR(4));
    
    // draw the repo type
    wmove(pMenuWindow, CREATE_MENU_ITEM_REPO_TYPE_ROW, CREATE_MENU_FORM_COL);
    wclrtoeol(pMenuWindow);
    wattron(pMenuWindow, COLOR_PAIR(4));
    mvwprintw(pMenuWindow, CREATE_MENU_ITEM_REPO_TYPE_ROW, CREATE_MENU_FORM_COL, "%s", createMenuRepoTypes[pConfig->installerRepoType].repo_name);
    wattroff(pMenuWindow, COLOR_PAIR(4));

    field_trim(pCreateConfig->installer_name, drawName, CREATE_MENU_FORM_FIELD_WIDTH);
    mvwprintw(pMenuWindow, CREATE_MENU_FORM_ROW,  CREATE_MENU_FORM_COL, "%s", drawName);

    field_trim(pCreateConfig->installer_out_location, drawName, CREATE_MENU_FORM_FIELD_WIDTH);
    if (pCreateConfig->is_installer_loc_valid)
    {
        mvwprintw(pMenuWindow, CREATE_MENU_FORM_ROW+1, CREATE_MENU_FORM_COL, "%s", drawName);
    }
    else
    {
        wattron(pMenuWindow, COLOR_PAIR(1));
        mvwprintw(pMenuWindow, CREATE_MENU_FORM_ROW+1, CREATE_MENU_FORM_COL, "%s", drawName);
        wattroff(pMenuWindow, COLOR_PAIR(1));
    }

    {
        wmove(pMenuWindow, CREATE_MENU_FORM_ROW+2, CREATE_MENU_FORM_COL);
        wclrtoeol(pMenuWindow);
    }

    // draw the installer dependency download type
    wmove(pMenuWindow, CREATE_MENU_ITEM_DEP_DOWNLOAD_ROW, CREATE_MENU_FORM_COL);
    wclrtoeol(pMenuWindow);
    wattron(pMenuWindow, COLOR_PAIR(4));
    mvwprintw(pMenuWindow, CREATE_MENU_ITEM_DEP_DOWNLOAD_ROW, CREATE_MENU_FORM_COL, "%s", createMenuDLTypes[pCreateConfig->currentInstallDLType].download_dep_name);
    wattroff(pMenuWindow, COLOR_PAIR(4));

    // draw the main create menu
    menu_draw(pMenuData);
}

char *get_home_directory()
{
    char *homeDir = getenv("HOME");

    if (homeDir == NULL) 
    {
        homeDir = getpwuid(getuid())->pw_dir;
    }

    return homeDir;
}

void create_menu_toggle_grey_items(MENU_DATA *pMenuData, bool enable)
{
    UNUSED(pMenuData);
    UNUSED(enable);
}

void create_menu_update_state(MENU_DATA *pMenuData)
{
    // Check global state and update the create menu
    UNUSED(pMenuData);
}

void do_create_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    // draw the create menu contents
    create_menu_draw(pMenuData);

    // create menu loop
    menu_loop(pMenuData);

    unpost_menu(pMenu);
}

// process "ENTER" key events from the Create configuration main menu
void process_create_menu(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;
    FORM *pForm = pMenuData->pFormList.pForm;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    CREATE_MENU_CONFIG *pCreateConfig = &pConfig->create_confg;

    ITEM *pCurrentItem = current_item(pMenu);
    int curMenuItemIndex = item_index(pCurrentItem);
    int curFormFieldIndex = 0;

    void (*ptrFormFnc)(MENU_DATA*, int);

    DEBUG_UI_MSG(pMenuData, "create menu: item %d", curMenuItemIndex);

    if (pForm)
    {
        ptrFormFnc = form_userptr(pForm);
    }

    if (curMenuItemIndex == CREATE_MENU_ITEM_INSTALLER_INPUT_INDEX)
    {
        // toggle the install input type
        pConfig->installerType++;
        if (pConfig->installerType == eINSTALL_TYPE_MAX) pConfig->installerType = eINSTALL_TYPE_REPO_PUBLIC;

        // state change to the config
        pConfig->configChg = true;
        
        create_menu_toggle_grey_items(pMenuData, false);
    }
    else if (curMenuItemIndex == CREATE_MENU_ITEM_REPO_TYPE_INDEX)
    {
    }
    // dependency download type
    else if (curMenuItemIndex == CREATE_MENU_ITEM_DEP_DOWNLOAD_INDEX)
    {
        // toggle the install input type
        pCreateConfig->currentInstallDLType++;
        if (pCreateConfig->currentInstallDLType == eDL_TYPE_MAX) pCreateConfig->currentInstallDLType = eDL_TYPE_FULL;
    }
    else if (curMenuItemIndex >= CREATE_MENU_ITEM_INSTALLER_NAME_INDEX && curMenuItemIndex <= CREATE_MENU_ITEM_TARBALL_INDEX )
    {
        if (curMenuItemIndex == CREATE_MENU_ITEM_TARBALL_INDEX)
        {
            return;
        }

        curFormFieldIndex = curMenuItemIndex - 5;

        // switch to the create menu field for installer name
        unpost_menu(pMenu);

        if (NULL != ptrFormFnc)
        {
            ptrFormFnc((MENU_DATA*)pMenuData, curFormFieldIndex);
        }
    }
    else
    {

    }
    
    create_menu_draw(pMenuData);
}

void process_create_menu_item(MENU_DATA *pMenuData)
{
    MENU *pMenu = pMenuData->pMenu;

    OFFLINE_INSTALL_CONFIG *pConfig = pMenuData->pConfig;
    CREATE_MENU_CONFIG *pCreateConfig = &pConfig->create_confg;

    ITEM *pCurrentItem = current_item(pMenu);
    int curMenuItemIndex = item_index(pCurrentItem);

    // installer input
    if (curMenuItemIndex == 0)
    {
        if (pConfig->installerType == eINSTALL_TYPE_REPO_PUBLIC) {
            print_menu_item_selection_opt(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X, CREATE_MENU_ITEM_INSTALLER_INPUT_PUBLIC_DESC);
        }
    }

     // dependency download type
    else if (curMenuItemIndex == 3)
    {
        if (pCreateConfig->currentInstallDLType == eDL_TYPE_FULL)
        {
            print_menu_item_selection_opt(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X, CREATE_MENU_ITEM_DEP_DOWNLOAD_FULL_DESC);
        }
        else if (pCreateConfig->currentInstallDLType == eDL_TYPE_MIN)
        {
            print_menu_item_selection_opt(pMenuData, MENU_SEL_START_Y, MENU_SEL_START_X, CREATE_MENU_ITEM_DEP_DOWNLOAD_MIN_DESC);
        }
    }
}

// process "ENTER" key event from menu if form userptr set
void process_create_menu_form(MENU_DATA *pMenuData, int fieldNum)
{
    MENU *pMenu = pMenuData->pMenu;
    FORM *pForm = pMenuData->pFormList.pForm;

    CREATE_MENU_CONFIG *pConfig = &(pMenuData->pConfig)->create_confg;

    // show only the required field and set it to current
    set_current_field(pForm, pMenuData->pFormList.field[fieldNum]);

    post_form(pForm);
    post_menu(pMenu);

    create_menu_draw(pMenuData);
    print_form_control_msg(pMenuData);

    // Switch to form control loop for entering data into given form field
    form_loop(pMenuData, false);

    unpost_form(pForm);
    unpost_menu(pMenu);

    // Store the installer params on exit
    if (fieldNum == 0)
    {
        strcpy(pConfig->installer_name, field_buffer(pForm->field[0], 0));
        clear_str(pConfig->installer_name_with_extension);
        size_t end = 0;
        for (size_t i = strlen(pConfig->installer_name) - 1; i > 0 ; i--)
        {
            char c = pConfig->installer_name[i];
            // Once we hit a space, we know we're at the end
            if (c != ' ')
            {
                // print_menu_dbg_msg(pMenuData, "Value of c: %c, index is : %d", c, i);
                end = i;
                break;
                
            }
            //pConfig->installer_name_with_extension[i] = c;
        }
        // end is the index at which we first find a non space character but we
        // have to add 1 because indices start from 0 but size_t param for strncpy
        // starts at 1.
        strncpy(pConfig->installer_name_with_extension, pConfig->installer_name, end + 1);
        //print_menu_dbg_msg(pMenuData, "Value of end: %d and string before run: %s", end, pConfig->installer_name_with_extension);
        strcat(pConfig->installer_name_with_extension, ".run");
    }
    else if (fieldNum == 1) 
    {
        strcpy(pConfig->installer_out_location, field_buffer(pForm->field[1], 0));

        if (check_path_exists(pConfig->installer_out_location, MAX_FORM_FIELD_WIDTH) == 0)
        {
            wattron(pMenuData->pMenuWindow, COLOR_PAIR(4));
            mvwprintw(pMenuData->pMenuWindow, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, "* Valid Path  ");
            wattroff(pMenuData->pMenuWindow, COLOR_PAIR(4));

            pConfig->is_installer_loc_valid = true;
        }
        else
        {
            wattron(pMenuData->pMenuWindow, COLOR_PAIR(1));
            mvwprintw(pMenuData->pMenuWindow, DEBUG_ERR_START_Y, DEBUG_ERR_START_X, "* Invalid Path  ");
            wattroff(pMenuData->pMenuWindow, COLOR_PAIR(1));

            pConfig->is_installer_loc_valid = false;
        }
    }

    DEBUG_UI_MSG(pMenuData, "length =%ld",(strlen(field_buffer(pForm->field[0], 0))) );
}

void create_config_help_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow)
{
    // Create menu window w/ border and title
    create_menu(pMenuData, pMenuWindow, &createMenuHelpProps, &createMenuHelpItems, NULL);
    menu_opts_off(pMenuData->pMenu, O_SHOWDESC);

    // create form that displays verbose help menu
    create_help_form(pMenuData, pMenuWindow, HELP_MENU_DESC_STARTX, HELP_MENU_DESC_STARTY, HELP_MENU_DESC_WIDTH, HELP_MENU_OP_STARTX, HELP_MENU_OP_WIDTH, createMenuHelpOps, createMenuHelpDesc); 
}
