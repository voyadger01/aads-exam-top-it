#include "commands.hpp"
#include <iostream>
#include <string>
#include "meets.hpp"

namespace
{
  struct Command
  {
    const char *name;
    void (*handler)(std::istream &input, std::ostream &output, karpovich::Vector< karpovich::Person > &persons,
                    karpovich::Vector< karpovich::Meet > &meets);
  };

  const Command COMMANDS[] = {{"anons", karpovich::cmdAnons},     {"deanon", karpovich::cmdDeanon},
                              {"redesc", karpovich::cmdRedesc},   {"desc", karpovich::cmdDesc},
                              {"meet", karpovich::cmdMeets},      {"meets", karpovich::cmdMeets},
                              {"commons", karpovich::cmdCommons}, {"less", karpovich::cmdLess},
                              {"greater", karpovich::cmdGreater}, {"out-persons", karpovich::cmdOutPersons}};

  const size_t COMMANDS_COUNT = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
}

void karpovich::processCommand(std::istream &input, std::ostream &output, Vector< Person > &persons,
                               Vector< Meet > &meets, const std::string &command)
{
  for (size_t i = 0; i < COMMANDS_COUNT; ++i) {
    if (command == COMMANDS[i].name) {
      COMMANDS[i].handler(input, output, persons, meets);
      return;
    }
  }
  output << "<INVALID COMMAND>\n";
  while (input.get() != '\n') {
    if (!input) {
      break;
    }
  }
}
