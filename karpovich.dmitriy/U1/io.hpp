#ifndef IO_HPP
#define IO_HPP

#include <cstddef>
#include <iosfwd>
#include "person_array.hpp"

namespace karpovich
{
  bool readPersons(std::istream &input, PersonArray &persons, size_t &validCount, size_t &ignoredCount);
  void writePersons(std::ostream &output, const PersonArray &persons);
  void writeStatistics(std::ostream &output, size_t validCount, size_t ignoredCount);
}

#endif
