//
//  main.cpp
//  HashCode2017
//
//  Created by Liang LIU on 07/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include <iostream>
#include "InputLoader.h"
#include <fstream>
using namespace std;


class Greedy
{
public:
    Greedy(InputLoader& input) : loader(input), pizza(loader.pizza), isTaken(loader.isTaken),
        ofs("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/outputs.txt", std::ofstream::out)
    {
        L = loader.const_min_ingredient;
        H = loader.const_max_cells_in_slice;
        t = 0;
        m = 0;
        maxValue = 0;
        r1 = -1;
        c1 = -1;
        score = 0;
    }
    
    void bt(int x0, int y0, int x1, int y1)
    {
        int sum = t+m;
        if (t >= L && m >= L && t+m <= H)
        {
            if (sum > maxValue)
            {
                maxValue = sum;
                r1 = x1;
                c1 = y1;
            }
        }
        if (sum>H)
            return;
        else
        {
            int oldT = t;
            int oldM = m;
            if (y1+1 < loader.const_column)
            {
                int s = 0;
                for (int i=x0;i<=x1;i++)
                {
                    if (pizza[i][y1+1]==1) t++;
                    else m++;
                    s+= isTaken[i][y1+1];
                }
                if (s == 0)
                {
                    bt(x0,y0,x1,y1+1);
                }
                t = oldT;
                m = oldM;
            }
            if (x1+1 < loader.const_row)
            {
                int s = 0;
                for (int j=y0;j<=y1;j++)
                {
                    if (pizza[x1+1][j]==1) t++;
                    else m++;
                    s+= isTaken[x1+1][j];
                }
                if (s == 0)
                {
                    bt(x0,y0,x1+1,y1);
                }
                t = oldT;
                m = oldM;
            }
        }
    }
    
    void GetMaxValue(int x, int y)
    {
        if (pizza[x][y] == 1) t++;
        else m++;
        bt(x,y,x,y);
        t = 0;
        m = 0;
    }
    
    void CutAndDump(int x0, int y0, int x1, int y1)
    {
        for (int i=x0;i<=x1;i++)
            for (int j=y0;j<=y1;j++)
                isTaken[i][j] = 1;
        int s = (x1-x0+1)*(y1-y0+1);
        score = score + s;
        cout << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
        ofs << x0 << " " << y0 << " " << x1 << " " << y1 << endl;
        
        t = 0;
        m = 0;
        maxValue = 0;
        r1 = -1;
        c1 = -1;
    }
    
    void Run()
    {
        for (int i=0; i<loader.const_row; i++)
            for (int j=0; j<loader.const_column;j++)
            {
                if (isTaken[i][j] != 1)
                {
                    GetMaxValue(i,j);
                    if (maxValue != 0)
                    {
                        CutAndDump(i,j,r1,c1);
                    }
                }
            }
        
        ofs.close();
    }
    
    void PrintIsTaken()
    {
        for (int i=0;i<loader.const_row;i++)
        {
            for (int j=0;j<loader.const_column;j++)
                if (isTaken[i][j] == 1)
                    cout << "*";
                else cout << " ";
            cout << endl;
        }
        cout << "Score is " << score <<endl;
    }
    
    int L;
    int H;
    int t;
    int m;
    int maxValue;
    int r1;
    int c1;
    int score;
    
    
    InputLoader& loader;
    vector<vector<int>>& pizza;
    vector<vector<int>>& isTaken;
    ofstream ofs;
};

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
    Greedy greedy(loader);
    greedy.Run();
    greedy.PrintIsTaken();
    return 0;
}
