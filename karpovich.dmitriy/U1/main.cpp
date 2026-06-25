#include <fstream>
#include <iostream>
#include <string>
#include "person.hpp"
#include "persons.hpp"
#include "vector.hpp"

int main(int argc, char **argv)
{
  if (argc > 3) {
    return 1;
  }
  bool hasInputFile = false;
  bool hasOutputFile = false;

  std::string inputFileName;
  std::string outputFileName;

  for (int i = 1; i < argc; ++i) {
    std::string argument = argv[i];
    if (argument.compare(0, 3, "in:") == 0) {
      if (hasInputFile) {
        return 1;
      }
      hasInputFile = true;
      inputFileName = argument.substr(3);
    } else if (argument.compare(0, 4, "out:") == 0) {
      if (hasOutputFile) {
        return 1;
      }
      hasOutputFile = true;
      outputFileName = argument.substr(4);
    } else {
      return 1;
    }
  }

  karpovich::Vector< karpovich::Person > persons;
  karpovich::initVector(persons);

  try {
    size_t validCount = 0;
    size_t ignoredCount = 0;
    if (hasInputFile) {
      std::ifstream input(inputFileName);
      if (!input) {
        karpovich::destroyVector(persons);
        return 2;
      }
      karpovich::readPersons(input, persons, validCount, ignoredCount);
    } else {
      karpovich::readPersons(std::cin, persons, validCount, ignoredCount);
    }
    if (hasOutputFile) {
      {
        std::ofstream output(outputFileName);
        if (!output) {
          karpovich::destroyVector(persons);
          return 2;
        }
        karpovich::writePersons(output, persons);
      }
      std::cout << "in file " << outputFileName << '\n';
      std::ifstream result(outputFileName);
      std::string line;
      while (std::getline(result, line)) {
        std::cout << line << '\n';
      }
    } else {
      karpovich::writePersons(std::cout, persons);
    }
  } catch (...) {
    karpovich::destroyVector(persons);
    return 2;
  }
  karpovich::destroyVector(persons);
}
