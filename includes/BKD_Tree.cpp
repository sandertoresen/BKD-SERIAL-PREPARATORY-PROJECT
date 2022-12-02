#include <iostream>
#include <list>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "Config.h"
#include "BKD_Tree.h"
#include "KDB_Tree.h"

void __print_dataNode(DataNode *ptr)
{
    printf("Cord:[");

    for (int d = 0; d < DIMENSIONS; d++)
    {
        if (d + 1 == DIMENSIONS)
        {
            // last
            printf("%d] data:%d\n", ptr->cordinates[d], ptr->data);
        }
        else
        {
            printf("%d, ", ptr->cordinates[d]);
        }
    }
}

class dataNodeCMP
{
    int dimension;

public:
    dataNodeCMP(int dim) : dimension(dim) {}

    // This operator overloading enables calling
    // operator function () on objects of increment
    bool operator()(DataNode &a, DataNode &b)
    {
        return (bool)(a.cordinates[dimension] < b.cordinates[dimension]);
    }
};

BKD_TREE::BKD_TREE() // default constructor
{
    // Generate memory array
    MemArray = new DataArray;
    if (MemArray == NULL)
    {
        exit(-1);
    }
    MemArray->size = 0;
}

BKD_TREE::~BKD_TREE() // Destructor
{
    // delete left;
    // delete right;
}

void BKD_TREE::_fetch_MemArray(DataArray *values)
{
    memcpy(values, MemArray, sizeof(DataArray));
}

void BKD_TREE::_fetch_DiskArray(DataArray *values)
{
    memcpy(values, DiskArray, sizeof(DataArray));
}

int BKD_TREE::insert(int value, int index[DIMENSIONS])
{ // insert value in memtable, if full push memtable to disk, if disk is full push to trees
    // space available in memory, insert
    bkd_tree_size++;
    if (MemArray->size < ARRAY_SIZE)
    {
        // create temporary pointer and increase size
        DataNode *tmp_data = &MemArray->array[MemArray->size++];

        tmp_data->data = value;
        memcpy(tmp_data->cordinates, index, sizeof(tmp_data->cordinates));

        return 1;
    }
    // Memory full, flush it to disk
    // if disk array free, flush data to it.
    else if (!DiskArrayFull)
    {
        DiskArray = MemArray;
        MemArray = new DataArray;
        MemArray->size = 0;
        DiskArrayFull = true;

        // create temporary pointer and increase size
        DataNode *tmp_data = &MemArray->array[MemArray->size++];
        tmp_data->data = value;

        memcpy(tmp_data->cordinates, index, sizeof(tmp_data->cordinates));

        return 1;
    }

    // MemArray and DiskArray is full, bulkloading new tree is needed.
    this->bulk_load_tree();

    // create temporary pointer and increase size
    DataNode *tmp_data = &MemArray->array[MemArray->size++];

    tmp_data->data = value;
    memcpy(tmp_data->cordinates, index, sizeof(tmp_data->cordinates));

    return 1;
}

int BKD_TREE::remove(int index[DIMENSIONS])
{
    // check memtable
    for (int i = 0; i < MemArray->size; i++)
    {
        if (__cord_equal(MemArray->array[i].cordinates, index))
        { // overwrite node and reduce array size
            if (MemArray->size - 1)
                memcpy(&MemArray->array[i], &MemArray->array[MemArray->size - 1], sizeof(DataNode));
            MemArray->size--;
            bkd_tree_size--;
            return 1;
        }
    }

    if (DiskArrayFull)
    {
        for (int i = 0; i < DiskArray->size; i++)
        {
            if (__cord_equal(DiskArray->array[i].cordinates, index))
            { // Set data to 0
                std::fill_n(DiskArray->array[i].cordinates, DIMENSIONS, 0);
                DiskArray->array[i].data = 0;
                bkd_tree_size--;
                DiskArray->size--;
                return 1;
            }
        }
    }
    // for each tree look for node and delete it
    for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
    {
        // return 1 if value is found and removed
        if (KDB_Tree_remove(*itr, index) == 1)
        {
            bkd_tree_size--;
            return 1;
        }
    }

    // TODO remove from tree or just use tombstone
    return 0;
}

void BKD_TREE::print_values()
{
    printf("Memory:\n");
    for (int i = 0; i < MemArray->size; i++)
    {
        __print_dataNode(&MemArray->array[i]);
    }
    printf("Disk:\n");
    if (DiskArrayFull)
    {
        for (int i = 0; i < DiskArray->size; i++)
        {
            __print_dataNode(&DiskArray->array[i]);
        }
    }

    // print all trees

    std::list<KDB_Tree *>::iterator it = trees.begin();
    printf("[%d]Trees:\n", trees.size());
    int count = 0;

    for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
    {
        KDB_Tree *ptr = *itr;
        printf("\nTree %d:\n", count++);
        printf("Leaf list:\n");
        if (ptr != NULL)
            __print_leafs(ptr);
        else
            printf("NULL\n");
    }
}

void BKD_TREE::range_search(int range[DIMENSIONS][2], std::list<DataNode> &values)
{ // range in search min, max for every dimension and list where values will be added.
    // Search MemArray
    for (int i = 0; i < MemArray->size; i++)
    {
        DataNode tmp_data = MemArray->array[i];
        bool in_range = true;
        for (int d = 0; d < DIMENSIONS; d++)
        {
            // check if node is within threshold, if not break and exit
            if (tmp_data.cordinates[d] < range[d][0] || tmp_data.cordinates[d] > range[d][1])
            {
                in_range = false;
                break;
            }
        }

        // if value in range add it to list
        if (in_range)
            values.push_back(tmp_data);
    }

    // Search DiskArray if it exists
    if (DiskArrayFull)
    {
        for (int i = 0; i < DiskArray->size; i++)
        {
            DataNode tmp_data = DiskArray->array[i];
            bool in_range = true;
            for (int d = 0; d < DIMENSIONS; d++)
            {
                // check if node is within threshold, if not break and exit
                if (tmp_data.cordinates[d] < range[d][0] || tmp_data.cordinates[d] > range[d][1])
                {
                    in_range = false;
                    break;
                }
            }

            // if value in range add it to list
            if (in_range)
                values.push_back(tmp_data);
        }
    }

    for (std::list<KDB_Tree *>::iterator it = trees.begin(); it != trees.end(); ++it)
    {
        if (*it != NULL)
            KDB_Tree_range_search(*it, range, values);
    }
}

void BKD_TREE::bulk_load_tree()
{
    // step 1, find first aveilable tree

    // count how many trees and nodes need inserting
    int num_nodes = MemArray->size + DiskArray->size;
    int trees_size = 0;

    // will add tree last if not changed
    bool add_last = true;
    std::list<KDB_Tree *>::iterator it;

    if (trees.size())
    {
        for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
        {
            KDB_Tree *ptr = *itr;
            if (ptr == NULL)
            {
                add_last = false;
                it = itr; // store pointer tree will be inserted
                break;
            }
            // TODO update tree size when deleting
            trees_size += ptr->size;
        }
    }

    num_nodes += trees_size;

    // allocate temporary file F, (store data DIMENSIONS times to be able to sort it on every dimention)

    DataNode *values = new DataNode[num_nodes * DIMENSIONS]; // allocate space for nodes per dim
    int offset = 0;
    for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
    { // copy all values from trees
        // break if we reach replacement node
        if (!add_last && itr == it)
            break;

        KDB_Tree *ptr = *itr;
        // insert data on first dimention |Mem|Disk|*Tree*
        KDB_Tree_fetch_all_nodes(ptr, &values[MemArray->size + DiskArray->size + offset]);
        offset += ptr->size;
    }

    // copy Mem and disk array
    memcpy(&values[0], MemArray->array, sizeof(DataNode) * MemArray->size);
    memcpy(&values[MemArray->size], DiskArray->array, sizeof(DataNode) * DiskArray->size);

    // memcpy mem and disk arrays
    for (int d = 0; d < DIMENSIONS; d++)
    {
        if (d) // paste over tree data
            memcpy(&values[d * num_nodes], &values[0], sizeof(DataNode) * num_nodes);

        std::sort(&values[d * num_nodes], &values[d * num_nodes + num_nodes], dataNodeCMP(d));
    }

    KDB_Tree *tree = Skratch_KDB_Create_Tree(values, num_nodes);

    // add tree at correct position
    if (add_last)
    {
        for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != trees.end(); ++itr)
        {
            KDB_Tree *ptr = *itr;
            // KDB_Tree_destroy(ptr);
            itr = trees.erase(itr);
            itr = trees.insert(itr, NULL);
        }

        trees.push_back(tree);
    }
    else
    {
        // remove all nodes before it and replace it
        it = trees.erase(it);
        it = trees.insert(it, tree);

        // delete all nodes before
        for (std::list<KDB_Tree *>::iterator itr = trees.begin(); itr != it; ++itr)
        {
            KDB_Tree *ptr = *itr;
            // KDB_Tree_destroy(ptr);
            itr = trees.erase(itr);
            itr = trees.insert(itr, NULL);
        }
    }

    // remove old nodes
    delete[] values;
    delete MemArray;
    delete DiskArray;

    MemArray = new DataArray;
    MemArray->size = 0;

    DiskArray = NULL;
    DiskArrayFull = false;
}

KDB_Tree *BKD_TREE::get_tree(int count)
{
    std::list<KDB_Tree *>::iterator it = trees.begin();
    int i = 0;
    while (*it != NULL)
    {
        KDB_Tree *ptr = *it;
        if (i == count)
            return ptr;

        if (it == trees.end())
        {
            break;
        }
        it++;
    }
    return NULL;
}

int BKD_TREE::get_size()
{
    return bkd_tree_size;
}