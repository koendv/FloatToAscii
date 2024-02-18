#include <stdio.h>

/* test program for powers of 10 algorithm. print 10**n, n = -45 ... 38 */

static float ipow10f(int n) {
  float p = 1.0f;
  float q = 10.0f;
  if (n < 0) {
    q = 0.1f;
    n = -n;
  }
  while (n != 0) {
    if (n & 0x1)
      p *= q;
    q *= q;
    n >>= 1;
  }
  return p;
}
int main() {
  for (int i = -45; i < 39; i++)
    printf("%d %g\n", i, ipow10f(i));
}
