#include "parser.h"
#include <iostream>
int main(){
    std::string rpn = getRPN("x+y");
    //printPlane(computePlane(rpn,100,100));
    size_t sizeX = 1000;
    size_t sizeY = 1000;
    std::vector<std::vector<double>> result(sizeY, std::vector<double>(sizeX, 0.0));

    for (size_t y=0; y<1000; y++)
        { 
            for (size_t x=0; x<1000; x++)
            {
                result[y][x] = computeNumber(rpn, static_cast<double>(x), static_cast<double>(y), 1000,1000);
                //std::cout<<result[y][x]<<std::endl;
            }
        }

    printPlane(result,"result.txt");

    return 0;
}