#pragma once

#include <gmpxx.h>

mpz_class fastExp(mpz_class x, mpz_class n, const mpz_class& mod);
mpz_class inverse(const mpz_class& a, const mpz_class& n);
mpz_class randomBigPrime(const int size, gmp_randclass& state);
std::string sanitizeString(std::string str);
std::string encodeString(const std::string_view str);
std::string decodeString(const std::string& str);
