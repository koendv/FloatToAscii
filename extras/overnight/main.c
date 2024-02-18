#include "ftoa.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 check reading the printed float produces the original float.
 print one dot on the screen for every million tested.
 */

typedef union f32_u {
  float f;
  unsigned int i;
} f32_u;

int main() {
  f32_u fval;
  char s[16];
  float f;
  int len, read;

  setbuf(stdout, NULL);
  while (1) {
    for (int i = 0; i < 10000000; i++) {
      fval.i = random();
      if (isnan(fval.f) || isinf(fval.f))
        continue;
      len = ftoa(s, sizeof(s), fval.f, -1);
      read = sscanf(s, "%f", &f);
      if ((read != 1) || (f != fval.f) || (len >= sizeof(s)))
        printf("\n%d '%15s' %15g\n", len, s, fval.f);
    }
    printf(".");
  }

  return 0;
}
