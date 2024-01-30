#include "btralloc.h"
#include <stdlib.h>

BtrAlloc* 
btralloc_new(const size_t _type_size, const size_t _per) {
    BtrAlloc *new = malloc( sizeof(BtrAlloc) );
    *new = (BtrAlloc) {
        .ptr = malloc(1),
        .alloc = 0,
        .count = 0,

        .per = _per,
        .type_size = _type_size,
    };
    return new;
}

void 
btralloc_free(BtrAlloc *self) {
    free(self->ptr);
    free(self);
}

void 
btralloc_reallocex(BtrAlloc *self, size_t new_count, BtrAllocMode mode) {
    int is_too_big = (mode & BTRALLOC_UP) ? 
        self->alloc < new_count : 0;
    int is_too_small = (mode & BTRALLOC_DOWN) ?
        (self->alloc - self->count) / self->per : 0;

    if (is_too_big || is_too_small) {
        self->alloc = (new_count / self->per + 1) * self->per;
        self->ptr = realloc(self->ptr, self->alloc * self->type_size);
    }
    self->count = new_count;
}
