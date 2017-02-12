//
//  Simple.cpp
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include "Simple.hpp"

void Simple::Run()
{
    vector<vector<int>>& pizza = loader.pizza;
    vector<vector<bool>>& isTaken = loader.isTaken;
    for (vector<bool>& v : isTaken)
    {
        for (int i = 0; i < v.size(); i++)
        {
            v[i] = false;
        }
    }
    
}

pair<int, int> Simple::GetStartPoint() {
    int m = loader.const_row, n = loader.const_column;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!loader.isTaken[i][j]) return make_pair(i, j);
        }
    }
    
    return make_pair(0,0);
}