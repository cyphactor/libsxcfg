/*
 * Copyright 2007 Andrew De Ponte
 *
 * This file is part of lib_sxcfg.
 *
 * lib_sxcfg is the intellectual property of Andrew De Ponte; any
 * distribution and/or modifications and/or reproductions of any portion
 * of lib_sxcfg MUST be approved by Andrew De Ponte.
 *
 * lib_sxcfg is dirstributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 */

/**
 * @file sxcfg_export.h
 * @brief This is a specifications file forWin32 DLL handling.
 *
 * The sxcfg_export.h file is a specifaciotns file that defines the
 * necessary macros for handling the complexities of Win32 DLL creation
 * and linking necessary for the cross-platform lib_sxcfg code base.
 */

#ifndef SXCFG_EXPORT_H
#define SXCFG_EXPORT_H

#ifdef DLL_EXPORT
    #define SXCFG_EXPORT __declspec(dllexport)
#else
    #ifdef LIBSXCFG_DLL_IMPORT
        #define SXCFG_EXPORT __declspec(dllimport)
    #endif
#endif
#ifndef SXCFG_EXPORT
    #define SXCFG_EXPORT
#endif

#endif /* SXCFG_EXPORT_H */
