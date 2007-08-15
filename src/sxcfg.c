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
 * @file sxcfg.c
 * @brief This is an implementation file for the lib_sxcfg API.
 *
 * The scxfg.c file is an implementation file for the general lib_sxcfg
 * API. It contains all the definitions of the functions which are part
 * of the general lib_sxcfg API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sxcfg_config.h"
#include "sxcfg.h"

int sxcfg_init_handle(sxcfg_handle_t *p_handle) {
    
    p_handle->p_first_sec = NULL;;

    return 0;
}

sxcfg_section_t *sxcfg_append_sec(sxcfg_handle_t *p_handle,
    const char *name) {

    sxcfg_section_t *p_cur_sec, *p_prev_sec, *p_ret_sec;
    int name_len;

    name_len = strlen(name);

    if (p_handle->p_first_sec == NULL) { // initial append, no secs in list
        p_handle->p_first_sec = malloc(sizeof(sxcfg_section_t));
        if (p_handle->p_first_sec == NULL) {
            return NULL;
        }

        p_handle->p_first_sec->name = malloc(name_len + 1);
        if (p_handle->p_first_sec->name == NULL) {
            free(p_handle->p_first_sec);
            p_handle->p_first_sec = NULL;
            return NULL;
        }

        strncpy(p_handle->p_first_sec->name, name, name_len);
        p_handle->p_first_sec->name[name_len] = '\0';

        p_handle->p_first_sec->p_first_opt = NULL;
        p_handle->p_first_sec->p_next_sec = NULL;

        p_ret_sec = p_handle->p_first_sec;
    } else { // already secs in list
        // find the last section in the list of sections
        p_cur_sec = p_handle->p_first_sec;
        while (p_cur_sec != NULL) {

            p_prev_sec = p_cur_sec;
            p_cur_sec = p_cur_sec->p_next_sec;
        }

        // at this point p_prev_sec should be the section right before
        // the NULL section.
        p_prev_sec->p_next_sec = malloc(sizeof(sxcfg_section_t));
        if (p_prev_sec->p_next_sec == NULL) {
            return NULL;
        }

        p_prev_sec->p_next_sec->name = malloc(name_len + 1);
        if (p_prev_sec->p_next_sec->name == NULL) {
            free(p_prev_sec->p_next_sec);
            p_prev_sec->p_next_sec = NULL;
            return NULL;
        }

        strncpy(p_prev_sec->p_next_sec->name, name, name_len);
        p_prev_sec->p_next_sec->name[name_len] = '\0';

        p_prev_sec->p_next_sec->p_first_opt = NULL;
        p_prev_sec->p_next_sec->p_next_sec = NULL;

        p_ret_sec = p_prev_sec->p_next_sec;
    }

    return p_ret_sec;
}

int sxcfg_append_opt(sxcfg_section_t *p_sec, const char *name,
    const char *value) {

    _sxcfg_option_t *p_cur_opt, *p_prev_opt;
    int name_len, value_len;

    name_len = strlen(name);
    value_len = strlen(value);

    if (p_sec->p_first_opt == NULL) { // initial append, no opts in list
        p_sec->p_first_opt = malloc(sizeof(_sxcfg_option_t));
        if (p_sec->p_first_opt == NULL) {
            return -1;
        }

        p_sec->p_first_opt->p_next_opt = NULL;

        p_sec->p_first_opt->name = malloc(name_len + 1);
        if (p_sec->p_first_opt->name == NULL) {
            free(p_sec->p_first_opt);
            p_sec->p_first_opt = NULL;
            return -2;
        }

        p_sec->p_first_opt->value = malloc(value_len + 1);
        if (p_sec->p_first_opt->value == NULL) {
            free(p_sec->p_first_opt->name);
            p_sec->p_first_opt->name = NULL;
            free(p_sec->p_first_opt);
            p_sec->p_first_opt = NULL;
            return -3;
        }
        
        strncpy(p_sec->p_first_opt->name, name, name_len);
        p_sec->p_first_opt->name[name_len] = '\0';

        strncpy(p_sec->p_first_opt->value, value, value_len);
        p_sec->p_first_opt->value[value_len] = '\0';
    } else { // already opts in list
        // find the last option in the list of options
        p_cur_opt = p_sec->p_first_opt;
        while (p_cur_opt != NULL) {

            p_prev_opt = p_cur_opt;
            p_cur_opt = p_cur_opt->p_next_opt;
        }

        // at this point p_prev_opt should be the option right before
        // the NULL option.
        p_prev_opt->p_next_opt = malloc(sizeof(_sxcfg_option_t));
        if (p_prev_opt->p_next_opt == NULL) {
            return -1;
        }

        p_prev_opt->p_next_opt->p_next_opt = NULL;
        
        p_prev_opt->p_next_opt->name = malloc(name_len + 1);
        if (p_prev_opt->p_next_opt->name == NULL) {
            free(p_prev_opt->p_next_opt);
            p_prev_opt->p_next_opt = NULL;
            return -2;
        }

        p_prev_opt->p_next_opt->value = malloc(value_len + 1);
        if (p_prev_opt->p_next_opt->value == NULL) {
            free(p_prev_opt->p_next_opt->name);
            p_prev_opt->p_next_opt->name = NULL;
            free(p_prev_opt->p_next_opt);
            p_prev_opt->p_next_opt = NULL;
            return -3;
        }

        strncpy(p_prev_opt->p_next_opt->name, name, name_len);
        p_prev_opt->p_next_opt->name[name_len] = '\0';

        strncpy(p_prev_opt->p_next_opt->value, value, value_len);
        p_prev_opt->p_next_opt->value[value_len] = '\0';
    }

    return 0;
}

int sxcfg_parse_config(sxcfg_handle_t *p_handle, const char *config_path) {

    FILE *conf_fp;
    int r;
    char buf[SXCFG_MAX_LINE_LEN];
    char line[SXCFG_MAX_LINE_LEN];
    size_t bytes_read;
    char *p_cur_line;
    char *p_value, *p_name;
    char *saveptr;
    int count;
    int line_split;
    int line_str_len;
    sxcfg_section_t *p_cur_sec;

    line_split = 0;
    p_cur_sec = NULL;

    conf_fp = fopen(config_path, "r");
    if (conf_fp == NULL) {
        return -1;
    }

    bytes_read = fread((void *)buf, 1, (SXCFG_MAX_LINE_LEN - 1), conf_fp);
    while (bytes_read > 0) {

        count = 0;
        buf[bytes_read] = '\0';

        p_cur_line = _sxcfg_get_next_line(buf, &saveptr, &count);
        while (p_cur_line != NULL) {
            
            if (line_split) {
                strncat(line, p_cur_line,
                    (SXCFG_MAX_LINE_LEN - strlen(line) -1));
                line_split = 0;
            } else {
                strncpy(line, p_cur_line, SXCFG_MAX_LINE_LEN);
            }

            if (strcmp(line, "") == 0) { // empty line

            } else if (line[0] == ';') { // comment

            } else if (line[0] == '[') {
                line_str_len = strlen(line);
                if (line[(line_str_len - 1)] == ']') {
                    line[(line_str_len - 1)] = '\0';
                    p_cur_sec = sxcfg_append_sec(p_handle, &line[1]);
                } else {
                    return -3;
                }
            } else { // Assume that it is a normal config line
                p_value = strchr(line, ':');
                if (p_value == NULL) { // failed to find colon
                    return -4;
                } else {
                    *p_value = '\0'; //replace : with null byte
                    p_value = p_value + 1;
                    p_name = &line[0];

                    if (p_cur_sec != NULL) {
                        r = sxcfg_append_opt(p_cur_sec, p_name, p_value);
                        if (r != 0) {
                            return -5;
                        }
                    } else {
                        return -6;
                    }
                }
            }
            
            p_cur_line = _sxcfg_get_next_line(NULL, &saveptr, &count);
        }

        if (count < bytes_read) {
            strncpy(line, saveptr, (SXCFG_MAX_LINE_LEN - 1));
            line_split = 1;
        } else if (count > bytes_read) {
            return -7;
        }

        bytes_read = fread((void *)buf, 1, (SXCFG_MAX_LINE_LEN - 1), conf_fp);
    }

    r = fclose(conf_fp);
    if (r != 0) {
        return -2;
    }

    return 0;
}

int sxcfg_get_opt(sxcfg_handle_t *p_handle, const char *sec_name,
    const char *opt_name, char *p_opt_value, unsigned int len) {

    sxcfg_section_t *p_cur_sec, *p_sel_sec;
    _sxcfg_option_t *p_cur_opt, *p_sel_opt;
    int found_sec, found_opt;

    found_sec = 0;
    found_opt = 0;
    p_sel_sec = NULL;
    p_sel_opt = NULL;
    p_cur_sec = NULL;
    p_cur_opt = NULL;

    p_cur_sec = p_handle->p_first_sec;
    while ((p_cur_sec != NULL) && (found_sec == 0)) {
        if (strcmp(p_cur_sec->name, sec_name) == 0) {
            p_sel_sec = p_cur_sec;
            found_sec = 1;
        }

        p_cur_sec = p_cur_sec->p_next_sec;
    }

    if (found_sec == 0) {
        return -1;
    }

    p_cur_opt = p_sel_sec->p_first_opt;
    while ((p_cur_opt != NULL) && (found_opt == 0)) {
        if (strcmp(p_cur_opt->name, opt_name) == 0) {
            p_sel_opt = p_cur_opt;
            found_opt = 1;
        }

        p_cur_opt = p_cur_opt->p_next_opt;
    }

    if (found_opt == 0) {
        return -2;
    }

    // At this point I know that the given option exists within the
    // given section. So, now I handle returning the value of the option
    // to the user by copying the value into the buffer pointed to by
    // p_opt_value.
    strncpy(p_opt_value, p_sel_opt->value, len);

    return 0;
}

int sxcfg_free_handle(sxcfg_handle_t *p_handle) {

    sxcfg_section_t *p_cur_sec, *p_next_sec;
    _sxcfg_option_t *p_cur_opt, *p_next_opt;

    p_cur_sec = p_handle->p_first_sec;
    while (p_cur_sec != NULL) {
        // Store the pointer to the next section before freeing this
        // current section
        p_next_sec = p_cur_sec->p_next_sec;

        // Free this current sections options
        p_cur_opt = p_cur_sec->p_first_opt;
        while (p_cur_opt != NULL) {
            // Store the pointer to the next option before freeing this
            // current option
            p_next_opt = p_cur_opt->p_next_opt;

            // Free this current option
            free(p_cur_opt->name);
            free(p_cur_opt->value);
            free(p_cur_opt);

            // Set current opt pointer to the previously stored next
            // opt pointer.
            p_cur_opt = p_next_opt;
        }
        
        // Free the current section
        free(p_cur_sec->name);
        free(p_cur_sec);

        // Set current sec pointer to the previously stored next sec
        // pointer.
        p_cur_sec = p_next_sec;
    }

    return 0;
}

char *_sxcfg_get_next_line(char *str, char **saveptr, int *p_count) {

    char *cur_line_ptr;
    char *cur_char_ptr;

    if (str != NULL) { // this should be the first call to this function
        cur_line_ptr = str;
    } else { // this should be a secondary call to this function
        cur_line_ptr = (*saveptr);
    }
    
    cur_char_ptr = cur_line_ptr;

    while ((*cur_char_ptr) != '\0') {

        if (((*cur_char_ptr) == '\r') && ((*(cur_char_ptr + 1)) == '\n')) {
            (*cur_char_ptr) = '\0';
            (*(cur_char_ptr + 1)) = '\0';
            *saveptr = (cur_char_ptr + 2);
            (*p_count) = (*p_count) + strlen(cur_line_ptr) + 2;
            return cur_line_ptr;
        } else if ((*cur_char_ptr) == '\n') {
            (*cur_char_ptr) = '\0';
            *saveptr = (cur_char_ptr + 1);
            (*p_count) = (*p_count) + strlen(cur_line_ptr) + 1;
            return cur_line_ptr;
        }

        cur_char_ptr++;
    }

    return NULL;
}
