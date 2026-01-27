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
        printf("Usage: %s <size> [<input_file>]\n", argv[0]);
        return 1;
    }


    size_t size = strtoul(argv[1], NULL, 20);
    buf = malloc(size);

    /* initialize input */
    if (argc == 3) {
        printf("Reading input from file: %s\n", argv[2]);
        FILE *f = fopen(argv[2], "r");
        fread(buf, 1, size, f);
        fclose(f);
    } else {
        klee_make_symbolic(buf, size, "buf");
    }
    buf[size - 1] = 0;

    int rc;
    osip_message_t *sip;

    rc = osip_message_init(&sip);
    if (rc != 0) { 
        fprintf(stderr, "cannot allocate\n"); 
        return -1; 
    }

    //add a breakpoint here
    rc = osip_message_parse(sip, (const char *)(buf), size);
    if (rc != 0) { 
        fprintf(stderr, "cannot parse sip message\n"); 
    }

    osip_message_free(sip);

    return 0;
}



// VERIFY THE CODE WITH ERROR
// #include <stdlib.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <assert.h>
// #include <string.h>

// #include <osipparser2/osip_message.h>

// int main() {
//     size_t size = 20;
//     char buf[20] = {0x01, 0x0A, 0x0A, 0x20, 0x01, 0x01, 0x3A, 0x01, 0x01, 
//                     0x01, 0x20, 0x53, 0x49, 0x50, 0x2F, 0x0D, 0x20, 0x3A, 0x0D, 0xFF};

//     int rc;
//     osip_message_t *sip;

//     rc = osip_message_init(&sip);
//     if (rc != 0) { 
//         fprintf(stderr, "cannot allocate\n"); 
//         return -1; 
//     }

//     rc = osip_message_parse(sip, (const char *)(buf), size);
//     if (rc != 0) { 
//         fprintf(stderr, "cannot parse sip message\n"); 
//     }

//     osip_message_free(sip);
//     return 0;
// }
