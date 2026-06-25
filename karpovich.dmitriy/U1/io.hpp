#ifndef IO_HPP
#define IO_HPP

#include <cstddef>
#include <iosfwd>
#include "person.hpp"
#include "vector.hpp"

namespace karpovich
{
  bool readPersons(std::istream &input, Vector< Person > &persons, size_t &validCount, size_t &ignoredCount);
  bool containsPerson(const Vector< Person > &persons, size_t id);
  void writePersons(std::ostream &output, const Vector< Person > &persons);
  void writeStatistics(std::ostream &output, size_t validCount, size_t ignoredCount);
}

#endif
