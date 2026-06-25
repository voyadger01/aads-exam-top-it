#include <cstddef>
#include <istream>
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

void karpovich::printMeets(std::ostream &output, const Vector< Meet > &meets, size_t id)
{
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
