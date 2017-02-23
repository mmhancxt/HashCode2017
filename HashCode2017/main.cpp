#include <iostream>
#include "InputLoader.h"
#include "Tools.h"
#include "InputLoader.h"

#include "Utilities.h"
#include "Algo1.h"
using namespace std;





int main(int argc, const char * argv[])
{
<<<<<<< HEAD
    //std::cout << "Hello, HashCode!\n";
	InputLoader loader("D:\\Codes\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
	//InputLoader loader("D:\\Codes\\HashCode2017\\HashCode2017\\input\\example.in");

	iterateEndPointMethod(loader);
    //std::cout << "Hello, HashCode!\n";

    //for (int i = 0; i < 10; ++i)
    //{
    //    cout << Tools::GetUniformRandomNumber(0, 5) << endl;
    //}

	cin.get();

=======
    //InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
    //InputLoader loader;
    InputLoader loader(argv[1]);
    Algo algo(loader);
    algo.Run();
>>>>>>> 5c9ca5ab3233a9ae9b469a414c7a15bf9fcfec40
    return 0;
}
