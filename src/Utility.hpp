#pragma once

#include <gmpxx.h>

mpz_class fastExp(mpz_class x, mpz_class n, const mpz_class& mod);
mpz_class inverse(const mpz_class& a, const mpz_class& n);
mpz_class randomBigPrime(const int size, gmp_randclass& state);
