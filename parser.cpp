#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <cassert>
#include <cctype>
#include <cmath>
#include <fstream>
#include "parser.h"
void printPlane(const std::vector<std::vector<double>>& a) {
    std::ofstream planeFile("plane.txt");
    if (!planeFile.is_open()) {
        std::cerr << "Error opening file!\n";
        return;
    }

    for (const auto& row : a) {
        for (const auto& val : row) {
            planeFile << val << " ";
        }
        planeFile << "\n";
    }
    planeFile.close();
}

void printPlane(std::vector<std::vector<double>>& a, std::string fname){
    std::ofstream planeFile;
    planeFile.open(fname);
    if(!planeFile.is_open())
        std::cerr<<"file cant be opened\n";
    for (size_t y=0; y<a.size(); y++)
        {
            planeFile<<"\n";
            for (size_t x=0; x<a[0].size(); x++)
            {
                planeFile<<a[y][x]<<" ";
            }
        }
    planeFile.close();
}


/// @brief 
/// @param a 
/// @param b 
/// @param op 
/// @return 
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::string op){
    std::vector<std::vector<double>> c = a;
    if(op=="+"){
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                c[y][x]=a[y][x]+b[y][x];
            }
        }
    }
    else if(op=="-"){
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                c[y][x]=a[y][x]-b[y][x];
            }
        }
    }
    else if(op=="*"){
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                c[y][x]=a[y][x]*b[y][x];
            }
        }
    }
    else if(op=="/"){
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                c[y][x]=a[y][x]/b[y][x];
            }
        }
    }
        /*
    else if(op=="sin")
        return sin(a);
    else if(op=="cos")
        return cos(a);
        */
    else if(op=="^"){
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                c[y][x]=pow(b[y][x], a[y][x]);
            }
        }
    }
    else{
        std::cerr<<"\nwrong operator: "<<op<<"\n";
    }
    return c;
}
/// @brief 
/// @param a 
/// @param op 
/// @return 
std::vector<std::vector<double>> evaluate(std::vector<std::vector<double>> a, std::string op){
    std::vector<std::vector<double>> b = a;
    if(op=="sin")
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                b[y][x]=sin(a[y][x]);
            }
        }
        
    else if(op=="cos")
        for (size_t y=0; y<a.size(); y++)
        {
            for (size_t x=0; x<a[0].size(); x++)
            {
                b[y][x]=cos(a[y][x]);
            }
        }
    else{
        std::cerr<<"\nwrong operator: "<<op<<"\n";
    }
    return b;
}

/// @brief 
/// @param a 
/// @param b 
/// @param op 
/// @return 
double evaluate(double a, double b, std::string op){
    if(op=="+")
        return a+b;
    else if(op=="-")
        return a-b;
    else if(op=="*")
        return a*b;
    else if(op=="/")
        return a/b;
        /*
    else if(op=="sin")
        return sin(a);
    else if(op=="cos")
        return cos(a);
        */
    else if(op=="^")
        return pow(b,a);//do sprawdzenia
    else{
        std::cerr<<"\nwrong operator: "<<op<<"\n";
        return 0;
    }
}

double evaluate(double a, std::string op){
    if(op=="sin")
        return sin(a);
    else if(op=="cos")
        return cos(a);
    else{
        std::cerr<<"\nwrong operator: "<<op<<"\n";
        return 0;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string getRPN(std::string inputString) {
    std::stack<std::string> ostack;
    std::queue<std::string> output;

    char bitToken;
    std::string wholeToken;
    //std::cout << "in!\n";
    for (size_t i = 0; i < inputString.length(); ++i) {
        bitToken = inputString.at(i);
        //std::cout << bitToken << "_\n";

        if (std::isspace(bitToken)) {
            continue;  // Skip whitespace
        }

        if (std::isdigit(bitToken)) {
            wholeToken.clear();
            while (i < inputString.length() && std::isdigit(inputString[i])) {
                wholeToken += inputString[i];
                ++i;
            }
            --i;
            output.push(wholeToken);
        } else if (bitToken == 'x' || bitToken == 'y') {
            wholeToken = bitToken;
            output.push(wholeToken);
        } else if (std::isalpha(bitToken)) {
            wholeToken.clear();
            while (i < inputString.length() && std::isalpha(inputString[i])) {
                wholeToken += inputString[i];
                ++i;
            }
            --i;
            ostack.push(wholeToken);
        } else if (bitToken == '*' || bitToken == '/' || bitToken == '+' || bitToken == '-' || bitToken == '^') {
            while (!ostack.empty() && ostack.top() != "(" && 
                   ((precedence(ostack.top().at(0)) > precedence(bitToken)) || 
                    (precedence(ostack.top().at(0)) == precedence(bitToken)))) {
                output.push(ostack.top());
                ostack.pop();
            }
            ostack.push(std::string(1, bitToken));
        } else if (bitToken == '(') {
            ostack.push("(");
        } else if (bitToken == ')') {
            while (!ostack.empty() && ostack.top() != "(") {
                output.push(ostack.top());
                ostack.pop();
            }
            if (!ostack.empty() && ostack.top() == "(") {
                ostack.pop();
            }
            // Handle potential function after ')'
            if (!ostack.empty() && std::isalpha(ostack.top().at(0))) {
                output.push(ostack.top());
                ostack.pop();
            }
        } else {
            std::cerr << "Invalid character encountered: " << bitToken << std::endl;
        }
    }

    while (!ostack.empty()) {
        assert(ostack.top() != "(");
        output.push(ostack.top());
        ostack.pop();
    }

    // Output handling
    std::string stringOutput = "";
    while (!output.empty()) {
        stringOutput += output.front() + " ";
        output.pop();
    }

    // Remove the trailing space if present
    if (!stringOutput.empty() && stringOutput.back() == ' ') {
        stringOutput.pop_back();
    }

    return stringOutput;
}


/// @brief 
/// @param RPN 
/// @param sizeX 
/// @param sizeY 
/// @return 


double computeNumber(std::string RPN, double x, double y){
    //std::cout<<RPN<<"\n";

    std::stack<double> sVar;
    std::stack<std::string> sOp;

    std::string token;
    char tokenBit;

    double a = 0;
    double b = 0;
    //std::cout<<RPN.length()<<" bytes long expression.\n";
    for(size_t i=0; i <= RPN.length(); ++i){
        //std::cout<<tokenBit<<"\n";
        tokenBit = RPN[i];
        if(tokenBit!='\0'&&i!=RPN.length()&&tokenBit!=' '){
            token+=tokenBit;
        }else{
            //std::cout<<token<<"is the current token.\n";
            if (std::isdigit(token.at(0)))
            {
                //std::cout<<token<<"pushed to sVar\n";
                sVar.push(std::stod(token)); 
            } else if(token == "x"){
                sVar.push(x);
            } else if(token == "y"){
                sVar.push(y);
            
            } else {
                if(token.length()==1){
                    a = sVar.top();
                    sVar.pop();
                    b = sVar.top();
                    sVar.pop();
                    sVar.push(evaluate(a,b,token));
                    //std::cout<<a<<b<<"evaluate op!\n";
                    //std::cout<<sVar.top()<<" at top!\n";
                }
                else{
                    a = sVar.top();
                    sVar.pop();
                    sVar.push(evaluate(a,token));
                    //std::cout<<"evaluate func!\n";
                }
            }
            token.clear();
            //std::cout<<sVar.top()<<" at top!\n";
        }
    }
    //std::cout<<"end\n";
    //std::cout<<sVar.top()<<" at top!\n";
    //std::cout<<sVar.top()<<"\n";

    return sVar.top();
}


std::tuple<std::vector<std::vector<double>>, std::vector<double>, std::vector<double>> evaluatePlaneExpression(std::string expression, double xMin, double xMax, double yMin, double yMax){
    std::string rpn = getRPN("y*sin(x)");
    //printPlane(computePlane(rpn,100,100));
    size_t sizeX = 1000;
    size_t sizeY = 1000;
    double dx = (xMax-xMin)/sizeX;
    double dy = (yMax-yMin)/sizeY;
    if(dx>dy){
        sizeX=1000;
        sizeY=sizeX*dy/dx;
    } else {
        sizeY=1000;
        sizeX=sizeY*dx/dy;
    }
    
    std::vector<std::vector<double>> result(sizeY, std::vector<double>(sizeX, 0.0));
    std::vector<double> planeX, planeY;
    std::cout<<"plane size: "<<sizeX<<" x "<<sizeY<<"\n";

    for (size_t ix = 0; ix < sizeX; ++ix) {
        planeX.push_back(xMin + ix * dx);
        std::cout<<planeX[ix]<<std::endl;
    }

    {
        double x = xMin;
        double y = yMin;
        for (size_t iy=0; iy<sizeY; iy++)
        { 
            for (size_t ix=0; ix<sizeX; ix++)
            {
                result[iy][ix] = computeNumber(rpn, (x), (y));
                //planeX.push_back(x);
                
                //std::cout<<result[iy][ix]<<"\t"<< x<< '\t' << y<<std::endl;
                x+=dx;
            }
            planeY.push_back(y);
            x=xMin;
            y+=dy;
        }
    }
    return std::make_tuple(result, planeX, planeY);
}
