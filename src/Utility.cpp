#include "Utility.hpp"


mpz_class fastExp(mpz_class x, mpz_class n, const mpz_class& mod)
{
    if (n < 0)
    {
        x = 1 / x;
        n = -n;
    }
    if (n == 0)
        return 1;
    mpz_class y = 1;
    while (n > 1)
    {
        if (n % 2 == 0)
        {
            x = (x * x) % mod;
            n = n / 2;
        }
        else
        {
            y = (x * y) % mod;
            x = (x * x) % mod;
            n = (n - 1) / 2;
        }
    }
    return (x * y) % mod;
}

mpz_class inverse(const mpz_class& a, const mpz_class& n)
{
    mpz_class t = 0;
    mpz_class newt = 1;
    mpz_class r = n;
    mpz_class newr = a;

    mpz_class quotient, tempt, tempr;
    while (newr != 0)
    {
        quotient = r / newr;
        tempt = t;
        t = newt;
        newt = tempt - quotient * newt;

        tempr = r;
        r = newr;
        newr = tempr - quotient * newr;
    }

    if (t < 0)
        t += n;

    return t;
}

mpz_class randomBigPrime( const int size, gmp_randclass& state)
{
    mpz_class prime = state.get_z_bits(size - 1);
    static mpz_class offset;
    mpz_ui_pow_ui(offset.get_mpz_t(), 2, size - 1);
    prime += offset;
    while (!mpz_probab_prime_p(prime.get_mpz_t(), 200))
    {
        prime = state.get_z_bits(size - 1);
        prime += offset;
    }
    return prime;
}