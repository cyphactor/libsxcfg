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
 * @file sxcfg.h
 * @brief This is a specifications file for the lib_sxcfg API.
 *
 * The sxcfg.h file is a specifications file for the general lib_sxcfg
 * API. It contains all the type definitions and function declarations
 * which are components of the general lib_sxcfg API.
 */

#ifndef SXCFG_H
#define SXCFG_H

#include "sxcfg_export.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SXCFG_MAX_OPT_LEN 50    /**> Maximum Option Name Length */
#define SXCFG_MAX_VAL_LEN 256   /**> Maximum Option Value Length */
#define SXCFG_MAX_LINE_LEN (SXCFG_MAX_OPT_LEN + 1 + SXCFG_MAX_VAL_LEN + 1)

/**
 * Config Option.
 *
 * The _sxcfg_option_t is an internal type which represents a
 * configuration file option. It is used to store both the option name
 * and its associated value. This type is used internally and should
 * never need to be accessed by any client software.
 */
typedef struct _sxcfg_option {
    char *name;
    char *value;
    struct _sxcfg_option *p_next_opt;
} _sxcfg_option_t;

/**
 * Config Section.
 *
 * The sxcfg_section_t is a type which is a configuration file section.
 * It is used to represent a section in a config file and store all the
 * option and value pairs associated with that section.
 */
typedef struct SXCFG_EXPORT sxcfg_section {
    char *name;
    struct _sxcfg_option *p_first_opt;
    struct sxcfg_section *p_next_sec;
} sxcfg_section_t;

/**
 * Config Handle.
 *
 * The sxcfg_handle_t is a type which is a handle for configuration
 * file.  It is used to store all the sections and their associated
 * option and value pairs. The config handles are commonly initiated by
 * the sxcfg_init_handle() function, filled by the sxcfg_parse_config()
 * function, and then freed by the sxcfg_free_handle() function.
 */
typedef struct SXCFG_EXPORT sxcfg_handle {
    struct sxcfg_section *p_first_sec;
} sxcfg_handle_t;

/**
 * Initialize config file handle.
 *
 * The sxcfg_init_handle() function initializes a handle which
 * represents a config file. After initializiing a config file handle
 * one should use the sxcfg_read() function to associate the initialized
 * handle with a specific config file.
 * @param p_handle Pointer to sxcfg_handle_t config file handle.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully initialized the config file handle.
 */
SXCFG_EXPORT int sxcfg_init_handle(sxcfg_handle_t *p_handle);

/**
 * Append a section to the given config handle.
 *
 * The sxcfg_append_sec() function appends a section named, 'name', to
 * the given config file handle pointed to by 'p_handle'.
 * @param p_handle Pointer to the config handle to add the section to.
 * @param name C-String containing the name of the section to add.
 * @return A pointer to the newly created section that was just appended
 * to the config handle.
 * @retval NULL Failed to append the section to the config handle.
 */
SXCFG_EXPORT sxcfg_section_t *sxcfg_append_sec(sxcfg_handle_t *p_handle,
    const char *name);

/**
 * Append an option to the given section.
 *
 * The sxcfg_append_opt() function appens an option named, 'name', with
 * a value of 'value' to the section pointed to by 'p_sec'.
 * @param p_sec Pointer to section to append the option to.
 * @param name C-String containing the name of the option to add.
 * @param value C-String containing the value of the option to add.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully appended the option to the section.
 * @retval -1 Failed to allocate mem for new option.
 * @retval -2 Failed to allocate mem for new options name.
 * @retval -3 Failed to allocate mem for new options value.
 */
SXCFG_EXPORT int sxcfg_append_opt(sxcfg_section_t *p_sec, const char *name,
    const char *value);

/**
 * Parse a config file and associate it with a handle.
 *
 * The sxcfg_parse() function opens a config file in the appropriate
 * format and loads the handle with all the data from the config file so
 * that functions like sxcfg_get_opt() may be used on the handle to
 * acquire values of specific options in the config file.
 * @param p_handle Pointer to the config handle to store parsed data in.
 * @param config_path Path the config file to parse.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully parsed and loaded in the specified config file.
 * @retval -1 Failed to open config file.
 * @retval -2 Failed to close config file.
 * @retval -3 Missing a closing bracket on section declaration.
 * @retval -4 Failed to find a colon character in the option line.
 * @retval -5 Failed to append option to current section.
 * @retval -6 Current section is NULL.
 * @retval -7 Processed count is greater than bytes read.
 */
SXCFG_EXPORT int sxcfg_parse_config(sxcfg_handle_t *p_handle,
    const char *config_path);

/**
 * @brief Write a config file given a handle.
 *
 * The sxcfg_write_config() function writes a config file in the appropriate
 * format based on the provided handle. In general this function is called
 * after calling sxcfg_append_sec() and sxcfg_append_opt() a few times.
 * Note: If a config file is previously loaded with the sxcfg_parse_config()
 * function and then re-written with the sxcfg_write_config() any comments
 * previously existing in that config file will be lost.
 * @param p_handle Pointer to the config handle to write to file.
 * @param config_path Path to write the config file to.
 * @return An integer represent success (zero) or failure (non-zero).
 * @retval 0 Successfully wrote the specified config file.
 * @retval -1 Failed to open config file for writing.
 * @retval -2 Failed to close config file after writing.
 * @retval -3 Failed to write a section to the config file.
 * @retval -4 Failed to close file after failing to write a section.
 * @retval -5 Failed to write a option to the config file.
 * @retval -6 Failed to close file after failing to write a section.
 */
SXCFG_EXPORT int sxcfg_write_config(sxcfg_handle_t *p_handle,
    const char *config_path);

/**
 * Obtain an options value.
 *
 * The sxcfg_get_opt() function provides a mechanism for obtaining the
 * value of an option in a config file after first calling the
 * sxcfg_init_handle() function and then the sxcfg_read_config()
 * function to load the config handle.
 * @param p_handle Pointer to the config handle to obtain the option
 * value from.
 * @param sec_name The name of the section the option can be found in.
 * @param opt_name The name of the option to obtain the value of.
 * @param p_opt_value Pointer to a buffer to store the resulting value
 * of the option in.
 * @param len The length of the buffer to store the obtained value in.
 * If no NULL byte is found within 'len' bytes then the resulting buffer
 * pointed to by 'p_opt_value' will not be NULL terminated.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully obtained option value.
 * @retval -1 Failed to find specified section.
 * @retval -2 Failed to find specified option.
 */
SXCFG_EXPORT int sxcfg_get_opt(sxcfg_handle_t *p_handle,
    const char *sec_name, const char *opt_name, char *p_opt_value,
    unsigned int len);

/**
 * @brief Set an options value.
 *
 * The sxcfg_set_opt() function provides a mechanism for setting the value
 * of a option which is already existant in a handle either by previously
 * being appended to a section using the sxcfg_append_opt() function or the
 * sxcfg_parse_config() function. Note: In the case of failure the original
 * option value is left in its original state.
 * @param p_handle Pointer to config handle to set option in.
 * @param sec_name Name of the section the option is in that you want to set.
 * @param opt_name Name of the option you want to set the value for.
 * @param opt_value The value to set the option to.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully set the option value.
 * @retval -1 Failed to find named section.
 * @retval -2 Failed to find named option in the named section.
 * @retval -3 Failed to allocate memory for new value.
 */
SXCFG_EXPORT int sxcfg_set_opt(sxcfg_handle_t *p_handle,
    const char *sec_name, const char *opt_name, const char *opt_value);

/**
 * Free config file handle.
 *
 * The sxcfg_free_handle() function frees any previously dynamically
 * allocated memory associated with a config file handle.
 * @param p_handle Pointer to sxcfg_handle_t config file handle.
 * @return An integer representing success (zero) or failure (non-zero).
 * @retval 0 Successfully freed the config file handle.
 */
SXCFG_EXPORT int sxcfg_free_handle(sxcfg_handle_t *p_handle);

/**
 * Obtain the next line in the given string.
 *
 * The _sxcfg_get_next_line() function parses a string into a sequence
 * of lines.  The 'saveptr' argument is a pointer to a 'char *' variable
 * that is used internally by _sxcfg_get_next_line() in order to
 * maintain context between successive calls that parse the same string.
 * On the first call to _sxcfg_get_next_line(), 'str' should point to
 * the string to be parsed, and the value of 'saveptr' is ignored. In
 * subsequent calls, 'str' should be NULL, and 'saveptr' should be
 * unchanged since the previous call.  Note: This function modifies the
 * first argument, such that the identity of the line termination
 * character(s) is lost.  Each call to _sxcfg_get_next_line() returns a
 * pointer to a null-terminated string containing the next line.  This
 * string does not include the respective CRLF (Windows) or LF (Unix/Mac
 * OS-X). The _sxcfg_get_next_line() also maintains a count of the
 * characters that have been processed as components of lines. This is
 * designed to allow comparison between processed character count and
 * total characters fed for processing. This allows for determination of
 * any left over characters at the end of a buffer that are NOT
 * terminated by line termination character(s).
 * @param str Pointer to string to parse into a sequence of lines.
 * @param saveptr A pointer to a 'char *' variable that is used
 * internally in order to maintain context between successive calls,
 * allowing this function to be reentrant.
 * @param p_count A pointer to a 'int' variable that is used to keep
 * track of the total number of characters processed.
 * @return A pointer to the next line, or NULL if there are no more
 * lines.
 */
char *_sxcfg_get_next_line(char *str, char **saveptr, int *p_count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SXCFG_H */
