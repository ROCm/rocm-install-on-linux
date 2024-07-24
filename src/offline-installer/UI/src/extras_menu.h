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
#ifndef _EXTRAS_MENU_H
#define _EXTRAS_MENU_H

#include "menu_data.h"

#define EXTRAS_MENU_ITEM_START_Y    5   // minimum starting y/row
#define EXTRAS_MENU_ITEM_START_X    1   // minimum starting x/col

// form setup
#define EXTRAS_MENU_NUM_FORM_FIELDS     1
#define EXTRAS_MENU_FORM_FIELD_WIDTH    25
#define EXTRAS_MENU_FORM_FIELD_HEIGHT   1       // one line

#define EXTRAS_MENU_FORM_ROW            9       // starting row for create menu form
#define EXTRAS_MENU_FORM_COL            27      // staring column for create menu form


void create_extras_menu_window(MENU_DATA *pMenuData, WINDOW *pMenuWindow, OFFLINE_INSTALL_CONFIG *pConfig);
void destroy_extras_menu_window(MENU_DATA *pMenuData);
void do_extras_menu(MENU_DATA *pMenuData);

void extras_menu_update_state(MENU_DATA *pMenuData);

#endif // _EXTRAS_MENU_H

