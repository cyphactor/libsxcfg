#include <stdio.h>
#include <stdlib.h>

#include <sxcfg.h>

int main(int argc, char *argv[]) {

    int r;
    sxcfg_handle_t handle;
    char buf[256];

    r = sxcfg_init_handle(&handle);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to init handle.\n", r);
        return 1;
    }

    r = sxcfg_parse_config(&handle, "test.cfg");
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to read config.\n", r);
        return 2;
    }

    r = sxcfg_get_opt(&handle, "kittysection", "myopt2", buf, 256);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to get opt myopt2.\n", r);
    } else {
        printf("value: %s\n", buf);
    }
    
    r = sxcfg_get_opt(&handle, "kittysection", "myfoo", buf, 256);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to get opt myfoo.\n", r);
    } else {
        printf("value: %s\n", buf);
    }
   
    r = sxcfg_get_opt(&handle, "kittysection", "mytity", buf, 256);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to get opt mytity.\n", r);
    } else {
        printf("value: %s\n", buf);
    }

    r = sxcfg_free_handle(&handle);
    if (r != 0) {
        fprintf(stderr, "Err(%d): Failed to free handle.\n", r);
        return 3;
    }

    return 0;
}
