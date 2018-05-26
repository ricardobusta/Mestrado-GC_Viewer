#ifndef RANDOM_H
#define RANDOM_H

namespace Ric{
  static bool seeded = false;
  void init();

  int rand(int a);
  int rand(int a, int b);
}

#endif // RANDOM_H

