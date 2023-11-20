#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>
#include <time.h>

//first test for small allocation amoutns
void testSmallAlloc() {
    char* pntrs[1000];
   //1 to 1000
    for(int i = 0; i < 1000; i++) {
        pntrs[i] = (char*) malloc(1);
    }
    for(int i = 0; i < 1000; i++) {
        free(pntrs[i]);
    }
}

//second test repeated amounts
void testRepeatAllocFree() {
    for(int i = 0; i < 1000; i++) {
        char* ptr = (char*) malloc(10);
        //free remaining
        free(ptr);
    }
}

//third test mixed random amounts
void testMixedAlloc() {
    char* pntrs[1000];
    //we can do it in incriments of like 0 - 500 and then =250 there after
    for(int i = 0; i < 500; i++) {
        pntrs[i] = (char*) malloc(1);
    }

    for(int i = 500; i < 750; i++) {
        pntrs[i] = (char*) malloc(500);
    }

    for(int i = 750; i < 1000; i++) {
        pntrs[i] = (char*) malloc(1);
    }
    
    for(int i = 0; i < 1000; i++) {
        //free remaining
        free(pntrs[i]);
    }
}



//coalescing test which is final needed thingy
void CoalescingTest() {
    char* pntrs[4];
    
    // allocate 1000 bytes 4 times
    for(int i = 0; i < 4; i++) {
        pntrs[i] = (char*) malloc(1000);
    }

    // free the first 2 allocations
    free(pntrs[0]);
    free(pntrs[1]);

    // allocate 1500 bytes
    char* newPointer = (char*) malloc(1500);

    // free alloc that remains
    free(pntrs[2]);
    free(pntrs[3]);
    free(newPointer);
}

void error_Test() {
    // Calling free() with an address not obtained from malloc().
    int x;
    free(&x);

    // Calling free() with an address not at the start of a chunk.
    int *y = malloc(sizeof(int)*2);
    free(y+1);

    // Calling free() a second time on the same pointer.
    int *p = malloc(sizeof(int)*1);
    int *q = p;
    free(p);
    free(q);
}

void PerfTest_1() {
    for (int i = 0; i < 120; i++) {
        char* p = malloc(1);
        free(p);
    }
}

void PerfTest_2() {
    char* p[120];
    for (int i = 0; i < 120; i++) {
        p[i] = malloc(1);
    }
    for (int i = 0; i < 120; i++) {
        free(p[i]);
    }
}

void PerfTest_3() {
    char* p[120];
    int alloc = 0;
    int de_alloc = 0;
    int random = 0;
    while (alloc < 120) {
        random = rand() % 2;
        if (random == 0) {
            p[alloc] = malloc(1);
            alloc++;
        } else {
            if (alloc > de_alloc) {
                int random_2 = rand() % alloc;
                free(p[random_2]);
                p[random_2] = NULL;
                de_alloc++;
            }
        }
    }

    for (int i = 0; i < alloc; i++) {
        free(p[i]);
        p[i] = NULL;
    }
}

int main() {
    //clock variab
    clock_t start, end;
    //cpu time
    double cpu_time;

    //small alloc
    start = clock(); //start clock
    testSmallAlloc();//run test
    end = clock();//end clock

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC; // this will give us time spent
    printf("Time taken for testSmallAlloc: %f\n", cpu_time);//print!

    //repeat alloc
    start = clock();
    testRepeatAllocFree();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for testRepeatAllocFree: %f\n", cpu_time);

    //mixed alloc
    start = clock();
    testMixedAlloc();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for testMixedAlloc: %f\n", cpu_time);

    //coalescing
    start = clock();
    CoalescingTest();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for CoalescingTest: %f\n", cpu_time);

    // errors
    start = clock();
    error_Test();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for error2_Test: %f\n", cpu_time);

    // Performance Test 1
    start = clock();
    PerfTest_1();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for PerfTest_1: %f\n", cpu_time);

    // Performance Test 2
    start = clock();
    PerfTest_2();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for PerfTest_2: %f\n", cpu_time);

    // Performance Test 3
    start = clock();
    PerfTest_3();
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for PerfTest_3: %f\n", cpu_time);

    return 0;
}