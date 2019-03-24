#include <gmp.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void writez(mpz_t z)
{
	mpz_out_str(stdout, 10, z);
	printf("\n");
}

void multiply_digits(mpz_t out, mpz_t n)
{
	mpz_t quotient;
	mpz_init(quotient);
	mpz_t remainder;
	mpz_init(remainder);

	mpz_t acc;
	mpz_init(acc);
	mpz_set_ui(acc, 1);
	
	while (mpz_sgn(n) > 0) {
		mpz_tdiv_qr_ui(n, remainder, n, 10);
		mpz_mul(acc, acc, remainder);
	}

	mpz_set(out, acc);
}

int measure_persistence(mpz_t in)
{
	mpz_t out;
	mpz_init(out);
	
	mpz_t n;
	mpz_init(n);
	mpz_set(n, in);

	int p = 0;
	while (mpz_cmp_ui(n, 10) >= 0) {
		p++;
		multiply_digits(n, n);
	}
	return p;
}

int main()
{
	mpz_t n;
	mpz_init_set_str(n, "277777788888899", 10);

	const int interesting_persistence = 10;
	const int goal_persistence = 11;
	
	while (true) {
		mpz_add_ui(n, n, 1);
		int persistence = measure_persistence(n);
		if (persistence >= goal_persistence) {
			writez(n);
			printf("has %d persistence!\n\n", persistence);
		} else if (persistence >= interesting_persistence) {
			writez(n);
			printf("has %d persistence...\n\n", persistence);
		}
	}
	
	return 0;
}
