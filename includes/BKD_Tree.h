#ifndef BKD_TREE_H
#define BKD_TREE_H
#include <list>
#include <cstdarg>
#include "Config.h"
#include "KDB_Tree.h"

// Smallest unit, node with data and index/cordinates

// For memory and disk storage
struct DataArray
{
    int size = 0;
    DataNode array[ARRAY_SIZE];
};

class BKD_TREE
{
public:
    BKD_TREE(); // default constructor
    // BKD_TREE(int x, int y) {} // constructor with variables

    ~BKD_TREE(); // Destructor

    // insert node with given value and index
    int insert(int value, int index[DIMENSIONS]);

    // remove value based on index
    int remove(int index[DIMENSIONS]);

    // fetch MemArray, memcpy it to given pointer
    void _fetch_MemArray(DataArray *values);

    // fetch DiskArray, memcpy it to given pointer
    void _fetch_DiskArray(DataArray *values);

    void range_search(int range[DIMENSIONS][2], std::list<DataNode> &values);

    void print_values();

    KDB_Tree *get_tree(int count);

    int get_size();

private:
    DataArray *MemArray;

    DataArray *DiskArray;
    bool DiskArrayFull = false;
    int bkd_tree_size = 0;
    std::list<KDB_Tree *> trees;

    // find first empty structure and bulk load into it
    void bulk_load_tree();
};

#endif

// BKD tree strucutre

// Mem_array[0] -> Disk_array[0] -> Disk_KDB[1] -> ... -> Disk_KDB[N]
// Struct size: Array config size, Disk_KDB[1] size = config_size + config_size, Disk_KDB[N] size = size of every struct from Mem_array[0] to Disk_KDB[N-1]

// Things to solve:

//  Transfering Mem_array[0] to Disk_array[0]
//  Grid loading
//  insert
//  delete
//  Window query

// Tests:

//  Can construct class on heap
//  Can insert in memtable
//  Can transfer memtable to disk
//  Can bulk load memtable and disktable to KDB tree

// implement delete
// implement search for node
// implement range search

// keep in mind memory management and memory leaks