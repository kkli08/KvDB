//
// Created by Damian Li on 2024-08-28.
//
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iostream>
#include "api.h"

namespace fs = std::filesystem;
using namespace kvdb;

/*
 * API::Open and Close Tests
 */
TEST(APITest, OpenNewDatabase) {
    auto api = std::make_unique<kvdb::API>();
    std::string db_name = "test_db";

    // Ensure the directory does not exist before the test
    if (fs::exists(db_name)) {
        fs::remove_all(db_name);
    }

    testing::internal::CaptureStdout();
    api->Open(db_name);
    std::string output = testing::internal::GetCapturedStdout();

    // Verify the directory was created
    EXPECT_TRUE(fs::exists(db_name));
    // Verify output
    EXPECT_TRUE(output.find("Created database directory: " + db_name) != std::string::npos);

    // Clean up
    api->Close();
    fs::remove_all(db_name);  // Clean up the created directory
}

TEST(APITest, OpenExistingDatabase) {
    auto api = std::make_unique<kvdb::API>();
    std::string db_name = "test_db_existing";

    // Create the directory before the test
    if (!fs::exists(db_name)) {
        fs::create_directory(db_name);
    }

    testing::internal::CaptureStdout();
    api->Open(db_name);
    std::string output = testing::internal::GetCapturedStdout();

    // Verify the directory exists
    EXPECT_TRUE(fs::exists(db_name));
    // Verify output
    EXPECT_TRUE(output.find("Existed database directory: " + db_name) != std::string::npos);

    // Clean up
    api->Close();
    fs::remove_all(db_name);  // Clean up the created directory
}

TEST(APITest, reOpen) {
    auto api = std::make_unique<kvdb::API>();
    std::string db_name = "test_db_reopen";
    api->Open(db_name);
    api->Close();
    api->Open(db_name);
    api->Close();
}

/*
 * Basic Insert and Get Tests with KeyValueWrapper
 */
TEST(APITest, BasicInsertAndGet) {
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs (int key, int value)
    db->Put(1, 100);
    db->Put(2, 200);

    // Retrieve the values using the keys
    KeyValueWrapper result1 = db->Get(KeyValueWrapper(1, ""));
    KeyValueWrapper result2 = db->Get(KeyValueWrapper(2, ""));

    // Verify the returned values are correct
    EXPECT_EQ(result1.kv.int_value(), 100);
    EXPECT_EQ(result2.kv.int_value(), 200);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, StringInsertAndGet) {
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs (string key, string value)
    db->Put("key1", "value1");
    db->Put("key2", "value2");

    // Retrieve the values using the keys
    KeyValueWrapper result1 = db->Get(KeyValueWrapper("key1", ""));
    KeyValueWrapper result2 = db->Get(KeyValueWrapper("key2", ""));

    // Verify the returned values are correct
    EXPECT_EQ(result1.kv.string_value(), "value1");
    EXPECT_EQ(result2.kv.string_value(), "value2");

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, MixedDataTypesInsertAndGet) {
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs with different types
    db->Put(1, "value1");
    db->Put("key2", 200);
    db->Put(3.5, "value3");
    db->Put("key4", 400.5);

    // Retrieve the values using the keys
    KeyValueWrapper result1 = db->Get(KeyValueWrapper(1, ""));
    KeyValueWrapper result2 = db->Get(KeyValueWrapper("key2", ""));
    KeyValueWrapper result3 = db->Get(KeyValueWrapper(3.5, ""));
    KeyValueWrapper result4 = db->Get(KeyValueWrapper("key4", ""));

    // Verify the returned values are correct
    EXPECT_EQ(result1.kv.string_value(), "value1");
    EXPECT_EQ(result2.kv.int_value(), 200);
    EXPECT_EQ(result3.kv.string_value(), "value3");
    EXPECT_EQ(result4.kv.double_value(), 400.5);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

/*
 * Scan tests using KeyValueWrapper
 */
TEST(APITest, BasicScanRange) {
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs (int key, int value)
    db->Put(1, 100);
    db->Put(2, 200);
    db->Put(3, 300);
    db->Put(4, 400);
    db->Put(5, 500);

    // Perform a scan for key-value pairs between 2 and 4
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper(2, ""), KeyValueWrapper(4, ""));

    // Verify the result
    ASSERT_EQ(resultSet.size(), 3);
    auto it = resultSet.begin();
    EXPECT_EQ(it->kv.int_key(), 2);
    EXPECT_EQ(it->kv.int_value(), 200);
    ++it;
    EXPECT_EQ(it->kv.int_key(), 3);
    EXPECT_EQ(it->kv.int_value(), 300);
    ++it;
    EXPECT_EQ(it->kv.int_key(), 4);
    EXPECT_EQ(it->kv.int_value(), 400);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, ScanNonExistentRange) {
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs
    db->Put(1, 100);
    db->Put(2, 200);
    db->Put(3, 300);

    // Perform a scan for a range with no matching key-value pairs
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper(10, ""), KeyValueWrapper(20, ""));

    // Verify that no key-value pairs were found
    EXPECT_EQ(resultSet.size(), 0);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

/*
 * Scan Tests Using KeyValueWrapper
 */
TEST(APITest, ScanSingleKeyValuePair) {
    // Set memtable size and create API instance
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs
    db->Put(1, 100);
    db->Put(2, 200);
    db->Put(3, 300);

    // Perform a scan for a single key-value pair (key = 2)
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper(2, ""), KeyValueWrapper(2, ""));

    // Verify that only one key-value pair was found
    ASSERT_EQ(resultSet.size(), 1);
    auto it = resultSet.begin();
    EXPECT_EQ(it->kv.int_key(), 2);
    EXPECT_EQ(it->kv.int_value(), 200);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, LargeScaleScan) {
    // Set memtable size and create API instance
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert 1000 key-value pairs
    for (int i = 0; i < 1000; ++i) {
        db->Put(i, i * 10);
    }

    // Perform a scan for key-value pairs between 100 and 900
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper(100, ""), KeyValueWrapper(900, ""));

    // Verify that the correct number of key-value pairs were found
    EXPECT_EQ(resultSet.size(), 801);

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, ScanForStringKeyValuePairs) {
    // Set memtable size and create API instance
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert key-value pairs with string keys and values
    db->Put("a", "value1");
    db->Put("b", "value2");
    db->Put("c", "value3");

    // Perform a scan for key-value pairs between "a" and "b"
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper("a", ""), KeyValueWrapper("b", ""));

    // Verify that the correct key-value pairs were found
    ASSERT_EQ(resultSet.size(), 2);
    auto it = resultSet.begin();
    EXPECT_EQ(it->kv.string_key(), "a");
    EXPECT_EQ(it->kv.string_value(), "value1");
    ++it;
    EXPECT_EQ(it->kv.string_key(), "b");
    EXPECT_EQ(it->kv.string_value(), "value2");

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}

TEST(APITest, LargeScaleInsertAndScanRange) {
    // Set memtable size and create API instance
    int memtableSize = 1000;
    auto db = std::make_unique<kvdb::API>(memtableSize);
    db->Open("test_db");

    // Insert 100,000 key-value pairs (int key, string value)
    for (int i = 0; i < 100000; ++i) {
        db->Put(i, "value_" + std::to_string(i));
    }

    // Perform a scan for key-value pairs between 1 and 50,000
    set<KeyValueWrapper> resultSet = db->Scan(KeyValueWrapper(1, ""), KeyValueWrapper(50000, ""));

    // Verify that 50,000 key-value pairs were found
    ASSERT_EQ(resultSet.size(), 50000);

    // Verify the content of the result set
    auto it = resultSet.begin();
    for (int i = 1; i <= 50000; ++i, ++it) {
        EXPECT_EQ(it->kv.int_key(), i);
        EXPECT_EQ(it->kv.string_value(), "value_" + std::to_string(i));
    }

    // Clean up
    db->Close();
    fs::remove_all("test_db");
}
