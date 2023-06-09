#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
  T* _p;
  int* _count;

 public:
  SharedPtr(T* p = nullptr) : _p{p} {
    _count = bool(_p) ? new int{1} : new int{0};
  }
  SharedPtr(const SharedPtr& other) : _p{other._p}, _count{other._count} {
    ++(*_count);
  }
  ~SharedPtr() {
    --(*_count);
    if (*_count == 0) {
      _p = nullptr;
    }
  }

  auto get() const -> T* { return _p; }
  auto use_count() const -> int { return *_count; }
  auto reset(T* t = nullptr) -> void {
    _p = t;
    *_count = bool(_p) ? 1 : 0;
  }

  auto operator*() const -> T& { return *_p; }
  auto operator->() const -> T* { return _p; }
  auto operator=(const SharedPtr& other) -> SharedPtr& {
    if (this != &other) {
      --(*_count);
      if (*_count == 0) {
        _p = nullptr;
      }
      _p = other._p;
      _count = other._count;
      ++(*_count);
    }
    return *this;
  }
  operator bool() const { return bool(_p); }
};

template <typename T>
SharedPtr<T> make_shared(T t) {
  return SharedPtr<T>{new T{t}};
}

#endif  // SHARED_PTR