#include <iostream>
#include "InputLoader.h"
#include "Tools.h"
#include "InputLoader.h"

#include "Utilities.h"
#include "Algo2.h"
using namespace std;





int main(int argc, const char * argv[])
{
    //InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
    //InputLoader loader;
    InputLoader loader(argv[1]);
    Algo algo(loader);
    algo.Run();
    //std::cout << "Hello, HashCode!\n";
	//InputLoader loader("D:\\Codes\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\trending_today.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\kittens.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\videos_worth_spreading.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\example.in");

	//iterateEndPointMethod(loader);
    //std::cout << "Hello, HashCode!\n";

    //for (int i = 0; i < 10; ++i)
    //{
    //    cout << Tools::GetUniformRandomNumber(0, 5) << endl;
    //}

	//cin.get();

    return 0;
}
