#include "Message.hpp"
#include <numeric>
#include <string>

Message::Message(const std::string_view msg) : firstMessage(msg) {}

void Message::encrypt(const PublicKey &key)
{
    if(messages.empty())
    {
        auto keySize = (key.n.get_str().size() - 1)/3;
        if(keySize == 0)
            throw "Key length is too short";
        for(std::size_t i = 0; i<firstMessage.size() / keySize; i++){
            messages.push_back(mpz_class{encodeString(firstMessage.substr(i*keySize, keySize).data())});
        }
        auto remaining = firstMessage.size() % keySize;
        if( remaining > 0){
            messages.push_back(mpz_class{encodeString(firstMessage.substr(firstMessage.size() - remaining, remaining).data())});
        }
    }
    for (auto &&message : messages)
    {
        message = fastExp(message, key.e, key.n);
    }
}

void Message::decrypt(const PrivateKey &key)
{
    for (auto &&message : messages)
    {
        mpz_class m1 = fastExp(message, key.dp, key.p);
        mpz_class m2 = fastExp(message, key.dq, key.q);
        mpz_class h = (key.qinv * (m1 - m2)) % key.p;
        mpf_class ratio = mpf_class(key.q) / mpf_class(key.p);
        if (m1 < m2)
        {
            h = (key.qinv * (m1 - m2 + mpz_class(ceil(ratio)) * key.p)) % key.p;
        }
        message = (m2 + h * key.q) % key.n;
    }
}

std::string Message::getMessage(bool decode) const
{
    return std::accumulate(messages.begin(), messages.end(), std::string{}, [decode](const std::string& a, const mpz_class& b){
        return std::move(a) + (decode ? decodeString(b.get_str()) : b.get_str());
    });
}