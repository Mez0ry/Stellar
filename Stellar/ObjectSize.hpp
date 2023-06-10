#ifndef __OBJECT_SIZE_HPP__
#define __OBJECT_SIZE_HPP__

struct ObjectSize {
  ObjectSize() = default;
  ObjectSize(int width, int height) : w_(width), h_(height) {}
  ~ObjectSize() = default;

  int GetWidth() const { return w_; }
  int GetHeight() const { return h_; }

  ObjectSize &operator+=(const ObjectSize &rhs) {
    this->w_ += rhs.w_;
    this->h_ += rhs.h_;

    return *this; // return the result by reference
  }

  friend ObjectSize operator+(ObjectSize lhs, const ObjectSize &rhs) {
    return (lhs += rhs);
  }

  ObjectSize &operator-=(const ObjectSize &rhs) {
    this->w_ -= rhs.w_;
    this->h_ -= rhs.h_;

    return *this; // return the result by reference
  }
  
  friend ObjectSize operator-(ObjectSize lhs, const ObjectSize &rhs) {
    return (lhs -= rhs);
  }
  
private:
  int w_, h_;
};

#endif //! __OBJECT_SIZE_HPP__