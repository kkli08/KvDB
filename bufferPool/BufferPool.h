//
// Created by damian on 9/15/24.
//

#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <string>
#include <unordered_map>
#include <list>
#include <vector>
#include <random>
#include "RedBlackTree.h"
#include "FileManager.h"

enum class EvictionPolicy {
    LRU,
    CLOCK,
    RANDOM
};

class BufferPool {
public:
    BufferPool(size_t capacity, EvictionPolicy policy, FileManager* fileManager);
    ~BufferPool();

    // Retrieves the RedBlackTree* associated with the filename.
    RedBlackTree* get(const std::string& filename);

private:
    size_t capacity;
    EvictionPolicy policy;
    FileManager* fileManager;

    // Mapping from filename to RedBlackTree*.
    std::unordered_map<std::string, RedBlackTree*> cache;

    // For LRU policy
    std::list<std::string> lruList;
    std::unordered_map<std::string, std::list<std::string>::iterator> lruMap;

    // For Clock policy
    std::vector<std::string> clockVector;
    size_t clockHand;
    std::unordered_map<std::string, bool> referenceBits;

    // For Random policy
    std::vector<std::string> randomVector;
    std::mt19937 rng;

    // Eviction functions
    void evictIfNecessary();
    void evictLRU();
    void evictClock();
    void evictRandom();

    // Helper functions
    void updateOnAccess(const std::string& filename);
};

#endif // BUFFERPOOL_H

