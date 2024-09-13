#include <iostream>
// #include "include/calc.hpp"
#include "build/defaultconfig.h"
#include "lib/wifi.hpp"
int main()
{
    std::cout<<"software version is : "<<HELLOAPP_VERSION_MAJOR<<"."<<HELLOAPP_VERSION_MINOR<<"\n";
    std::cout<<"PRODUCT_TYPE"<<" : "<<PRODUCT_TYPE<<"\n";
    std::cout<<"PRODUCT_YEAR"<<" : "<<PRODUCT_YEAR<<"\n";
    return 0;
}