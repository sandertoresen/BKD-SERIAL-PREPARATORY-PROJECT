#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>
#include "tests.h"
#include "Config.h"
#include "BKD_Tree.h"

int _test_inserts_MemArray()
{ // Fill tree memory structure and verify data
    BKD_TREE *tree = new BKD_TREE();

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int cords[DIMENSIONS] = {};
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = j * i;
        }

        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    // verify result
    DataArray *MemArray = new DataArray;
    tree->_fetch_MemArray(MemArray);
    if (MemArray->size != ARRAY_SIZE)
    {
        // MemArray size is off
        printf("Wrong MemArray size, data is lost\n");
        tree->~BKD_TREE();
        delete MemArray;
        return -1;
    }

    // Compare and assert data is correct
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int solution_cordinates[DIMENSIONS] = {};
        int solution_data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            solution_cordinates[j] = j * i;
        }

        // check data is correct
        if (solution_data != MemArray->array[i].data)
        {
            printf("Inserted data is wrong.\n");
            tree->~BKD_TREE();
            delete MemArray;
            return -1;
        }

        for (int c = 0; c < DIMENSIONS; c++)
        {
            if (MemArray->array[i].cordinates[c] != solution_cordinates[c])
            {
                printf("Inserted cordinate is wrong.\n");
                tree->~BKD_TREE();
                delete MemArray;
                return -1;
            }
        }
    }

    tree->~BKD_TREE();
    delete MemArray;
    printf("Insert MemArray succeded!\n");
    return 1;
}

int _test_inserts_DiskArray()
{ // Fill tree memory structure and fill disk data
    BKD_TREE *tree = new BKD_TREE();

    for (int i = 0; i < ARRAY_SIZE * 2; i++)
    {
        int cords[DIMENSIONS] = {};
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = j * i;
        }

        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }
    // verify result
    DataArray *DiskArray = new DataArray;

    tree->_fetch_DiskArray(DiskArray);
    if (DiskArray->size != ARRAY_SIZE)
    {
        // DiskArray size is off
        printf("Wrong DiskArray size, data is lost\n");
        tree->~BKD_TREE();
        delete DiskArray;
        return -1;
    }

    // Compare and assert data is correct
    for (int i = 0; i < ARRAY_SIZE; i++)
    { // first inserted data should be data in disk array
        int solution_cordinates[DIMENSIONS] = {};
        int solution_data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            solution_cordinates[j] = j * i;
        }

        // check data is correct
        if (solution_data != DiskArray->array[i].data)
        {
            printf("Inserted data is wrong.\n");
            tree->~BKD_TREE();
            delete DiskArray;
            return -1;
        }

        for (int c = 0; c < DIMENSIONS; c++)
        {
            if (DiskArray->array[i].cordinates[c] != solution_cordinates[c])
            {
                printf("Inserted cordinate is wrong.\n");
                tree->~BKD_TREE();
                delete DiskArray;
                return -1;
            }
        }
    }

    tree->~BKD_TREE();
    delete DiskArray;
    printf("Insert DiskArray succeded!\n");
    return 1;
}

int _test_remove_from_MemArray()
{ // Fill tree memory structure
    BKD_TREE *tree = new BKD_TREE();
    // Data node to remove
    DataNode removed_node;
    // remove middle value
    int insert_nr = ARRAY_SIZE / 2;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int cords[DIMENSIONS] = {};
        int data = i + 100;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = j * i + i;

            // store node we will remove
            if (i == insert_nr)
                removed_node.cordinates[j] = cords[j];
        }

        if (i == insert_nr)
        {
            removed_node.data = i + 100;
        }

        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    // remove node with given cords
    tree->remove(removed_node.cordinates);

    // verify node is removed
    DataArray *MemArray = new DataArray;
    tree->_fetch_MemArray(MemArray);
    if (MemArray->size != ARRAY_SIZE - 1)
    {
        // MemArray size is off
        printf("Wrong MemArray size, data is removed wrongly\n");
        tree->~BKD_TREE();
        free(MemArray);
        return -1;
    }

    // Assert deleted node is no longer in structure
    for (int i = 0; i < ARRAY_SIZE; i++)
    { // first inserted data should be data in disk array

        // If removed value is found, assert it's also the same cords
        if (removed_node.data == MemArray->array[i].data)
        {
            bool equal = true;

            for (int j = 0; j < DIMENSIONS; j++)
            {
                if (removed_node.cordinates[j] != MemArray->array->cordinates[j])
                { // not same cords
                    equal = false;
                    break;
                }
            }
            if (equal)
            {
                printf("Deleted node wasn't removed!.\n");
                tree->~BKD_TREE();
                free(MemArray);
                return -1;
            }
        }
    }

    tree->~BKD_TREE();
    free(MemArray);
    printf("Remove MemArray succeded!\n");
    return 1;
}

int _test_remove_from_DiskArray()
{ // Fill tree memory structure and fill disk data
    BKD_TREE *tree = new BKD_TREE();
    // Data node to remove
    DataNode removed_node;
    // remove middle value in disk array
    int insert_nr = ARRAY_SIZE / 2;

    for (int i = 0; i < ARRAY_SIZE * 2; i++)
    {
        int cords[DIMENSIONS] = {};
        int data = i + 100;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = j * i + i;

            // store node we will remove
            if (i == insert_nr)
                removed_node.cordinates[j] = cords[j];
        }

        if (i == insert_nr)
        {
            removed_node.data = i + 100;
        }
        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    // remove node with given cords
    tree->remove(removed_node.cordinates);

    // verify node is removed
    DataArray *DiskArray = new DataArray;
    tree->_fetch_DiskArray(DiskArray);
    if (DiskArray->size != ARRAY_SIZE - 1)
    {
        // DiskArray size is off
        printf("Wrong DiskArray size, data is removed wrongly\n");
        tree->~BKD_TREE();
        free(DiskArray);
        return -1;
    }

    // Assert deleted node is no longer in structure
    for (int i = 0; i < ARRAY_SIZE; i++)
    { // first inserted data should be data in disk array

        // If removed value is found, assert it's also the same cords
        if (removed_node.data == DiskArray->array[i].data)
        {
            bool equal = true;

            for (int j = 0; j < DIMENSIONS; j++)
            {
                if (removed_node.cordinates[j] != DiskArray->array->cordinates[j])
                { // not same cords
                    equal = false;
                    break;
                }
            }
            if (equal)
            {
                printf("Deleted node wasn't removed!.\n");
                tree->~BKD_TREE();
                free(DiskArray);
                return -1;
            }
        }
    }

    tree->~BKD_TREE();
    free(DiskArray);
    printf("Remove DiskArray succeded!\n");
    return 1;
}

int _test_remove_from_last_tree()
{
    BKD_TREE *tree = new BKD_TREE();
    int size = ARRAY_SIZE * 20 + 1;

    int remove_node[DIMENSIONS];
    int cords[DIMENSIONS] = {};
    for (int i = 0; i < size; i++)
    {
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = rand() % 1000;
            if (i == 5) // store node we will delete
                remove_node[j] = cords[j];
        }

        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    if (tree->remove(remove_node) != 1)
    {
        printf("Didn't find node to delete!\n");
        tree->~BKD_TREE();
        return -1;
    }
    std::list<DataNode> result;
    int range[DIMENSIONS][2];
    for (int d = 0; d < DIMENSIONS; d++)
    {
        // entire input range
        range[d][0] = remove_node[d];
        range[d][1] = remove_node[d];
    }

    tree->range_search(range, result);

    if (result.size())
    { // if value was found, failed
        tree->~BKD_TREE();
        return -1;
    }
    printf("test remove from tree succeded!\n");
    tree->~BKD_TREE();
    return 1;
}

int _test_window_query_MemArray()
{
    // Fill tree memory structure and verify data
    BKD_TREE *tree = new BKD_TREE();

    for (int i = 0; i < ARRAY_SIZE * 2; i++)
    {
        int cords[DIMENSIONS] = {};
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = i;
        }

        if (tree->insert(data, cords) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            return -1;
        }
    }

    std::list<DataNode> result;
    int range[DIMENSIONS][2];
    for (int d = 0; d < DIMENSIONS; d++)
    {
        range[d][0] = ARRAY_SIZE / 20;
        range[d][1] = ARRAY_SIZE / 10;
    }

    tree->range_search(range, result);

    int min_val = ARRAY_SIZE / 20;
    int max_val = ARRAY_SIZE / 10;
    if (result.size() != (max_val - min_val + 1))
    {
        printf("Range query returned less results than expected. \n");
        ARRAY_SIZE / 10;

        return -1;
    }

    for (int i = min_val; i <= max_val; i++)
    {
        // look for given val
        DataNode test_val;
        for (int d = 0; d < DIMENSIONS; d++)
        {
            test_val.cordinates[d] = i;
        }
        test_val.data = i;

        bool found_node = false;
        // look for test val in result list
        for (DataNode tmp_data : result)
        {

            if (__cord_equal(tmp_data.cordinates, test_val.cordinates) && tmp_data.data == test_val.data)
            {
                found_node = true;
                break;
            }
        }
        if (!found_node)
        {
            printf("Didn't find node in range search result!\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    printf("MemArray range search succeded!\n");
    return 1;
}

int _test_bulk_loading_single_tree()
{
    BKD_TREE *tree = new BKD_TREE();

    int size = ARRAY_SIZE * 2 + 1;
    int cords[size][DIMENSIONS] = {};
    for (int i = 0; i < size; i++)
    {
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[i][j] = rand() % 1000;
        }

        if (tree->insert(data, cords[i]) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    std::list<DataNode> result;
    int range[DIMENSIONS][2];
    for (int d = 0; d < DIMENSIONS; d++)
    {
        // entire input range
        range[d][0] = 0;
        range[d][1] = 1000;
    }
    tree->range_search(range, result);

    for (int i = 0; i < size; i++)
    {
        bool found_value = false;
        for (std::list<DataNode>::iterator it = result.begin(); it != result.end(); ++it)
        {
            if (it->data == i)
            {
                found_value = true;
                break;
            }
        }
        if (!found_value)
        {
            printf("Didn't find %d!\n", i);
            tree->~BKD_TREE();
            // DELETE result!
            return -1;
        }
    }

    printf("test bulk loading single tree succeded!\n");
    return 1;
}

int _test_fetching_KDB_tree()
{
    BKD_TREE *tree = new BKD_TREE();
    int tree_size = ARRAY_SIZE * 2;
    int size = tree_size + 1;
    int cords[size][DIMENSIONS] = {};
    for (int i = 0; i < size; i++)
    {
        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[i][j] = rand() % 1000;
        }

        if (tree->insert(data, cords[i]) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }

    DataNode *values = new DataNode[tree_size];
    KDB_Tree *first = tree->get_tree(0);
    KDB_Tree_fetch_all_nodes(first, values);

    for (int i = 0; i < tree_size; i++)
    { // assert nodes match input data
        bool found_data = false;
        for (int j = 0; j < tree_size; j++)
        {
            if (values[j].data == i)
            {
                found_data = true;
                // found data, check cords!
                for (int d = 0; d < DIMENSIONS; d++)
                {
                    if (__cord_equal(cords[i], values[j].cordinates) != 1)
                    { // cords doesn't match
                        tree->~BKD_TREE();
                        delete[] values;
                        return -1;
                    }
                }
                break;
            }
        }
        if (!found_data)
        {
            tree->~BKD_TREE();
            delete[] values;
            return -1;
        }
    }

    tree->~BKD_TREE();
    delete values;
    printf("Fetch all nodes from KDB_Tree succeded!\n");
    return 1;
}

int _test_bulk_loading_multiple_trees()
{
    BKD_TREE *tree = new BKD_TREE();
    int size = ARRAY_SIZE * 20 + 1;
    // TODO under variable don't handle 20 * 16k values
    int cords[size][DIMENSIONS] = {};
    for (int i = 0; i < size; i++)
    {

        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[i][j] = rand() % 1000;
        }
        if (tree->insert(data, cords[i]) == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }
    std::list<DataNode> result;
    int range[DIMENSIONS][2];
    for (int d = 0; d < DIMENSIONS; d++)
    {
        // entire input range
        range[d][0] = 0;
        range[d][1] = 100000;
    }

    tree->range_search(range, result);

    for (int i = 0; i < size; i++)
    {
        bool found_value = false;
        for (std::list<DataNode>::iterator it = result.begin(); it != result.end(); ++it)
        {
            if (it->data == i)
            {
                found_value = true;
                break;
            }
        }
        if (!found_value)
        {
            tree->~BKD_TREE();
            // DELETE result!
            return -1;
        }
    }
    printf("test bulk loading multiple trees succeded!\n");
    return 1;
}

int _performance_test_inserts()
{
    BKD_TREE *tree = new BKD_TREE();

    int size = ARRAY_SIZE * 40 + 1;
    // TODO under variable don't handle 20 * 16k values
    int cords[DIMENSIONS] = {};
    bool overflow;

    long int *timings = new long int[size];

    // open file
    std::ofstream MyFile("timings_inserts.txt");

    for (int i = 0; i < size; i++)
    {

        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            cords[j] = rand() % 1000;
        }

        auto start = std::chrono::high_resolution_clock::now();
        int added = tree->insert(data, cords);
        auto stop = std::chrono::high_resolution_clock::now();

        overflow = false;
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        if (duration.count() < 0)
        {
            printf("Integer overflow!\n");
            overflow = true;
            duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
            if (duration.count() < 0)
            {
                printf("overflow again\n");
                exit(1);
            }
        }
        if (added == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
        timings[i] = duration.count();
        if (timings[i] < 0)
        {
            printf("timings overflow!\n");
            exit(1);
        }
        if (overflow)
            MyFile << timings[i] * 1000000000 << std::endl;
        else
            MyFile << timings[i] << std::endl;
    }
    if (tree->get_size() != size)
    {
        printf("OBS.. Wrong size!\n");
    }

    // Write to the file

    // Got all timings write them to file

    MyFile.close();
    printf("performance test insert succeded!\n");
    tree->~BKD_TREE();
    return 1;
}

int _performance_test_deletes()
{
    BKD_TREE *tree = new BKD_TREE();

    int size = ARRAY_SIZE * 40 + 1;
    // TODO under variable don't handle 20 * 16k values
    int cords[DIMENSIONS] = {};
    int remove_cords[100][DIMENSIONS];
    for (int i = 0; i < size; i++)
    {

        int data = i;
        for (int j = 0; j < DIMENSIONS; j++)
        {
            if (i < 100)
            {
                cords[j] = -(rand() % 1000);
                remove_cords[i][j] = cords[j];
            }
            else
                cords[j] = rand() % 1000;
        }
        int added = tree->insert(data, cords);
        if (added == -1)
        { // return -1 if insert failed
            printf("Inserting data failed\n");
            tree->~BKD_TREE();
            return -1;
        }
    }
    if (tree->get_size() != size)
    {
        printf("OBS.. Wrong size!\n");
    }

    long int *timings = new long int[100];

    // open file
    std::ofstream MyFile("timings_deletes.txt");
    // remove test start
    for (int i = 0; i < 100; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        tree->remove(remove_cords[i]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        timings[i] = duration.count();
        if (timings[i] < 0)
        {
            printf("timings overflow!\n");
            exit(1);
        }
        if (i + 1 != 100)
            MyFile << timings[i] << std::endl;
        else
            MyFile << timings[i];
    }

    MyFile.close();

    printf("performance test insert succeded!\n");
    tree->~BKD_TREE();
    return 1;
}