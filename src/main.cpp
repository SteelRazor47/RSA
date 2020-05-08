#include <iostream>
#include "RSA.hpp"

int main()
{
    RSA Alice, Bob;
    auto msg = Message(mpz_class("570000000000000000000000000"));
    std::cout << msg.getMessage() << "\n\n";
    Message m = Alice.encrypt(Bob.getPublicKey(), msg);
    auto tmp = m.getMessage();
    std::cout<<tmp<< "\n\n";
    auto decrypted = Bob.decrypt(m).getMessage();
    std::cout << decrypted << "\n\n";
}