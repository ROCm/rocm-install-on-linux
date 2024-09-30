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
#include "rocm_menu.h"
#include "driver_menu.h"
#include "extras_menu.h"
#include "summary_menu.h"
#include "config.h"
#include "utils.h"

#include <libgen.h>
#include <sys/utsname.h>
#include <stdio.h>

#define SYSTEM_INFO_CHAR_SIZE                   512

// Structure defining the menus (menu data) objects making up the offline installer UI
typedef struct _OFFLINE_INSTALL_MENUS
{
    MENU_DATA menuMain;
    MENU_DATA menuCreate;
    MENU_DATA menuROCM;
    MENU_DATA menuDriver;
    MENU_DATA menuExtras;
    MENU_DATA menuSummary;
}OFFLINE_INSTALL_MENUS;

typedef struct _ARGS_INFO
{
    char wconfig[DEFAULT_CHAR_SIZE];
    bool isWconfig;
    char createArgs[DEFAULT_CHAR_SIZE];
}ARGS_INFO;

// Main Menu Setup
char *mainMenuOps[] = {
    "Create Configuration",
    SKIPPABLE_MENU_ITEM, 
    "ROCm Options",
    "Driver Options",
    "Extra Packages",
    SKIPPABLE_MENU_ITEM,
    "< CREATE OFFLINE INSTALLER >",
    (char *)NULL,
};

char *mainMenuDesc[] = {
    "Input settings for creating offline installer",
    " ",
    "Set ROCm install options",
    "Set Driver (amdgpu) options",
    "Set Extra packages for installer",
    " ",
    "Create the offline installer",
    (char*)NULL,
};

MENU_PROP mainMenuProperties = {
    .pMenuTitle = "ROCm Offline Installer Creator",
    .pMenuControlMsg = "F1 to exit",
    .numLines = ARRAY_SIZE(mainMenuOps) - 1,
    .numCols = MAX_MENU_ITEM_COLS,
    .startx = 1,
    .starty = 8,
    .numItems = ARRAY_SIZE(mainMenuOps)
};

ITEMLIST_PARAMS mainMenuItems = {
    .numItems           = ARRAY_SIZE(mainMenuOps),
    .pItemListTitle     = "Main Menu",
    .pItemListChoices   = mainMenuOps,
    .pItemListDesp      = mainMenuDesc
};

void get_os_release_value(char *key, char *value) 
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/etc/os-release", "r");
    if (fp == NULL) 
    {
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        if (strstr(line, key) != NULL) 
        {
            if (key[0] == line[0])
            {
                char *p = strchr(line, '=');
                if (p[1] == '\"')
                {
                    strcpy(value, p + 2);
                     value[strlen(value) - 2] = '\0';
                }
                else
                {
                    strcpy(value, p + 1);
                    value[strlen(value) - 1] = '\0';
                }
                break;
            }
        }
    }
    fclose(fp);

    if (line) 
    {
        free(line);
    }
}

int get_os_info(OFFLINE_INSTALL_CONFIG *pConfig)
{
    uint32_t i;
    struct utsname unameData;

    if (uname(&unameData) < 0)
    {
        return -1;
    }
    
    strcpy(pConfig->kernelVersion, unameData.release);

    get_os_release_value("PRETTY_NAME", pConfig->distroName);
    get_os_release_value("ID", pConfig->distroID);
    get_os_release_value("VERSION_ID", pConfig->distroVersion);

    char *debList[] = {"ubuntu", "debian", "linuxmint"};
    char *elList[]  = {"rhel", "rocky", "almalinux", "fedora", "centos"};
    char *sleList[] = {"suse", "opensuse", "sles"};

    for (i = 0; i < ARRAY_SIZE(debList); i++) 
    {
        if (strstr(pConfig->distroID, debList[i]) != NULL) 
        {
            pConfig->distroType = eDISTRO_TYPE_DEB;
        }
    }

    for (i = 0; i < ARRAY_SIZE(elList); i++) 
    {
        if (strstr(pConfig->distroID, elList[i]) != NULL) 
        {
            pConfig->distroType = eDISTRO_TYPE_EL;
        }
    }

    for (i = 0; i < ARRAY_SIZE(sleList); i++) 
    {
        if (strstr(pConfig->distroID, sleList[i]) != NULL) 
        {
            pConfig->distroType = eDISTRO_TYPE_SLE;
        }
    }

    return 0;
}

void main_menu_draw(MENU_DATA *pMenuData, OFFLINE_INSTALL_CONFIG *pConfig)
{   
    char systemInfo[SYSTEM_INFO_CHAR_SIZE] = {0};

    wclear(pMenuData->pMenuWindow);

    // resizes pMenuWindow and subwindow that displays menu items to its original
    // size in case user resized terminal window
    resize_and_reposition_window_and_subwindow(pMenuData, WIN_NUM_LINES, WIN_WIDTH_COLS);

    wattron(pMenuData->pMenuWindow, COLOR_PAIR(9) | A_UNDERLINE);
    mvwprintw(pMenuData->pMenuWindow, ITEM_TITLE_Y, ITEM_TITLE_X, "Target Installer");
    wattroff(pMenuData->pMenuWindow, COLOR_PAIR(9) | A_UNDERLINE);
    
    sprintf(systemInfo, "    OS     : %s\n       Kernel : %s", pConfig->distroName, pConfig->kernelVersion);

    print_menu_title(pMenuData, MENU_TITLE_Y, MENU_TITLE_X, WIN_WIDTH_COLS, "ROCm Offline Installer Creator", COLOR_PAIR(2));
    print_menu_item_title(pMenuData, ITEM_TITLE_Y + 1, ITEM_TITLE_X,  systemInfo, COLOR_PAIR(9));

    print_menu_control_msg(pMenuData);

    print_version(pMenuData);

    box(pMenuData->pMenuWindow, 0, 0);
}

void update_menu_states(OFFLINE_INSTALL_MENUS *pOfflineMenus)
{
    // walk through each offline menu and update the stat
    create_menu_update_state(&pOfflineMenus->menuCreate);

    rocm_menu_update_state(&pOfflineMenus->menuROCM);
    
    driver_menu_update_state(&pOfflineMenus->menuDriver);
    
    extras_menu_update_state(&pOfflineMenus->menuExtras);

    summary_menu_update_state(&pOfflineMenus->menuSummary);
}

void write_offline_configuration(OFFLINE_INSTALL_CONFIG *pConfig, char *wconfig)
{
    int len;

    FILE *file = fopen(wconfig, "w");
    if (file == NULL)  
    {
        // Print an error message to the console if opening the file fails.
        printw("Error opening file for writing\n");
        return;
    }

    // check if driver install is enabled - if so, add to the rocm usecase list
    if (pConfig->driver_config.install_driver)
    {
        len = strlen(pConfig->rocm_config.rocm_usescases);
        if (len)
        {
            strcat(pConfig->rocm_config.rocm_usescases, ",");
        }
        strcat(pConfig->rocm_config.rocm_usescases, "dkms");
    }

    fprintf(file, "%s\n", "# Creator/Build Options");
    fprintf(file, "%s\n", "###############################");
    fprintf(file, "%s%d\n", "INSTALL_PACKAGE_TYPE=", (int)pConfig->installerType);
    fprintf(file, "%s\"%s\"\n", "INSTALL_PACKAGE_NAME=", pConfig->create_confg.installer_name_with_extension);
    fprintf(file, "%s%s\n\n", "INSTALL_PACKAGE_DIR=", pConfig->create_confg.installer_out_location);
    fprintf(file, "%s%d\n\n", "INSTALL_PACKAGE_REPO=", pConfig->installerRepoType);
    fprintf(file, "%s%d\n\n", "DOWNLOAD_PKG_CONFIG_NUM=", (int)pConfig->create_confg.currentInstallDLType);

    fprintf(file, "%s\n", "# ROCm Options");
    fprintf(file, "%s\n", "###############################");
    fprintf(file, "%s%s\n", "ROCM_USECASES=", pConfig->rocm_config.rocm_usescases);
    fprintf(file, "%s%s\n\n", "ROCM_VERSIONS=", pConfig->rocm_config.rocm_versions);

    fprintf(file, "%s\n", "# Driver/amdgpu Options");
    fprintf(file, "%s\n", "###############################");
    fprintf(file, "%s%s\n", "AMDGPU_INSTALL_DRIVER=", (pConfig->driver_config.install_driver ? "yes" : "no"));
    fprintf(file, "%s%s\n", "AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP=", (pConfig->driver_config.set_group ? "yes" : "no"));
    fprintf(file, "%s%s\n", "AMDGPU_POST_INSTALL_BLACKLIST=", (pConfig->driver_config.blacklist_driver ? "yes" : "no"));
    fprintf(file, "%s%s\n\n", "AMDGPU_POST_INSTALL_START=", (pConfig->driver_config.start_driver ? "yes" : "no"));

    fprintf(file, "%s\n", "# Extra Package Options");
    fprintf(file, "%s\n", "###############################");

    char extra_packages[DEFAULT_CHAR_SIZE];
    extra_packages[0] = '\0';

    // set the extra packages according to the rocm usecase
    char *tok = strtok (pConfig->rocm_config.rocm_usescases, ",");
    if (tok)
    {
        if (strcmp(tok, ROCM_USECASE) != 0)
        {
            if ( (pConfig->extras_config.rocminfo_install) || (pConfig->extras_config.rocmsmi_install) )
            {
                fprintf(file, "%s\n", "EXTRA_PACKAGES_ONLY=yes");

                if (pConfig->extras_config.rocminfo_install)
                {
                    sprintf(extra_packages + strlen(extra_packages), "rocminfo ");
                }
            
                if (pConfig->extras_config.rocmsmi_install)
                {
                    sprintf(extra_packages + strlen(extra_packages), "%s", "rocm-smi-lib ");
                }
            }
        }
    }

    fprintf(file, "%s\n", "EXTRA_PACKAGES_ONLY=no");
    fprintf(file, "%s%s%s\n\n", "EXTRA_PACKAGES=\"", extra_packages, "\"");

    fclose(file);
}

int create_offline_installer(OFFLINE_INSTALL_CONFIG *pConfig, char *wconfig)
{
    // Write out all configuration setting to the configuration file
    write_offline_configuration(pConfig, wconfig);

    return 0;
}

void parse_args(char* argv[], int argc, int arglist_size, ARGS_INFO *argsInfo) 
{
    int len = 0;
    // Concatenate args into a single string
    for (int i = 1; i < argc; i++) 
    {

        len += strlen(argv[i]);
        if (len > arglist_size)break;

        strcat(argsInfo->createArgs, argv[i]);
        if (i < argc - 1) 
        {
            len++;
            if (len > arglist_size) break;
            strcat(argsInfo->createArgs, " ");
        }

        if (strstr(argv[i], "wconfig=") != NULL)
        {
            if (!get_value_of_wconfig(argv[i], argsInfo->wconfig))
            {
                printf("\nIncorrect value passed to wconfig. The correct format is wconfig=<PATH_TO_CONFIG_FILE_TO_SAVE>");
                exit(1);
            } 
            argsInfo->isWconfig = true;

            char *wconfigcopy = strdup(argsInfo->wconfig);
            char *wconfigDir = dirname(wconfigcopy);
            
            if (!is_dir_exist(wconfigDir))
            {
                printf("\nPath passed via wconfig '%s' is not valid because directory '%s' does not exist\n", argsInfo->wconfig, wconfigDir);
                exit(1);
            } 

            printf("\nWrite config file only: %s\n", argsInfo->wconfig);
        }
    }
}

int main(int argc, char *argv[])
{
    ARGS_INFO argsInfo = {0};
    WINDOW *menuWindow;
    MENU *pMenu;
    ITEM *pCurrentItem;

    OFFLINE_INSTALL_CONFIG offlineConfig = {0};
    OFFLINE_INSTALL_MENUS offlineMenus = {0};

    int c;
    int done = 0;
    int status = -1;

    // set default value for wconfig
    strcpy(argsInfo.wconfig, "create.config");

    // parse any args for create script
    parse_args(argv,argc, DEFAULT_CHAR_SIZE, &argsInfo);

    // Get distro/kernel info on the host system
    get_os_info(&offlineConfig);

    // Initialize ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // init colors
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    init_pair(6, COLOR_WHITE, COLOR_RED);
    init_pair(7, COLOR_WHITE, COLOR_GREEN);
    init_pair(8, COLOR_WHITE, COLOR_BLUE);

    init_pair(9, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(10, COLOR_YELLOW, COLOR_BLACK);

    // Create the window to be associated with the menu 
    menuWindow = newwin(WIN_NUM_LINES, WIN_WIDTH_COLS, WIN_START_Y, WIN_START_X);
    keypad(menuWindow, TRUE);
    
    // Create the main menu
    create_menu(&offlineMenus.menuMain, menuWindow, &mainMenuProperties, &mainMenuItems, NULL);

    pMenu = offlineMenus.menuMain.pMenu;

    offlineConfig.installerType = DEFAULT_INSTALLER_TYPE;

    // set items to non-selectable for the main menu
    set_menu_grey(pMenu, COLOR_PAIR(3));
    menu_set_item_select(&offlineMenus.menuMain, 1, false);  // space after create config
    menu_set_item_select(&offlineMenus.menuMain, 5, false);  // space before create install

    // Create the various main option menus
    create_config_menu_window(&offlineMenus.menuCreate, menuWindow, &offlineConfig);
    create_rocm_menu_window(&offlineMenus.menuROCM, menuWindow, &offlineConfig);
    create_driver_menu_window(&offlineMenus.menuDriver, menuWindow, &offlineConfig);
    create_extras_menu_window(&offlineMenus.menuExtras, menuWindow, &offlineConfig);
    create_summary_menu_window(&offlineMenus.menuSummary, menuWindow, &offlineConfig);

    // Draw the main menu
    main_menu_draw(&offlineMenus.menuMain, &offlineConfig);

    // Post the main menu
    post_menu(pMenu);
    print_menu_item_selection(&offlineMenus.menuMain, MENU_SEL_START_Y, MENU_SEL_START_X);
    wrefresh(menuWindow);

    while( done == 0 )
    {
        c = wgetch(menuWindow);
        switch(c)
        {	
            case KEY_RESIZE: // Terminal window resize
                if (should_window_be_resized(menuWindow, WIN_NUM_LINES,WIN_WIDTH_COLS))
                {
                    reset_window_before_resizing(&offlineMenus.menuMain);
                    
                    main_menu_draw(&offlineMenus.menuMain, &offlineConfig);
                    post_menu(pMenu);
                }
                break;

            case KEY_DOWN:
                menu_driver(pMenu, REQ_DOWN_ITEM);

                skip_menu_item_down_if_skippable(pMenu);

                break;

            case KEY_UP:
                menu_driver(pMenu, REQ_UP_ITEM);

                skip_menu_item_up_if_skippable(pMenu);

                break;

            case KEY_F(1):
                done = 1;
                break;

            case 10:    // Enter
                pCurrentItem = current_item(pMenu);
                unpost_menu(pMenu);

                if ( item_index(pCurrentItem) == 0 )
                {
                    do_create_menu(&offlineMenus.menuCreate);
                }
                else if ( item_index(pCurrentItem) == 2 )
                {
                    do_rocm_menu(&offlineMenus.menuROCM);
                }
                else if ( item_index(pCurrentItem) == 3 )
                {
                    do_driver_menu(&offlineMenus.menuDriver);
                }
                else if ( item_index(pCurrentItem) == 4 )
                {
                    do_extras_menu(&offlineMenus.menuExtras);   
                }
                else if ( item_index(pCurrentItem) == 6 )
                {
                    do_summary_menu(&offlineMenus.menuSummary);
                    
                    if (offlineMenus.menuSummary.isCreateInstaller)
                    {
                        status = create_offline_installer(&offlineConfig, argsInfo.wconfig);
                        done = 1;
                    }
                }
                else
                {
                    print_menu_err_msg(&offlineMenus.menuMain, "Invalid item");
                }

                // update any state changes for the menus
                update_menu_states(&offlineMenus);
                if (offlineConfig.configChg)
                {
                    offlineConfig.configChg = false;
                }

                // return to the main menu
                main_menu_draw(&offlineMenus.menuMain, &offlineConfig);
                post_menu(pMenu);

                break;
        }

        print_menu_item_selection(&offlineMenus.menuMain, MENU_SEL_START_Y, MENU_SEL_START_X);
        wrefresh(menuWindow);
    } 

    destroy_menu(&offlineMenus.menuMain);

    destroy_rocm_menu_window(&offlineMenus.menuROCM);
    destroy_config_menu_window(&offlineMenus.menuCreate);
    destroy_driver_menu_window(&offlineMenus.menuDriver);
    destroy_extras_menu_window(&offlineMenus.menuExtras);
    destroy_summary_menu_window(&offlineMenus.menuSummary);
    
    delwin(menuWindow);
    endwin();

    // call the creator script
    if (status == 0)
    {
        if (argsInfo.isWconfig)
        {
            return 0;
        }
        char cmd[LARGE_CHAR_SIZE];
        char createCreatorDir[LARGE_CHAR_SIZE];
        clear_str(cmd);
        
        // Only run below 2 commands with sudo if current user isn't a root user
        char sudo[SMALL_CHAR_SIZE] = {'\0'};
        if (getuid() != 0)
        {
            sprintf(sudo, "sudo");
        }

        printf("Create directory: /var/log/offline_creator\n");
        fflush(stdout);
        sprintf(createCreatorDir, "%s mkdir -p /var/log/offline_creator", sudo);
        system(createCreatorDir);
        sprintf(cmd, "./create-offline.sh %s 2>&1 | %s tee %s", argsInfo.createArgs, sudo, offlineConfig.create_confg.installer_creation_log_out_location);
        system(cmd);
        printf("Creation log stored in: %s\n", offlineConfig.create_confg.installer_creation_log_out_location);
    }

    return 0;

}


