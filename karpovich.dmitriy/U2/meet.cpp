#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include "meets.hpp"

namespace
{
  struct MeetKey
  {
    size_t id;
    size_t duration;
  };

  bool isLess(const MeetKey &a, const MeetKey &b)
  {
    if (a.id != b.id) {
      return a.id < b.id;
    }

    return a.duration < b.duration;
  }

  void sortMeets(karpovich::Vector< MeetKey > &meets)
  {
    for (size_t i = 0; i < meets.size; ++i) {
      for (size_t j = i + 1; j < meets.size; ++j) {
        if (isLess(meets.data[j], meets.data[i])) {
          MeetKey temp = meets.data[i];
          meets.data[i] = meets.data[j];
          meets.data[j] = temp;
        }
      }
    }
  }

  void printInvalidCommand(std::ostream &output)
  {
    output << "<INVALID COMMAND>\n";
  }
}

void karpovich::readMeets(std::istream &input, Vector< Meet > &meets)
{
  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    size_t pos = 0;
    size_t firstId = 0;
    size_t secondId = 0;
    size_t duration = 0;

    try {
      firstId = std::stoul(line, &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
      ++pos;
    }

    if (pos == line.size()) {
      throw std::runtime_error("Invalid meet data");
    }

    try {
      secondId = std::stoul(line.substr(pos), &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
      ++pos;
    }

    if (pos == line.size()) {
      throw std::runtime_error("Invalid meet data");
    }

    try {
      duration = std::stoul(line.substr(pos), &pos);
    } catch (...) {
      throw std::runtime_error("Invalid meet data");
    }

    Meet meet;
    meet.firstId = firstId;
    meet.secondId = secondId;
    meet.duration = duration;

    pushBack(meets, meet);
  }
}

void karpovich::removeSelfMeets(Vector< Meet > &meets)
{
  Vector< Meet > filtered;
  initVector(filtered);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].firstId != meets.data[i].secondId) {
      pushBack(filtered, meets.data[i]);
    }
  }

  destroyVector(meets);
  meets = filtered;
}

void karpovich::cmdAnons(std::istream &, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  Vector< size_t > anons;
  initVector(anons);

  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].info.empty()) {
      pushBack(anons, persons.data[i].id);
    }
  }

  for (size_t i = 0; i < anons.size; ++i) {
    for (size_t j = i + 1; j < anons.size; ++j) {
      if (anons.data[j] < anons.data[i]) {
        size_t temp = anons.data[i];
        anons.data[i] = anons.data[j];
        anons.data[j] = temp;
      }
    }
  }

  for (size_t i = 0; i < anons.size; ++i) {
    output << anons.data[i] << '\n';
  }

  destroyVector(anons);
}

void karpovich::cmdDeanon(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets)
{
  size_t anonId = 0;
  size_t id = 0;

  input >> anonId >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  try {
    const Person *anon = findPersonById(persons, anonId);

    if (anon == nullptr || !anon->info.empty()) {
      printInvalidCommand(output);
      return;
    }

    const Person *target = findPersonById(persons, id);

    if (target == nullptr || target->info.empty()) {
      printInvalidCommand(output);
      return;
    }

    for (size_t i = 0; i < meets.size; ++i) {
      if (meets.data[i].firstId == anonId) {
        meets.data[i].firstId = id;
      }

      if (meets.data[i].secondId == anonId) {
        meets.data[i].secondId = id;
      }
    }

    for (size_t i = 0; i < persons.size; ++i) {
      if (persons.data[i].id == anonId) {
        for (size_t j = i; j + 1 < persons.size; ++j) {
          persons.data[j] = persons.data[j + 1];
        }

        --persons.size;
        break;
      }
    }

    removeSelfMeets(meets);
  } catch (...) {
    printInvalidCommand(output);
  }
}

void karpovich::cmdRedesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  size_t id = 0;
  std::string description;

  input >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  char quote = 0;
  input >> quote;

  if (quote != '"') {
    printInvalidCommand(output);
    return;
  }

  std::getline(input, description, '"');

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  try {
    Person *person = findPersonById(persons, id);

    if (person == nullptr) {
      printInvalidCommand(output);
      return;
    }

    person->info = description;
  } catch (...) {
    printInvalidCommand(output);
  }
}

void karpovich::cmdDesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  size_t id = 0;

  input >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  try {
    const Person *person = findPersonById(persons, id);

    if (person == nullptr) {
      printInvalidCommand(output);
      return;
    }

    if (person->info.empty()) {
      output << "<ANON>\n";
    } else {
      output << person->info << '\n';
    }
  } catch (...) {
    printInvalidCommand(output);
  }
}

void karpovich::cmdMeets(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t id = 0;

  input >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  Vector< MeetKey > result;
  initVector(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].firstId == id) {
      MeetKey key;
      key.id = meets.data[i].secondId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    } else if (meets.data[i].secondId == id) {
      MeetKey key;
      key.id = meets.data[i].firstId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  destroyVector(result);
}

void karpovich::cmdCommons(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t id1 = 0;
  size_t id2 = 0;

  input >> id1 >> id2;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  Vector< size_t > contacts1;
  Vector< size_t > contacts2;
  Vector< size_t > result;

  initVector(contacts1);
  initVector(contacts2);
  initVector(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].firstId == id1) {
      pushBack(contacts1, meets.data[i].secondId);
    } else if (meets.data[i].secondId == id1) {
      pushBack(contacts1, meets.data[i].firstId);
    }

    if (meets.data[i].firstId == id2) {
      pushBack(contacts2, meets.data[i].secondId);
    } else if (meets.data[i].secondId == id2) {
      pushBack(contacts2, meets.data[i].firstId);
    }
  }

  for (size_t i = 0; i < contacts1.size; ++i) {
    bool found = false;

    for (size_t j = 0; j < contacts2.size; ++j) {
      if (contacts1.data[i] == contacts2.data[j]) {
        found = true;
        break;
      }
    }

    if (found) {
      bool duplicate = false;

      for (size_t j = 0; j < result.size; ++j) {
        if (result.data[j] == contacts1.data[i]) {
          duplicate = true;
          break;
        }
      }

      if (!duplicate) {
        pushBack(result, contacts1.data[i]);
      }
    }
  }

  for (size_t i = 0; i < result.size; ++i) {
    for (size_t j = i + 1; j < result.size; ++j) {
      if (result.data[j] < result.data[i]) {
        size_t temp = result.data[i];
        result.data[i] = result.data[j];
        result.data[j] = temp;
      }
    }
  }

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i] << '\n';
  }

  destroyVector(contacts1);
  destroyVector(contacts2);
  destroyVector(result);
}

void karpovich::cmdLess(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t time = 0;
  size_t id = 0;

  input >> time >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  Vector< MeetKey > result;
  initVector(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].firstId == id && meets.data[i].duration < time) {
      MeetKey key;
      key.id = meets.data[i].secondId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    } else if (meets.data[i].secondId == id && meets.data[i].duration < time) {
      MeetKey key;
      key.id = meets.data[i].firstId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  destroyVector(result);
}

void karpovich::cmdGreater(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets)
{
  size_t time = 0;
  size_t id = 0;

  input >> time >> id;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  Vector< MeetKey > result;
  initVector(result);

  for (size_t i = 0; i < meets.size; ++i) {
    if (meets.data[i].firstId == id && meets.data[i].duration > time) {
      MeetKey key;
      key.id = meets.data[i].secondId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    } else if (meets.data[i].secondId == id && meets.data[i].duration > time) {
      MeetKey key;
      key.id = meets.data[i].firstId;
      key.duration = meets.data[i].duration;
      pushBack(result, key);
    }
  }

  sortMeets(result);

  for (size_t i = 0; i < result.size; ++i) {
    output << result.data[i].id << ' ' << result.data[i].duration << '\n';
  }

  destroyVector(result);
}

void karpovich::cmdOutPersons(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &)
{
  std::string filename;

  input >> filename;

  if (!input) {
    printInvalidCommand(output);
    return;
  }

  std::ofstream outputFile(filename);

  if (!outputFile.is_open()) {
    printInvalidCommand(output);
    return;
  }

  Vector< Person > withDescription;
  initVector(withDescription);

  for (size_t i = 0; i < persons.size; ++i) {
    if (!persons.data[i].info.empty()) {
      pushBack(withDescription, persons.data[i]);
    }
  }

  writePersons(outputFile, withDescription);

  destroyVector(withDescription);
}
