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
#include "computePlane.h"
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
    {
    size_t x=0;
    for (size_t y=0; y<yVec; y++)
        {
            
            for (; x<xVec; x++)
            {
                xConstVec[y][x]=x;
                yConstVec[y][x] = y;
            }
            x=0;
        }
    }
    

    printPlane(xConstVec,"x.txt");
    printPlane(yConstVec,"y.txt");
    std::stack<std::vector<std::vector<double>>> sVar;
    std::stack<std::string> sOp;

    std::string token;
    char tokenBit = '\0';


    std::cout<<RPN.length()<<" bytes long expression.\n";
    for(size_t i=0; i <= RPN.length(); ++i){
        std::cout<<tokenBit<<"\n";
        tokenBit = RPN[i];
        if(tokenBit!='\0'&&i!=RPN.length()&&tokenBit!=' '){
            token+=tokenBit;
        }else{
            //std::cout<<token<<"is the current token.\n";
            if (std::isdigit(token.at(0)))
            {
                //std::cout<<token<<"pushed to sVar\n";
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
                    //std::cout<<"evaluate func!\n";
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
