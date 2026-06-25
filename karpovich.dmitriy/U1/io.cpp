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

bool karpovich::readPersons(std::istream &input, Vector< Person > &persons, size_t &validCount, size_t &ignoredCount)
{
  validCount = 0;
  ignoredCount = 0;
  std::string line;
  while (std::getline(input, line)) {
    size_t pos = 0;
    while (pos < line.size() && std::isspace(line[pos])) {
      ++pos;
    }
    size_t id = 0;
    size_t idBegin = pos;
    while (pos < line.size() && std::isdigit(line[pos])) {
      id = id * 10 + static_cast< size_t >(line[pos] - '0');
      ++pos;
    }
    if (idBegin == pos) {
      ++ignoredCount;
      continue;
    }
    while (pos < line.size() && std::isspace(line[pos])) {
      ++pos;
    }
    if (pos == line.size()) {
      ++ignoredCount;
      continue;
    }
    if (containsPerson(persons, id)) {
      ++ignoredCount;
      continue;
    }
    Person person;
    person.id = id;
    person.info = line.substr(pos);
    if (!pushBack(persons, person)) {
      return false;
    }
    ++validCount;
  }
  return true;
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
