#include <fstream>
#include <iostream>
#include <string>
#include "io.hpp"
#include "person.hpp"
#include "vector.hpp"

int main(int argc, char **argv)
{
  bool hasInputFile = false;
  bool hasOutputFile = false;
  std::string inputFileName;
  std::string outputFileName;
  for (int i = 1; i < argc; ++i) {
    std::string argument = argv[i];
    if (argument.substr(0, 3) == "in:") {
      if (hasInputFile) {
        return 1;
      }
      hasInputFile = true;
      inputFileName = argument.substr(3);
    } else if (argument.substr(0, 4) == "out:") {
      if (hasOutputFile) {
        return 1;
      }
      hasOutputFile = true;
      outputFileName = argument.substr(4);
    } else {
      return 1;
    }
  }
  if (argc > 3) {
    return 1;
  }
  std::ifstream inputFile;
  std::ofstream outputFile;
  std::istream *input = &std::cin;
  std::ostream *output = &std::cout;
  if (hasInputFile) {
    inputFile.open(inputFileName);
    if (!inputFile) {
      return 2;
    }
    input = &inputFile;
  }
  if (hasOutputFile) {
    outputFile.open(outputFileName);
    if (!outputFile) {
      return 2;
    }
    output = &outputFile;
  }
  karpovich::Vector< karpovich::Person > persons;
  karpovich::initVector(persons);
  size_t validCount = 0;
  size_t ignoredCount = 0;
  if (!karpovich::readPersons(*input, persons, validCount, ignoredCount)) {
    karpovich::destroyVector(persons);
    return 2;
  }
  karpovich::writePersons(*output, persons);
  karpovich::writeStatistics(std::cerr, validCount, ignoredCount);
  karpovich::destroyVector(persons);

  return 0;
}
