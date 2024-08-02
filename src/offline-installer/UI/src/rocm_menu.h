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
#ifndef _ROCM_MENU_H
#define _ROCM_MENU_H

#include "menu_data.h"


#define ROCM_MENU_ITEM_START_Y                              5   // minimum starting y/row
#define ROCM_MENU_ITEM_START_X                              1   // minimum starting x/col

#define ROCM_MENU_USECASES_ITEM_START_X                     4

// form setup
#define ROCM_MENU_NUM_FORM_FIELDS                           1
#define ROCM_MENU_FORM_FIELD_WIDTH                          50
#define ROCM_MENU_FORM_FIELD_HEIGHT                         1       // one line

#define ROCM_MENU_FORM_ROW                                  9       // starting row for create menu form
#define ROCM_MENU_FORM_COL                                  26      // staring column for create menu form

#define ROCM_MENU_USECASES_WIDTH                            WIN_WIDTH_COLS - ROCM_MENU_FORM_COL - 2

// menu item indices

// rocm menu indices
#define ROCM_MENU_ITEM_INSTALL_ROCM_INDEX                   0
#define ROCM_MENU_ITEM_VERSIONS_INDEX                       2
#define ROCM_MENU_ITEM_USECASES_INDEX                       3

// rocm menu item rows
#define ROCM_MENU_ITEM_INSTALL_ROCM_ROW                     5
#define ROCM_MENU_ITEM_VERSION_ROW                          7
#define ROCM_MENU_ITEM_USECASES_ROW                         8

// rocm usecases menu indices
#define ROCM_USECASES_MENU_ITEM_MULTIMEDIASDK_INDEX         8

// definitions for rocm verions matrix
#define ROCM_VERS_ROWS                                      10
#define ROCM_VERS_COLS                                      10

#define ROCM_VERS_MENU_MAX_SIZE                             13


void create_rocm_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_rocm_menu_window(MENU_DATA *pMenuData);
void do_rocm_menu(MENU_DATA *pMenuData);

void rocm_menu_update_state(MENU_DATA *pMenuData);
bool is_specific_usecase_selected(MENU_DATA *pMenuData, char *usecase); 

void do_rocm_menu_version();

void reset_rocm_version_menu(ROCM_MENU_CONFIG *pRocmConfig);
void reset_rocm_usecases_menu(ROCM_MENU_CONFIG *pRocmConfig);

#endif // _ROCM_MENU_H

