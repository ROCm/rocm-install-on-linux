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
#include "utils.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int calculate_text_height(char *desc, int width)
{
    int desc_length = strlen(desc);
    int rows_needed = ceil(desc_length/width);
    return rows_needed + 1;
}

int get_char_array_size(char *array[])
{
    // array must have last element defined as NULL
    int size = 0;
    if (array != NULL) 
    {
        while (array[size] != NULL) {
            size++;
        }

    }
    return size;
}

bool is_field_empty(char *text)
{
    int count = strlen(text);
    int i = 0;
   
    while (i < count)
    {
        // When user deletes char(s) from form field, it simply replaces the deleted
        // char w/ the ' ' (space) char. So strlen still returns an incorrect value,
        // even when the string is empty. This is a fix for that.
        if (text[i] != ' ')
        {
            return false;
        }

        i++;
    }

    return true;
}

int get_field_length(char *text, int field_width)
{
    char temp[256];
    int i;

    strcpy(temp, text);

    for (i = 0; i < field_width; i++)
    {
        if ((temp[i] == ' ') || (temp[i] == '\0'))
            break;
    }

    return i;
}

void field_trim(char *src, char *dst, int max)
{
    int field_len = get_field_length(src, max);
    
    memset(dst, '\0', 256);
    strncpy(dst, src, (max-3));
    if (field_len > (max -3) )
    {
        strcat(dst, "...");
    }
}

int check_url(char *url) 
{
    char command[256];

    sprintf(command, "wget -q --spider %s", url);
    
    return system(command);
}

int check_path_exists(char *path, int max)
{
    int ret = 0;
    struct stat buffer;

    remove_end_spaces(path, max);

    ret = stat(path, &buffer);

    return ret;
}

void remove_slash(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '/')
        {
            str[i] = '-';
        }
    }
}

void remove_end_spaces(char *str, int max)
{
    int field_len = get_field_length(str, max);

    char temp[256];

    memset(temp, '\0', 256);
    strncpy(temp, str, field_len);
    
    strcpy(str, temp);
}

int clear_str(char *str)
{
    if (NULL == str)
    {
        return -1;
    }

    memset(str, '\0', strlen(str));

    return 0;
}