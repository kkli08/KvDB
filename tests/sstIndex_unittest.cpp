//
// Created by Damian Li on 2024-08-29.
//
#include <gtest/gtest.h>
#include "SSTIndex.h"
#include "Memtable.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <string>
namespace fs = std::filesystem;

/*
 * SSTIndex Unit Tests
 */


/*
 * void SSTIndex::addSST(const string& filename, KeyValueWrapper smallest_key, KeyValueWrapper largest_key);
 */
TEST(SSTIndexTest, AddSingleSST) {
    // Create an SSTIndex instance
    SSTIndex sstIndex;

    // Define a filename and KeyValueWrapper instances for smallest and largest keys
    string filename = "sst_001.sst";
    KeyValueWrapper smallestKey(1, "one");
    KeyValueWrapper largestKey(100, "hundred");

    // Add the SST to the index
    sstIndex.addSST(filename, smallestKey, largestKey);

    // Verify the SST was added correctly
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 1);
    EXPECT_EQ(index.front()->filename, filename);
    EXPECT_EQ(index.front()->smallest_key.kv.int_key(), 1);
    EXPECT_EQ(index.front()->largest_key.kv.string_value(), "hundred");

    index.clear();
}

TEST(SSTIndexTest, AddMultipleSSTs) {
    // Create an SSTIndex instance
    SSTIndex sstIndex;

    // Add multiple SST files to the index
    sstIndex.addSST("sst_001.sst", KeyValueWrapper(1, "one"), KeyValueWrapper(100, "hundred"));
    sstIndex.addSST("sst_002.sst", KeyValueWrapper(101, "hundred and one"), KeyValueWrapper(200, "two hundred"));

    // Verify the SST files were added correctly
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 2);

    // Check first SST
    EXPECT_EQ(index[0]->filename, "sst_001.sst");
    EXPECT_EQ(index[0]->smallest_key.kv.int_key(), 1);
    EXPECT_EQ(index[0]->largest_key.kv.string_value(), "hundred");

    // Check second SST
    EXPECT_EQ(index[1]->filename, "sst_002.sst");
    EXPECT_EQ(index[1]->smallest_key.kv.int_key(), 101);
    EXPECT_EQ(index[1]->largest_key.kv.string_value(), "two hundred");
    index.clear();

}

TEST(SSTIndexTest, AddSSTUpdatesSize) {
    // Create an SSTIndex instance
    SSTIndex sstIndex;

    // Verify the index starts empty
    EXPECT_EQ(sstIndex.getSSTsIndex().size(), 0);

    // Add an SST file
    sstIndex.addSST("sst_001.sst", KeyValueWrapper(1, "one"), KeyValueWrapper(100, "hundred"));

    // Verify the index size increases
    EXPECT_EQ(sstIndex.getSSTsIndex().size(), 1);

    // Add another SST file
    sstIndex.addSST("sst_002.sst", KeyValueWrapper(101, "hundred and one"), KeyValueWrapper(200, "two hundred"));

    // Verify the index size increases again
    EXPECT_EQ(sstIndex.getSSTsIndex().size(), 2);
}

TEST(SSTIndexTest, AddSSTWithComplexKeyValues) {
    // Create an SSTIndex instance
    SSTIndex sstIndex;

    // Add SST with different types for smallest and largest keys
    sstIndex.addSST("sst_003.sst", KeyValueWrapper(1.23, "one point two three"), KeyValueWrapper('z', "zebra"));

    // Verify the SST was added with correct key-value pairs
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 1);

    EXPECT_EQ(index.front()->filename, "sst_003.sst");
    EXPECT_EQ(index.front()->smallest_key.kv.double_key(), 1.23);
    EXPECT_EQ(index.front()->largest_key.kv.string_value(), "zebra");

    index.clear();

}

/*
 *  // Retrieve all SSTs into index (e.g., when reopening the database)
 *  void getAllSSTs();  // updated with KeyValueWrapper
 *  // flush index info into "Index.sst"
 *  void flushToDisk(); // updated with KeyValueWrapper
 */
TEST(SSTIndexTest, BasicFlushAndRetrieve) {
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Add a single SST file
    sstIndex.addSST("sst_001.sst", KeyValueWrapper(1, "one"), KeyValueWrapper(100, "hundred"));

    // Flush to disk
    sstIndex.flushToDisk();

    // Clear the index and retrieve SSTs from disk
    sstIndex.getAllSSTs();

    // Verify that the index has been restored
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 1);
    EXPECT_EQ(index.front()->filename, "sst_001.sst");
    EXPECT_EQ(index.front()->smallest_key.kv.int_key(), 1);
    EXPECT_EQ(index.front()->largest_key.kv.string_value(), "hundred");

    // Clean up
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, MultipleFilesFlushAndRetrieve) {
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Add multiple SST files
    sstIndex.addSST("sst_001.sst", KeyValueWrapper(1, "one"), KeyValueWrapper(100, "hundred"));
    sstIndex.addSST("sst_002.sst", KeyValueWrapper(101, "hundred and one"), KeyValueWrapper(200, "two hundred"));
    sstIndex.addSST("sst_003.sst", KeyValueWrapper(201, "two hundred and one"), KeyValueWrapper(300, "three hundred"));

    // Flush to disk
    sstIndex.flushToDisk();

    // Clear the index and retrieve SSTs from disk
    sstIndex.getAllSSTs();

    // Verify that the index has been restored
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 3);
    EXPECT_EQ(index[0]->filename, "sst_001.sst");
    EXPECT_EQ(index[1]->filename, "sst_002.sst");
    EXPECT_EQ(index[2]->filename, "sst_003.sst");

    // Clean up
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, LargeNumberOfFilesFlushAndRetrieve) {
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Add 1000 SST files
    for (int i = 0; i < 1000; ++i) {
        sstIndex.addSST("sst_" + std::to_string(i) + ".sst", KeyValueWrapper(i, "smallest"), KeyValueWrapper(i + 100, "largest"));
    }

    // Flush to disk
    sstIndex.flushToDisk();

    // Clear the index and retrieve SSTs from disk
    sstIndex.getAllSSTs();

    // Verify that the index has been restored
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 1000);
    EXPECT_EQ(index[0]->filename, "sst_0.sst");

    // Clean up
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, RetrieveWithoutFlush) {
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Add SST files without flushing to disk
    sstIndex.addSST("sst_001.sst", KeyValueWrapper(1, "one"), KeyValueWrapper(100, "hundred"));

    // Clear the index and attempt to retrieve SSTs from disk (nothing should be loaded)
    sstIndex.getAllSSTs();

    // Verify that the index is still empty
    deque<SSTInfo*> index = sstIndex.getSSTsIndex();
    ASSERT_EQ(index.size(), 1);

    // Clean up
    fs::remove_all("test_db");
}



TEST(SSTIndexTest, FlushWithOneInstanceRetrieveWithAnother) {
    fs::path test_path = "test_db";

    // First instance of SSTIndex for flushing data to disk
    SSTIndex sstIndexFlush;
    sstIndexFlush.set_path(test_path);

    // Add 500 SST files to the first SSTIndex instance
    for (int i = 0; i < 500; ++i) {
        sstIndexFlush.addSST("sst_" + std::to_string(i) + ".sst", KeyValueWrapper(i, "smallest"), KeyValueWrapper(i + 10, "largest"));
    }

    // Flush to disk using the first instance
    sstIndexFlush.flushToDisk();

    // Second instance of SSTIndex for retrieving data from disk
    SSTIndex sstIndexRetrieve;
    sstIndexRetrieve.set_path(test_path);

    // Retrieve SST files using the second instance
    sstIndexRetrieve.getAllSSTs();

    // Get the index from both instances
    deque<SSTInfo*> flushedIndex = sstIndexFlush.getSSTsIndex();
    deque<SSTInfo*> retrievedIndex = sstIndexRetrieve.getSSTsIndex();

    // Verify the size of the indices
    ASSERT_EQ(flushedIndex.size(), retrievedIndex.size());

    // Verify that all SST files and key-value pairs match between the two instances
    for (size_t i = 0; i < flushedIndex.size(); ++i) {
        EXPECT_EQ(flushedIndex[i]->filename, retrievedIndex[i]->filename);
        EXPECT_EQ(flushedIndex[i]->smallest_key.kv.int_key(), retrievedIndex[i]->smallest_key.kv.int_key());
        EXPECT_EQ(flushedIndex[i]->largest_key.kv.int_key(), retrievedIndex[i]->largest_key.kv.int_key());
        EXPECT_EQ(flushedIndex[i]->smallest_key.kv.string_value(), retrievedIndex[i]->smallest_key.kv.string_value());
        EXPECT_EQ(flushedIndex[i]->largest_key.kv.string_value(), retrievedIndex[i]->largest_key.kv.string_value());
    }

    // Clean up
    fs::remove_all(test_path);
}

TEST(SSTIndexTest, SearchInSingleSSTFile) {
    // Create a Memtable and insert key-value pairs
    Memtable* memtable = new Memtable(10); // small threshold
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));

    // Flush the Memtable to an SST file
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Search for an existing key in the SST file
    KeyValueWrapper result = sstIndex.SearchInSST(info.fileName, KeyValueWrapper(2, ""));
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 2);
    EXPECT_EQ(result.kv.string_value(), "two");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchNonExistentKeyInSingleSSTFile) {
    // Create a Memtable and insert key-value pairs
    Memtable* memtable = new Memtable(10);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));

    // Flush the Memtable to an SST file
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Search for a non-existent key in the SST file
    KeyValueWrapper result = sstIndex.SearchInSST(info.fileName, KeyValueWrapper(4, ""));
    EXPECT_TRUE(result.isEmpty());

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchInMultipleSSTFiles) {
    // Create a Memtable and insert key-value pairs
    Memtable* memtable = new Memtable(10);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable and flush them
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    FlushSSTInfo info1 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    memtable->put(KeyValueWrapper(3, "three"));
    memtable->put(KeyValueWrapper(4, "four"));
    FlushSSTInfo info2 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Search for a key in the second SST file
    KeyValueWrapper result = sstIndex.SearchInSST(info2.fileName, KeyValueWrapper(3, ""));
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 3);
    EXPECT_EQ(result.kv.string_value(), "three");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchInLargeNumberOfSSTFiles) {
    // Create a Memtable and insert large number of key-value pairs
    Memtable* memtable = new Memtable(100);
    memtable->set_path(fs::path("test_db"));

    // Insert 1000 key-value pairs and flush them to SST files
    for (int i = 0; i < 1000; ++i) {
        memtable->put(KeyValueWrapper(i, "value_" + std::to_string(i)));
    }

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Search for a key in the middle of the range
    KeyValueWrapper result = sstIndex.SearchInSST("sst_5.sst", KeyValueWrapper(500, ""));
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 500);
    EXPECT_EQ(result.kv.string_value(), "value_500");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchForExistingKey) {
    // Create a Memtable with a threshold of 3 (flushes after 3 key-value pairs)
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs (memtable will automatically flush after reaching threshold)
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));  // Flushing occurs here

    // Manually add the SST information to SSTIndex after the flush
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST file info into SSTIndex
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Search for an existing key in the SST file
    KeyValueWrapper result = sstIndex.Search(KeyValueWrapper(3, ""));

    // Verify that the key-value pair was found
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 3);
    EXPECT_EQ(result.kv.string_value(), "three");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchForNonExistentKey) {
    // Create a Memtable with a threshold of 3
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs (flush occurs automatically)
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));

    // Manually add the SST information to SSTIndex after the flush
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST file info into SSTIndex
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Search for a non-existent key in the SST file
    KeyValueWrapper result = sstIndex.Search(KeyValueWrapper(10, ""));

    // Verify that the key-value pair was not found (empty result)
    EXPECT_TRUE(result.isEmpty());

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}


TEST(SSTIndexTest, SearchAcrossMultipleSSTFiles) {
    // Create a Memtable with a threshold of 3
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs to trigger multiple flushes
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));  // First flush occurs here
    FlushSSTInfo info1 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    memtable->put(KeyValueWrapper(4, "four"));
    memtable->put(KeyValueWrapper(5, "five"));
    memtable->put(KeyValueWrapper(6, "six"));    // Second flush occurs here
    FlushSSTInfo info2 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    memtable->put(KeyValueWrapper(7, "seven"));

    // Create an SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST files into SSTIndex
    sstIndex.addSST(info1.fileName, info1.smallest_key, info1.largest_key);
    sstIndex.addSST(info2.fileName, info2.smallest_key, info2.largest_key);

    // Search for keys across multiple SST files
    KeyValueWrapper result1 = sstIndex.Search(KeyValueWrapper(2, ""));
    KeyValueWrapper result2 = sstIndex.Search(KeyValueWrapper(6, ""));

    // Verify both keys were found
    EXPECT_FALSE(result1.isEmpty());
    EXPECT_EQ(result1.kv.int_key(), 2);
    EXPECT_EQ(result1.kv.string_value(), "two");

    EXPECT_FALSE(result2.isEmpty());
    EXPECT_EQ(result2.kv.int_key(), 6);
    EXPECT_EQ(result2.kv.string_value(), "six");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, SearchIn1e3OfSSTFiles) {
    // Create a Memtable with a threshold of 100 (flushes after 100 key-value pairs)
    Memtable* memtable = new Memtable(100);
    memtable->set_path(fs::path("test_db"));

    // Create SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Insert 1000 key-value pairs (this will trigger multiple flushes)
    for (int i = 0; i < 1e3; ++i) {
        KeyValueWrapper kv(i, "value_" + std::to_string(i));

        // After every flush (each 100 key-value pairs), manually add the SST info to SSTIndex
        if (i % 100 == 0 && i != 0) {
            FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());
            sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);
        }
        memtable->put(kv);
    }

    // Search for a key in the middle of the range
    KeyValueWrapper result = sstIndex.Search(KeyValueWrapper(500, ""));

    // Verify that the key-value pair was found
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result.kv.int_key(), 500);
    EXPECT_EQ(result.kv.string_value(), "value_500");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, Search1e5KeyValuePairs) {
    const int numKVPairs = 1e4;  // Total number of key-value pairs
    const int memtableSize = 1e2;  // Memtable threshold

    // Create a Memtable with a threshold of 100
    Memtable* memtable = new Memtable(memtableSize);
    memtable->set_path(fs::path("test_db"));

    // Create an SSTIndex instance to store the SST information
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Insert key-value pairs into the Memtable (this will trigger multiple flushes)
    for (int i = 0; i < numKVPairs; ++i) {
        KeyValueWrapper kv(i, "value_" + std::to_string(i));

        // After every flush, manually add the SST info to SSTIndex
        if (i % memtableSize == 0 && i != 0) {
            FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());
            sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);
            // continue;
        }
        memtable->put(kv);
    }

    // After all insertions, there might still be data left in the Memtable, flush it
    FlushSSTInfo finalInfo = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());
    sstIndex.addSST(finalInfo.fileName, finalInfo.smallest_key, finalInfo.largest_key);

    // Search for every inserted key-value pair and verify it exists
    for (int i = 1; i < numKVPairs; ++i) {
        KeyValueWrapper result = sstIndex.Search(KeyValueWrapper(i, ""));
        EXPECT_FALSE(result.isEmpty());
        EXPECT_EQ(result.kv.int_key(), i);
        EXPECT_EQ(result.kv.string_value(), "value_" + std::to_string(i));
    }

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, ScanRangeOfKeyValuePairs) {
    // Create a Memtable with a small threshold to trigger flushes quickly
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));  // Flushing occurs here

    // Flush the Memtable to an SST file
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST file to the SSTIndex
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Perform a scan for the range of key-value pairs
    set<KeyValueWrapper> resultSet;
    sstIndex.Scan(KeyValueWrapper(1, ""), KeyValueWrapper(3, ""), resultSet);

    // Verify the scanned result
    ASSERT_EQ(resultSet.size(), 3);
    EXPECT_EQ(resultSet.begin()->kv.int_key(), 1);
    EXPECT_EQ(resultSet.rbegin()->kv.string_value(), "three");

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}


// ==============================================

TEST(SSTIndexTest, ScanForNonExistentRange) {
    // Create a Memtable with a small threshold to trigger flushes quickly
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable using KeyValueWrapper
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));  // Flushing occurs here

    // Flush the Memtable to an SST file
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST file to the SSTIndex
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Perform a scan for a range with no matching key-value pairs
    set<KeyValueWrapper> resultSet;
    sstIndex.ScanInSST(KeyValueWrapper(10, ""), KeyValueWrapper(20, ""), info.fileName, resultSet);

    // Verify that no key-value pairs were found
    EXPECT_EQ(resultSet.size(), 0);

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, ScanLargeNumberOfKeyValuePairs) {
    // Create a Memtable with a large threshold
    Memtable* memtable = new Memtable(1000);
    memtable->set_path(fs::path("test_db"));

    // Insert 1000 key-value pairs into the memtable using KeyValueWrapper
    for (int i = 0; i < 1000; ++i) {
        memtable->put(KeyValueWrapper(i, "value_" + std::to_string(i)));
    }

    // Flush the Memtable to an SST file
    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create SSTIndex instance
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Manually add the flushed SST file to the SSTIndex
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Perform a scan for a large range of key-value pairs
    set<KeyValueWrapper> resultSet;
    sstIndex.ScanInSST(KeyValueWrapper(100, ""), KeyValueWrapper(900, ""), info.fileName, resultSet);

    // Verify that the correct number of key-value pairs were found
    EXPECT_EQ(resultSet.size(), 801);

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, BasicScanRangeAcrossSSTFiles) {
    // Create a Memtable with a small threshold to trigger flushes quickly
    Memtable* memtable = new Memtable(3);
    memtable->set_path(fs::path("test_db"));

    // Insert key-value pairs into the memtable using KeyValueWrapper
    memtable->put(KeyValueWrapper(1, "one"));
    memtable->put(KeyValueWrapper(2, "two"));
    memtable->put(KeyValueWrapper(3, "three"));  // First flush
    FlushSSTInfo info1 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    memtable->put(KeyValueWrapper(4, "four"));
    memtable->put(KeyValueWrapper(5, "five"));
    memtable->put(KeyValueWrapper(6, "six"));    // Second flush
    FlushSSTInfo info2 = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

    // Create SSTIndex instance and manually add SST files to the index
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));
    sstIndex.addSST(info1.fileName, info1.smallest_key, info1.largest_key);
    sstIndex.addSST(info2.fileName, info2.smallest_key, info2.largest_key);

    // Perform a scan across SST files for a range of key-value pairs
    set<KeyValueWrapper> resultSet;
    sstIndex.Scan(KeyValueWrapper(2, ""), KeyValueWrapper(5, ""), resultSet);

    // Verify the scanned result
    ASSERT_EQ(resultSet.size(), 4);
    EXPECT_EQ(resultSet.begin()->kv.int_key(), 2);
    EXPECT_EQ(resultSet.rbegin()->kv.int_key(), 5);

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}

TEST(SSTIndexTest, LargeScaleScanAcrossSSTFiles) {
    // Create a Memtable with a large threshold
    Memtable* memtable = new Memtable(100);
    memtable->set_path(fs::path("test_db"));
    SSTIndex sstIndex;
    sstIndex.set_path(fs::path("test_db"));

    // Insert 1000 key-value pairs using KeyValueWrapper
    for (int i = 0; i < 1000; ++i) {
        KeyValueWrapper kv(i, "value_" + std::to_string(i));

        // After every flush, manually add the SST info to SSTIndex
        if (i % 100 == 0 && i != 0) {
            FlushSSTInfo info = memtable->put(kv);
            sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);
            continue;
        }
        memtable->put(kv);
    }

    FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());
    sstIndex.addSST(info.fileName, info.smallest_key, info.largest_key);

    // Perform a scan for a large range of key-value pairs
    set<KeyValueWrapper> resultSet;
    sstIndex.Scan(KeyValueWrapper(100, ""), KeyValueWrapper(900, ""), resultSet);

    // Verify that the correct number of key-value pairs were found
    EXPECT_EQ(resultSet.size(), 801);

    // Clean up
    delete memtable;
    fs::remove_all("test_db");
}
