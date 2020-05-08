#include "RSA.hpp"
#include "Utility.hpp"
#include <chrono>
#include <iostream>

RSA::RSA(const int s)
    : m_Size(s), m_State(gmp_randinit_mt),
      m_Keys([&]() {
          time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
          m_State.seed(time);

          mpz_class p = randomBigPrime(m_Size / 2, m_State);
          mpz_class q = randomBigPrime(m_Size / 2, m_State);
          mpz_class n = p * q;
          mpz_class lambda = lcm(p - 1, q - 1);
          mpz_class e = m_State.get_z_range(lambda - 1) + 1;
          while (gcd(e, lambda) != 1)
              e = m_State.get_z_range(lambda - 1) + 1;
          mpz_class d = inverse(e, lambda);
          std::cout << "e: " << e << "\n\n";
          std::cout << "d: " << d << "\n\n";

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
