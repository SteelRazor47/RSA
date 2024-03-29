#include "RSA.hpp"
#include "Utility.hpp"
#include <chrono>

RSA::RSA(const int s)
    : m_State(gmp_randinit_mt),
      m_Keys([&]() {
          auto time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
          m_State.seed(time);

          mpz_class p = randomBigPrime(s / 2, m_State);
          mpz_class q = randomBigPrime(s / 2, m_State);
          mpz_class n = p * q;
          mpz_class lambda = lcm(p - 1,  q - 1);
          mpz_class e = m_State.get_z_range(lambda - 1) + 1;
          while (gcd(e, lambda) != 1)
              e = m_State.get_z_range(lambda - 1) + 1;
          mpz_class d = inverse(e, lambda);

          return std::pair<PublicKey, PrivateKey>{{n, e}, {p, q, d}};
      }())
{
}

RSA::RSA(const mpz_class &p, const mpz_class &q)
    : m_State(gmp_randinit_mt),
      m_Keys([&]() {
          mpz_class n = p * q;
          mpz_class lambda = lcm(p - 1,  q - 1);
          mpz_class e = m_State.get_z_range(lambda - 1) + 1;
          while (gcd(e, lambda) != 1)
              e = m_State.get_z_range(lambda - 1) + 1;
          mpz_class d = inverse(e, lambda);

          return std::pair<PublicKey, PrivateKey>{{n, e}, {p, q, d}};
      }())
{
}

Message RSA::decrypt(Message message) const
{
    message.decrypt(m_Keys.second);
    return message;
}

Message RSA::encrypt(const PublicKey &key, Message message) const
{
    message.encrypt(key);
    return message;
}
