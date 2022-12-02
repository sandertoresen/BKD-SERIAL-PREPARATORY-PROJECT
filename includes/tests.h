#ifndef TESTS_H
#define TESTS_H

int _test_inserts_MemArray();

int _test_inserts_DiskArray();

int _test_remove_from_MemArray();

int _test_remove_from_DiskArray();

int _test_remove_from_last_tree();

int _test_window_query_MemArray();

int _test_window_query_DiskArray();

int _test_window_query_Arrays();

int _test_bulk_loading_single_tree();

int _test_fetching_KDB_tree();

int _test_bulk_loading_multiple_trees();

int _performance_test_inserts();

int _performance_test_deletes();

#endif