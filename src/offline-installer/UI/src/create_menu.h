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
#ifndef _CONFIG_MENU_H
#define _CONFIG_MENU_H

#include "menu_data.h"


#define CREATE_MENU_ITEM_START_Y                                        5   // minimum starting y/row
#define CREATE_MENU_ITEM_START_X                                        1   // minimum starting x/col
 
// form setup
#define CREATE_MENU_NUM_FORM_FIELDS                                     3
#define CREATE_MENU_FORM_FIELD_WIDTH                                    50
#define CREATE_MENU_FORM_FIELD_HEIGHT                                   1       // one line

#define CREATE_MENU_FORM_ROW                                            10      // starting row for create menu form
#define CREATE_MENU_FORM_COL                                            30      // staring column for create menu form

// menu item indicies
#define CREATE_MENU_ITEM_INSTALLER_INPUT_INDEX                          0
#define CREATE_MENU_ITEM_REPO_TYPE_INDEX                                1
#define CREATE_MENU_ITEM_DEP_DOWNLOAD_INDEX                             3
#define CREATE_MENU_ITEM_INSTALLER_NAME_INDEX                           5
#define CREATE_MENU_ITEM_INSTALLER_PATH_INDEX                           6
#define CREATE_MENU_ITEM_TARBALL_INDEX                                  7

// menu item rows
#define CREATE_MENU_ITEM_INSTALLER_INPUT_ROW                            5
#define CREATE_MENU_ITEM_REPO_TYPE_ROW                                  6
#define CREATE_MENU_ITEM_DEP_DOWNLOAD_ROW                               8


#define CREATE_MENU_DEFAULT_INSTALLER_NAME                              "rocm-offline-install"

#define CREATE_MENU_INSTALLER_LOG_OUT_PATH                              "/var/log/offline_creator"


// item descriptions for options within specific menu items
#define CREATE_MENU_ITEM_INSTALLER_INPUT_PUBLIC_DESC                    "Input source for packages used in offline installer creation. 'repo-public'        provides packages from repo.radeon.com"
#define CREATE_MENU_ITEM_DEP_DOWNLOAD_FULL_DESC                         "Set package dependency download configuration. 'full' recursively downloads        package dependencies regardless of the current packages installed on the host"
#define CREATE_MENU_ITEM_DEP_DOWNLOAD_MIN_DESC                          "Set package dependency download configuration. 'minimum' downloads package         dependencies based on the current host configuration."


void create_config_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_config_menu_window(MENU_DATA *pMenuData);
void do_create_menu(MENU_DATA *pMenuData);

void create_menu_update_state(MENU_DATA *pMenuData);


#endif // _CONFIG_MENU_H

