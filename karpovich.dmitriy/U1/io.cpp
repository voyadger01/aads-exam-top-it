#include "io.hpp"
#include <istream>
#include <ostream>
#include <string>

void karpovich::writePersons(std::ostream &output, const Vector< Person > &persons)
{
  for (size_t i = 0; i < persons.size; ++i) {
    output << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }
}

void karpovich::writeStatistics(std::ostream &output, size_t validCount, size_t ignoredCount)
{
  output << validCount << ' ' << ignoredCount << '\n';
}