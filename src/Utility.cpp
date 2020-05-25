#include "Utility.hpp"

mpz_class fastExp(mpz_class x, mpz_class n, const mpz_class &mod)
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

mpz_class inverse(const mpz_class &a, const mpz_class &n)
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

mpz_class randomBigPrime(const int size, gmp_randclass &state)
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

std::string sanitizeString(std::string str)
{
    while (str[0] == '0')
    {
        str.erase(str.begin());
    }
    return str;
}

std::string encodeString(const std::string_view str)
{
    std::string result = std::to_string(int(str[0]));
    for (std::size_t i = 1; i < str.size(); i++)
    {
        auto &&ch = str[i];
        if (ch > 99)
            result += std::to_string(int(ch));
        else if (ch > 9)
            result += "0" + std::to_string(int(ch));
        else
            result += "00" + std::to_string(int(ch));
    }

    return result;
}

std::string decodeString(const std::string &msg)
{
    std::string result{};
    int offset = 0;
    if (msg.size() % 3 == 1)
    {
        result += char(msg[0] - '0');
        offset = 1;
    }
    else if (msg.size() % 3 == 2)
    {
        result += char((msg[0] - '0') * 10 + msg[1] - '0');
        offset = 2;
    }

    for (std::size_t i = offset; i < msg.size(); i += 3)
    {
        result += char((msg[i] - '0') * 100 + (msg[i + 1] - '0') * 10 + msg[i + 2] - '0');
    }

    return result;
}