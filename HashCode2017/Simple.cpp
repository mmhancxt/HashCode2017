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
    std::ofstream ofs ("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/outputs.txt", std::ofstream::out);
    vector<vector<int>>& pizza = loader.pizza;
    vector<vector<bool>>& isTaken = loader.isTaken;
    
    using Point = pair<int,int>;
    
    Point start = make_pair(0,0);
    Point end = make_pair(0,1);
    while (start.first != -1)
    {
        if (end.first > loader.const_row)
            break;
        if (isValidPizza(pizza, start.first, start.second, end.first, end.second, loader.const_min_ingredient, loader.const_max_cells_in_slice))
        {
            CutAndDump(ofs, isTaken, start.first, start.second, end.first, end.second);
            if (end.second >= loader.const_column-2)
            {
                int row = start.first+1;
                start = make_pair(row, 0);
                end = make_pair(row, 1);
            }
            else
            {
                start.second = end.second+1;
                end.second = start.second+1;
            }
            cout << "Next start is : " << start.first << "," << start.second << endl;
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
    
    ofs.close();
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