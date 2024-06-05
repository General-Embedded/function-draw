#include "parser.h"
#include "computePlane.h"
#include <iostream>
int main(){
    /*
    std::string rpn = getRPN("y*sin(x)");
    //printPlane(computePlane(rpn,100,100));
    size_t sizeX = 1000;
    size_t sizeY = 1000;
    double xMin = -10;
    double xMax = 10;
    double yMin = -10;
    double yMax = 10;
    double dx = (xMax-xMin)/sizeX;
    double dy = (yMax-yMin)/sizeY;
    
    std::vector<std::vector<double>> result(sizeY, std::vector<double>(sizeX, 0.0));

    {
    double x = xMin;
    double y = yMin;
    for (size_t iy=0; iy<sizeY; iy++)
        { 
            for (size_t ix=0; ix<sizeX; ix++)
            {
                result[iy][ix] = computeNumber(rpn, (x), (y));
                //std::cout<<result[iy][ix]<<"\t"<< x<< '\t' << y<<std::endl;
                x+=dx;
            }
            x=xMin;
            y+=dy;
        }
    }
    */
    auto [result, planeXvec, planeYvec] = evaluatePlaneExpression("sin(x)",0,100,0,10);

    printPlane(result,"result.txt");
    printVector(planeXvec, "xV.txt");
    printVector(planeYvec, "yV.txt");

    return 0;
}