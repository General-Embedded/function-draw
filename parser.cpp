#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <cassert>
#include <cctype>
#include <cmath>

double evaluate(double a, double b, std::string op){
    if(op=="+")
        return a+b;
    else if(op=="-")
        return a-b;
    else if(op=="*")
        return a*b;
    else if(op=="/")
        return a/b;
    else if(op=="sin")
        return sin(b);
    else if(op=="cos")
        return cos(b);
    else if(op=="^")
        return pow(a,b);//do sprawdzenia
    else
        std::cerr<<"\nwrong operator: "<<op<<"\n";
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string getRPN(std::string inputString) {
    std::stack<std::string> ostack;
    std::queue<std::string> output;

    char bitToken;
    std::string wholeToken;
    std::cout << "in!\n";
    for (size_t i = 0; i < inputString.length(); ++i) {
        bitToken = inputString.at(i);
        std::cout << bitToken << "_\n";

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
        } else if (bitToken == '*' || bitToken == '/' || bitToken == '+' || bitToken == '-') {
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

//
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY){

    std::vector<std::vector<double>> aVec;
    std::vector<std::vector<double>> bVec;
    std::vector<std::vector<double>> cVec;

    std::stack<double> sVar;
    std::stack<std::string> sOp;

    std::string token,tokenBit;

    double a = 0;
    double b = 0;
    double c = 0;
    double x = 1;
    double y = 1;
    for(size_t i; i<RPN.length(); ++i){
        tokenBit = RPN.at(i);
        if(tokenBit!=" "){
            token+=tokenBit;
        }else{
            if (std::isdigit(token.at(0)))
            {
               sVar.push(std::stod(token)); 
            } else if(token == "x"){
                sVar.push(x);
            } else if(token == "y"){
                sVar.push(y);
            } else {
                if(token.length()==1)
                    sVar.push(evaluate(a,b,token));
                else
                    sVar.push(evaluate(b,token));
            }
        }
    }
    std::cout<<sVar.top()<<"\n";
    return cVec;
}