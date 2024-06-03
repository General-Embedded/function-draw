#include <string>
#include <vector>

double evaluate(double a, double b, std::string op);
int precedence(char op);
std::string getRPN(std::string input);
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY);
