#include <string>
#include <vector>

double evaluate(double a, double b, std::string op);
double evaluate(double a, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::string op);

int precedence(char op);
std::string getRPN(std::string input);
double computeNumber(std::string RPN, double x, double y,  int sizeX, int sizeY);
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY);

template <typename T>
std::vector<std::vector<T>> initVec(T);

void printPlane(std::vector<std::vector<double>> a);
void printPlane(std::vector<std::vector<double>> a, std::string fname);