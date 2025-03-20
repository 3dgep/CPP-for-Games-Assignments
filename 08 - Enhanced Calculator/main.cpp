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

double readNumber()
{
    double value;
    std::cout << "Enter a number: ";

    std::cin >> value;

    while (std::cin.fail())
    {
        std::cout << "ERROR: Expected a number." << std::endl;

        clearInput();

        std::cout << "Enter a number: ";
        std::cin >> value;
    }

    return value;
}

char readOperator()
{
    char op;
    std::cout << "Enter an operator (+, -, *, /, %, ^): ";
    std::cin >> op;

    while (op != '+' && op != '-' && op != '*' && op != '/' && op != '%' && op != '^')
    {
        std::cout << "ERROR: Expected an operator (+, -, *, /, %, ^)!" << std::endl;

        clearInput();

        std::cout << "Enter an operator (+, -, *, /, %, ^): ";
        std::cin >> op;
    }

    return op;
}

double evaluate(double lhs, char op, double rhs)
{
    switch (op)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    case '%':
        return std::fmod(lhs, rhs);
    case '^':
        return std::pow(lhs, rhs);
    }

    return 0;
}

int main()
{
    double lhs = readNumber();
    char op = readOperator();
    double rhs = readNumber();

    while (op == '/' || op == '%' && rhs == 0.0)
    {
        std::cout << "ERROR: Cannot divide by 0!" << std::endl;
        rhs = readNumber();
    }

    double result = evaluate(lhs, op, rhs);

    std::cout << lhs << " " << op << " " << rhs << " = " << result << std::endl;

    pause();
}