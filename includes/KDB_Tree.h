#ifndef KDB_TREE_H
#define KDB_TREE_H
#include <list>
#include <cstdarg>
#include "Config.h"

// Smallest unit, node with data and index/cordinates
struct DataNode
{
    int cordinates[DIMENSIONS];
    int data;
};

// Leaf in disk tree
struct KDB_Leaf
{
    DataNode LeafArray[KDB_LEAF_SIZE];
};

// Branch node traversing tree
struct KDB_branch
{
    int split = -1; // value splitting the tree
    int dimension = -1;
    KDB_branch *left = NULL;
    KDB_branch *right = NULL;

    KDB_branch *next_leaf = NULL;  // connect leafs through list
    KDB_Leaf *leaf = NULL;         // if leaf != NULL, the tree has been traversed
    int leaf_size = KDB_LEAF_SIZE; // add leafsize
};

// KDB tree root node
struct KDB_Tree
{
    int split = -1;
    int size = 0;
    KDB_branch *left;
    KDB_branch *right;

    KDB_branch *firts_leaf = NULL; // pointer to leaf branch linked list
};

int __cord_equal(int c1[DIMENSIONS], int c2[DIMENSIONS]);

void __print_dataNode(DataNode *ptr);

void __print_kdb_branch(KDB_branch *branch);
void __print_kdb_tree(KDB_Tree *tree);

void __print_leafs(KDB_Tree *tree);

KDB_branch *KDB_Create_Branch(DataNode *values, int num_nodes, KDB_Tree *root, KDB_branch *parent_node, int current_dim);

KDB_Tree *KDB_Create_Tree(DataNode *values, int num_nodes);

void KDB_Tree_range_search(KDB_Tree *tree, int range[DIMENSIONS][2], std::list<DataNode> &values);

void _KDB_Branch_range_search(KDB_branch *branch, int range[DIMENSIONS][2], int curr_dim, std::list<DataNode> &values);

void KDB_Tree_fetch_all_nodes(KDB_Tree *tree, DataNode *values);

int KDB_Tree_remove(KDB_Tree *tree, int index[DIMENSIONS]);

int _KDB_Branch_remove(KDB_branch *branch, int index[DIMENSIONS]);

KDB_branch *Skratch_KDB_Create_Branch(DataNode *values, int num_nodes, KDB_Tree *root, KDB_branch *parent_node, int current_dim);

KDB_Tree *Skratch_KDB_Create_Tree(DataNode *values, int num_nodes);

#endif

// OBS.. Each KDB_Branch should probably keep track of the nr. of branches and not assume KDB_LEAF_SIZE