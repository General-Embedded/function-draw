#include "parser.h"
#include <iostream>
int main(){
    std::cout<<getRPN("90+2*4+sin(x)");
    return 0;
}