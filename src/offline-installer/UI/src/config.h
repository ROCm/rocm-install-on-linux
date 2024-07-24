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
#ifndef _CONFIG_H
#define _CONFIG_H

#include "install_types.h"

// Menus default installer type
#define DEFAULT_INSTALLER_TYPE    eINSTALL_TYPE_REPO_PUBLIC


/* Create Menu Configuration ************************************************************************/
typedef struct _INSTALL_TYPE_PROP
{
    INSTALL_TYPE    installer_input_type;
    char            installer_input[32];
}INSTALL_TYPE_PROP;

typedef struct _INSTALL_DL_PROP
{
    DEP_DL_TYPE download_dep_type;
    char        download_dep_name[32];
}INSTALL_DL_PROP;

typedef struct _INSTALL_REPO_PROP
{
    REPO_TYPE repo_type;
    char      repo_name[32];
}INSTALL_REPO_PROP;

// Have to define these variables as extern so we can use them in
// summary_menu.c and create_menu.c
extern INSTALL_TYPE_PROP createMenuInstallTypes[eINSTALL_TYPE_MAX];
extern INSTALL_REPO_PROP createMenuRepoTypes[eREPO_TYPE_MAX];
extern INSTALL_DL_PROP createMenuDLTypes[eDL_TYPE_MAX];


// Structure for special configuration setting for creating the offline installer
typedef struct _CREATE_MENU_CONFIG
{
    DEP_DL_TYPE currentInstallDLType;

    char installer_name[256];
    char installer_name_with_extension[260];
    
    char installer_out_location[256];
    bool is_installer_loc_valid;
}CREATE_MENU_CONFIG;

/* ROCm Menu Configuration ************************************************************************/

// Structure for all rocm main/sub menu configuration settings
typedef struct _ROCM_MENU_CONFIG
{
    bool install_rocm;

    // tracks when user unselects 'rocm' after selecting it
    bool is_rocm_usecase_deselected; 
    char rocm_usescases[256];
    char rocm_versions[256];
    bool rocm_version_selected;
}ROCM_MENU_CONFIG;

/* Driver Menu Configuration ************************************************************************/

// Structure for all driver main/sub menu configuration settings
typedef struct _DRIVER_MENU_CONFIG
{
    bool install_driver;

    bool set_group;
    bool blacklist_driver;
    bool start_driver;
}DRIVER_MENU_CONFIG;

/* Extras Menu Configuration ************************************************************************/


// Structure for all extra packages menu configuration settings
typedef struct _EXTRAS_MENU_CONFIG
{
    bool rocminfo_install;
    bool rocmsmi_install;
}EXTRAS_MENU_CONFIG;


/* Global Configuration ************************************************************************/

// Global Installer create configuration
typedef struct _OFFLINE_INSTALL_CONFIG
{
    bool configChg;
    
    char distroName[64];
    char distroID[64];
    char distroVersion[64];
    
    DISTRO_TYPE distroType;
    char kernelVersion[128];

    INSTALL_TYPE        installerType;
    REPO_TYPE           installerRepoType;

    CREATE_MENU_CONFIG  create_confg;
    ROCM_MENU_CONFIG    rocm_config;
    DRIVER_MENU_CONFIG  driver_config;
    EXTRAS_MENU_CONFIG  extras_config;
}OFFLINE_INSTALL_CONFIG;


#endif // _CONFIG_H

