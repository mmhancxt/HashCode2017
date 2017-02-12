//
//  Simple.hpp
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#ifndef Simple_hpp
#define Simple_hpp

#include <stdio.h>
#include "InputLoader.h"
#include <pair>

class Simple
{
public:
    Simple(InputLoader& input) : loader(input)
    {}
    
    pair<int,int> GetStartPoint();
    void Run();
    
    InputLoader& loader;
};


#endif /* Simple_hpp */
