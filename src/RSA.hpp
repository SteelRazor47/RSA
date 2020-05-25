#pragma once

#include <gmpxx.h>
#include "Message.hpp"

class RSA
{
public:
    explicit RSA(const int size);
    explicit RSA(const mpz_class &p, const mpz_class &q);

    Message encrypt(const PublicKey &key, Message message) const;
    Message decrypt(Message message) const;

    PublicKey getPublicKey() const { return m_Keys.first; }

public:
    gmp_randclass m_State;
    std::pair<PublicKey, PrivateKey> m_Keys;
};