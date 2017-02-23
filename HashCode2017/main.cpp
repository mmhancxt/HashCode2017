#include <iostream>
#include "InputLoader.h"
#include "Tools.h"
#include "InputLoader.h"

#include "Utilities.h"
#include "Algo1.h"
using namespace std;





int main(int argc, const char * argv[])
{
    //InputLoader loader("C:\\HashCode2017\\HashCode2017\\input\\me_at_the_zoo.in");
    //InputLoader loader;
    InputLoader loader(argv[1]);
    Algo algo(loader);
    algo.Run();
    return 0;
}
