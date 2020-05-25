#include <iostream>
#include "RSA.hpp"

struct Pair
{
    RSA n1;
    RSA n2;
};

Pair init();

int main()
{
    auto [Alice, Bob] = init();

    std::cout << "Enter Alice's message ";
    std::string msg;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, msg);

    auto isSanitized = [](const std::string &s) { return std::all_of(s.begin(), s.end(), [](auto &&ch) { return isascii(ch); }); };

    while (!isSanitized(msg))
    {
        std::cout << "Only ASCII characters in range 0-127 are supported. Try again: ";
        std::cin >> msg;
    }

    try
    {
        Message encrypted = Alice.encrypt(Bob.getPublicKey(), Message(msg));
        std::cout << "\nEncrypted message: " << encrypted.getMessage() << "\n\n";

        auto decrypted = Bob.decrypt(encrypted);
        std::cout << "Decrypted message: " << decrypted.getMessage(true) << "\n\n";
    }
    catch (const char *msg)
    {
        std::cout << "ERROR: " << msg << '\n';
    }
}

Pair init()
{
    std::cout << "Input p and q?(Y/N): ";
    char ans;
    std::cin >> ans;
    mpz_class p, q;

    switch (std::tolower(ans))
    {
    case 'y':
        std::cout << "P: ";
        std::cin >> p;
        std::cout << "Q: ";
        std::cin >> q;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!mpz_probab_prime_p(p.get_mpz_t(), 200) || !mpz_probab_prime_p(q.get_mpz_t(), 200))
        {
            std::cout << "p and/or q are not prime. Try again.\n";
            std::cout << "P: ";
            std::cin >> p;
            std::cout << "Q: ";
            std::cin >> q;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Generating Alice and Bob's keys based on the input.\n";
        return {RSA(p, q), RSA(p, q)};
    case 'n':
        std::cout << "Generating Alice and Bob's keys with random numbers and 2048bit key length.\n";
        return {RSA(2048), RSA(2048)};
    default:
        std::cout << "Please enter Y or N\n";
        return init();
    }
}