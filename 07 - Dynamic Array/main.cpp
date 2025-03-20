#include <iostream>
#include <string>

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

int readNumber(const std::string& message = "Enter a number: ")
{
    int value;
    std::cout << message;
    std::cin >> value;

    while (std::cin.fail())
    {
        std::cout << "ERROR: Expected an integer." << std::endl;

        clearInput();

        std::cout << message;
        std::cin >> value;
    }

    return value;
}

int main()
{
    int size = readNumber("How many elements does the array have?: ");

    while (size < 1 || size > 100)
    {
        std::cout << "ERROR: The size must be between 1 and 100." << std::endl;
        size = readNumber();
    }

    int* array = new int[size];
    int minimum = INT_MAX;
    int maximum = INT_MIN;
    long long sum = 0;

    for (int i = 0; i < size; i++)
    {
        array[i] = readNumber("Enter a number [" + std::to_string(i) + "]: ");

        minimum = std::min(minimum, array[i]);
        maximum = std::max(maximum, array[i]);
        sum += array[i];
    }

    std::cout << "The minimum value is: " << minimum << std::endl;
    std::cout << "The maximum value is: " << maximum << std::endl;
    std::cout << "The average value is: " << (static_cast<double>(sum) / static_cast<double>(size)) << std::endl;

    delete[] array;

    pause();

    return 0;
}