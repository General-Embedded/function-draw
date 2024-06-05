#include <string>
#include <vector>

double evaluate(double a, double b, std::string op);
double evaluate(double a, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::string op);

int precedence(char op);
std::string getRPN(std::string input);
void computeNumber(std::string RPN, int sizeX, int sizeY);
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY);

template <typename T>
std::vector<std::vector<T>> initVec(T);