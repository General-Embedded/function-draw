#include "parser.h"
#include <iostream>
int main(){
    std::string rpn = getRPN("3 + sin( x ) * ( 2 - cos( y ) ) ^ 2");
    auto x = computePlane(rpn,1,1)[0][0];
    std::cout<<"Result: "<<x<<"\n";
    return 0;
}