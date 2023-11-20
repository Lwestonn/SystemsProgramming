Systems Programming - Assignment 1
my little malloc()

Group:
Lucas Weston - lsw78
Woogyeom Sim - ws386

Test plan:
Mem Grind holds all test functions. The goal with testing our mymalloc() and myFree() is to test 3 main types of allocation: 
1. small allocation amounts
2. mixed allocation
3. repeated allocation of freeing variables

If all three of these tests work then we believe that the program is able to handle small amounts, mixed, and repeated usage.
These 3 attributes cover most cases of memory allocation






Description of test functions:
1. testSmallAllocations()
small test for allocation. most basic test that we have it goes from 1 to 1000 adds to the array then frees it up after


2. testRepeatedAllocFree()
test repeats over and over through the entire for loop to stress test. Longest test out of the ones we have made with the longest time taken

3. testMixedAllocations()
test of mixed values that go in incriments of 0 - 500, 500 - 750, 750 - 1000
the time taken for this test varies heavily based on what is chosen so there is no consistent time


4. CoalescingTest()
Allocate 1000 bytes 4 times using mymalloc() and free the first two blocks using myfree(),
then allocate 1500 bytes using mymalloc() to test if the first two freed blocks coalesce and are
ready to be allocated again.


5. error tests
error_test is the set of tests for error detection in the pdf and PerfTest_1, 2, 3 are the performance tests based on the pdf
the point of this is to showcase that there is an error message that shows when one of the 3 listed errors occurs.


6. Performance tests
these are 3 base tests done to check the time differences between different inputs
each performance test gives a different random input 




Extra design notes:


Test times for each test:

Time taken for testSmallAlloc: 0.000018
Time taken for testRepeatAllocFree: 0.000015
Time taken for testMixedAlloc: 0.000013
Time taken for CoalescingTest: 0.000001
Calling free() either with an address not obtained from malloc() or with an address not at the start of a chunk. memgrind.c(76) // error test
Calling free() either with an address not obtained from malloc() or with an address not at the start of a chunk. memgrind.c(80) // error test
Time taken for error2_Test: 0.000011
Time taken for PerfTest_1: 0.000002
Time taken for PerfTest_2: 0.000002
Time taken for PerfTest_3: 0.000010

