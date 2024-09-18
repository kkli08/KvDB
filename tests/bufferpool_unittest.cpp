//
// Created by damian on 9/17/24.
//
#include <gtest/gtest.h>
#include "BufferPool.h"
#include "RedBlackTree.h"
#include "FileManager.h"
#include <filesystem>
#include <vector>
#include <thread>

namespace fs = std::filesystem;
using namespace std;
/*
 * BufferPool Unit Tests
 */

/*
 * Test BufferPool with LRU eviction policy
 */
TEST(BufferPoolTest, LRUCacheHit) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_lru"));
    size_t capacity = 3;
    BufferPool bufferPool(capacity, EvictionPolicy::LRU, &fileManager);

    // Create some SST files
    std::vector<KeyValueWrapper> kv_pairs1 = { KeyValueWrapper(1, "one") };
    std::vector<KeyValueWrapper> kv_pairs2 = { KeyValueWrapper(2, "two") };
    std::vector<KeyValueWrapper> kv_pairs3 = { KeyValueWrapper(3, "three") };

    // Flush data to disk
    FlushSSTInfo info1 = fileManager.flushToDisk(kv_pairs1);
    FlushSSTInfo info2 = fileManager.flushToDisk(kv_pairs2);
    FlushSSTInfo info3 = fileManager.flushToDisk(kv_pairs3);

    // Access SST files via BufferPool
    bufferPool.get(info1.fileName); // Access info1
    bufferPool.get(info2.fileName); // Access info2

    // Access info1 again to update its usage
    bufferPool.get(info1.fileName);

    // At this point, cache should have info1 and info2
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info2.fileName));

    // Access info3, which should be added to the cache
    bufferPool.get(info3.fileName);

    // Now the cache is full (capacity 3)
    EXPECT_TRUE(bufferPool.fileExistsInPool(info3.fileName));

    // Access info1 again
    bufferPool.get(info1.fileName);

    // Access a new SST file to trigger eviction
    std::vector<KeyValueWrapper> kv_pairs4 = { KeyValueWrapper(4, "four") };
    FlushSSTInfo info4 = fileManager.flushToDisk(kv_pairs4);
    bufferPool.get(info4.fileName);

    // Since info2 was the least recently used, it should have been evicted
    EXPECT_FALSE(bufferPool.fileExistsInPool(info2.fileName));

    // Verify that info1, info3, and info4 are in the cache
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info3.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info4.fileName));

    // Clean up
    fs::remove_all("test_db_lru");
}

TEST(BufferPoolTest, LRUCacheEvictionOrder) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_lru_eviction"));
    size_t capacity = 2;
    BufferPool bufferPool(capacity, EvictionPolicy::LRU, &fileManager);

    // Create SST files
    std::vector<KeyValueWrapper> kv_pairs1 = { KeyValueWrapper(1, "one") };
    std::vector<KeyValueWrapper> kv_pairs2 = { KeyValueWrapper(2, "two") };
    std::vector<KeyValueWrapper> kv_pairs3 = { KeyValueWrapper(3, "three") };

    // Flush data to disk
    FlushSSTInfo info1 = fileManager.flushToDisk(kv_pairs1);
    FlushSSTInfo info2 = fileManager.flushToDisk(kv_pairs2);
    FlushSSTInfo info3 = fileManager.flushToDisk(kv_pairs3);

    // Access SST files to fill cache
    bufferPool.get(info1.fileName); // Cache: [info1]
    bufferPool.get(info2.fileName); // Cache: [info2, info1]

    // Access info1 to make it most recently used
    bufferPool.get(info1.fileName); // Cache: [info1, info2]

    // Verify that both info1 and info2 are in the cache
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info2.fileName));

    // Access info3, should evict info2
    bufferPool.get(info3.fileName); // Cache: [info3, info1]

    // Verify that info2 was evicted
    EXPECT_FALSE(bufferPool.fileExistsInPool(info2.fileName));

    // Verify that info1 and info3 are in the cache
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info3.fileName));

    // Clean up
    fs::remove_all("test_db_lru_eviction");
}

/*
 * Test BufferPool with Clock eviction policy
 */
TEST(BufferPoolTest, ClockPolicyEviction) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_clock"));
    size_t capacity = 2;
    BufferPool bufferPool(capacity, EvictionPolicy::CLOCK, &fileManager);

    // Create SST files
    std::vector<KeyValueWrapper> kv_pairs1 = { KeyValueWrapper(1, "one") };
    std::vector<KeyValueWrapper> kv_pairs2 = { KeyValueWrapper(2, "two") };
    std::vector<KeyValueWrapper> kv_pairs3 = { KeyValueWrapper(3, "three") };

    // Flush data to disk
    FlushSSTInfo info1 = fileManager.flushToDisk(kv_pairs1);
    FlushSSTInfo info2 = fileManager.flushToDisk(kv_pairs2);
    FlushSSTInfo info3 = fileManager.flushToDisk(kv_pairs3);

    // Access SST files
    bufferPool.get(info1.fileName); // Reference bit set to true
    bufferPool.get(info2.fileName); // Reference bit set to true

    // Verify that both files are in the cache
    // cout << "bp0" << endl;
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info2.fileName));

    // Access info1 again
    bufferPool.get(info1.fileName); // Reference bit remains true

    // Access info3, should trigger eviction
    bufferPool.get(info3.fileName);

    // Verify that one of the files was evicted
    // cout << "bp1" << endl;
    int filesInCache = 0;
    if (bufferPool.fileExistsInPool(info1.fileName)) filesInCache++;
    if (bufferPool.fileExistsInPool(info2.fileName)) filesInCache++;
    if (bufferPool.fileExistsInPool(info3.fileName)) filesInCache++;

    EXPECT_EQ(filesInCache, 2); // Since capacity is 2

    // Verify that info2 was likely evicted
    // cout << "bp2" << endl;
    EXPECT_FALSE(bufferPool.fileExistsInPool(info1.fileName));

    // Clean up
    fs::remove_all("test_db_clock");
    // cout << "bp3" << endl;

}

/*
 * Test BufferPool with Random eviction policy
 */
TEST(BufferPoolTest, RandomPolicyEviction) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_random"));
    size_t capacity = 2;
    BufferPool bufferPool(capacity, EvictionPolicy::RANDOM, &fileManager);

    // Create SST files
    std::vector<KeyValueWrapper> kv_pairs1 = { KeyValueWrapper(1, "one") };
    std::vector<KeyValueWrapper> kv_pairs2 = { KeyValueWrapper(2, "two") };
    std::vector<KeyValueWrapper> kv_pairs3 = { KeyValueWrapper(3, "three") };

    // Flush data to disk
    FlushSSTInfo info1 = fileManager.flushToDisk(kv_pairs1);
    FlushSSTInfo info2 = fileManager.flushToDisk(kv_pairs2);
    FlushSSTInfo info3 = fileManager.flushToDisk(kv_pairs3);

    // Access SST files
    bufferPool.get(info1.fileName);
    bufferPool.get(info2.fileName);

    // Verify that info1 and info2 are in the cache
    EXPECT_TRUE(bufferPool.fileExistsInPool(info1.fileName));
    EXPECT_TRUE(bufferPool.fileExistsInPool(info2.fileName));

    // Access a new SST file to trigger eviction
    bufferPool.get(info3.fileName);

    // Since eviction is random, we cannot predict which one was evicted
    // Verify that exactly two files are in the cache
    int filesInCache = 0;
    if (bufferPool.fileExistsInPool(info1.fileName)) filesInCache++;
    if (bufferPool.fileExistsInPool(info2.fileName)) filesInCache++;
    if (bufferPool.fileExistsInPool(info3.fileName)) filesInCache++;

    EXPECT_EQ(filesInCache, 2);

    // Clean up
    fs::remove_all("test_db_random");
}

/*
 * Test BufferPool with large amount of data
 */
TEST(BufferPoolTest, LargeDataSetLRU) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_large_lru"));
    size_t capacity = 100;
    BufferPool bufferPool(capacity, EvictionPolicy::LRU, &fileManager);

    // Generate and flush 200 SST files
    std::vector<FlushSSTInfo> sstInfos;
    for (int i = 0; i < 200; ++i) {
        std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(i, "value" + std::to_string(i)) };
        FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);
        sstInfos.push_back(info);
    }

    // Access the first 100 SST files
    for (int i = 0; i < 100; ++i) {
        bufferPool.get(sstInfos[i].fileName);
    }

    // Verify that the first 100 SSTs are in the cache
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(bufferPool.fileExistsInPool(sstInfos[i].fileName));
    }

    // Access the next 100 SST files
    for (int i = 100; i < 200; ++i) {
        bufferPool.get(sstInfos[i].fileName);
    }

    // At this point, the cache should contain SSTs from index 100 to 199
    // Verify that SSTs at index 0 to 99 have been evicted
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(bufferPool.fileExistsInPool(sstInfos[i].fileName));
    }

    // Verify that SSTs at index 100 to 199 are in the cache
    for (int i = 100; i < 200; ++i) {
        EXPECT_TRUE(bufferPool.fileExistsInPool(sstInfos[i].fileName));
    }

    // Clean up
    fs::remove_all("test_db_large_lru");
}

/*
 * Test BufferPool with large amount of data and Clock policy
 */
TEST(BufferPoolTest, LargeDataSetClock) {
    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_large_clock"));
    size_t capacity = 100;
    BufferPool bufferPool(capacity, EvictionPolicy::CLOCK, &fileManager);

    // Generate and flush 200 SST files
    std::vector<FlushSSTInfo> sstInfos;
    for (int i = 0; i < 200; ++i) {
        std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(i, "value" + std::to_string(i)) };
        FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);
        sstInfos.push_back(info);
    }

    // Access all SST files once
    for (int i = 0; i < 200; ++i) {
        bufferPool.get(sstInfos[i].fileName);
    }

    // At this point, the cache should contain 100 SSTs due to capacity limit
    // We can check that exactly 100 files are in the cache
    int filesInCache = 0;
    for (int i = 0; i < 200; ++i) {
        if (bufferPool.fileExistsInPool(sstInfos[i].fileName)) {
            filesInCache++;
        }
    }
    EXPECT_EQ(filesInCache, 100);

    // Clean up
    fs::remove_all("test_db_large_clock");
}

/*
 * Test BufferPool with concurrent access (if applicable)
 */
TEST(BufferPoolTest, ConcurrentAccess) {
    // This test is only relevant if your BufferPool is thread-safe
    // If not, you can skip this test or ensure thread safety before running

    // Setup FileManager and BufferPool
    FileManager fileManager(fs::path("test_db_concurrent"));
    size_t capacity = 10;
    BufferPool bufferPool(capacity, EvictionPolicy::LRU, &fileManager);

    // Generate and flush SST files
    std::vector<FlushSSTInfo> sstInfos;
    for (int i = 0; i < 20; ++i) {
        std::vector<KeyValueWrapper> kv_pairs = { KeyValueWrapper(i, "value" + std::to_string(i)) };
        FlushSSTInfo info = fileManager.flushToDisk(kv_pairs);
        sstInfos.push_back(info);
    }

    // Perform concurrent access
    std::vector<std::thread> threads;
    for (int i = 0; i < 20; ++i) {
        threads.emplace_back([&bufferPool, &sstInfos, i]() {
            bufferPool.get(sstInfos[i].fileName);
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Verify that the buffer pool contains at most 'capacity' items
    int filesInCache = 0;
    for (int i = 0; i < 20; ++i) {
        if (bufferPool.fileExistsInPool(sstInfos[i].fileName)) {
            filesInCache++;
        }
    }
    EXPECT_LE(filesInCache, capacity);

    // Clean up
    fs::remove_all("test_db_concurrent");
}

