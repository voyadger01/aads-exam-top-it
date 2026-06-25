#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include "commands.hpp"
#include "meet.hpp"
#include "meets.hpp"

namespace
{
  bool startsWith(const std::string &str, const std::string &prefix)
  {
    if (str.size() < prefix.size()) {
      return false;
    }
    for (size_t i = 0; i < prefix.size(); ++i) {
      if (str[i] != prefix[i]) {
        return false;
      }
    }
    return true;
  }
}

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  bool hasInputFile = false;
  bool hasDataFile = false;

  std::string inputFileName;
  std::string dataFileName;

  for (size_t i = 1; i < static_cast<size_t>(argc); ++i) {
    std::string argument = argv[i];

    if (startsWith(argument, "in:")) {
      if (hasInputFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasInputFile = true;
      inputFileName = argument.substr(3);
    } else if (startsWith(argument, "data:")) {
      if (hasDataFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasDataFile = true;
      dataFileName = argument.substr(5);
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }

  if (!hasDataFile) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  karpovich::Vector< karpovich::Person > persons;
  karpovich::initVector(persons);

  if (hasInputFile) {
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
      std::cerr << "Cannot open file\n";
      karpovich::destroyVector(persons);
      return 2;
    }

    size_t validCount = 0;
    size_t ignoredCount = 0;

    karpovich::readPersons(inputFile, persons, validCount, ignoredCount);
  }

  karpovich::Vector< karpovich::Meet > meets;
  karpovich::initVector(meets);

  try {
    std::ifstream dataFile(dataFileName);

    if (!dataFile.is_open()) {
      std::cerr << "Cannot open file\n";
      karpovich::destroyVector(persons);
      karpovich::destroyVector(meets);
      return 2;
    }

    karpovich::readMeets(dataFile, meets);
    karpovich::removeSelfMeets(meets);

    for (size_t i = 0; i < meets.size; ++i) {
      if (!karpovich::containsPerson(persons, meets.data[i].firstId)) {
        karpovich::Person anon;
        anon.id = meets.data[i].firstId;
        anon.info = "";
        karpovich::pushBack(persons, anon);
      }

      if (!karpovich::containsPerson(persons, meets.data[i].secondId)) {
        karpovich::Person anon;
        anon.id = meets.data[i].secondId;
        anon.info = "";
        karpovich::pushBack(persons, anon);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    karpovich::destroyVector(persons);
    karpovich::destroyVector(meets);
    return 3;
  }

  std::string command;

  while (std::cin >> command) {
    try {
      karpovich::processCommand(std::cin, std::cout, persons, meets, command);
      std::cout << '\n';
    } catch (const std::exception &) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  karpovich::destroyVector(persons);
  karpovich::destroyVector(meets);

  return 0;
}
