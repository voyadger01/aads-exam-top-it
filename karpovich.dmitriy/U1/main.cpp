#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <person.hpp>
#include <persons.hpp>
#include <vector.hpp>

int main(int argc, char **argv)
{
  if (argc > 3) {
    std::cerr << "Invalid arguments\n";
    return 0;
  }
  bool hasInputFile = false;
  bool hasOutputFile = false;

  std::string inputFileName;
  std::string outputFileName;

  for (size_t i = 1; i < static_cast< size_t >(argc); ++i) {
    std::string argument = argv[i];

    if (argument.compare(0, 3, "in:") == 0) {
      if (hasInputFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasInputFile = true;
      inputFileName = argument.substr(3);
    } else if (argument.compare(0, 4, "out:") == 0) {
      if (hasOutputFile) {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasOutputFile = true;
      outputFileName = argument.substr(4);
    } else {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
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

    std::cerr << validCount << ' ' << ignoredCount << '\n';
  } else {
    size_t validCount = 0;
    size_t ignoredCount = 0;

    karpovich::readPersons(std::cin, persons, validCount, ignoredCount);

    std::cerr << validCount << ' ' << ignoredCount << '\n';
  }

  if (hasOutputFile) {
    std::ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
      std::cerr << "Cannot open file\n";
      karpovich::destroyVector(persons);
      return 2;
    }

    karpovich::writePersons(outputFile, persons);

    std::cout << "in file " << outputFileName << '\n';
    karpovich::writePersons(std::cout, persons);
  } else {
    karpovich::writePersons(std::cout, persons);
  }

  karpovich::destroyVector(persons);

  return 0;
}
