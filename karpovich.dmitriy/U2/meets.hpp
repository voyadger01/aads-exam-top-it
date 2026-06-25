#ifndef MEETS_HPP
#define MEETS_HPP

#include <iosfwd>
#include "../common/person.hpp"
#include "../common/persons.hpp"
#include "../common/vector.hpp"
#include "meet.hpp"

namespace karpovich
{
  void readMeets(std::istream &input, Vector< Meet > &meets);
  void removeSelfMeets(Vector< Meet > &meets);
  void cmdAnons(std::istream &, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdDeanon(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets);
  void cmdRedesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdDesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdMeets(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdCommons(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdLess(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdGreater(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdOutPersons(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
}

#endif
