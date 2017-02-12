//
//  Simple.cpp
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include "Simple.hpp"
#include "Common.h"
using namespace std;

void Simple::Run()
{
    cout << "Start" << endl;
    vector<vector<int>>& pizza = loader.pizza;
    vector<vector<bool>>& isTaken = loader.isTaken;
    
    using Point = pair<int,int>;
    
    Point start = make_pair(0,0);
    Point end = make_pair(0,1);
    while (start.first != -1)
    {
        cout << "start : " << start.first << "," << start.second << endl;
        cout << "end : " << end.first << "," << end.second << endl;
        if (isValidPizza(pizza, start.first, start.second, end.first, end.second, loader.const_min_ingredient, loader.const_max_cells_in_slice))
        {
            CutAndDump(isTaken, start.first, start.second, end.first, end.second);
            start = GetStartPoint();
        }
        else
        {
            if (end.second == loader.const_column-1)
            {
                int row = start.first+1;
                start = make_pair(row, 0);
                end = make_pair(row, 1);
            }
            else
            {
                end.second = end.second + 1;
            }
        }
    }
    
    cout << "End" << endl;
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
    
    return make_pair(-1,0);
}