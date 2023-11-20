// mymalloc.h
#include <stddef.h>


//chunk head struct
typedef struct chunkHeader {
    size_t size;
    struct chunkHeader* next;
    int alloc;
} chunkHeader;

void initialHeap();
void* mymalloc(size_t size, char *file, int line);
void coalescing();
void myfree(void* ptr, char *file, int line);

extern void* freed_ptr;

//def for malloc and free variables
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
//free
#define free(p) myfree(p, __FILE__, __LINE__)
