#include "random_data_generator.h"
#include <random>

int generate_random_int()
{
  std::random_device rd;
  std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
  return dist(rd);
}

int generate_random_int(int min, int max)
{
  std::random_device rd;
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rd);
}

char generate_random_char()
{
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 'z' - 'a');
  return 'a' + dist(rd);
}

QString generate_random_string(int len)
{
  QString str;
  for (auto i = 0; i < len; i++) {
    str += generate_random_char();
  }
  return str;
}
