#include "persons.hpp"
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

void karpovich::readPersons(std::istream &input, Vector< Person > &persons, size_t &validCount, size_t &ignoredCount)
{
  validCount = 0;
  ignoredCount = 0;

  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    size_t pos = 0;
    size_t id = 0;

    try {
      id = std::stoul(line, &pos);
    } catch (...) {
      ++ignoredCount;
      continue;
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
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

    pushBack(persons, person);

    ++validCount;
  }
}

void karpovich::writePersons(std::ostream &output, const Vector< Person > &persons)
{
  for (size_t i = 0; i < persons.size; ++i) {
    output << persons.data[i].id << ' ' << persons.data[i].info << '\n';
  }

  if (persons.size == 0) {
    output << '\n';
  }
}
