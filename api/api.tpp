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

}
