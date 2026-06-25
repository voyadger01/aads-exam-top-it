#ifndef KARPOVICH_COMMANDS_HPP
#define KARPOVICH_COMMANDS_HPP

#include <iosfwd>
#include <string>
#include "meets.hpp"

namespace karpovich
{
  void processCommand(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets,
                      const std::string &command);
}

#endif
