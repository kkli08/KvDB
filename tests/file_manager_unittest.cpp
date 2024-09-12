//
// Created by Damian Li on 2024-09-08.
//

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <filesystem>
#include "FileManager.h"
#include "KeyValue.h"
namespace fs = std::filesystem;

TEST(FileManagerTest, FlushEmptyKVPairVector) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> empty_kv_pairs;

    FlushSSTInfo info = fileManager.flushToDisk(empty_kv_pairs);

    // Verify the filename is generated correctly
    EXPECT_FALSE(info.fileName.empty());
    EXPECT_EQ(info.smallest_key.isDefault(), true);
    EXPECT_EQ(info.largest_key.isDefault(), true);

    // Clean up: Delete the test directory
    fs::remove_all("test_db");
}

TEST(FileManagerTest, FlushSingleKVPair) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, "one") };

    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Verify filename is generated
    EXPECT_FALSE(info.fileName.empty());

    // Verify smallest and largest keys
    EXPECT_EQ(info.smallest_key.kv.int_key(), 1);
    EXPECT_EQ(info.largest_key.kv.int_key(), 1);

    // Clean up: Delete the test directory
    fs::remove_all("test_db");
}

TEST(FileManagerTest, FlushMultipleKVPairSameType) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, "one"), KeyValueWrapper(2, "two"), KeyValueWrapper(3, "three") };

    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Verify filename is generated
    EXPECT_FALSE(info.fileName.empty());

    // Verify smallest and largest keys
    EXPECT_EQ(info.smallest_key.kv.int_key(), 1);
    EXPECT_EQ(info.largest_key.kv.int_key(), 3);

    // Clean up: Delete the test directory
    fs::remove_all("test_db");
}

TEST(FileManagerTest, FlushMultipleKVPairDifferentTypes) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, "one"), KeyValueWrapper(3.14, 'a'), KeyValueWrapper(100LL, 200LL) };

    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Verify filename is generated
    EXPECT_FALSE(info.fileName.empty());

    // Verify smallest and largest keys
    EXPECT_EQ(info.smallest_key.kv.int_key(), 1);
    EXPECT_EQ(info.largest_key.kv.long_key(), 100LL);

    // Clean up: Delete the test directory
    fs::remove_all("test_db");
}

TEST(FileManagerTest, VerifyFlushedFileContent) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, 100), KeyValueWrapper(2, 200) };

    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Open the SST file and check its content
    std::ifstream file("test_db/" + info.fileName, std::ios::binary);
    ASSERT_TRUE(file.is_open());

    // Deserialize the header
    SSTHeader header = SSTHeader::deserialize(file);
    EXPECT_EQ(header.num_key_values, 2);

    // Deserialize and check the first KeyValueWrapper pair
    KeyValueWrapper kv1;
    kv1.kv.ParseFromIstream(&file);
    EXPECT_EQ(kv1.kv.int_key(), 1);
    EXPECT_EQ(kv1.kv.int_value(), 100);

    // Deserialize and check the second KeyValueWrapper pair
    KeyValueWrapper kv2;
    kv2.kv.ParseFromIstream(&file);
    EXPECT_EQ(kv2.kv.int_key(), 2);
    EXPECT_EQ(kv2.kv.int_value(), 200);

    file.close();

    // Clean up: Delete the test directory
    fs::remove_all("test_db");
}

TEST(FileManagerTest, LoadSingleKVPairFromDisk) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, "one") };

    // Flush the data to disk
    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Load data back into RedBlackTree
    RedBlackTree* tree = fileManager.loadFromDisk(info.fileName);

    // Verify the tree contains the key-value pair
    KeyValueWrapper searchKey(1, "");
    KeyValueWrapper result = tree->getValue(searchKey);
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 1);
    EXPECT_EQ(result.kv.string_value(), "one");

    delete tree;
    fs::remove_all("test_db");
}

TEST(FileManagerTest, LoadMultipleKVPairsFromDisk) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(1, "one"), KeyValueWrapper(2, "two"), KeyValueWrapper(3, "three") };

    // Flush the data to disk
    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Load data back into RedBlackTree
    RedBlackTree* tree = fileManager.loadFromDisk(info.fileName);

    // Verify the tree contains all key-value pairs
    KeyValueWrapper searchKey1(1, "");
    KeyValueWrapper searchKey2(2, "");
    KeyValueWrapper searchKey3(3, "");
    KeyValueWrapper result1 = tree->getValue(searchKey1);
    KeyValueWrapper result2 = tree->getValue(searchKey2);
    KeyValueWrapper result3 = tree->getValue(searchKey3);

    EXPECT_FALSE(result1.isEmpty());
    EXPECT_FALSE(result2.isEmpty());
    EXPECT_FALSE(result3.isEmpty());

    EXPECT_EQ(result1.kv.int_key(), 1);
    EXPECT_EQ(result1.kv.string_value(), "one");

    EXPECT_EQ(result2.kv.int_key(), 2);
    EXPECT_EQ(result2.kv.string_value(), "two");

    EXPECT_EQ(result3.kv.int_key(), 3);
    EXPECT_EQ(result3.kv.string_value(), "three");

    delete tree;
    fs::remove_all("test_db");
}

TEST(FileManagerTest, LoadDifferentTypeKVPairsFromDisk) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> kv_pairs = {
        KeyValueWrapper(1, "one"), KeyValueWrapper(3.14, 'a'), KeyValueWrapper(100LL, 200LL)
    };

    // Flush the data to disk
    FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);

    // Load data back into RedBlackTree
    RedBlackTree* tree = fileManager.loadFromDisk(info.fileName);

    // Verify the tree contains all key-value pairs
    KeyValueWrapper searchKey1(1, "");
    KeyValueWrapper searchKey2(100LL, 0LL);
    KeyValueWrapper searchKey3(3.14, 0);
    KeyValueWrapper result1 = tree->getValue(searchKey1);
    KeyValueWrapper result2 = tree->getValue(searchKey2);
    KeyValueWrapper result3 = tree->getValue(searchKey3);

    EXPECT_FALSE(result1.isEmpty());
    EXPECT_FALSE(result2.isEmpty());
    EXPECT_FALSE(result3.isEmpty());

    EXPECT_EQ(result1.kv.int_key(), 1);
    EXPECT_EQ(result1.kv.string_value(), "one");

    EXPECT_EQ(result2.kv.long_key(), 100LL);
    EXPECT_EQ(result2.kv.long_value(), 200LL);

    EXPECT_EQ(result3.kv.double_key(), 3.14);
    EXPECT_EQ(result3.kv.char_value(), std::string(1, 'a'));

    delete tree;
    fs::remove_all("test_db");
}

TEST(FileManagerTest, LoadFromEmptyFile) {
    FileManager fileManager(fs::path("test_db"));
    std::vector<KeyValueWrapper> empty_kv_pairs;

    // Flush empty data to disk
    FlushSSTInfo info = fileManager.flushToDisk(empty_kv_pairs);

    // Load data back into RedBlackTree
    RedBlackTree* tree = fileManager.loadFromDisk(info.fileName);

    // Verify the tree contains no key-value pairs
    KeyValueWrapper searchKey1(1, "");
    KeyValueWrapper result = tree->getValue(searchKey1);
    EXPECT_TRUE(result.isEmpty());

    delete tree;
    fs::remove_all("test_db");
}



