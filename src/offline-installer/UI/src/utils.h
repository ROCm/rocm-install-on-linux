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
#include <stdbool.h>

#ifndef _UTILIS_H
#define _UTILIS_H

#define TOGGLE_BIT(val, bitIndx) val ^= (1 << bitIndx)
#define TOGGLE_FALSE(val, bitIndx) val &= ~(1 << bitIndx) 


#define DEFAULT_CHAR_SIZE      256
#define LARGE_CHAR_SIZE        1024
#define SMALL_CHAR_SIZE        32

int calculate_text_height(char *desc, int width);
int get_char_array_size(char *array[]);
bool is_field_empty(char *text);
int get_field_length(char *text, int field_width);
void field_trim(char *src, char *dst, int max);

int check_url(char *url);
int check_path_exists(char *path, int max);

void remove_slash(char *str);
void remove_end_spaces(char *str, int max);
int clear_str(char *str);

bool is_rocm_installed();
bool get_value_of_wconfig(char *src, char *dst);
bool is_dir_exist(char *path);



#endif // _UTILIS_H
