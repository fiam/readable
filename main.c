#include <stdio.h>
#include <stdlib.h>

#include <libxml/parser.h>

#include "readable.h"

int
main(int argc, char *argv[])
{
    char *contents = NULL;
    FILE *fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);
    contents = malloc(len + 1);
    long r = 0;
    while (r < len) {
        r += fread(contents + r, 1, len - r, fp);
    }
    fclose(fp);
    contents[len] = '\0';
#ifdef READABLE_TEST
    for (int ii = 0; ii < 1000; ++ii) {
        char *readable_contents = readable(contents, "", NULL, READABLE_OPTIONS_DEFAULT);
        if (readable_contents) {
            free(readable_contents);
        }
    }
#else
    int options = READABLE_OPTIONS_DEFAULT;
    while (options) {
        char *readable_contents = readable(contents, "", NULL, options);
        printf("Readable content:\n%s\n", readable_contents);
        if (readable_contents) {
            free(readable_contents);
            break;
        }
        int opts[] = {
            READABLE_OPTION_STRIP_UNLIKELYS,
            READABLE_OPTION_WEIGHT_CLASSES,
            READABLE_OPTION_CLEAN_CONDITIONALLY,
            0xFFFF,
        };
        for (int ii = 0; ii < 4; ++ii) {
            if (options & opts[ii]) {
                options &= ~(opts[ii]);
            }
        }
    }
#endif
    free(contents);
    /* Exit cleanly, don't do this in readable(),
    since it frees internal libxml structures
    which would need to be rebuilt
    */
    xmlCleanupParser();
    return 0;
}
