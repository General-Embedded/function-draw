#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <cassert>
#include <cctype>
#include <cmath>

template <typename T>
std::vector<std::vector<T>> initVec(T a, size_t sizeX, size_t sizeY){
    return std::vector<std::vector<T>>(sizeY, std::vector<T>(sizeX, a));
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


void computeNumber(std::string RPN, int sizeX, int sizeY){
    std::cout<<RPN<<"\n";
    std::vector<std::vector<double>> aVec;
    std::vector<std::vector<double>> bVec;
    std::vector<std::vector<double>> cVec;

    std::stack<double> sVar;
    std::stack<std::string> sOp;

    std::string token;
    char tokenBit;

    double a = 0;
    double b = 0;
    double x = 1;
    double y = 1;
    std::cout<<RPN.length()<<" bytes long expression.\n";
    for(size_t i=0; i <= RPN.length(); ++i){
        std::cout<<tokenBit<<"\n";
        tokenBit = RPN[i];
        if(tokenBit!='\0'&&i!=RPN.length()&&tokenBit!=' '){
            token+=tokenBit;
        }else{
            std::cout<<token<<"is the current token.\n";
            if (std::isdigit(token.at(0)))
            {
                std::cout<<token<<"pushed to sVar\n";
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
                    std::cout<<a<<b<<"evaluate op!\n";
                    std::cout<<sVar.top()<<" at top!\n";
                }
                else{
                    a = sVar.top();
                    sVar.pop();
                    sVar.push(evaluate(a,token));
                    std::cout<<"evaluate func!\n";
                }
            }
            token.clear();
            std::cout<<sVar.top()<<" at top!\n";
        }
    }
    std::cout<<"end\n";
    std::cout<<sVar.top()<<" at top!\n";
    std::cout<<sVar.top()<<"\n";
}


/// @brief 
/// @param RPN 
/// @param sizeX 
/// @param sizeY 
/// @return 
std::vector<std::vector<double>> computePlane(std::string RPN, int sizeX, int sizeY){
    std::cout<<RPN<<"\n";
    std::vector<std::vector<double>> aVec;
    std::vector<std::vector<double>> bVec;
    std::vector<std::vector<double>> cVec;
    std::vector<std::vector<double>> xConstVec;
    std::vector<std::vector<double>> yConstVec;
    //calculate the vector sizing
    size_t xVec,yVec;
    if(sizeX>sizeY){
        xVec = 1000;
        yVec = xVec*sizeY/sizeX;
    } else {
        yVec = 1000;
        xVec = yVec*sizeY/sizeX;
    }

    aVec.resize(yVec, std::vector<double>(xVec));
    bVec.resize(yVec, std::vector<double>(xVec));
    cVec.resize(yVec, std::vector<double>(xVec));
    xConstVec.resize(yVec, std::vector<double>(xVec));
    yConstVec.resize(yVec, std::vector<double>(xVec));

    //initialisation of x-y

    std::stack<std::vector<std::vector<double>>> sVar;
    std::stack<std::string> sOp;

    std::string token;
    char tokenBit;

    double a = 0;
    double b = 0;
    double x = 1;
    double y = 1;
    std::cout<<RPN.length()<<" bytes long expression.\n";
    for(size_t i=0; i <= RPN.length(); ++i){
        std::cout<<tokenBit<<"\n";
        tokenBit = RPN[i];
        if(tokenBit!='\0'&&i!=RPN.length()&&tokenBit!=' '){
            token+=tokenBit;
        }else{
            std::cout<<token<<"is the current token.\n";
            if (std::isdigit(token.at(0)))
            {
                std::cout<<token<<"pushed to sVar\n";
                sVar.push(initVec(std::stod(token),xVec,yVec)); 
            } else if(token == "x"){
                sVar.push(xConstVec);
            } else if(token == "y"){
                sVar.push(yConstVec);
            
            } else {
                if(token.length()==1){
                    aVec = sVar.top();
                    sVar.pop();
                    bVec = sVar.top();
                    sVar.pop();
                    sVar.push(evaluate(aVec,bVec,token));
                    //std::cout<<a<<b<<"evaluate op!\n";
                    //std::cout<<sVar.top()<<" at top!\n";
                }
                else{
                    aVec = sVar.top();
                    sVar.pop();
                    sVar.push(evaluate(aVec,token));
                    std::cout<<"evaluate func!\n";
                }
            }
            token.clear();
            //std::cout<<sVar.top()<<" at top!\n";
        }
    }
    std::cout<<"end\n";
    //std::cout<<sVar.top()<<" at top!\n";
    //std::cout<<sVar.top()<<"\n";
    return cVec;
}

