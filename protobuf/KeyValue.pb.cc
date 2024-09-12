// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: KeyValue.proto

#include "KeyValue.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class KeyValueDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<KeyValue> _instance;
  ::PROTOBUF_NAMESPACE_ID::int32 int_key_;
  ::PROTOBUF_NAMESPACE_ID::int64 long_key_;
  double double_key_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr string_key_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr char_key_;
  ::PROTOBUF_NAMESPACE_ID::int32 int_value_;
  ::PROTOBUF_NAMESPACE_ID::int64 long_value_;
  double double_value_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr string_value_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr char_value_;
} _KeyValue_default_instance_;
static void InitDefaultsscc_info_KeyValue_KeyValue_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_KeyValue_default_instance_;
    new (ptr) ::KeyValue();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::KeyValue::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_KeyValue_KeyValue_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_KeyValue_KeyValue_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_KeyValue_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_KeyValue_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_KeyValue_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_KeyValue_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::KeyValue, _internal_metadata_),
  ~0u,  // no _extensions_
  PROTOBUF_FIELD_OFFSET(::KeyValue, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  offsetof(::KeyValueDefaultTypeInternal, int_key_),
  offsetof(::KeyValueDefaultTypeInternal, long_key_),
  offsetof(::KeyValueDefaultTypeInternal, double_key_),
  offsetof(::KeyValueDefaultTypeInternal, string_key_),
  offsetof(::KeyValueDefaultTypeInternal, char_key_),
  offsetof(::KeyValueDefaultTypeInternal, int_value_),
  offsetof(::KeyValueDefaultTypeInternal, long_value_),
  offsetof(::KeyValueDefaultTypeInternal, double_value_),
  offsetof(::KeyValueDefaultTypeInternal, string_value_),
  offsetof(::KeyValueDefaultTypeInternal, char_value_),
  PROTOBUF_FIELD_OFFSET(::KeyValue, key_type_),
  PROTOBUF_FIELD_OFFSET(::KeyValue, value_type_),
  PROTOBUF_FIELD_OFFSET(::KeyValue, key_),
  PROTOBUF_FIELD_OFFSET(::KeyValue, value_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::KeyValue)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_KeyValue_default_instance_),
};

const char descriptor_table_protodef_KeyValue_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016KeyValue.proto\"\215\003\n\010KeyValue\022\021\n\007int_key"
  "\030\001 \001(\005H\000\022\022\n\010long_key\030\002 \001(\003H\000\022\024\n\ndouble_k"
  "ey\030\003 \001(\001H\000\022\024\n\nstring_key\030\004 \001(\tH\000\022\022\n\010char"
  "_key\030\005 \001(\tH\000\022\023\n\tint_value\030\006 \001(\005H\001\022\024\n\nlon"
  "g_value\030\007 \001(\003H\001\022\026\n\014double_value\030\010 \001(\001H\001\022"
  "\026\n\014string_value\030\t \001(\tH\001\022\024\n\nchar_value\030\n "
  "\001(\tH\001\022(\n\010key_type\030\013 \001(\0162\026.KeyValue.KeyVa"
  "lueType\022*\n\nvalue_type\030\014 \001(\0162\026.KeyValue.K"
  "eyValueType\"C\n\014KeyValueType\022\007\n\003INT\020\000\022\010\n\004"
  "LONG\020\001\022\n\n\006DOUBLE\020\002\022\010\n\004CHAR\020\003\022\n\n\006STRING\020\004"
  "B\005\n\003keyB\007\n\005valueb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_KeyValue_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_KeyValue_2eproto_sccs[1] = {
  &scc_info_KeyValue_KeyValue_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_KeyValue_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_KeyValue_2eproto = {
  false, false, descriptor_table_protodef_KeyValue_2eproto, "KeyValue.proto", 424,
  &descriptor_table_KeyValue_2eproto_once, descriptor_table_KeyValue_2eproto_sccs, descriptor_table_KeyValue_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_KeyValue_2eproto::offsets,
  file_level_metadata_KeyValue_2eproto, 1, file_level_enum_descriptors_KeyValue_2eproto, file_level_service_descriptors_KeyValue_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_KeyValue_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_KeyValue_2eproto)), true);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* KeyValue_KeyValueType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_KeyValue_2eproto);
  return file_level_enum_descriptors_KeyValue_2eproto[0];
}
bool KeyValue_KeyValueType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr KeyValue_KeyValueType KeyValue::INT;
constexpr KeyValue_KeyValueType KeyValue::LONG;
constexpr KeyValue_KeyValueType KeyValue::DOUBLE;
constexpr KeyValue_KeyValueType KeyValue::CHAR;
constexpr KeyValue_KeyValueType KeyValue::STRING;
constexpr KeyValue_KeyValueType KeyValue::KeyValueType_MIN;
constexpr KeyValue_KeyValueType KeyValue::KeyValueType_MAX;
constexpr int KeyValue::KeyValueType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void KeyValue::InitAsDefaultInstance() {
  ::_KeyValue_default_instance_.int_key_ = 0;
  ::_KeyValue_default_instance_.long_key_ = PROTOBUF_LONGLONG(0);
  ::_KeyValue_default_instance_.double_key_ = 0;
  ::_KeyValue_default_instance_.string_key_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::_KeyValue_default_instance_.char_key_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::_KeyValue_default_instance_.int_value_ = 0;
  ::_KeyValue_default_instance_.long_value_ = PROTOBUF_LONGLONG(0);
  ::_KeyValue_default_instance_.double_value_ = 0;
  ::_KeyValue_default_instance_.string_value_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::_KeyValue_default_instance_.char_value_.UnsafeSetDefault(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
class KeyValue::_Internal {
 public:
};

KeyValue::KeyValue(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:KeyValue)
}
KeyValue::KeyValue(const KeyValue& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&key_type_, &from.key_type_,
    static_cast<size_t>(reinterpret_cast<char*>(&value_type_) -
    reinterpret_cast<char*>(&key_type_)) + sizeof(value_type_));
  clear_has_key();
  switch (from.key_case()) {
    case kIntKey: {
      _internal_set_int_key(from._internal_int_key());
      break;
    }
    case kLongKey: {
      _internal_set_long_key(from._internal_long_key());
      break;
    }
    case kDoubleKey: {
      _internal_set_double_key(from._internal_double_key());
      break;
    }
    case kStringKey: {
      _internal_set_string_key(from._internal_string_key());
      break;
    }
    case kCharKey: {
      _internal_set_char_key(from._internal_char_key());
      break;
    }
    case KEY_NOT_SET: {
      break;
    }
  }
  clear_has_value();
  switch (from.value_case()) {
    case kIntValue: {
      _internal_set_int_value(from._internal_int_value());
      break;
    }
    case kLongValue: {
      _internal_set_long_value(from._internal_long_value());
      break;
    }
    case kDoubleValue: {
      _internal_set_double_value(from._internal_double_value());
      break;
    }
    case kStringValue: {
      _internal_set_string_value(from._internal_string_value());
      break;
    }
    case kCharValue: {
      _internal_set_char_value(from._internal_char_value());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:KeyValue)
}

void KeyValue::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_KeyValue_KeyValue_2eproto.base);
  ::memset(&key_type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&value_type_) -
      reinterpret_cast<char*>(&key_type_)) + sizeof(value_type_));
  clear_has_key();
  clear_has_value();
}

KeyValue::~KeyValue() {
  // @@protoc_insertion_point(destructor:KeyValue)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void KeyValue::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  if (has_key()) {
    clear_key();
  }
  if (has_value()) {
    clear_value();
  }
}

void KeyValue::ArenaDtor(void* object) {
  KeyValue* _this = reinterpret_cast< KeyValue* >(object);
  (void)_this;
}
void KeyValue::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KeyValue::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const KeyValue& KeyValue::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_KeyValue_KeyValue_2eproto.base);
  return *internal_default_instance();
}


void KeyValue::clear_key() {
// @@protoc_insertion_point(one_of_clear_start:KeyValue)
  switch (key_case()) {
    case kIntKey: {
      // No need to clear
      break;
    }
    case kLongKey: {
      // No need to clear
      break;
    }
    case kDoubleKey: {
      // No need to clear
      break;
    }
    case kStringKey: {
      key_.string_key_.Destroy(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
      break;
    }
    case kCharKey: {
      key_.char_key_.Destroy(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
      break;
    }
    case KEY_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = KEY_NOT_SET;
}

void KeyValue::clear_value() {
// @@protoc_insertion_point(one_of_clear_start:KeyValue)
  switch (value_case()) {
    case kIntValue: {
      // No need to clear
      break;
    }
    case kLongValue: {
      // No need to clear
      break;
    }
    case kDoubleValue: {
      // No need to clear
      break;
    }
    case kStringValue: {
      value_.string_value_.Destroy(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
      break;
    }
    case kCharValue: {
      value_.char_value_.Destroy(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[1] = VALUE_NOT_SET;
}


void KeyValue::Clear() {
// @@protoc_insertion_point(message_clear_start:KeyValue)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&key_type_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&value_type_) -
      reinterpret_cast<char*>(&key_type_)) + sizeof(value_type_));
  clear_key();
  clear_value();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KeyValue::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 int_key = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _internal_set_int_key(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 long_key = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _internal_set_long_key(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // double double_key = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 25)) {
          _internal_set_double_key(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr));
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // string string_key = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          auto str = _internal_mutable_string_key();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "KeyValue.string_key"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string char_key = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_char_key();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "KeyValue.char_key"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 int_value = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          _internal_set_int_value(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 long_value = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          _internal_set_long_value(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // double double_value = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 65)) {
          _internal_set_double_value(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr));
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // string string_value = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 74)) {
          auto str = _internal_mutable_string_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "KeyValue.string_value"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string char_value = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 82)) {
          auto str = _internal_mutable_char_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "KeyValue.char_value"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .KeyValue.KeyValueType key_type = 11;
      case 11:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 88)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_key_type(static_cast<::KeyValue_KeyValueType>(val));
        } else goto handle_unusual;
        continue;
      // .KeyValue.KeyValueType value_type = 12;
      case 12:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 96)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_value_type(static_cast<::KeyValue_KeyValueType>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KeyValue::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:KeyValue)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 int_key = 1;
  if (_internal_has_int_key()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_int_key(), target);
  }

  // int64 long_key = 2;
  if (_internal_has_long_key()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_long_key(), target);
  }

  // double double_key = 3;
  if (_internal_has_double_key()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(3, this->_internal_double_key(), target);
  }

  // string string_key = 4;
  if (_internal_has_string_key()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_string_key().data(), static_cast<int>(this->_internal_string_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "KeyValue.string_key");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_string_key(), target);
  }

  // string char_key = 5;
  if (_internal_has_char_key()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_char_key().data(), static_cast<int>(this->_internal_char_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "KeyValue.char_key");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_char_key(), target);
  }

  // int32 int_value = 6;
  if (_internal_has_int_value()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(6, this->_internal_int_value(), target);
  }

  // int64 long_value = 7;
  if (_internal_has_long_value()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(7, this->_internal_long_value(), target);
  }

  // double double_value = 8;
  if (_internal_has_double_value()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(8, this->_internal_double_value(), target);
  }

  // string string_value = 9;
  if (_internal_has_string_value()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_string_value().data(), static_cast<int>(this->_internal_string_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "KeyValue.string_value");
    target = stream->WriteStringMaybeAliased(
        9, this->_internal_string_value(), target);
  }

  // string char_value = 10;
  if (_internal_has_char_value()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_char_value().data(), static_cast<int>(this->_internal_char_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "KeyValue.char_value");
    target = stream->WriteStringMaybeAliased(
        10, this->_internal_char_value(), target);
  }

  // .KeyValue.KeyValueType key_type = 11;
  if (this->key_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      11, this->_internal_key_type(), target);
  }

  // .KeyValue.KeyValueType value_type = 12;
  if (this->value_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      12, this->_internal_value_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:KeyValue)
  return target;
}

size_t KeyValue::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:KeyValue)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .KeyValue.KeyValueType key_type = 11;
  if (this->key_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_key_type());
  }

  // .KeyValue.KeyValueType value_type = 12;
  if (this->value_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_value_type());
  }

  switch (key_case()) {
    // int32 int_key = 1;
    case kIntKey: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_int_key());
      break;
    }
    // int64 long_key = 2;
    case kLongKey: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->_internal_long_key());
      break;
    }
    // double double_key = 3;
    case kDoubleKey: {
      total_size += 1 + 8;
      break;
    }
    // string string_key = 4;
    case kStringKey: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_string_key());
      break;
    }
    // string char_key = 5;
    case kCharKey: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_char_key());
      break;
    }
    case KEY_NOT_SET: {
      break;
    }
  }
  switch (value_case()) {
    // int32 int_value = 6;
    case kIntValue: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_int_value());
      break;
    }
    // int64 long_value = 7;
    case kLongValue: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->_internal_long_value());
      break;
    }
    // double double_value = 8;
    case kDoubleValue: {
      total_size += 1 + 8;
      break;
    }
    // string string_value = 9;
    case kStringValue: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_string_value());
      break;
    }
    // string char_value = 10;
    case kCharValue: {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_char_value());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KeyValue::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:KeyValue)
  GOOGLE_DCHECK_NE(&from, this);
  const KeyValue* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KeyValue>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:KeyValue)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:KeyValue)
    MergeFrom(*source);
  }
}

void KeyValue::MergeFrom(const KeyValue& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:KeyValue)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.key_type() != 0) {
    _internal_set_key_type(from._internal_key_type());
  }
  if (from.value_type() != 0) {
    _internal_set_value_type(from._internal_value_type());
  }
  switch (from.key_case()) {
    case kIntKey: {
      _internal_set_int_key(from._internal_int_key());
      break;
    }
    case kLongKey: {
      _internal_set_long_key(from._internal_long_key());
      break;
    }
    case kDoubleKey: {
      _internal_set_double_key(from._internal_double_key());
      break;
    }
    case kStringKey: {
      _internal_set_string_key(from._internal_string_key());
      break;
    }
    case kCharKey: {
      _internal_set_char_key(from._internal_char_key());
      break;
    }
    case KEY_NOT_SET: {
      break;
    }
  }
  switch (from.value_case()) {
    case kIntValue: {
      _internal_set_int_value(from._internal_int_value());
      break;
    }
    case kLongValue: {
      _internal_set_long_value(from._internal_long_value());
      break;
    }
    case kDoubleValue: {
      _internal_set_double_value(from._internal_double_value());
      break;
    }
    case kStringValue: {
      _internal_set_string_value(from._internal_string_value());
      break;
    }
    case kCharValue: {
      _internal_set_char_value(from._internal_char_value());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
}

void KeyValue::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:KeyValue)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KeyValue::CopyFrom(const KeyValue& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:KeyValue)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KeyValue::IsInitialized() const {
  return true;
}

void KeyValue::InternalSwap(KeyValue* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(KeyValue, value_type_)
      + sizeof(KeyValue::value_type_)
      - PROTOBUF_FIELD_OFFSET(KeyValue, key_type_)>(
          reinterpret_cast<char*>(&key_type_),
          reinterpret_cast<char*>(&other->key_type_));
  swap(key_, other->key_);
  swap(value_, other->value_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
  swap(_oneof_case_[1], other->_oneof_case_[1]);
}

::PROTOBUF_NAMESPACE_ID::Metadata KeyValue::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::KeyValue* Arena::CreateMaybeMessage< ::KeyValue >(Arena* arena) {
  return Arena::CreateMessageInternal< ::KeyValue >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>