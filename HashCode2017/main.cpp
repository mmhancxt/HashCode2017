//
//  main.cpp
//  HashCode2017
//
//  Created by Liang LIU on 07/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include <iostream>
#include "Simple.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    //InputLoader loader("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/example.in");
    //
    //std::cout << "Hello, HashCode!\n";
	//InputLoader loader;
	//loader.const_column;
	//InputLoader loader("small.in");
	//InputLoader loader("C:\\HashCode2017\\HashCode2017.vsproj\\HashCode2017\\Debug\\small.in");

    InputLoader loader("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/big.in");
    Simple simple(loader);
    simple.Run();
    
    return 0;
}
