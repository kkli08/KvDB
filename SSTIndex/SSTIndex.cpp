//
// Created by Damian Li on 2024-08-29.
//

#include "SSTIndex.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileManager.h"
#include "KeyValue.h"

#define RECORD_SIZE 18

// Constructor: Initialize path
SSTIndex::SSTIndex() {
    path = fs::path("defaultDB");
    if (!fs::exists(path)) {
        fs::create_directories(path);  // Ensure the directory exists
    }
    fileManager.setDirectory(path);
}

// Add a new SST to the index
void SSTIndex::addSST(const std::string& filename, const KeyValueWrapper& smallest_key, const KeyValueWrapper& largest_key) {
    SSTInfo* info = new SSTInfo{filename, smallest_key, largest_key};
    index.push_back(info);
}

// Serialize SSTIndex to disk
void SSTIndex::flushToDisk() {
    sstindex::SSTIndex sstIndexProto;

    // Convert each SSTInfo to its Protobuf counterpart
    for (const auto& sstInfo : index) {
        sstindex::SSTInfo* sstInfoProto = sstIndexProto.add_sst_infos();
        sstInfoProto->set_filename(sstInfo->filename);
        *sstInfoProto->mutable_smallest_key() = sstInfo->smallest_key.toProto();  // Convert KeyValueWrapper to KeyValue
        *sstInfoProto->mutable_largest_key() = sstInfo->largest_key.toProto();    // Convert KeyValueWrapper to KeyValue
    }

    // Serialize to file
    std::string filepath = (path / "Index.sst").string();
    serializeToFile(sstIndexProto, filepath);
}

// Deserialize SSTIndex from disk
void SSTIndex::getAllSSTs() {
    std::string filepath = (path / "Index.sst").string();

    // Check if the file exists
    if (!fs::exists(filepath)) {
        // If the file does not exist, create a new, empty Index.sst file
        std::ofstream outfile(filepath, std::ios::binary);
        if (!outfile.is_open()) {
            throw std::runtime_error("SSTIndex::getAllSSTs() >>>> Failed to create new Index.sst file.");
        }
        outfile.close();  // Close the newly created file
        return;  // No further logic needed, the file is empty
    }

    // If the file exists, proceed with deserialization
    sstindex::SSTIndex sstIndexProto = deserializeFromFile(filepath);

    // Clear the current index to avoid duplication
    index.clear();

    // Convert each Protobuf SSTInfo back into SSTInfo objects
    for (const auto& sstInfoProto : sstIndexProto.sst_infos()) {
        KeyValueWrapper smallestKey(sstInfoProto.smallest_key());
        KeyValueWrapper largestKey(sstInfoProto.largest_key());
        addSST(sstInfoProto.filename(), smallestKey, largestKey);
    }
}


// Search in a specific SST file
KeyValueWrapper SSTIndex::SearchInSST(const std::string& filename, const KeyValueWrapper& _key) {
    RedBlackTree* tree = fileManager.loadFromDisk(filename);
    if (!tree) {
        throw std::runtime_error("SSTIndex::SearchInSST() >>>> Failed to load SST file: " + filename);
    }

    KeyValueWrapper result = tree->getValue(_key);
    delete tree;  // Clean up tree
    return result;
}

// Search for a key in all SST files
KeyValueWrapper SSTIndex::Search(const KeyValueWrapper& _key) {
    for (auto it = index.rbegin(); it != index.rend(); ++it) {
        SSTInfo* sst_info = *it;
        if (sst_info->smallest_key <= _key && sst_info->largest_key >= _key) {
            KeyValueWrapper result = SearchInSST(sst_info->filename, _key);
            if (!result.isEmpty()) {
                return result;
            }
        }
    }
    return KeyValueWrapper();  // Return an empty result if not found
}

// Scan all SST files in the specified range
void SSTIndex::Scan(const KeyValueWrapper& smallestKey, const KeyValueWrapper& largestKey, set<KeyValueWrapper>& res) {
    for (auto it = index.rbegin(); it != index.rend(); ++it) {
        SSTInfo* sst_info = *it;
        if (sst_info->largest_key >= smallestKey && sst_info->smallest_key <= largestKey) {
            ScanInSST(smallestKey, largestKey, sst_info->filename, res);
        }
    }
}

// Scan a specific SST file
void SSTIndex::ScanInSST(const KeyValueWrapper& smallestKey, const KeyValueWrapper& largestKey, const std::string& filename, set<KeyValueWrapper>& resultSet) {
    RedBlackTree* tree = fileManager.loadFromDisk(filename);
    if (!tree) {
        throw std::runtime_error("SSTIndex::ScanInSST() >>>> Failed to load SST file: " + filename);
    }

    tree->inOrderTraversal([&](const KeyValueWrapper& kv) {
        if (kv >= smallestKey && kv <= largestKey) {
            resultSet.insert(kv);
        }
    });
    delete tree;
}

// Helper method: Serialize the Protobuf SSTIndex to a file
void SSTIndex::serializeToFile(const sstindex::SSTIndex& sstIndexProto, const std::string& filename) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("SSTIndex::serializeToFile() >>>> Could not open file for writing: " + filename);
    }
    if (!sstIndexProto.SerializeToOstream(&outfile)) {
        throw std::runtime_error("SSTIndex::serializeToFile() >>>> Failed to serialize to file: " + filename);
    }
    outfile.close();
}

// Helper method: Deserialize the Protobuf SSTIndex from a file
sstindex::SSTIndex SSTIndex::deserializeFromFile(const std::string& filename) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("SSTIndex::deserializeFromFile() >>>> Could not open file for reading: " + filename);
    }
    sstindex::SSTIndex sstIndexProto;
    if (!sstIndexProto.ParseFromIstream(&infile)) {
        throw std::runtime_error("SSTIndex::deserializeFromFile() >>>> Failed to parse from file: " + filename);
    }
    infile.close();
    return sstIndexProto;
}

// Set the file path
void SSTIndex::set_path(fs::path _path) {
    if (!fs::exists(_path)) {
        fs::create_directories(_path);
    }
    fileManager.setDirectory(_path);
    path = _path;
}


