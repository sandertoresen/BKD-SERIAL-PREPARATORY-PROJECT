#include <iostream>
#include <string.h>
#include "includes/Config.h"
#include "includes/BKD_Tree.h"
#include "includes/tests.h"

// Next steps:
//[1] Implement window query for MemArray and DiskArray
//  -> Need a compare function
//  -> loop through arrays and select data within window

//[2] Start bulk grid loading implementation
// -> need to sort input on all dimentions
// -> split data based on dimention
// -> build tree structure based on split grid data
// -> insert data in tree

//[3] figure out how trees should be merged together (gridloading without overflowing memory)

//[4] implement insert, remove and windowquery for final tree.

//[5] check for memory leaks

//[6] create performance tests and benchmark solution

int main()
{
    srand(0);
    // if (_test_inserts_MemArray() == -1)
    //     printf("[ERROR] MemArray insert test failed.\n");

    // if (_test_inserts_DiskArray() == -1)
    //     printf("[ERROR] DiskArray insert test failed.\n");

    // if (_test_remove_from_MemArray() == -1)
    //     printf("[ERROR] MemArray remove test failed.\n");

    // if (_test_remove_from_DiskArray() == -1)
    //     printf("[ERROR] DiskArray remove test failed.\n");

    // if (_test_window_query_MemArray() == -1)
    //     printf("[ERROR] Range search failed!\n");

    // if (_test_bulk_loading_single_tree() == -1)
    //     printf("[ERROR] Bulk loading single tree failed!\n");

    // if (_test_fetching_KDB_tree() == -1)
    //     printf("[ERROR] Fetching KDB tree failed!\n");

    // if (_test_bulk_loading_multiple_trees() == -1)
    //     printf("[ERROR] Bulk loading multiple tree failed!\n");

    // if (_test_remove_from_last_tree() == -1)
    //     printf("[ERROR] Tree remove test failed.\n");

    // _performance_test_inserts();
    _performance_test_deletes();
}

// Things to solve:
/*
- (4)KDB_Tree assume KDB_LEAF_SIZE  (think this is done)

- (1) implement tombstone deletion solution

- Testing?
- Create more tests to find all possible problems?


- Benchmark
- Delete vs tombstone
- worst case insert
- view how time grows on each bulkload

Configure parameters:
- Lower and higher Array sizes

Compare solution against b+-tree?
Insert vs range


- performance (100% lookup test, 80%, 50, 30, 20, 10)

- Memory leaks? (siste prioritering)


*/