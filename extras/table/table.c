/*
 generate tables of powers of ten powers_ten[] and powers_ten_e[]
 compile with gcc table.c -lgmp -o table
 fixme: get rounding of last bit right
 */

#include <gmp.h>
#include <stdio.h>

int main() {
  int j;
  mpz_t d, n, q, round;
  mpz_init(d);
  mpz_init(n);
  mpz_init(q);
  mpz_init(round);

  /* negative powers of 10 */
  mpz_set_ui(d, 1);
  mpz_mul_2exp(d, d, 255);
  mpz_set_ui(round, 1);
  mpz_mul_2exp(round, round, 191);

  for (j = 37; j >= 0; --j) {
    mpz_set_ui(n, 1);
    for (int i = 0; i < j; i++) {
      mpz_mul_ui(n, n, 10U);
    }
    mpz_cdiv_q(q, d, n);
    int exp = 0;
    exp = mpz_sizeinbase(q, 2);
    mpz_mul_2exp(q, q, 256 - exp);
    //mpz_add(q, q, round); // rounding
    mpz_cdiv_q_2exp(q, q, 64 * 3);
    char *s = mpz_get_str(NULL, 16, q);
    printf("%d 0x%s %d\n", j, s, exp - 256 - 4);
  }

  /* positive powers of 10 */
  for (j = 1; j < 47; j++) {
    mpz_set_ui(n, 1);
    for (int i = 0; i < j; i++) {
      mpz_mul_ui(n, n, 10U);
    }
    int exp = 0;
    exp = mpz_sizeinbase(n, 2);
    mpz_mul_2exp(n, n, 256 - exp);
    //mpz_add(q, q, round); // rounding
    mpz_cdiv_q_2exp(n, n, 64 * 3);
    char *s = mpz_get_str(NULL, 16, n);
    printf("%d 0x%s %d\n", j, s, exp - 5);
  }
}
// not truncated
