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
