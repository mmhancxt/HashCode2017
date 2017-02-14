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
#include "Common.h"


class Simple
{
public:
    Simple(InputLoader& input) : loader(input), ofs("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/outputs.txt", std::ofstream::out)
    {}
    
    using Point=pair<int,int>;
    pair<int,int> GetStartPoint(Point& start)
    {
        int m = loader.const_row, n = loader.const_column;
        for (int j = start.second+1; j<n; j++)
        {
            if (!loader.isTaken[start.first][j])
            {
                return make_pair(start.first,j);
            }
        }
        
        for (int i = start.first+1; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (!loader.isTaken[i][j]) return make_pair(i, j);
            }
        }
        
        return make_pair(-1,0);
    }
    
    void MoveRight(vector<vector<int>>& pizza, Point& start, Point& end)
    {
        cout << "Right : " << end.first << "," << end.second << endl;
        end.second = end.second+1;
        for (int i = start.first; i<= end.first; i++)
        {
            if (pizza[i][end.second] == 1)
            {
                tomato++;
            }
            else
            {
                mush++;
            }
        }
        cout << "T : " << tomato << endl;
        cout << "M : " << mush << endl;
    }
    
    void MoveDown(vector<vector<int>>& pizza, Point& start, Point& end)
    {
        cout << "Down : " << end.first << "," << end.second << endl;
        end.first = end.first+1;
        for (int j = start.second; j <= end.second; j++)
        {
            if (pizza[end.first][j] == 1)
            {
                tomato++;
            }
            else
            {
                mush++;
            }
        }
        cout << "T : " << tomato << endl;
        cout << "M : " << mush << endl;
    }
    
    bool MoveRightOrDown(vector<vector<int>>& pizza, Point& start, Point& end, Point& lastEnd)
    {
        if (end.first == loader.const_row-1 || loader.isTaken[end.first+1][end.second])
        {
            if (end.second == loader.const_column-1 || loader.isTaken[end.first][end.second+1])
            {
                if (isLValid && isHValid)
                    CutAndDump(loader.isTaken, start.first, start.second, lastEnd.first, lastEnd.second);
                return false;
            }
            else
            {
                MoveRight(loader.pizza, start, end);
            }
        }
        else
        {
            if (end.second == loader.const_column-1 || loader.isTaken[end.first][end.second+1])
            {
                MoveDown(loader.pizza, start, end);
            }
            else
            {
                int r = rand() % 100;
                if (r > 60)
                {
                    MoveRight(loader.pizza, start, end);
                }
                else
                {
                    MoveDown(loader.pizza, start, end);
                }
            }
        }
        return true;
    }
    
    void CutAndDump(vector<vector<bool>>& isTaken, int r0, int c0, int r1, int c1)
    {
        cout << "CutAndDump" << endl;
        for (int i = r0 ; i <= r1; ++i)
        {
            for (int j = c0; j <= c1; j++)
            {
                isTaken[i][j] = true;
            }
        }
        isLValid = false;
        isHValid = true;
        
        cout << r0 << " " << c0 << " " << r1 << " " << c1 << endl;
        
        ofs << r0 << " " << c0 << " " << r1 << " " << c1 << endl;
    }
    
    bool MoveStartPoint(vector<vector<int>>& pizza, Point& start, Point& end)
    {
        if (start.second == loader.const_column-1)
        {
            if (start.first == loader.const_row-1)
            {
                return false;
            }
            else
            {
                start.first++;
            }
        }
        else
        {
            int r = rand() % 100;
            if (r > 60)
            {
                start.first++;
            }
            else
            {
                start.second++;
            }
        }
        end= start;
        isLValid = false;
        isHValid = true;
        if (pizza[start.first][start.second] == 1)
        {
            tomato=1;
            mush=0;
        }
        else
        {
            tomato=0;
            mush=1;
        }
        return true;
    }
    
    void Run()
    {
        cout << "Start" << endl;
        vector<vector<int>>& pizza = loader.pizza;
        vector<vector<bool>>& isTaken = loader.isTaken;
        
        using Point = pair<int,int>;
        
        Point start = make_pair(0,0);
        Point end = start;
        
        if (pizza[0][0] == 1)
        {
            tomato++;
        }
        else
        {
            mush++;
        }
        int L = loader.const_min_ingredient;
        int H = loader.const_max_cells_in_slice;
        Point lastEnd = end;
        while (start.first != -1)
        {
            if (end.first > loader.const_row)
                break;
            bool wasLValid = isLValid;
            if (mush >= L && tomato >= L)
            {
                isLValid = true;
            }
            if (mush + tomato > H)
            {
                isHValid = false;
            }
            
            if (isLValid)
            {
                if (isHValid)
                {
                    lastEnd = end;
                    if (!MoveRightOrDown(pizza, start, end, lastEnd))
                    {
                        break;
                    }
                }
                else
                {
                    if (wasLValid)
                    {
                        // use lastEnd
                        CutAndDump(isTaken, start.first, start.second, lastEnd.first, lastEnd.second);
                        start = GetStartPoint(start);
                        //cout << "DEBUG : start " << start.first <<","<< start.second << endl;
                        end = start;
                        lastEnd = end;
                        if (pizza[start.first][start.second] == 1)
                        {
                            tomato=1;
                            mush=0;
                        }
                        else
                        {
                            tomato=0;
                            mush=1;
                        }
                    }
                    else
                    {
                        if (!MoveStartPoint(pizza, start, end))
                        {
                            break;
                        }
                    }
                    
                }
            }
            else
            {
                if (isHValid)
                {
                    if (!MoveRightOrDown(pizza, start, end, lastEnd))
                    {
                        break;
                    }
                }
                else
                {
                    // move start point
                    if (!MoveStartPoint(pizza, start, end))
                    {
                        break;
                    }
                }
            }
        }
        
        ofs.close();
        cout << "End" << endl;
    }
    
    bool isLValid = false;
    bool isHValid = true;
    int tomato = 0;
    int mush = 0;
    InputLoader& loader;
    std::ofstream ofs;
};


#endif /* Simple_hpp */
