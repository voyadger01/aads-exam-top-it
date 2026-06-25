#ifndef PERSONS_HPP
#define PERSONS_HPP

#include <cstddef>
#include <iosfwd>
#include "person.hpp"
#include "vector.hpp"

namespace karpovich
{
  void readPersons(std::istream &input, Vector< Person > &persons, size_t &validCount, size_t &ignoredCount);
  bool containsPerson(const Vector< Person > &persons, size_t id);
  void writePersons(std::ostream &output, const Vector< Person > &persons);
  Person *findPersonById(Vector< Person > &persons, size_t id);
  const Person *findPersonById(const Vector< Person > &persons, size_t id);
}

#endif
