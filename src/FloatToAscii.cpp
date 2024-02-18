#include "FloatToAscii.h"
#include "ftoa.h"

String &FloatToAscii(String &s, float f, int precision) {
  char buf[20] = { 0 };
  int len = ftoa(buf, sizeof(buf), f, precision);
  buf[sizeof(buf) - 1] = '\0';
  s = buf;
  return s;
}
