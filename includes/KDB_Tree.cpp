#include <iostream>
#include <string.h>
#include <list>
#include "Config.h"
#include "KDB_Tree.h"

void __print_kdb_branch(KDB_branch *branch)
{
    if (!branch)
    {
        printf("bottom\n");
    }
    if (branch->leaf != NULL)
    {
        if (KDB_LEAF_SIZE == 1)
        {
            printf("Leaf : ");
            for (int d = 0; d < DIMENSIONS; d++)
            {
                if (!d)
                    printf("[(%d, ", branch->leaf->LeafArray[0].cordinates[0]);
                else if (d + 1 == DIMENSIONS)
                    printf("%d) data:%d]\n", branch->leaf->LeafArray[0].cordinates[d], branch->leaf->LeafArray[0].data);
                else
                    printf("%d, ", branch->leaf->LeafArray[0].cordinates[d]);
            }
            return;
        }
        printf("Leafs : ");
        for (int i = 0; i < KDB_LEAF_SIZE; i++)
        {
            for (int d = 0; d < DIMENSIONS; d++)
            {
                if (!d)
                    printf("[(%d, ", branch->leaf->LeafArray[i].cordinates[d]);
                else if (d + 1 == DIMENSIONS)
                    printf("%d) data:%d] ", branch->leaf->LeafArray[i].cordinates[d], branch->leaf->LeafArray[i].data);
                else
                    printf("%d, ", branch->leaf->LeafArray[i].cordinates[d]);
            }
        }
        printf("\n");

        return;
    }

    __print_kdb_branch(branch->left);
    __print_kdb_branch(branch->right);
}

void __print_kdb_tree(KDB_Tree *tree)
{
    __print_kdb_branch(tree->left);
    __print_kdb_branch(tree->right);
}

void __print_leafs(KDB_Tree *tree)
{
    KDB_branch *ptr = tree->firts_leaf;
    while (ptr != NULL)
    {
        if (KDB_LEAF_SIZE == 1)
        {
            printf("Leaf : ");
            for (int d = 0; d < DIMENSIONS; d++)
            {
                if (!d)
                    printf("[(%d, ", ptr->leaf->LeafArray[0].cordinates[0]);
                else if (d + 1 == DIMENSIONS)
                    printf("%d) data:%d]\n", ptr->leaf->LeafArray[0].cordinates[d], ptr->leaf->LeafArray[0].data);
                else
                    printf("%d, ", ptr->leaf->LeafArray[0].cordinates[d]);
            }
        }
        else
        {
            printf("Leafs : ");
            for (int i = 0; i < KDB_LEAF_SIZE; i++)
            {
                for (int d = 0; d < DIMENSIONS; d++)
                {
                    if (!d)
                        printf("[(%d, ", ptr->leaf->LeafArray[i].cordinates[d]);
                    else if (d + 1 == DIMENSIONS)
                        printf("%d) data:%d] ", ptr->leaf->LeafArray[i].cordinates[d], ptr->leaf->LeafArray[i].data);
                    else
                        printf("%d, ", ptr->leaf->LeafArray[i].cordinates[d]);
                }
            }
            printf("\n");
        }
        ptr = ptr->next_leaf;
    }
}

int __cord_equal(int c1[DIMENSIONS], int c2[DIMENSIONS])
{
    for (int i = 0; i < DIMENSIONS; i++)
    {
        if (c1[i] != c2[i])
            return 0;
    }
    return 1;
}

KDB_branch *KDB_Create_Branch(DataNode *values, int num_nodes, KDB_Tree *root, KDB_branch *parent_node, int current_dim)
{

    if (num_nodes <= KDB_LEAF_SIZE)
    {
        if (!parent_node)
        {
            printf("ERROR parent node = NULL!\n");
            return NULL;
        }
        // create new leaf and insert values
        KDB_branch *leaf_branch = new KDB_branch;
        leaf_branch->dimension = current_dim;
        leaf_branch->leaf = new KDB_Leaf;

        // add root pointer
        if (root->firts_leaf == NULL)
        {
            root->firts_leaf = leaf_branch;
        }
        else
        {
            KDB_branch *ptr = root->firts_leaf;
            while (ptr != NULL)
            {
                if (ptr->next_leaf == NULL)
                {
                    ptr->next_leaf = leaf_branch;
                    break;
                }
                ptr = ptr->next_leaf;
            }
        }
        memcpy(&leaf_branch->leaf->LeafArray, &values[num_nodes * current_dim], sizeof(DataNode) * num_nodes);
        return leaf_branch;
    }

    // int mid = low + ((high - low)) / 2;
    int left_idx = num_nodes / 2 - !(num_nodes % 2);
    int right_idx = left_idx + 1;

    int right_size = right_idx - (num_nodes % 2);

    KDB_branch *branch = new KDB_branch;
    branch->dimension = current_dim;

    branch->split = (values[num_nodes * current_dim + left_idx].cordinates[current_dim] + values[num_nodes * current_dim + right_idx].cordinates[current_dim]) / 2;
    printf("\n\n");
    printf("Sizes Left/Right %d/%d\n", right_idx * DIMENSIONS, right_size * DIMENSIONS);
    DataNode *left_vals = new DataNode[right_idx * DIMENSIONS];
    DataNode *right_vals = new DataNode[right_size * DIMENSIONS];

    printf("Insert pos Left/Right %d/%d\n", current_dim * right_idx, current_dim * right_size);
    printf("Nr of inserts Left/Right %d/%d\n", right_idx, right_size);

    memcpy(&left_vals[current_dim * right_idx], &values[current_dim * num_nodes], sizeof(DataNode) * right_idx);
    memcpy(&right_vals[current_dim * right_size], &values[current_dim * num_nodes + right_idx], sizeof(DataNode) * right_size);

    int left_count[DIMENSIONS] = {};
    int right_count[DIMENSIONS] = {};

    for (int i = 0; i < num_nodes; i++)
    {
        for (int d = 0; d < DIMENSIONS; d++)
        {
            if (d == current_dim)
                continue;
            DataNode tmp = values[num_nodes * d + i];

            if (tmp.cordinates[current_dim] <= branch->split) // left
            {
                left_vals[right_idx * d + left_count[d]++] = tmp;
            }

            else
            { // right
                right_vals[right_size * d + right_count[d]++] = tmp;
            }
        }
    }

    branch->left = KDB_Create_Branch(left_vals, right_idx, root, branch, (current_dim + 1) % DIMENSIONS);
    branch->right = KDB_Create_Branch(right_vals, right_size, root, branch, (current_dim + 1) % DIMENSIONS);

    // delete[] left_vals;
    // delete[] right_vals;

    return branch;
}

KDB_Tree *KDB_Create_Tree(DataNode *values, int num_nodes)
{ // if val > split: go right else left
    KDB_Tree *tree = new KDB_Tree;
    tree->size = num_nodes;

    int left_idx = num_nodes / 2 - !(num_nodes % 2);
    int right_idx = left_idx + 1;

    int right_size = right_idx - (num_nodes % 2);
    tree->split = (values[left_idx].cordinates[0] + values[right_idx].cordinates[0]) / 2;

    DataNode *left_vals = new DataNode[right_idx * DIMENSIONS];
    DataNode *right_vals = new DataNode[right_size * DIMENSIONS];

    memcpy(left_vals, &values[0], sizeof(DataNode) * right_idx);
    memcpy(right_vals, &values[num_nodes / 2], sizeof(DataNode) * right_size);

    // TODO remove these
    int left_count[DIMENSIONS] = {};
    int right_count[DIMENSIONS] = {};

    for (int i = 0; i < num_nodes; i++)
    {
        for (int d = 1; d < DIMENSIONS; d++)
        {
            DataNode tmp = values[num_nodes * d + i];
            if (tmp.cordinates[0] <= tree->split) // left

                left_vals[right_idx * d + left_count[d]++] = tmp;

            else // right
                right_vals[right_size * d + right_count[d]++] = tmp;
        }
    }

    tree->left = KDB_Create_Branch(left_vals, right_idx, tree, NULL, (1) % DIMENSIONS);
    tree->right = KDB_Create_Branch(right_vals, right_size, tree, NULL, (1) % DIMENSIONS);

    delete[] left_vals;
    delete[] right_vals;

    return tree;
}

void KDB_Tree_range_search(KDB_Tree *tree, int range[DIMENSIONS][2], std::list<DataNode> &values)
{
    if (range[0][0] <= tree->split)
    {
        _KDB_Branch_range_search(tree->left, range, 1 % DIMENSIONS, values);
    }

    if (range[0][1] > tree->split)
    {
        _KDB_Branch_range_search(tree->right, range, 1 % DIMENSIONS, values);
    }
}

void _KDB_Branch_range_search(KDB_branch *branch, int range[DIMENSIONS][2], int curr_dim, std::list<DataNode> &values)
{
    if (branch->leaf != NULL)
    {
        for (int i = 0; i < branch->leaf_size; i++)
        {
            DataNode leaf_ptr = branch->leaf->LeafArray[i];
            bool in_range = true;
            for (int d = 0; d < DIMENSIONS; d++)
            {
                // break if cord is outside scope
                if (range[d][0] > leaf_ptr.cordinates[d] || leaf_ptr.cordinates[d] > range[d][1])
                {
                    in_range = false;
                    break;
                }
                // if(range[d][0])
            }
            if (in_range)
            {
                values.push_back(leaf_ptr);
            }
        }
        return;
    }

    if (range[curr_dim][0] <= branch->split)
    {
        _KDB_Branch_range_search(branch->left, range, (curr_dim + 1) % DIMENSIONS, values);
    }

    if (range[curr_dim][1] > branch->split)
    {
        _KDB_Branch_range_search(branch->right, range, (curr_dim + 1) % DIMENSIONS, values);
    }
}

void KDB_Tree_fetch_all_nodes(KDB_Tree *tree, DataNode *values)
{
    KDB_branch *leaf_branch = tree->firts_leaf;
    int count = 0;
    while (leaf_branch)
    {
        memcpy(&values[count], &leaf_branch->leaf->LeafArray, sizeof(DataNode) * leaf_branch->leaf_size);
        count += leaf_branch->leaf_size;
        leaf_branch = leaf_branch->next_leaf;
    }
}

int KDB_Tree_remove(KDB_Tree *tree, int index[DIMENSIONS])
{ // return 0 if node not found, otherwise 1 if succesfull delete
    if (!tree)
        return 0;
    if (index[0] < tree->split)
    {
        return _KDB_Branch_remove(tree->left, index);
    }

    if (index[0] > tree->split)
    {
        return _KDB_Branch_remove(tree->right, index);
    }

    if (index[0] == tree->split)
    {
        if (_KDB_Branch_remove(tree->left, index))
            return 1;
        if (_KDB_Branch_remove(tree->right, index))
            return 1;
    }

    return 0;
}

int _KDB_Branch_remove(KDB_branch *branch, int index[DIMENSIONS])
{
    if (branch->leaf != NULL)
    {
        // looking in leaf:
        for (int i = 0; i < branch->leaf_size; i++)
        {
            DataNode tmp = branch->leaf->LeafArray[i];
            bool match = true;
            if (!__cord_equal(tmp.cordinates, index))
            {
                match = false;
            }
            if (match)
            {
                // overwrite datanode
                // obs we don't write over last node
                memcpy(&branch->leaf->LeafArray[i], &branch->leaf->LeafArray[branch->leaf_size - 1], sizeof(DataNode));

                branch->leaf_size--;
                return 1;
            }
        }
        return 0;
    }

    if (index[branch->dimension] < branch->split)
    {
        // printf("|%d|Go left %d < %d\n", branch->dimension, index[branch->dimension], branch->split);
        return _KDB_Branch_remove(branch->left, index);
    }

    if (index[branch->dimension] > branch->split)
    {
        // printf("|%d|Go right %d > %d\n", branch->dimension, index[branch->dimension], branch->split);
        return _KDB_Branch_remove(branch->right, index);
    }

    if (index[branch->dimension] == branch->split)
    {
        // printf("|%d|Go both %d == %d\n", branch->dimension, index[branch->dimension], branch->split);
        if (_KDB_Branch_remove(branch->left, index))
            return 1;
        if (_KDB_Branch_remove(branch->right, index))
            return 1;
    }

    return 0;
}

KDB_branch *Skratch_KDB_Create_Branch(DataNode *values, int num_nodes, KDB_Tree *root, KDB_branch *parent_node, int current_dim)
{
    if (num_nodes <= KDB_LEAF_SIZE)
    {

        KDB_branch *leaf_branch = new KDB_branch;
        leaf_branch->dimension = current_dim;
        leaf_branch->leaf = new KDB_Leaf;

        // add root pointer
        if (root->firts_leaf == NULL)
        {
            root->firts_leaf = leaf_branch;
        }
        else
        {
            KDB_branch *ptr = root->firts_leaf;
            while (ptr != NULL)
            {
                if (ptr->next_leaf == NULL)
                {
                    ptr->next_leaf = leaf_branch;
                    break;
                }
                ptr = ptr->next_leaf;
            }
        }

        memcpy(leaf_branch->leaf->LeafArray, &values[num_nodes * current_dim], sizeof(DataNode) * num_nodes);
        return leaf_branch;
    }

    KDB_branch *branch = new KDB_branch;

    int left_mid_idx = num_nodes / 2 - !(num_nodes % 2);
    int right_mid_idx = left_mid_idx + 1;
    int right_size = right_mid_idx - (num_nodes % 2);
    branch->split = (values[num_nodes * current_dim + left_mid_idx].cordinates[current_dim] + values[num_nodes * current_dim + right_mid_idx].cordinates[current_dim]) / 2;
    branch->dimension = current_dim;

    DataNode *left_values = new DataNode[right_mid_idx * DIMENSIONS];
    DataNode *right_values = new DataNode[right_size * DIMENSIONS];

    // fill data
    memcpy(&left_values[right_mid_idx * current_dim], &values[current_dim * num_nodes], sizeof(DataNode) * right_mid_idx);
    memcpy(&right_values[right_size * current_dim], &values[current_dim * num_nodes + right_mid_idx], sizeof(DataNode) * right_size);

    int left_count[DIMENSIONS] = {};
    int right_count[DIMENSIONS] = {};

    for (int i = 0; i < num_nodes; i++)
    {
        for (int d = 0; d < DIMENSIONS; d++)
        {
            if (current_dim == d)
            {
                continue;
            }

            DataNode tmp = values[num_nodes * d + i];

            if (tmp.cordinates[current_dim] == branch->split)
            { // cordinate might be left or right, need to check data and other cords
                bool gone_left = false;
                for (int j = 0; j < right_mid_idx; j++)
                { // go through split left nodes, look for match
                    // TODO: ha en annen id også?
                    if (__cord_equal(tmp.cordinates, left_values[right_mid_idx * current_dim + j].cordinates) && tmp.data == left_values[right_mid_idx * current_dim + j].data)
                    { // add value to left
                        gone_left = true;
                        memcpy(&left_values[d * right_mid_idx + left_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
                        break;
                    }
                }
                if (!gone_left)
                { // right
                    memcpy(&right_values[d * right_size + right_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
                }
            }

            else if (tmp.cordinates[current_dim] < branch->split)
            { // left
                memcpy(&left_values[d * right_mid_idx + left_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
            }
            else
            { // right
                memcpy(&right_values[d * right_size + right_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
            }
        }
    }
    branch->left = Skratch_KDB_Create_Branch(left_values, right_mid_idx, root, NULL, 1 % DIMENSIONS);
    branch->right = Skratch_KDB_Create_Branch(right_values, right_size, root, NULL, 1 % DIMENSIONS);

    // TODO: remove memory leak
    delete[] left_values;
    delete[] right_values;

    return branch;
}

KDB_Tree *Skratch_KDB_Create_Tree(DataNode *values, int num_nodes)
{
    KDB_Tree *tree = new KDB_Tree;
    tree->size = num_nodes;

    int left_mid_idx = num_nodes / 2 - !(num_nodes % 2);
    int right_mid_idx = left_mid_idx + 1;

    int right_size = right_mid_idx - (num_nodes % 2);

    tree->split = (values[left_mid_idx].cordinates[0] + values[right_mid_idx].cordinates[0]) / 2;

    DataNode *left_values = new DataNode[right_mid_idx * DIMENSIONS];
    DataNode *right_values = new DataNode[right_size * DIMENSIONS];

    // fill data
    memcpy(left_values, &values[0], sizeof(DataNode) * right_mid_idx);
    memcpy(right_values, &values[right_mid_idx], sizeof(DataNode) * right_size);
    int left_count[DIMENSIONS] = {};
    int right_count[DIMENSIONS] = {};
    for (int i = 0; i < num_nodes; i++)
    {
        for (int d = 1; d < DIMENSIONS; d++)
        {
            DataNode tmp = values[num_nodes * d + i];

            if (tmp.cordinates[0] == tree->split)
            { // cordinate might be left or right, need to check data and other cords
                bool gone_left = false;
                for (int j = 0; j < right_mid_idx; j++)
                { // go through split left nodes, look for match
                    if (__cord_equal(tmp.cordinates, left_values[j].cordinates) && tmp.data == left_values[j].data)
                    { // add left
                        gone_left = true;
                        memcpy(&left_values[d * right_mid_idx + left_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
                        break;
                    }
                }
                if (!gone_left)
                { // right
                    memcpy(&right_values[d * right_size + right_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
                }
            }

            else if (tmp.cordinates[0] < tree->split)
            { // left
                memcpy(&left_values[d * right_mid_idx + left_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
            }
            else
            { // right
                memcpy(&right_values[d * right_size + right_count[d]++], &values[num_nodes * d + i], sizeof(DataNode));
            }
        }
    }

    tree->left = Skratch_KDB_Create_Branch(left_values, right_mid_idx, tree, NULL, 1 % DIMENSIONS);
    tree->right = Skratch_KDB_Create_Branch(right_values, right_size, tree, NULL, 1 % DIMENSIONS);

    return tree;
}