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

    // Set smallest and largest keys
    flushInfo.smallest_key = kv_pairs.front();
    flushInfo.largest_key = kv_pairs.back();

    // Create the header
    sstHeader.num_key_values = kv_pairs.size();
    sstHeader.header_checksum = sstHeader.calculateChecksum();

    // Write the header
    sstHeader.serialize(file);

    // Write each KeyValueWrapper to the file
    for (const auto& kv : kv_pairs) {
        if (!kv.kv.SerializeToOstream(&file)) {
            std::cerr << "FileManager::flushToDisk() >>>> Failed to serialize KeyValueWrapper to stream." << std::endl;
            break;
        }
    }

    file.close();
    return flushInfo;
}



RedBlackTree* FileManager::loadFromDisk(const std::string& sst_filename) {
    std::ifstream file(directory / sst_filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("FileManager::loadFromDisk() >>>> Could not open SST file for reading.");
    }

    // Check file size
    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (file_size == 0) {
        file.close();
        return new RedBlackTree();  // Return empty tree if file is empty
    }

    // Deserialize the SST header
    SSTHeader sstHeader = SSTHeader::deserialize(file);
    std::cout << "Header num_key_values: " << sstHeader.num_key_values << std::endl;

    // Create a new RedBlackTree to store deserialized key-value pairs
    auto* tree = new RedBlackTree();

    // Loop through and deserialize each KeyValueWrapper
    for (uint32_t i = 0; i < sstHeader.num_key_values; ++i) {
        if (!file.good()) {
            std::cerr << "FileManager::loadFromDisk() >>>> File stream is not valid during deserialization." << std::endl;
            break;
        }

        KeyValueWrapper kvWrapper;
        if (!kvWrapper.kv.ParseFromIstream(&file)) {
            std::cerr << "FileManager::loadFromDisk() >>>> Failed to parse KeyValueWrapper from stream." << std::endl;
            break;
        }

        // Insert deserialized kvWrapper into RedBlackTree
        tree->insert(kvWrapper);

        std::cout << "Deserialized Key: " << kvWrapper.kv.int_key() << ", Value: " << kvWrapper.kv.int_value() << std::endl;
    }

    file.close();
    return tree;
}





