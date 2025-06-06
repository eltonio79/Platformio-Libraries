// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#pragma once

#include <ArduinoJson/Configuration.hpp>
#include <ArduinoJson/Operators/VariantOperators.hpp>
#include <ArduinoJson/Variant/VariantTo.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4522)
#endif

namespace ARDUINOJSON_NAMESPACE {

template <typename TArray>
class ElementProxy : public VariantOperators<ElementProxy<TArray> >,
                     public Visitable {
  typedef ElementProxy<TArray> this_type;

 public:
  FORCE_INLINE ElementProxy(TArray array, size_t index)
      : _array(array), _index(index) {}

  FORCE_INLINE this_type& operator=(const this_type& src) {
    getUpstreamElement().set(src.as<VariantConstRef>());
    return *this;
  }

  // Replaces the value
  //
  // operator=(const TValue&)
  // TValue = bool, long, int, short, float, double, serialized, VariantRef,
  //          std::string, String, ArrayRef, ObjectRef
  template <typename T>
  FORCE_INLINE this_type& operator=(const T& src) {
    getUpstreamElement().set(src);
    return *this;
  }
  //
  // operator=(TValue)
  // TValue = char*, const char*, const __FlashStringHelper*
  template <typename T>
  FORCE_INLINE this_type& operator=(T* src) {
    getUpstreamElement().set(src);
    return *this;
  }

  FORCE_INLINE bool operator==(VariantConstRef rhs) const {
    return static_cast<VariantConstRef>(getUpstreamElement()) == rhs;
  }

  FORCE_INLINE bool operator!=(VariantConstRef rhs) const {
    return static_cast<VariantConstRef>(getUpstreamElement()) != rhs;
  }

  FORCE_INLINE void clear() const {
    getUpstreamElement().clear();
  }

  FORCE_INLINE bool isNull() const {
    return getUpstreamElement().isNull();
  }

  template <typename T>
  FORCE_INLINE typename VariantAs<T>::type as() const {
    return getUpstreamElement().template as<T>();
  }

  template <typename T>
  FORCE_INLINE bool is() const {
    return getUpstreamElement().template is<T>();
  }

  template <typename T>
  FORCE_INLINE typename VariantTo<T>::type to() const {
    return getUpstreamElement().template to<T>();
  }

  // Replaces the value
  //
  // bool set(const TValue&)
  // TValue = bool, long, int, short, float, double, serialized, VariantRef,
  //          std::string, String, ArrayRef, ObjectRef
  template <typename TValue>
  FORCE_INLINE bool set(const TValue& value) const {
    return getUpstreamElement().set(value);
  }
  //
  // bool set(TValue)
  // TValue = char*, const char*, const __FlashStringHelper*
  template <typename TValue>
  FORCE_INLINE bool set(TValue* value) const {
    return getUpstreamElement().set(value);
  }

  template <typename Visitor>
  void accept(Visitor& visitor) const {
    return getUpstreamElement().accept(visitor);
  }

  FORCE_INLINE size_t size() const {
    return getUpstreamElement().size();
  }

  template <typename TNestedKey>
  VariantRef getMember(TNestedKey* key) const {
    return getUpstreamElement().getMember(key);
  }

  template <typename TNestedKey>
  VariantRef getMember(const TNestedKey& key) const {
    return getUpstreamElement().getMember(key);
  }

  template <typename TNestedKey>
  VariantRef getOrAddMember(TNestedKey* key) const {
    return getUpstreamElement().getOrAddMember(key);
  }

  template <typename TNestedKey>
  VariantRef getOrAddMember(const TNestedKey& key) const {
    return getUpstreamElement().getOrAddMember(key);
  }

  VariantRef addElement() const {
    return getUpstreamElement().addElement();
  }

  VariantRef getElement(size_t index) const {
    return getUpstreamElement().getElement(index);
  }

  FORCE_INLINE void remove(size_t index) const {
    getUpstreamElement().remove(index);
  }
  // remove(char*) const
  // remove(const char*) const
  // remove(const __FlashStringHelper*) const
  template <typename TChar>
  FORCE_INLINE typename enable_if<IsString<TChar*>::value>::type remove(
      TChar* key) const {
    getUpstreamElement().remove(key);
  }
  // remove(const std::string&) const
  // remove(const String&) const
  template <typename TString>
  FORCE_INLINE typename enable_if<IsString<TString>::value>::type remove(
      const TString& key) const {
    getUpstreamElement().remove(key);
  }

 private:
  FORCE_INLINE VariantRef getUpstreamElement() const {
    return _array.getElement(_index);
  }

  TArray _array;
  const size_t _index;
};

template <typename TArray>
inline ElementProxy<const TArray&> ArrayShortcuts<TArray>::operator[](
    size_t index) const {
  return ElementProxy<const TArray&>(*impl(), index);
}

}  // namespace ARDUINOJSON_NAMESPACE

#ifdef _MSC_VER
#pragma warning(pop)
#endif
