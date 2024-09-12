//
// Created by Damian Li on 2024-08-26.
//
#include <gtest/gtest.h>
#include "BinaryTree.h"

#include <gtest/gtest.h>
#include "BinaryTree.h"

// Test inserting and searching an integer key
TEST(BinaryTreeTest, InsertAndSearchInt) {
    BinaryTree tree;
    tree.insert(42, "TestValue");

    // Test if the inserted key can be found
    EXPECT_TRUE(tree.search(42));

    // Test if a non-existent key is not found
    EXPECT_FALSE(tree.search(100));
}

// Test inserting and searching a double key
TEST(BinaryTreeTest, InsertAndSearchDouble) {
    BinaryTree tree;
    tree.insert(3.14, "Pi");

    // Test if the inserted key can be found
    EXPECT_TRUE(tree.search(3.14));

    // Test if a non-existent key is not found
    EXPECT_FALSE(tree.search(2.71));
}

// Test inserting and searching a string key
TEST(BinaryTreeTest, InsertAndSearchString) {
    BinaryTree tree;
    tree.insert("Key", 123);

    // Test if the inserted key can be found
    EXPECT_TRUE(tree.search("Key"));

    // Test if a non-existent key is not found
    EXPECT_FALSE(tree.search("NonExistent"));
}

// Test inserting and searching a char key
TEST(BinaryTreeTest, InsertAndSearchChar) {
    BinaryTree tree;
    tree.insert('A', 100);

    // Test if the inserted key can be found
    EXPECT_TRUE(tree.search('A'));

    // Test if a non-existent key is not found
    EXPECT_FALSE(tree.search('B'));
}

// Test inserting multiple keys of different types
TEST(BinaryTreeTest, InsertMultipleTypes) {
    BinaryTree tree;
    tree.insert(42, "IntValue");
    tree.insert(3.14, "DoubleValue");
    tree.insert("Key", 123);
    tree.insert('A', "CharValue");

    // Test if all inserted keys can be found
    EXPECT_TRUE(tree.search(42));
    EXPECT_TRUE(tree.search(3.14));
    EXPECT_TRUE(tree.search("Key"));
    EXPECT_TRUE(tree.search('A'));

    // Test if non-existent keys are not found
    EXPECT_FALSE(tree.search(100));
    EXPECT_FALSE(tree.search("NonExistent"));
}

// Test searching in an empty tree
TEST(BinaryTreeTest, SearchInEmptyTree) {
    BinaryTree tree;

    // Test if searching in an empty tree returns false
    EXPECT_FALSE(tree.search(42));
    EXPECT_FALSE(tree.search("Key"));
    EXPECT_FALSE(tree.search(3.14));
}

// Test inserting and searching a long long int key
TEST(BinaryTreeTest, InsertAndSearchLongLong) {
    BinaryTree tree;
    tree.insert(9223372036854775807LL, "LongLongMax");

    // Test if the inserted key can be found
    EXPECT_TRUE(tree.search(9223372036854775807LL));

    // Test if a non-existent key is not found
    EXPECT_FALSE(tree.search(9223372036854775806LL));
}

// Test inserting and searching with duplicate keys
TEST(BinaryTreeTest, InsertAndSearchDuplicateKeys) {
    BinaryTree tree;
    tree.insert(42, "FirstValue");
    tree.insert(42, "SecondValue");  // Duplicate key

    // Test if the key can be found after inserting a duplicate
    EXPECT_TRUE(tree.search(42));

    // Since the tree structure doesn't specify handling duplicates,
    // the test checks that the key exists (specific value handling depends on the implementation).
}

