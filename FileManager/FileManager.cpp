//
// Created by Damian Li on 2024-09-08.
//

#include "FileManager.h"
#include <stdexcept>
#include <functional>
#include <cstdint>

// Constructor
FileManager::FileManager() : directory("defaultDB") {}

// Constructor with custom directory
FileManager::FileManager(fs::path dir) : directory(std::move(dir)) {
    if (!fs::exists(directory)) {
        fs::create_directories(directory);  // Ensure the directory exists
    }
}

// Set directory for SST files
void FileManager::setDirectory(const fs::path& path) {
    directory = path;
}

// Get directory for SST files
fs::path FileManager::getDirectory() const {
    return directory;
}

// Generate a unique filename for an SST file
std::string FileManager::generateSstFilename() {
    return "sst_" + std::to_string(increaseFileCounter()) + ".sst";
}

/*
 * SSTHeader Methods
 */
uint32_t SSTHeader::calculateChecksum() const {
    return sizeof(num_key_values) + sizeof(header_checksum);
}

void SSTHeader::serialize(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(&num_key_values), sizeof(num_key_values));
    file.write(reinterpret_cast<const char*>(&header_checksum), sizeof(header_checksum));
}

SSTHeader SSTHeader::deserialize(std::ifstream& file) {
    SSTHeader header;
    file.read(reinterpret_cast<char*>(&header.num_key_values), sizeof(header.num_key_values));
    file.read(reinterpret_cast<char*>(&header.header_checksum), sizeof(header.header_checksum));
    return header;
}

/*
 * FileManager Methods
 */
FlushSSTInfo FileManager::flushToDisk(const std::vector<KeyValueWrapper>& kv_pairs) {
    FlushSSTInfo flushInfo;
    flushInfo.fileName = generateSstFilename();

    if (!fs::exists(directory)) {
        throw std::runtime_error("FileManager::flushToDisk() >>>> Directory does not exist: " + directory.string());
    }

    std::ofstream file(directory / flushInfo.fileName, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("FileManager::flushToDisk() >>>> Could not open SST file for writing.");
    }

    if (kv_pairs.empty()) return flushInfo;

    flushInfo.smallest_key = kv_pairs.front();
    flushInfo.largest_key = kv_pairs.back();

    // Create the header
    sstHeader.num_key_values = kv_pairs.size();
    sstHeader.header_checksum = sstHeader.calculateChecksum();
    sstHeader.serialize(file);

    // Serialize each KeyValueWrapper using Protobuf's built-in serialization method
    for (const auto& kv : kv_pairs) {
        kv.kv.SerializeToOstream(&file);  // Directly serialize the KeyValueWrapper to the file
    }

    file.close();
    return flushInfo;
}

RedBlackTree* FileManager::loadFromDisk(const std::string& sst_filename) {
    std::ifstream file(directory / sst_filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("FileManager::loadFromDisk() >>>> Could not open SST file for reading.");
    }

    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (file_size == 0) {
        file.close();
        return new RedBlackTree();
    }

    SSTHeader sstHeader = SSTHeader::deserialize(file);

    auto* tree = new RedBlackTree();

    for (uint32_t i = 0; i < sstHeader.num_key_values; ++i) {
        KeyValueWrapper kvWrapper;
        kvWrapper.kv.ParseFromIstream(&file);  // Deserialize the KeyValueWrapper from the file
        tree->insert(kvWrapper);  // Insert into the RedBlackTree
    }

    file.close();
    return tree;
}



