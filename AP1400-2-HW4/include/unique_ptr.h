#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
  T* _p;

 public:
  UniquePtr(T* p = nullptr) : _p{p} {}

  auto get() const -> T* {
    return _p;
  }
  auto reset(T* t = nullptr) -> void {
    delete _p;
    _p = t;
  }
  auto release() -> T* {
    T* temp = _p;
    _p = nullptr;
    return temp;
  }

  auto operator*() const -> T& { return *_p; }
  auto operator->() -> T* { return _p; }
  operator bool() const { return _p != nullptr; }
};

template <typename T>
UniquePtr<T> make_unique(T t) {
  return UniquePtr<T>{new T{t}};
}

#endif  // UNIQUE_PTR