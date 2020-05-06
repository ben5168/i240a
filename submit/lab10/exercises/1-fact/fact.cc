#include "fact.hh"

unsigned fact(unsigned n) {
  return (n <= 1) ? 1 : n * fact(n - 1);
}
