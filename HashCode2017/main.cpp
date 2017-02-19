#include <iostream>

#include "Tools.h"

using namespace std;

int main(int argc, const char * argv[])
{
    std::cout << "Hello, HashCode!\n";

    for (int i = 0; i < 10; ++i)
    {
        cout << Tools::GetUniformRandomNumber(0, 5) << endl;
    }
    return 0;
}
