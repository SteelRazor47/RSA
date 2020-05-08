#pragma once

#include <gmpxx.h>
#include "Message.hpp"


class RSA
{
public:
    explicit RSA(const int size = 2048);

    Message encrypt(const PublicKey& key, Message message) const;
    Message decrypt(Message message) const;

    PublicKey getPublicKey() const { return m_Keys.first; }

private:
    const int m_Size;
    gmp_randclass m_State;
    const std::pair<PublicKey, PrivateKey> m_Keys;
};