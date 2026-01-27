#include <yaml.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <klee/klee.h>

int
main(int argc, char *argv[]) {
    yaml_parser_t parser;
    yaml_token_t token;
    bool done = false;
    unsigned char *buf = NULL;

    if (argc < 2) {
        return 1;
    }

    unsigned int size = strtoul(argv[1], NULL, 10);
    buf = malloc(size);

    /* initialize input */
    if (argc == 3) {
        FILE *f = fopen(argv[2], "r");
        fread(buf, 1, size, f);
        fclose(f);
    } else {
#ifdef TEST_SYMBOLIC
        klee_make_symbolic(buf, size, "buf");
#endif
    }
    buf[size - 1] = 0;

    /* initialize parser */
    if (!yaml_parser_initialize(&parser)) {
        return 1;
    }
    yaml_parser_set_input_string(&parser, buf, size);

    while (!done) {
        if (!yaml_parser_scan(&parser, &token)) {
            //fprintf(stderr, "yaml_parser_parse failed\n");
            break;
        }

        if (token.type == YAML_STREAM_END_TOKEN) {
            done = true;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);

    return 0;
}
