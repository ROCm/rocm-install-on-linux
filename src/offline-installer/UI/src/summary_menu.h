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
#ifndef _SUMMARY_MENU_H
#define _SUMMARY_MENU_H

#include "menu_data.h"

// Summary page sub window settings
#define SUMMARY_SUBWIN_WIDTH_COLS                   82
#define SUMMARY_SUBWIN_NUM_LINES                    17
#define SUMMARY_SUBWIN_START_X                      1
#define SUMMARY_SUBWIN_START_Y                      3

// Summary page column settings
#define COL1_SUMMARY_MENU_OP_STARTX                 3
#define COL2_SUMMARY_MENU_VALUE_STARTX              30
#define COL2_SUMMARY_DRIVER_MENU_VALUE_STARTX       35
#define COL2_SUMMARY_MENU_VALUE_WIDTH               SUMMARY_SUBWIN_WIDTH_COLS - COL2_SUMMARY_MENU_VALUE_STARTX
#define COL2_SUMMARY_DRIVIER_MENU_VALUE_WIDTH       SUMMARY_SUBWIN_WIDTH_COLS - COL2_SUMMARY_DRIVER_MENU_VALUE_STARTX
// Starting row for displaying settings and their values
#define COLS_SUMMARY_MENU_STARTY                    0

// Start position of menu items (Next Page, Prev Page, Return, Accept, page nums)
#define SUMMARY_MENU_ITEM_START_Y                   20   // minimum starting y/row
#define SUMMARY_MENU_ITEM_START_X                   1    // minimum starting x/col
#define SUMMARY_PAGE_NUM_STARTX                     75   // page number location
#define SUMMARY_MENU_ITEM_NEXT_PAGE_INDEX           0

void create_summary_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_summary_menu_window(MENU_DATA *pMenuData);
void do_summary_menu(MENU_DATA *pMenuData);

void summary_menu_update_state(MENU_DATA *pMenuData);

#endif // _SUMMARY_MENU_H
