#include <iostream>
#include <string>
#include <limits>

int main()
{
    std::string name;
    int age;

    std::cout << "What is your name?" << std::endl;
    std::cin >> name;
    std::cout << "What is your age?" << std::endl;
    std::cin >> age;

    while (std::cin.fail())
    {
        std::cout << "ERROR: I expected a number!" << std::endl;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');

        std::cout << "What is your age?" << std::endl;
        std::cin >> age;
    }

    std::cout << "Hello, " << name << ". You are " << age << " years old." << std::endl;

    return 0;
}