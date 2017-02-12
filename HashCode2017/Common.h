//
//  Common.h
//  HashCode2017
//
//  Created by Liang LIU on 12/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#ifndef Common_h
#define Common_h

bool isValid(std::vector< std::vector<int> > pizza, int r0, int c0, int r1, int c1, int L, int H){
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

#endif /* Common_h */
