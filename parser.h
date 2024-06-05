#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

double evaluate(double a, double b, std::string op);
double evaluate(double a, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::string op);
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::string op);

int precedence(char op);
std::string getRPN(std::string input);
double computeNumber(std::string RPN, double x, double y);
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY);

template <typename T>
std::vector<std::vector<T>> initVec(T a, size_t sizeX, size_t sizeY){
    return std::vector<std::vector<T>>(sizeY, std::vector<T>(sizeX, a));
}


void printPlane(std::vector<std::vector<double>>& a, std::string fname="plane.txt");

template <typename T>
void printVector(std::vector<T> v, std::string fname){
    std::ofstream planeFile;
    planeFile.open(fname);
    if(!planeFile.is_open())
        std::cerr<<"file cant be opened\n";
    for (auto &i : v)
    {
        planeFile<<i<<"\n";
        //std::cout<<i;
    }
    planeFile.close();
}

/// @brief 
/// @param expression Expression consisting of integers, arguments x, y, operators +, -, *, /, ^, brackets and functions: sin(...), cos(...).
/// @param xMin //
/// @param xMax 
/// @param yMin 
/// @param yMax 
/// @return 2d double vector representing a plane's z coordinates, being results of expression, with x and y being coordinates starting at xMin, yMin, ending at xMax, yMax.
std::tuple<std::vector<std::vector<double>>, std::vector<double>, std::vector<double>> evaluatePlaneExpression(std::string expression, double xMin, double xMax, double yMin, double yMax);