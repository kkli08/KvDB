## KvDB
![Unit Tests](https://github.com/kkli08/KvDB/actions/workflows/cmake-unit-tests-multi-platform.yml/badge.svg)

Persistent key-value store database library. The KV-Storage database is a high-performance system designed to store 
key-value pairs and allow efficient retrieval based on the key. This system is inspired by modern databases like 
[LevelDB](https://github.com/google/leveldb) and [RocksDB](https://github.com/facebook/rocksdb), and supports multiple data types using C++ templates and Protocol Buffers.

### Supported Data Types
> 2024-09-12 Restructure with `Protobuf`

> 2024-09-09 Support Template<typename K, typename V>
```c++
enum KeyValueType { INT, LONG, DOUBLE, CHAR, STRING };
```

> 2024-08-28 Support <int_64, int_64>
### Operations

#### **kvdb::API::Open(string db_name)**
Initializes the database system, setting up the necessary files and directories (including SSTs and related data). Can be initialized with a custom Memtable size or default size of `1e4`.

```c++
// Initialize with default memtable size
auto MyDBDefault = std::make_unique<kvdb::API>();
MyDBDefault->Open("database_name");

// Initialize with a custom memtable size
int memtableSize = 1e3;
auto MyDBCustom = std::make_unique<kvdb::API>(memtableSize);
MyDBCustom->Open("database_name");
```

#### **template<typename K, typename V> kvdb::API::Put(K key, V value)**
Inserts a key-value pair into the database, where both the key and value can be of various types (int, double, string, etc.).

```c++
// Example of inserting different data types
auto MyDB = std::make_unique<kvdb::API>();
MyDB->Open("database_name");
MyDB->Put(1, 100);             // int -> int
MyDB->Put(1.5, 'A');           // double -> char
MyDB->Put("Hello", 1e8LL);     // string -> long long
```

#### **kvdb::API::Get(const KeyValueWrapper& key)**
Retrieves a value from the database based on the key. Supports multiple data types.

```c++
// Example of retrieving values
auto MyDB = std::make_unique<kvdb::API>();
MyDB->Open("database_name");
MyDB->Put(1, 100);
MyDB->Put(1.5, 'A');
MyDB->Put("Hello", 1e8LL);

// Retrieve the value by key
auto kv = MyDB->Get("Hello");
// Retrieve the value by `KeyValueWrapper` instance
auto kv = MyDB->Get(KeyValueWrapper("Hello", ""));
// Expected output: { key: "Hello", value: 1e8LL }
```

#### **kvdb::API::Close()**
Closes the database, flushing any data in memory (Memtable) to disk and storing it in SSTs.

```c++
// Close the database and flush the Memtable to disk
auto MyDB = std::make_unique<kvdb::API>();
MyDB->Open("database_name");
MyDB->Close();
```

#### **kvdb::API::Scan(KeyValueWrapper smallestKey, KeyValueWrapper largestKey)**
Scans the database for key-value pairs within a specified key range. The results are returned in sorted key order.

```c++
// Scan for key-value pairs within a range
auto MyDB = std::make_unique<kvdb::API>();
MyDB->Open("database_name");
// Scan by key
std::set<KeyValueWrapper> results = MyDB->Scan(1, 10);
// Scan by `KeyValueWrapper` instance
std::set<KeyValueWrapper> results = MyDB->Scan(KeyValueWrapper(1, ""), KeyValueWrapper(10, ""));
```

#### **kvdb::API::Update()** (Coming Soon)
This will allow the updating of key-value pairs within the database.

#### **kvdb::API::Delete()** (Coming Soon)
This will allow the deletion of key-value pairs from the database.

### Dataflow Diagram
![DFD](/img/kvdb_lv0.jpg)

### Supported Platforms and Compilers
The KV-Store system has been tested across multiple platforms and compilers. Below is the current support status:

| Platform     | Compiler       | Status |
|--------------|----------------|--------|
| Ubuntu ARM64 | GCC            | ✅     |
| Ubuntu ARM64 | Clang          | ✅     |
| Windows x86  | MSVC (cl)      | ✅     |


### Roadmap & Features
- **2024-09-12**: Restructure data storage, better performance with protobuf serialization / deserialization.
- **2024-09-09**: Added support for templates using `KeyValueWrapper` class for multi-type key-value storage.
- **2024-08-28**: Initial support for `<int64, int64>` pairs.
- Future updates will include delete and update operations, along with optimizations for large-scale operations.


### Protobuf Instruction
```shell
cd KvDB/protobuf
protoc --proto_path=. --cpp_out=. className.proto
```