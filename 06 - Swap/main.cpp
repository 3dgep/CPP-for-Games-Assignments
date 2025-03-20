#include <iostream>

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pause()
{
    std::cout << "Press enter to continue...";
    clearInput();
    std::cin.get();
}

void swap(char& a, char& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap(bool& a, bool& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap(int& a, int& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap(unsigned int& a, unsigned int& b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void swap(float& a, float& b)
{
    *reinterpret_cast<unsigned int*>(&a) = *reinterpret_cast<unsigned int*>(&a) ^ *reinterpret_cast<unsigned int*>(&b);
    *reinterpret_cast<unsigned int*>(&b) = *reinterpret_cast<unsigned int*>(&a) ^ *reinterpret_cast<unsigned int*>(&b);
    *reinterpret_cast<unsigned int*>(&a) = *reinterpret_cast<unsigned int*>(&a) ^ *reinterpret_cast<unsigned int*>(&b);
}

void swap(double& a, double& b)
{
    *reinterpret_cast<unsigned long long*>(&a) = *reinterpret_cast<unsigned long long*>(&a) ^ *reinterpret_cast<unsigned long long*>(&b);
    *reinterpret_cast<unsigned long long*>(&b) = *reinterpret_cast<unsigned long long*>(&a) ^ *reinterpret_cast<unsigned long long*>(&b);
    *reinterpret_cast<unsigned long long*>(&a) = *reinterpret_cast<unsigned long long*>(&a) ^ *reinterpret_cast<unsigned long long*>(&b);
}

template<typename T>
void test(T a, T b)
{
    std::cout << "Before swap: " << a << ", " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: " << a << ", " << b << std::endl;
    std::cout << std::endl;
}

int main()
{
    test('A', 'B');
    test(true, false);
    test(false, true);
    test(-3, 4);
    test(3u, 4u);
    test(3.14f, 4.15f);
    test(-3.14f, 4.15f);
    test(3.14, 4.15);
    test(-3.14, 4.15);

    pause();

    return 0;
}