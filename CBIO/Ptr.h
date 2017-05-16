#ifndef __CB_IO_PTR_H__
#define __CB_IO_PTR_H__

namespace cb {
  template<typename _Type>
  class ptr {
  private:
    _Type* mpPtr;

  public:
    ptr();
    ptr(const ptr& other);
    ptr(_Type* other);

    _Type* Get();
    const _Type* Get() const;

    void MakeNull();
    void Delete();

    _Type* operator->();
    const _Type* operator->() const;

    _Type& operator*();
    const _Type& operator*() const;

    void operator=(_Type * other);
    void operator=(ptr<_Type>& other);

    const bool operator==(const ptr<_Type>& other) const;
    const bool operator==(const _Type* other) const;
    const bool operator!=(const ptr<_Type>& other) const;
    const bool operator!=(const _Type* other) const;

    const bool operator!() const;

    operator bool() const;
    operator _Type*();
    operator const _Type*() const;
  };

  template<typename _Type>
  inline ptr<_Type>::ptr() : mpPtr(nullptr) {}

  template<typename _Type>
  inline ptr<_Type>::ptr(const ptr & other) 
    : mpPtr(other.mpPtr)
  {}

  template<typename _Type>
  inline ptr<_Type>::ptr(_Type * other) 
    : mpPtr(other)
  {}

  template<typename _Type>
  inline _Type * ptr<_Type>::Get() {
    return mpPtr;
  }

  template<typename _Type>
  inline const _Type * ptr<_Type>::Get() const {
    return mpPtr;
  }

  template<typename _Type>
  inline void ptr<_Type>::MakeNull() {
    mpPtr = nullptr;
  }

  template<typename _Type>
  inline void ptr<_Type>::Delete() {
    delete mpPtr;
    mpPtr = nullptr;
  }

  template<typename _Type>
  inline _Type * ptr<_Type>::operator->() {
    return mpPtr;
  }

  template<typename _Type>
  inline const _Type * ptr<_Type>::operator->() const {
    return mpPtr;
  }

  template<typename _Type>
  inline _Type & ptr<_Type>::operator*() {
    return *mpPtr;
  }

  template<typename _Type>
  inline const _Type & ptr<_Type>::operator*() const {
    return *mpPtr;
  }

  template<typename _Type>
  inline void ptr<_Type>::operator=(_Type* other) {
    mpPtr = other;
  }

  template<typename _Type>
  inline void ptr<_Type>::operator=(ptr<_Type>& other) {
    mpPtr = other.mpPtr;
  }

  template<typename _Type>
  inline const bool ptr<_Type>::operator==(const ptr<_Type>& other) const {
    return mpPtr == other.mpPtr;
  }

  template<typename _Type>
  inline const bool ptr<_Type>::operator==(const _Type * other) const {
    return mpPtr == other;
  }

  template<typename _Type>
  inline const bool ptr<_Type>::operator!=(const ptr<_Type>& other) const {
    return mpPtr != other.mpPtr;
  }

  template<typename _Type>
  inline const bool ptr<_Type>::operator!=(const _Type * other) const {
    return mpPtr != other;
  }

  template<typename _Type>
  inline const bool ptr<_Type>::operator!() const {
    return mpPtr == nullptr;
  }

  template<typename _Type>
  inline ptr<_Type>::operator bool() const {
    return (bool)(mpPtr != nullptr);
  }

  template<typename _Type>
  inline ptr<_Type>::operator _Type*() {
    return mpPtr;
  }

  template<typename _Type>
  inline ptr<_Type>::operator const _Type*() const {
    return mpPtr;
  }
}

#endif // !__CB_IO_PTR_H__

