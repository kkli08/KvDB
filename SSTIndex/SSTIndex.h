//
// Created by Damian Li on 2024-08-29.
//
#pragma once
#include <string>
#include <deque>
#include <unordered_map>
#ifndef SSTINDEX_H
#define SSTINDEX_H
#include "FileManager.h"
#include "KeyValue.h" // Assuming this wraps the Protobuf KeyValue
#include "SSTIndex.pb.h"     // Protobuf-generated header for SSTIndex and SSTInfo
#include <filesystem>        // C++17 lib
#include "BufferPool.h"
#include <memory>

namespace fs = std::filesystem;
using namespace std;

struct SSTInfo {
    std::string filename;
    KeyValueWrapper smallest_key;
    KeyValueWrapper largest_key;
};

class SSTIndex {
public:
    SSTIndex(size_t bufferPoolCapacity, EvictionPolicy policy);
    SSTIndex();
    ~SSTIndex() = default;

    /*
     * IO Operations
     */
    // Retrieve all SSTs into index (e.g., when reopening the database)
    void getAllSSTs();
    // Flush index info into "Index.sst"
    void flushToDisk();
    // Add a new SST to the index
    void addSST(const std::string& filename, const KeyValueWrapper& smallest_key, const KeyValueWrapper& largest_key);
    // Get the SSTs index
    deque<SSTInfo*> getSSTsIndex() { return index; }

    /*
     * Search Operations
     */
    KeyValueWrapper SearchInSST(const std::string& filename, const KeyValueWrapper& _key); // Search in one SST file
    KeyValueWrapper Search(const KeyValueWrapper& _key); // Search in all SST files

    /*
     * Scan Operations
     */
    void Scan(const KeyValueWrapper& smallestKey, const KeyValueWrapper& largestKey, set<KeyValueWrapper>& res); // Scan in all SST files
    void ScanInSST(const KeyValueWrapper& smallestKey, const KeyValueWrapper& largestKey, const std::string& filename, set<KeyValueWrapper>& res); // Scan in one SST file

    /*
     * Buffer Pool
     *
     */
    // void Set

    // Helper functions
    void set_path(fs::path _path);
    fs::path get_path() const { return path; }

private:
    deque<SSTInfo*> index;
    fs::path path;
    FileManager fileManager;
    unique_ptr<BufferPool> bufferPool;

    // Helper for serializing/deserializing Protobuf files
    void serializeToFile(const sstindex::SSTIndex& sstIndexProto, const std::string& filename);
    sstindex::SSTIndex deserializeFromFile(const std::string& filename);
};

#endif // SSTINDEX_H
