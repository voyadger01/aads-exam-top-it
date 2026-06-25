#include <cstddef>
#include <istream>
#include <stdexcept>
#include <string>
#include "meets.hpp"

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
  for (size_t i = 0; i < meets.size; ++i)
  {
    if (meets.data[i].firstId != meets.data[i].secondId)
    {
      pushBack(filtered, meets.data[i]);
    }
  }
  destroyVector(meets);
  meets = filtered;
}
