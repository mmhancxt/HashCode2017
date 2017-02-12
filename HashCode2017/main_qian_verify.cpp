//
//  main.cpp
//  HashCode2017
//
//  Created by Liang LIU on 07/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include <iostream>
#include <vector>
const int L = 1;
const int H = 6;

// 1 tomator 0 muschroom



bool isValid(std::vector< std::vector<int> > pizza, int r0, int c0, int r1, int c1){
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


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, HashCode!\n";
    std::vector< std::vector<int> > pizza = {{1, 1, 1, 1, 1},{1, 0, 0, 0, 1},{1,1, 1, 1, 1}};
    std::cout<< isValid(pizza,0,2,2,2)<<std::endl;
    std::cout<< isValid(pizza,0,3,2,4)<<std::endl;

    return 0;
}
