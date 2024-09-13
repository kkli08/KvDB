//
// Created by Damian Li on 2024-09-12.
//

namespace kvdb {

    /*
     * template function to put key-value pair
     * K = key type, V = value type
     */
    template<typename K, typename V>
    void API::Put(K key, V value) {
        check_if_open();

        // Create a KeyValueWrapper instance and insert it into the memtable
        KeyValueWrapper kvWrapper(key, value);
        FlushSSTInfo info = memtable->put(kvWrapper);

        // If the Memtable triggers a flush, add the new SST to the index
        if (!info.fileName.empty()) {
            index->addSST(info.fileName, info.smallest_key, info.largest_key);
        }
    }

    // Overloaded Get method to simplify retrieval by passing a key directly
    template<typename K>
    KeyValueWrapper API::Get(K key) {
        check_if_open();
        // Convert the key to a KeyValueWrapper and call the existing Get method
        KeyValueWrapper kvWrapper(key, "");
        return Get(kvWrapper);
    }

    // Overloaded Scan method to simplify scanning by passing two keys directly
    template<typename K1, typename K2>
    set<KeyValueWrapper> API::Scan(K1 small_key, K2 large_key) {
        // Convert the keys to KeyValueWrapper and call the existing Scan method
        KeyValueWrapper kvSmallKey(small_key, "");
        KeyValueWrapper kvLargeKey(large_key, "");
        return Scan(kvSmallKey, kvLargeKey);
    }


}
