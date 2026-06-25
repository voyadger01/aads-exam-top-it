#include "person_array.hpp"

void karpovich::initPersonArray(PersonArray &array)
{
  array.data = nullptr;
  array.size = 0;
  array.capacity = 0;
}

void karpovich::destroyPersonArray(PersonArray &array)
{
  delete[] array.data;

  array.data = nullptr;
  array.size = 0;
  array.capacity = 0;
}

bool karpovich::reservePersonArray(PersonArray &array, size_t newCapacity)
{
  if (newCapacity <= array.capacity) {
    return true;
  }
  Person *newData = nullptr;
  try {
    newData = new Person[newCapacity];
  } catch (...) {
    return false;
  }
  for (size_t i = 0; i < array.size; ++i) {
    newData[i] = array.data[i];
  }
  delete[] array.data;
  array.data = newData;
  array.capacity = newCapacity;
  return true;
}

bool karpovich::containsPerson(const PersonArray &array, size_t id)
{
  for (size_t i = 0; i < array.size; ++i) {
    if (array.data[i].id == id) {
      return true;
    }
  }
  return false;
}

bool karpovich::pushBackPerson(PersonArray &array, const Person &person)
{
  if (array.size == array.capacity) {
    size_t newCapacity = 4;
    if (array.capacity != 0) {
      newCapacity = array.capacity * 2;
    }
    if (!reservePersonArray(array, newCapacity)) {
      return false;
    }
  }
  array.data[array.size] = person;
  ++array.size;
  return true;
}
