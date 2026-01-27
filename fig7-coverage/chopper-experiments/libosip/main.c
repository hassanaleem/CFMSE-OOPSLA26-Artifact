#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <klee/klee.h>

#include <osipparser2/osip_message.h>

void klee_make_symbolic(void *addr, size_t nbytes, const char *name) {

}

int main(int argc, char *argv[]) {
    char *buf = NULL;

    if (argc < 2) {
        return 1;
    }

    size_t size = strtoul(argv[1], NULL, 10);
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

    int rc;
    osip_message_t *sip;

    rc = osip_message_init(&sip);
    if (rc != 0) { 
        fprintf(stderr, "cannot allocate\n"); 
        return -1; 
    }

    rc = osip_message_parse(sip, (const char *)(buf), size);
    if (rc != 0) { 
        //fprintf(stderr, "cannot parse sip message\n"); 
    }

    osip_message_free(sip);

    return 0;
}
