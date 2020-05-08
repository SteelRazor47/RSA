#include "Message.hpp"

Message::Message(const mpz_class& num) : message(num) {}

void Message::encrypt(const PublicKey& key)
{
    message = fastExp(message, key.e, key.n);
}

void Message::decrypt(const PrivateKey& key)
{
    mpz_class m1 = fastExp(message, key.dp, key.p);
    mpz_class m2 = fastExp(message, key.dq, key.q);
    mpz_class h = key.qinv * (m1 - m2);
    mpf_class ratio = mpf_class(key.q) / mpf_class(key.p);
    if (m1 < m2)
    {
        h = (key.qinv * (m1 - m2 + mpz_class(ceil(ratio)) * key.p)) % key.p;
    }
    message = m2 + h * key.q;
}

std::string Message::getMessage() const
{
    return message.get_str();
    //const char* temp1 = message.get_str().c_str();
    //auto temp2 = std::string_view(temp1);
    //return temp2;
}



