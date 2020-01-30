#include "fns-compare.hh"

static double
quadratic(double n)
{
  const double C = 1e3;
  return C*n*n;
}

static const bool isRegistered =
  register_fn(FnInfo("quadratic", quadratic));

