#include <iostream>
#include <vector>

double n1;
double n2;

int main()
{
    std::cout << "Please enter your first number" << std::endl;
    std::cin >> n1;

    std::cout << "Please enter your second number" << std::endl;
    std::cin >> n2;

    n1 = 10;
    n2 = 4;

    std::cout << "add " << n1 + n2 << std::endl;
    std::cout << "subt " << n1 - n2 << std::endl;
    std::cout << "mult " << n1 * n2 << std::endl;
    std::cout << "divi " << n1 / n2 << std::endl;
    std::cout << "avg " << (n1 + n2) / 2 << std::endl;

    int nOne = 7;
    int nTwo = 2;

    std::cout << "int div " << nOne / nTwo << std::endl;

    double nuOne = 7;
    double nuTwo = 2;

    std::cout << "double div " << nuOne / nuTwo << std::endl;

    std::cout << std::endl;
    std::vector<std::vector<double>> nums = {
        {10, 5},
        {7, 2},
        {15.5, 4}};

    for (const auto &item : nums)
    {
        std::cout << "add " << item[0] + item[1] << std::endl;
        std::cout << "subt " << item[0] - item[1] << std::endl;
        std::cout << "mult " << item[0] * item[1] << std::endl;
        std::cout << "divi " << item[0] / item[1] << std::endl;
        std::cout << "avg " << (item[0] + item[1]) / 2 << std::endl;
    }

    return 0;
}
