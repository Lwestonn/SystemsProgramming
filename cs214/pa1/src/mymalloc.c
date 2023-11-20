#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "mymalloc.h"


//literally given to us
#define MEMLENGTH 512
double memory[MEMLENGTH];

// pointer to the start of  heap
chunkHeader* startHeap = (chunkHeader*) memory;

void* freed_ptr = NULL;

// initialize the heap
void initialHeap() {
    //head of heap to find new mem length
    startHeap->size = MEMLENGTH - sizeof(chunkHeader);
    startHeap->next = NULL;
    startHeap->alloc = 0;
}

// Malloc
void* mymalloc(size_t size, char *file, int line) {
    if (startHeap->size == 0) {
        initialHeap();
    }

    if (size <= 0) {
        return NULL;
    }

    // find an unallocated chunk that fits the request
    chunkHeader* current = startHeap;
    while (current) {
        if (!current->alloc && current->size >= size) {
            current->alloc = 1;
            if ((current + 1) == freed_ptr) {
                freed_ptr = NULL;
            }
            return (void*)(current + 1); // return pointer
        }
        if (!current->next) {
            if ((char*)current + sizeof(chunkHeader) + current->size + sizeof(chunkHeader) < (char*)memory + MEMLENGTH) {
                chunkHeader* newChunk = (chunkHeader*)((char*)current + sizeof(chunkHeader) + current->size);
                newChunk->size = MEMLENGTH - ((char*)newChunk - (char*)memory - sizeof(chunkHeader));
                newChunk->next = NULL;
                newChunk->alloc = 0;
                current->next = newChunk;
            } else {
                return NULL;
            }
        }
        current = current->next;
    }

    printf("Not Malloced %s(%d)\n", file, line);
    return NULL; // only return null if failed
}

void coalescing() {
    chunkHeader* current = startHeap;
    while (current) {
        if (current->next) {
            if (!(current->alloc) && !(current->next->alloc)) {
            current->size += current->next->size + sizeof(chunkHeader);
            current->next = current->next->next;
            }
        }
        current = current->next;
    }
}

//myfree function
void myfree(void* ptr, char *file, int line) {

    if (!ptr) {
        return;
    }

    if (ptr == freed_ptr) {
        printf("Calling free() a second time on the same pointer. %s(%d)\n", file, line);
        return;
    }

    chunkHeader* current = startHeap;

    while (current) {
        if ((void*) current + sizeof(chunkHeader) == ptr) {
            break;
        }
        current = current->next;
    }

    if (!current) {
        printf("Calling free() either with an address not obtained from malloc() or with an address not at the start of a chunk. %s(%d)\n", file, line);
        return;
    }

    current->alloc = 0;
    coalescing();
    
    freed_ptr = ptr;
    return;
}

