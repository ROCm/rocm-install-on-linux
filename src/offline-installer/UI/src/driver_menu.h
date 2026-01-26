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
#ifndef _DRIVER_MENU_H
#define _DRIVER_MENU_H

#include "menu_data.h"
#include "rocm_menu.h"


#define DRIVER_MENU_ITEM_START_Y        5   // minimum starting y/row
#define DRIVER_MENU_ITEM_START_X        1   // minimum starting x/col

// form setup
#define DRIVER_MENU_NUM_FORM_FIELDS     2
#define DRIVER_MENU_FORM_FIELD_WIDTH    40
#define DRIVER_MENU_FORM_FIELD_HEIGHT   1       // one line

#define DRIVER_MENU_FORM_ROW            7       // starting row for create menu form
#define DRIVER_MENU_FORM_COL            40      // staring column for create menu form

// menu item indicies
#define DRIVER_MENU_ITEM_INSTALL_DRIVER_INDEX    0
#define DRIVER_MENU_ITEM_DRIVER_VER_INDEX        2
#define DRIVER_MENU_ITEM_BLACKLIST_INDEX         4
#define DRIVER_MENU_ITEM_START_DRIVER_INDEX      5
#define DRIVER_MENU_ITEM_ADVANCED_MENU_INDEX     7

// menu item rows
#define DRIVER_MENU_ITEM_INSTALL_DRIVER_ROW     5
#define DRIVER_MENU_ITEM_DRIVER_VER_ROW         7
#define DRIVER_MENU_ITEM_BLACKLIST_ROW          9
#define DRIVER_MENU_ITEM_START_DRIVER_ROW       10

// advanced menu item indices
#define ADVANCED_DRIVER_MENU_ITEM_KERNEL_VERSION_INDEX          0
#define ADVANCED_DRIVER_MENU_ITEM_RHCK_KERNEL_VERSION_INDEX     1

#define ADVANCED_DRIVER_MENU_MAX_ITEMS                          6

#define ADVANCED_DRIVER_MENU_FORM_ROW            5       // starting row for create menu form
#define ADVANCED_DRIVER_MENU_FORM_COL            30      // staring column for advanced driver menu form

// definitions for rocm verions matrix
#define DRIVER_ROCM_NUM_VERS                     ROCM_VERS_COLS      // Number of rocm versions (should match ROCM_VERS_COLS)



void create_driver_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_driver_menu_window(MENU_DATA *pMenuData);
void do_driver_menu(MENU_DATA *pMenuData);

void driver_menu_update_state(MENU_DATA *pMenuData);
void reset_driver_version_menu();

bool is_driver_version_empty();
int get_driver_version_index_by_name();
void set_driver_version_menu(int index);

bool is_user_selected_kernel();
bool is_user_selected_rhck_kernel();


#endif // _DRIVER_MENU_H

