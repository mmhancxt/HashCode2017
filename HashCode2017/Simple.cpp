//
//  Simple.cpp
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include "Simple.hpp"
#include "Common.h"

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
    
    using Point = pair<int,int>;
    
    Point start = make_pair(0,0);
    Point end = start;
    while (start.first != -1)
    {
        end.second = end.second + 1;
        if (isValidPizza(pizza, start.first, start.second, end.first, end.second, 1, 5))
        {
            CutAndDump(isTaken, start.first, start.second, end.first, end.second);
        }
        start = GetStartPoint();
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