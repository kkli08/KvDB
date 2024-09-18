//
// Created by damian on 9/15/24.
//

#include "BufferPool.h"

BufferPool::BufferPool(size_t capacity, EvictionPolicy policy, FileManager* fileManager)
    : capacity(capacity), policy(policy), fileManager(fileManager), handPosition(0), rng(std::random_device{}()) {
    if (policy == EvictionPolicy::CLOCK) {
        clockEntries.resize(capacity);
    }
}

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

        if (cache.size() < capacity) {
            // There's room in the cache
            cache[filename] = tree;

            if (policy == EvictionPolicy::LRU) {
                lruList.push_front(filename);
                lruMap[filename] = lruList.begin();
            } else if (policy == EvictionPolicy::CLOCK) {
                clockEntries[cache.size() - 1] = {filename, tree, true};
            } else if (policy == EvictionPolicy::RANDOM) {
                randomVector.push_back(filename);
            }
        } else {
            // Cache is full, need to evict
            if (policy == EvictionPolicy::LRU) {
                // Add new entry before eviction to maintain correct state
                cache[filename] = tree;
                lruList.push_front(filename);
                lruMap[filename] = lruList.begin();
                evictLRU();
            } else if (policy == EvictionPolicy::CLOCK) {
                evictClock(filename, tree);
            } else if (policy == EvictionPolicy::RANDOM) {
                // Add new entry before eviction
                cache[filename] = tree;
                randomVector.push_back(filename);
                evictRandom();
            }
        }

        return tree;
    }
}

bool BufferPool::fileExistsInPool(const std::string& filename) const {
    return cache.find(filename) != cache.end();
}

void BufferPool::updateOnAccess(const std::string& filename) {
    if (policy == EvictionPolicy::LRU) {
        // Move accessed filename to the front
        auto it = lruMap[filename];
        lruList.erase(it);
        lruList.push_front(filename);
        lruMap[filename] = lruList.begin();
    } else if (policy == EvictionPolicy::CLOCK) {
        // Set reference bit to true
        for (ClockEntry& entry : clockEntries) {
            if (entry.filename == filename) {
                entry.referenceBit = true;
                break;
            }
        }
    }
    // Random policy doesn't need to update on access
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

void BufferPool::evictClock(const std::string& newFilename, RedBlackTree* newTree) {
    while (true) {
        ClockEntry& entry = clockEntries[handPosition];
        if (!entry.referenceBit) {
            // Evict this entry
            cache.erase(entry.filename);
            delete entry.tree;

            // Replace with new entry
            entry.filename = newFilename;
            entry.tree = newTree;
            entry.referenceBit = true;
            cache[newFilename] = newTree;

            // Advance hand for next operation
            handPosition = (handPosition + 1) % capacity;
            break;
        } else {
            // Give a second chance
            entry.referenceBit = false;
            handPosition = (handPosition + 1) % capacity;
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


