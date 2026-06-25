#include "io.hpp"
#include <istream>
#include <ostream>
#include <string>

bool karpovich::containsPerson(const Vector< Person > &persons, size_t id)
{
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      return true;
    }
  }
  return false;
}

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
