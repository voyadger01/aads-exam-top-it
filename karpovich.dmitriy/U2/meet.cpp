#ifndef KARPOVICH_MEETS_HPP
#define KARPOVICH_MEETS_HPP

#include "meet.hpp"
#include <cstddef>
#include <iosfwd>
#include "../common/person.hpp"
#include "../common/vector.hpp"

namespace karpovich
{
  void readMeets(std::istream &input, Vector< Meet > &meets);
  void removeSelfMeets(Vector< Meet > &meets);
  void printMeets(std::ostream &output, const Vector< Meet > &meets, size_t id);
  void printAnons(std::ostream &output, const Vector< Person > &persons);
  void deanon(Vector< Person > &persons, Vector< Meet > &meets, size_t anonId, size_t id);
  void redesc(Vector< Person > &persons, size_t id, const std::string &description);
  void desc(std::ostream &output, const Vector< Person > &persons, size_t id);
  void commons(std::ostream &output, const Vector< Meet > &meets, size_t id1, size_t id2);
  void less(std::ostream &output, const Vector< Meet > &meets, size_t time, size_t id);
  void greater(std::ostream &output, const Vector< Meet > &meets, size_t time, size_t id);
  void outPersons(std::ostream &output, const Vector< Person > &persons);
}

#endif
