#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace karpovich
{
  template< typename T >
  struct Vector
  {
    T *data;
    size_t size;
    size_t capacity;
  };

  template< typename T >
  void initVector(Vector< T > &vector)
  {
    vector.data = nullptr;
    vector.size = 0;
    vector.capacity = 0;
  }

  template< typename T >
  void destroyVector(Vector< T > &vector)
  {
    delete[] vector.data;
    vector.data = nullptr;
    vector.size = 0;
    vector.capacity = 0;
  }

  template< typename T >
  bool reserveVector(Vector< T > &vector, size_t newCapacity)
  {
    if (newCapacity <= vector.capacity) {
      return true;
    }
    T *newData = nullptr;
    try {
      newData = new T[newCapacity];
    } catch (...) {
      return false;
    }
    for (size_t i = 0; i < vector.size; ++i) {
      newData[i] = vector.data[i];
    }
    delete[] vector.data;
    vector.data = newData;
    vector.capacity = newCapacity;
    return true;
  }

  template< typename T >
  bool pushBack(Vector< T > &vector, const T &value)
  {
    if (vector.size == vector.capacity) {
      size_t newCapacity = vector.capacity == 0 ? 4 : vector.capacity * 2;
      if (!reserveVector(vector, newCapacity)) {
        return false;
      }
    }
    vector.data[vector.size] = value;
    ++vector.size;
    return true;
  }

  template< typename T >
  void clearVector(Vector< T > &vector)
  {
    vector.size = 0;
  }

  template< typename T >
  T &at(Vector< T > &vector, size_t index)
  {
    return vector.data[index];
  }

  template< typename T >
  const T &at(const Vector< T > &vector, size_t index)
  {
    return vector.data[index];
  }
}

#endif
