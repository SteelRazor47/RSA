#pragma once

#include <gmpxx.h>
#include <string_view>
#include "Utility.hpp"

struct PublicKey
{
public:
    PublicKey() = default;
    PublicKey(const mpz_class &n_, const mpz_class &e_) : n(n_), e(e_) {}
    friend class Message;

public:
    const mpz_class n;
    const mpz_class e;
};

struct PrivateKey
{
public:
    PrivateKey() = default;
    PrivateKey(const mpz_class &p_, const mpz_class &q_, const mpz_class &d_)
        : p(p_), q(q_), n(p_ * q_), d(d_), dp(d_ % (p_ - 1)), dq(d_ % (q_ - 1)), qinv(inverse(q_, p_)) {}
    friend class Message;

public:
    const mpz_class n;
    const mpz_class d;
    const mpz_class p;
    const mpz_class q;
    const mpz_class dp;
    const mpz_class dq;
    const mpz_class qinv;
};

class Message
{
public:
    explicit Message(const std::string_view msg);

    void encrypt(const PublicKey &key);
    void decrypt(const PrivateKey &key);

    std::string getMessage(bool decode = false) const;

private:
    std::vector<mpz_class> messages;
    const std::string firstMessage;
};