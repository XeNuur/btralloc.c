#include "btralloc.h"
#include <stdio.h>

int
main(void) {
    BtrAlloc *inst = btralloc_new(sizeof(int), 8);

    for(int i=0; i<80; i++) {
        btralloc_push(inst);
        BTRALLOC_PTR(inst, int)[i] = i;
    }
    printf("%d\n", BTRALLOC_LAST(inst, int) );

    btralloc_realloc(inst, 1);
    BTRALLOC_PTR(inst, int)[0] = 2137;
    printf("%d\n", BTRALLOC_LAST(inst, int) );

    btralloc_free(inst);
    return 0;
}

