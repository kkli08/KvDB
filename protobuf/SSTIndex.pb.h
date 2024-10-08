// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SSTIndex.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_SSTIndex_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_SSTIndex_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "KeyValue.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_SSTIndex_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_SSTIndex_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_SSTIndex_2eproto;
namespace sstindex {
class SSTIndex;
class SSTIndexDefaultTypeInternal;
extern SSTIndexDefaultTypeInternal _SSTIndex_default_instance_;
class SSTInfo;
class SSTInfoDefaultTypeInternal;
extern SSTInfoDefaultTypeInternal _SSTInfo_default_instance_;
}  // namespace sstindex
PROTOBUF_NAMESPACE_OPEN
template<> ::sstindex::SSTIndex* Arena::CreateMaybeMessage<::sstindex::SSTIndex>(Arena*);
template<> ::sstindex::SSTInfo* Arena::CreateMaybeMessage<::sstindex::SSTInfo>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace sstindex {

// ===================================================================

class SSTInfo PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:sstindex.SSTInfo) */ {
 public:
  inline SSTInfo() : SSTInfo(nullptr) {};
  virtual ~SSTInfo();

  SSTInfo(const SSTInfo& from);
  SSTInfo(SSTInfo&& from) noexcept
    : SSTInfo() {
    *this = ::std::move(from);
  }

  inline SSTInfo& operator=(const SSTInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline SSTInfo& operator=(SSTInfo&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SSTInfo& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SSTInfo* internal_default_instance() {
    return reinterpret_cast<const SSTInfo*>(
               &_SSTInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SSTInfo& a, SSTInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(SSTInfo* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SSTInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SSTInfo* New() const final {
    return CreateMaybeMessage<SSTInfo>(nullptr);
  }

  SSTInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SSTInfo>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SSTInfo& from);
  void MergeFrom(const SSTInfo& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SSTInfo* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "sstindex.SSTInfo";
  }
  protected:
  explicit SSTInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_SSTIndex_2eproto);
    return ::descriptor_table_SSTIndex_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFilenameFieldNumber = 1,
    kSmallestKeyFieldNumber = 2,
    kLargestKeyFieldNumber = 3,
  };
  // string filename = 1;
  void clear_filename();
  const std::string& filename() const;
  void set_filename(const std::string& value);
  void set_filename(std::string&& value);
  void set_filename(const char* value);
  void set_filename(const char* value, size_t size);
  std::string* mutable_filename();
  std::string* release_filename();
  void set_allocated_filename(std::string* filename);
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  std::string* unsafe_arena_release_filename();
  GOOGLE_PROTOBUF_RUNTIME_DEPRECATED("The unsafe_arena_ accessors for"
  "    string fields are deprecated and will be removed in a"
  "    future release.")
  void unsafe_arena_set_allocated_filename(
      std::string* filename);
  private:
  const std::string& _internal_filename() const;
  void _internal_set_filename(const std::string& value);
  std::string* _internal_mutable_filename();
  public:

  // .KeyValue smallest_key = 2;
  bool has_smallest_key() const;
  private:
  bool _internal_has_smallest_key() const;
  public:
  void clear_smallest_key();
  const ::KeyValue& smallest_key() const;
  ::KeyValue* release_smallest_key();
  ::KeyValue* mutable_smallest_key();
  void set_allocated_smallest_key(::KeyValue* smallest_key);
  private:
  const ::KeyValue& _internal_smallest_key() const;
  ::KeyValue* _internal_mutable_smallest_key();
  public:
  void unsafe_arena_set_allocated_smallest_key(
      ::KeyValue* smallest_key);
  ::KeyValue* unsafe_arena_release_smallest_key();

  // .KeyValue largest_key = 3;
  bool has_largest_key() const;
  private:
  bool _internal_has_largest_key() const;
  public:
  void clear_largest_key();
  const ::KeyValue& largest_key() const;
  ::KeyValue* release_largest_key();
  ::KeyValue* mutable_largest_key();
  void set_allocated_largest_key(::KeyValue* largest_key);
  private:
  const ::KeyValue& _internal_largest_key() const;
  ::KeyValue* _internal_mutable_largest_key();
  public:
  void unsafe_arena_set_allocated_largest_key(
      ::KeyValue* largest_key);
  ::KeyValue* unsafe_arena_release_largest_key();

  // @@protoc_insertion_point(class_scope:sstindex.SSTInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr filename_;
  ::KeyValue* smallest_key_;
  ::KeyValue* largest_key_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_SSTIndex_2eproto;
};
// -------------------------------------------------------------------

class SSTIndex PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:sstindex.SSTIndex) */ {
 public:
  inline SSTIndex() : SSTIndex(nullptr) {};
  virtual ~SSTIndex();

  SSTIndex(const SSTIndex& from);
  SSTIndex(SSTIndex&& from) noexcept
    : SSTIndex() {
    *this = ::std::move(from);
  }

  inline SSTIndex& operator=(const SSTIndex& from) {
    CopyFrom(from);
    return *this;
  }
  inline SSTIndex& operator=(SSTIndex&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const SSTIndex& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SSTIndex* internal_default_instance() {
    return reinterpret_cast<const SSTIndex*>(
               &_SSTIndex_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SSTIndex& a, SSTIndex& b) {
    a.Swap(&b);
  }
  inline void Swap(SSTIndex* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SSTIndex* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SSTIndex* New() const final {
    return CreateMaybeMessage<SSTIndex>(nullptr);
  }

  SSTIndex* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SSTIndex>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SSTIndex& from);
  void MergeFrom(const SSTIndex& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SSTIndex* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "sstindex.SSTIndex";
  }
  protected:
  explicit SSTIndex(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_SSTIndex_2eproto);
    return ::descriptor_table_SSTIndex_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSstInfosFieldNumber = 1,
  };
  // repeated .sstindex.SSTInfo sst_infos = 1;
  int sst_infos_size() const;
  private:
  int _internal_sst_infos_size() const;
  public:
  void clear_sst_infos();
  ::sstindex::SSTInfo* mutable_sst_infos(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::sstindex::SSTInfo >*
      mutable_sst_infos();
  private:
  const ::sstindex::SSTInfo& _internal_sst_infos(int index) const;
  ::sstindex::SSTInfo* _internal_add_sst_infos();
  public:
  const ::sstindex::SSTInfo& sst_infos(int index) const;
  ::sstindex::SSTInfo* add_sst_infos();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::sstindex::SSTInfo >&
      sst_infos() const;

  // @@protoc_insertion_point(class_scope:sstindex.SSTIndex)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::sstindex::SSTInfo > sst_infos_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_SSTIndex_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SSTInfo

// string filename = 1;
inline void SSTInfo::clear_filename() {
  filename_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline const std::string& SSTInfo::filename() const {
  // @@protoc_insertion_point(field_get:sstindex.SSTInfo.filename)
  return _internal_filename();
}
inline void SSTInfo::set_filename(const std::string& value) {
  _internal_set_filename(value);
  // @@protoc_insertion_point(field_set:sstindex.SSTInfo.filename)
}
inline std::string* SSTInfo::mutable_filename() {
  // @@protoc_insertion_point(field_mutable:sstindex.SSTInfo.filename)
  return _internal_mutable_filename();
}
inline const std::string& SSTInfo::_internal_filename() const {
  return filename_.Get();
}
inline void SSTInfo::_internal_set_filename(const std::string& value) {
  
  filename_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value, GetArena());
}
inline void SSTInfo::set_filename(std::string&& value) {
  
  filename_.Set(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:sstindex.SSTInfo.filename)
}
inline void SSTInfo::set_filename(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  filename_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value),
              GetArena());
  // @@protoc_insertion_point(field_set_char:sstindex.SSTInfo.filename)
}
inline void SSTInfo::set_filename(const char* value,
    size_t size) {
  
  filename_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:sstindex.SSTInfo.filename)
}
inline std::string* SSTInfo::_internal_mutable_filename() {
  
  return filename_.Mutable(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline std::string* SSTInfo::release_filename() {
  // @@protoc_insertion_point(field_release:sstindex.SSTInfo.filename)
  return filename_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void SSTInfo::set_allocated_filename(std::string* filename) {
  if (filename != nullptr) {
    
  } else {
    
  }
  filename_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), filename,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:sstindex.SSTInfo.filename)
}
inline std::string* SSTInfo::unsafe_arena_release_filename() {
  // @@protoc_insertion_point(field_unsafe_arena_release:sstindex.SSTInfo.filename)
  GOOGLE_DCHECK(GetArena() != nullptr);
  
  return filename_.UnsafeArenaRelease(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      GetArena());
}
inline void SSTInfo::unsafe_arena_set_allocated_filename(
    std::string* filename) {
  GOOGLE_DCHECK(GetArena() != nullptr);
  if (filename != nullptr) {
    
  } else {
    
  }
  filename_.UnsafeArenaSetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      filename, GetArena());
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:sstindex.SSTInfo.filename)
}

// .KeyValue smallest_key = 2;
inline bool SSTInfo::_internal_has_smallest_key() const {
  return this != internal_default_instance() && smallest_key_ != nullptr;
}
inline bool SSTInfo::has_smallest_key() const {
  return _internal_has_smallest_key();
}
inline const ::KeyValue& SSTInfo::_internal_smallest_key() const {
  const ::KeyValue* p = smallest_key_;
  return p != nullptr ? *p : *reinterpret_cast<const ::KeyValue*>(
      &::_KeyValue_default_instance_);
}
inline const ::KeyValue& SSTInfo::smallest_key() const {
  // @@protoc_insertion_point(field_get:sstindex.SSTInfo.smallest_key)
  return _internal_smallest_key();
}
inline void SSTInfo::unsafe_arena_set_allocated_smallest_key(
    ::KeyValue* smallest_key) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(smallest_key_);
  }
  smallest_key_ = smallest_key;
  if (smallest_key) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:sstindex.SSTInfo.smallest_key)
}
inline ::KeyValue* SSTInfo::release_smallest_key() {
  auto temp = unsafe_arena_release_smallest_key();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::KeyValue* SSTInfo::unsafe_arena_release_smallest_key() {
  // @@protoc_insertion_point(field_release:sstindex.SSTInfo.smallest_key)
  
  ::KeyValue* temp = smallest_key_;
  smallest_key_ = nullptr;
  return temp;
}
inline ::KeyValue* SSTInfo::_internal_mutable_smallest_key() {
  
  if (smallest_key_ == nullptr) {
    auto* p = CreateMaybeMessage<::KeyValue>(GetArena());
    smallest_key_ = p;
  }
  return smallest_key_;
}
inline ::KeyValue* SSTInfo::mutable_smallest_key() {
  // @@protoc_insertion_point(field_mutable:sstindex.SSTInfo.smallest_key)
  return _internal_mutable_smallest_key();
}
inline void SSTInfo::set_allocated_smallest_key(::KeyValue* smallest_key) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(smallest_key_);
  }
  if (smallest_key) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(smallest_key)->GetArena();
    if (message_arena != submessage_arena) {
      smallest_key = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, smallest_key, submessage_arena);
    }
    
  } else {
    
  }
  smallest_key_ = smallest_key;
  // @@protoc_insertion_point(field_set_allocated:sstindex.SSTInfo.smallest_key)
}

// .KeyValue largest_key = 3;
inline bool SSTInfo::_internal_has_largest_key() const {
  return this != internal_default_instance() && largest_key_ != nullptr;
}
inline bool SSTInfo::has_largest_key() const {
  return _internal_has_largest_key();
}
inline const ::KeyValue& SSTInfo::_internal_largest_key() const {
  const ::KeyValue* p = largest_key_;
  return p != nullptr ? *p : *reinterpret_cast<const ::KeyValue*>(
      &::_KeyValue_default_instance_);
}
inline const ::KeyValue& SSTInfo::largest_key() const {
  // @@protoc_insertion_point(field_get:sstindex.SSTInfo.largest_key)
  return _internal_largest_key();
}
inline void SSTInfo::unsafe_arena_set_allocated_largest_key(
    ::KeyValue* largest_key) {
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(largest_key_);
  }
  largest_key_ = largest_key;
  if (largest_key) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:sstindex.SSTInfo.largest_key)
}
inline ::KeyValue* SSTInfo::release_largest_key() {
  auto temp = unsafe_arena_release_largest_key();
  if (GetArena() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
  return temp;
}
inline ::KeyValue* SSTInfo::unsafe_arena_release_largest_key() {
  // @@protoc_insertion_point(field_release:sstindex.SSTInfo.largest_key)
  
  ::KeyValue* temp = largest_key_;
  largest_key_ = nullptr;
  return temp;
}
inline ::KeyValue* SSTInfo::_internal_mutable_largest_key() {
  
  if (largest_key_ == nullptr) {
    auto* p = CreateMaybeMessage<::KeyValue>(GetArena());
    largest_key_ = p;
  }
  return largest_key_;
}
inline ::KeyValue* SSTInfo::mutable_largest_key() {
  // @@protoc_insertion_point(field_mutable:sstindex.SSTInfo.largest_key)
  return _internal_mutable_largest_key();
}
inline void SSTInfo::set_allocated_largest_key(::KeyValue* largest_key) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArena();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(largest_key_);
  }
  if (largest_key) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
      reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(largest_key)->GetArena();
    if (message_arena != submessage_arena) {
      largest_key = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, largest_key, submessage_arena);
    }
    
  } else {
    
  }
  largest_key_ = largest_key;
  // @@protoc_insertion_point(field_set_allocated:sstindex.SSTInfo.largest_key)
}

// -------------------------------------------------------------------

// SSTIndex

// repeated .sstindex.SSTInfo sst_infos = 1;
inline int SSTIndex::_internal_sst_infos_size() const {
  return sst_infos_.size();
}
inline int SSTIndex::sst_infos_size() const {
  return _internal_sst_infos_size();
}
inline void SSTIndex::clear_sst_infos() {
  sst_infos_.Clear();
}
inline ::sstindex::SSTInfo* SSTIndex::mutable_sst_infos(int index) {
  // @@protoc_insertion_point(field_mutable:sstindex.SSTIndex.sst_infos)
  return sst_infos_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::sstindex::SSTInfo >*
SSTIndex::mutable_sst_infos() {
  // @@protoc_insertion_point(field_mutable_list:sstindex.SSTIndex.sst_infos)
  return &sst_infos_;
}
inline const ::sstindex::SSTInfo& SSTIndex::_internal_sst_infos(int index) const {
  return sst_infos_.Get(index);
}
inline const ::sstindex::SSTInfo& SSTIndex::sst_infos(int index) const {
  // @@protoc_insertion_point(field_get:sstindex.SSTIndex.sst_infos)
  return _internal_sst_infos(index);
}
inline ::sstindex::SSTInfo* SSTIndex::_internal_add_sst_infos() {
  return sst_infos_.Add();
}
inline ::sstindex::SSTInfo* SSTIndex::add_sst_infos() {
  // @@protoc_insertion_point(field_add:sstindex.SSTIndex.sst_infos)
  return _internal_add_sst_infos();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::sstindex::SSTInfo >&
SSTIndex::sst_infos() const {
  // @@protoc_insertion_point(field_list:sstindex.SSTIndex.sst_infos)
  return sst_infos_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace sstindex

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_SSTIndex_2eproto
