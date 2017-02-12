//
//  Common.h
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#ifndef Common_h
#define Common_h
#include <fstream>

static bool isValidPizza(std::vector< std::vector<int> > pizza, int r0, int c0, int r1, int c1, int L, int H){
    if ((c1-c0+1)*(r1-r0+1)>H)
        return false;
    int count_t = 0;
    int count_m = 0;
    for(int i = r0; i<=r1;i++)
        for(int j = c0; j <=c1; j++){
            if(pizza[i][j]==1)
                count_t++;
            else
                count_m++;
        }
    
    if(count_t >= L && count_m >=L)
        return true;
    return false;
    
}

using namespace std;
static void CutAndDump(vector<vector<bool>>& isTaken, int r0, int c0, int r1, int c1)
{
    for (int i = 0 ; i < isTaken.size(); ++i)
    {
        vector<bool> row = isTaken[i];
        for (int j = 0; i < row[j]; j++)
        {
            row[j] = true;
        }
    }
    
    filebuf fb;
    fb.open("outputs.txt", std::ios::out);
    ostream os(&fb);
    os << r0 << " " << c0 << " " << r1 << " " << c1 << endl;
}

#endif /* Common_h */
