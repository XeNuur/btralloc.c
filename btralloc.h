#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum btralloc_mode {
    BTRALLOC_UP = 1 << 1,
    BTRALLOC_DOWN = 1 << 2,
} BtrAllocMode;

typedef struct btr_alloc{
    void *ptr;

    size_t alloc;
    size_t count;

    size_t per;
    uint32_t type_size; 
} BtrAlloc;

BtrAlloc *btralloc_new(const size_t, const size_t);
void btralloc_free(BtrAlloc*);
void btralloc_reallocex(BtrAlloc*, size_t, BtrAllocMode);

static inline void 
btralloc_realloc(BtrAlloc*in, size_t s) { 
    btralloc_reallocex(in, s, BTRALLOC_UP | BTRALLOC_DOWN); 
}

static inline void 
btralloc_push(BtrAlloc*in) { 
    btralloc_reallocex(in, in->count + 1, BTRALLOC_UP); 
}

static inline void 
btralloc_pop(BtrAlloc*in) { 
    btralloc_reallocex(in, in->count - 1, BTRALLOC_DOWN); 
}

#define BTRALLOC_PTR(in, t) ((t*)in->ptr)
#define BTRALLOC_LAST(in, t) ( ((t*)in->ptr) [in->count-1] )

