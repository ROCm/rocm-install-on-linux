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
#ifndef _INSTALL_TYPES_H
#define _INSTALL_TYPES_H

#include <ncurses.h>
#include <menu.h>
#include <form.h>

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>


#ifndef OFFLINE_VERSION
#define OFFLINE_VERSION "custom"
#endif

#ifndef ROCM_VERSION
#define ROCM_VERSION "intnl"
#endif

/* Global types for all menu configurations */

// Input source repo used for installer packages
typedef enum _INSTALL_TYPE
{
    eINSTALL_TYPE_REPO_PUBLIC,      // install created from public (repo.radeon.com)
    eINSTALL_TYPE_MAX
}INSTALL_TYPE;

// Level of package dependency download for installer packages
typedef enum _DEP_DL_TYPE
{
    eDL_TYPE_FULL,   // package download attempting to resolve all dependencies recursively
    eDL_TYPE_MIN,     // package download using current host state to resolve dependencies for a "minimum" target OS
    eDL_TYPE_UNAVAILABLE, // unavailable when rocm is installed on system and user is on rhel or ol
    eDL_TYPE_MAX,
}DEP_DL_TYPE;

// Repo source
typedef enum _DISTRO_TYPE
{
    eDISTRO_TYPE_DEB,       // Deb-based
    eDISTRO_TYPE_EL,        // RHEL-based
    eDISTRO_TYPE_SLE,       // Suse-based
}DISTRO_TYPE;

// Repo source
typedef enum _REPO_TYPE
{
    eREPO_TYPE_RADEON,              // repo.radeon.com
    eREPO_TYPE_MAX
}REPO_TYPE;

// rocm usecase/component types
typedef enum _ROCM_USECASES_TYPE
{
    eROCM_USECASES_TYPE_NONE,    // type not initialized
    eROCM_USECASES_TYPE_V1,      // version type 1 : amdgpu-install usecases
    eROCM_USECASES_TYPE_V2,      // version type 2 : meta packages list
}ROCM_USECASES_TYPE;

// kernel version status
typedef enum _USER_SELECTED_KERNEL_STATUS
{
    eKERNEL_STATUS_CHECKING,     // status when waiting to see if user selected kernel is valid or not
    eKERNEL_STATUS_VALID,         
    eKERNEL_STATUS_INVALID,       
}USER_SELECTED_KERNEL_STATUS;



// String sizes
#define DEFAULT_CHAR_SIZE                   256
#define LARGE_CHAR_SIZE                     1024
#define SMALL_CHAR_SIZE                     32


#endif // _INSTALL_TYPES_H
