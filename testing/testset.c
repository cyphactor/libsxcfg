#include <stdio.h>
#include <stdlib.h>

#include <sxcfg.h>

int main(int argc, char *argv[]) {

    int r;
    sxcfg_handle_t handle;
    sxcfg_section_t *p_sec;

    r = sxcfg_init_handle(&handle);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to init handle.\n", r);
        return 1;
    }
    
    p_sec = NULL;
    p_sec = sxcfg_append_sec(&handle, "foo");
    if (p_sec == NULL) {
        fprintf(stderr, "Err: Failed to add section.\n");
        return 2;
    }
    
    r = sxcfg_append_opt(p_sec, "titty", "kitty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add first option.", r);
        return 3;
    }

    r = sxcfg_append_opt(p_sec, "city", "witty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add second option.", r);
        return 4;
    }

    p_sec = NULL;
    p_sec = sxcfg_append_sec(&handle, "bar");
    if (p_sec == NULL) {
        fprintf(stderr, "Err: Failed to add section.\n");
        return 2;
    }
    
    r = sxcfg_append_opt(p_sec, "titty", "kitty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add first option.", r);
        return 3;
    }

    r = sxcfg_append_opt(p_sec, "city", "witty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add second option.", r);
        return 4;
    }
    
    p_sec = NULL;
    p_sec = sxcfg_append_sec(&handle, "tar");
    if (p_sec == NULL) {
        fprintf(stderr, "Err: Failed to add section.\n");
        return 2;
    }
    
    r = sxcfg_append_opt(p_sec, "titty", "kitty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add first option.", r);
        return 3;
    }

    r = sxcfg_append_opt(p_sec, "city", "witty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to add second option.", r);
        return 4;
    }
    
    r = sxcfg_set_opt(&handle, "bar", "titty", "pitty");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to set option.", r);
        return 8;
    }
    
    r = sxcfg_write_config(&handle, "testout.cfg");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to write config.\n", r);
        return 5;
    }

    r = sxcfg_free_handle(&handle);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to free handle.\n", r);
        return 3;
    }

    return 0;
}