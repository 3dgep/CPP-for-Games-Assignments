#include <iostream>
#include <stdexcept>
#include <queue>
#include <stack>
#include <string>

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pause()
{
    std::cout << "Press enter to continue..." << std::endl;
    clearInput();
    std::cin.get();
}

int precedence(const std::string& op)
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "^") return 3;

    return 0;
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
        if (rhs == 0.0f)
        {
            throw std::runtime_error("Division by zero!");
        }
        return lhs / rhs;
    case '%':
        if (rhs == 0.0f)
        {
            throw std::runtime_error("Modulo by zero!");
        }
        return std::fmod(lhs, rhs);
    case '^':
        return std::pow(lhs, rhs);
    default:
        throw std::runtime_error("Invalid operator!");
    }
}

bool isNumber(const std::string& token)
{
    return std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]));
}

bool isOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
}

double parse()
{
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;
    std::string token;

    do
    {
        std::cin >> token;

        if (isNumber(token))
        {
            // If it's a number, add it to the output queue.
            outputQueue.push(token);
        }
        else if (token == "(")
        {
            operatorStack.push(token);
        }
        else if (token == ")")
        {
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            if (operatorStack.empty())
            {
                throw std::runtime_error("Mismatched parentheses!");
            }
            operatorStack.pop(); // Pop the "(".
        }
        else if (isOperator(token))
        {
            // If it's an operator...
            while (!operatorStack.empty() && precedence(token) <= precedence(operatorStack.top()))
            {
                // Pop the operators off the operator stack as long as they have a higher (or equal) precedence.
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            // Add it to the operator stack.
            operatorStack.push(token);
        }
        else
        {
            throw std::runtime_error("Invalid token: " + token);
        }
    } while (std::cin.peek() != '\n');

    // Push any remaining operators to the output queue.
    while (!operatorStack.empty())
    {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    // Evaluate the expression in reverse polish notation (RPN).
    std::stack<double> evaluationStack;
    while (!outputQueue.empty())
    {
        token = outputQueue.front();
        outputQueue.pop();

        if (isNumber(token))
        {
            // Push numbers to the evaluation stack.
            evaluationStack.push(std::stod(token));
        }
        else // It's an operator.
        {
            // Evaluate the (sub) expression.
            if (evaluationStack.size() < 2)
            {
                throw std::runtime_error("Invalid RPN expression (not enough operands)!");
            }
            double rhs = evaluationStack.top();
            evaluationStack.pop();
            double lhs = evaluationStack.top();
            evaluationStack.pop();
            double res = evaluate(lhs, token[0], rhs);
            evaluationStack.push(res);
        }
    }

    if (evaluationStack.size() > 1)
    {
        throw std::runtime_error("Invalid RPN expression (too many operands)!");
    }

    return evaluationStack.top();
}

int main()
{
    char choice = 'y';
    while (choice == 'y')
    {
        std::cout << "Enter an expression: ";
        try
        {
            double result = parse();
            std::cout << "Result: " << result << std::endl;
        }
        catch (const std::runtime_error& error)
        {
            std::cerr << "Error: " << error.what() << std::endl;
        }

        clearInput();
        std::cout << "Would you like to enter another expression? (y/n): ";
        std::cin >> choice;
    }

    pause();

    return 0;
}