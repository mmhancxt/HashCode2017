#include <iostream>
#include "InputLoader.h"
#include "Tools.h"
#include "InputLoader.h"

#include "Utilities.h"
using namespace std;





int main(int argc, const char * argv[])
{
    std::cout << "Hello, HashCode!\n";
	//InputLoader loader;
    InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\example.in");
	iterateEndPointMethod(loader);
    //std::cout << "Hello, HashCode!\n";

    //for (int i = 0; i < 10; ++i)
    //{
    //    cout << Tools::GetUniformRandomNumber(0, 5) << endl;
    //}

    //InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\example.in");


	cin.get();
    return 0;
}
