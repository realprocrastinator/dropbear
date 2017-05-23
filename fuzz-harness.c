#include "includes.h"
#include "buffer.h"
#include "dbutil.h"

extern int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size);

int main(int argc, char ** argv) {
    int i;
    buffer *input = buf_new(100000);

    for (i = 1; i < argc; i++) {
#if DEBUG_TRACE
        if (strcmp(argv[i], "-v") == 0) {
            debug_trace = 1;
        }
#endif
    }

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // ignore arguments
            continue;
        }

        char* fn = argv[i];
        buf_setlen(input, 0);
        buf_readfile(input, fn);
        buf_setpos(input, 0);

        printf("Running %s once \n", fn);
        LLVMFuzzerTestOneInput(input->data, input->len);
        printf("Running %s twice \n", fn);
        LLVMFuzzerTestOneInput(input->data, input->len);
        printf("Done %s\n", fn);
    }

    printf("Finished\n");

    return 0;
}