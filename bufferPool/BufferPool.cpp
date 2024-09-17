//
// Created by damian on 9/15/24.
//

#include "BufferPool.h"

BufferPool::BufferPool(size_t capacity, EvictionPolicy policy, FileManager* fileManager)
    : capacity(capacity), policy(policy), fileManager(fileManager), clockHand(0), rng(std::random_device{}()) {}

BufferPool::~BufferPool() {
    // Clean up all cached RedBlackTree objects.
    for (auto& pair : cache) {
        delete pair.second;
    }
}

RedBlackTree* BufferPool::get(const std::string& filename) {
    auto it = cache.find(filename);
    if (it != cache.end()) {
        // Cache hit
        updateOnAccess(filename);
        return it->second;
    } else {
        // Cache miss: Load from disk
        RedBlackTree* tree = fileManager->loadFromDisk(filename);
        cache[filename] = tree;

        // Update eviction policy data structures
        if (policy == EvictionPolicy::LRU) {
            lruList.push_front(filename);
            lruMap[filename] = lruList.begin();
        } else if (policy == EvictionPolicy::CLOCK) {
            clockVector.push_back(filename);
            referenceBits[filename] = true;
        } else if (policy == EvictionPolicy::RANDOM) {
            randomVector.push_back(filename);
        }

        evictIfNecessary();
        return tree;
    }
}

void BufferPool::updateOnAccess(const std::string& filename) {
    if (policy == EvictionPolicy::LRU) {
        // Move accessed filename to the front
        lruList.erase(lruMap[filename]);
        lruList.push_front(filename);
        lruMap[filename] = lruList.begin();
    } else if (policy == EvictionPolicy::CLOCK) {
        referenceBits[filename] = true;
    }
    // Random policy doesn't need to update on access
}

void BufferPool::evictIfNecessary() {
    if (cache.size() > capacity) {
        if (policy == EvictionPolicy::LRU) {
            evictLRU();
        } else if (policy == EvictionPolicy::CLOCK) {
            evictClock();
        } else if (policy == EvictionPolicy::RANDOM) {
            evictRandom();
        }
    }
}

void BufferPool::evictLRU() {
    // Evict least recently used item (back of lruList)
    std::string filenameToEvict = lruList.back();
    lruList.pop_back();
    lruMap.erase(filenameToEvict);

    // Remove from cache
    delete cache[filenameToEvict];
    cache.erase(filenameToEvict);
}

void BufferPool::evictClock() {
    while (true) {
        if (clockHand >= clockVector.size()) {
            clockHand = 0;
        }
        std::string& filename = clockVector[clockHand];
        if (referenceBits[filename]) {
            referenceBits[filename] = false;
            clockHand++;
        } else {
            // Evict this entry
            delete cache[filename];
            cache.erase(filename);

            // Remove from clock structures
            referenceBits.erase(filename);
            clockVector.erase(clockVector.begin() + clockHand);
            // Do not increment clockHand since we've removed an item
            break;
        }
    }
}

void BufferPool::evictRandom() {
    std::uniform_int_distribution<size_t> dist(0, randomVector.size() - 1);
    size_t idx = dist(rng);
    std::string filenameToEvict = randomVector[idx];

    // Remove from cache
    delete cache[filenameToEvict];
    cache.erase(filenameToEvict);

    // Remove from randomVector
    randomVector.erase(randomVector.begin() + idx);
}

