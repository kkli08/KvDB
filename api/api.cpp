//
// Created by Damian Li on 2024-08-26.
//
#include "api.h"
#include <iostream>
#include <string>
#include <filesystem> // C++17 lib

namespace fs = std::filesystem;
namespace kvdb {
  /*
   * void API::Open(string)
   *
   * Open db by name
   */
  void API::Open(string db_name) {
    std::cout << "Opening database " << db_name << std::endl;

    if (is_open) {
      throw runtime_error("Database is already open.");
    }

    // Allocate or reallocate memtable and index
    if (!memtable) {
      memtable = make_unique<Memtable>();
    }
    if (!index) {
      index = make_unique<SSTIndex>();
    }

    // Define the path to the database directory
    fs::path db_path = db_name;
    // Check if the directory exists
    if (!fs::exists(db_path)) {
      // Directory does not exist, so create it
      if (fs::create_directory(db_path)) {
        std::cout << "Created database directory: " << db_name << std::endl;
      } else {
        std::cerr << "Failed to create directory: " << db_name << std::endl;
      }
    } else {
      std::cout << "Existed database directory: " << db_name << std::endl;
    }
    // set api attribute fs::path
    set_path(db_path);
    // set flag
    is_open = true;
    // retrieve all SST index
    index->getAllSSTs();
  }

  /*
   * void API::Close()
   *
   * Close and cleanup the database
   */
  void API::Close() {
    check_if_open();
    std::cout << "Closing database " << std::endl;

    // Check if the memtable has any entries before attempting to flush
    if (memtable->get_currentSize() > 0) {
      // The close command should transform whatever is in the current Memtable into an SST
      FlushSSTInfo info = memtable->file_manager.flushToDisk(memtable->getTree()->inOrderFlushToSst());

      /*
       *  Insert file into SSTIndex
       */
      if (info.largest_key >= info.smallest_key) {
        // non-empty SST file
        index->addSST(info.fileName, info.smallest_key, info.largest_key);
      }
    } else {
      std::cout << "Memtable is empty. No flush needed." << std::endl;
    }

    // Set the flag to indicate the database is closed
    is_open = false;
  }


  /*
   * KeyValueWrapper API::Get(const KeyValueWrapper&)
   *
   * Return the value of a key, return an empty KeyValueWrapper if the key
   * doesn't exist in memtable or SSTs
   */
  KeyValueWrapper API::Get(const KeyValueWrapper& keyValueWrapper) {
    // Check if the database is open
    check_if_open();

    // Attempt to get the value from the memtable
    KeyValueWrapper result = memtable->get(keyValueWrapper);

    // Check if the returned KeyValueWrapper is empty
    if (result.isEmpty()) {
      // If the result is empty, check in the SSTs
      result = index->Search(keyValueWrapper);
      if (!result.isEmpty()) {
        return result;
      }
    }

    // Return the result (either from memtable or SSTs)
    return result;
  }

  /*
   * set<KeyValueWrapper> API::Scan(KeyValueWrapper, KeyValueWrapper)
   *
   * Search the memtable and the SSTs.
   * step 1:
   *    scan the memtable
   * step 2:
   *    scan the SSTs from oldest to youngest
   */
  set<KeyValueWrapper> API::Scan(KeyValueWrapper small_key, KeyValueWrapper large_key) {
    set<KeyValueWrapper> result;

    // step 1:
    // scan the memtable
    memtable->Scan(small_key, large_key, result);

    // step 2:
    // scan the SSTs from youngest to oldest
    index->Scan(small_key, large_key, result);

    return result;
  }

  // helper function
  void API::set_path(fs::path _path) {
    path = _path;
    memtable->set_path(_path);
    index->set_path(_path);

    // Construct the full path to the "Index.sst" file
    fs::path indexFilePath = path / "Index.sst";

    // Check if the "Index.sst" file exists
    if (!fs::exists(indexFilePath)) {
      // If the file does not exist, create an empty "Index.sst" file
      std::ofstream outfile(indexFilePath);
      if (!outfile.is_open()) {
        throw std::runtime_error("API::set_path()-->> Failed to create Index.sst file at: " + indexFilePath.string());
      }
      outfile.close();  // Close the file after creation
      std::cout << "API::set_path()-->> Created new Index.sst file at: " << indexFilePath << std::endl;
    } else {
      std::ofstream outfile(indexFilePath);
      if (outfile.is_open()) {
        std::cout << "API::set_path()-->> Existing Index.sst file at: " << indexFilePath << std::endl;
      } else {
        std::cerr << "API::set_path()-->> Failed to open existing Index.sst file at: " << indexFilePath << std::endl;
      }
      outfile.close();
    }
  }

}
