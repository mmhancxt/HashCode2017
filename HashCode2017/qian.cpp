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



bool isValid(const std::vector< std::vector<int> >& pizza, int r0, int c0, int r1, int c1){
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

int getMaxCut(const std::vector< std::vector<int> >& pizza, int r0, int c0, int r1, int c1){
	int sum = 0;
	int area =(c1-c0+1)*(r1-r0+1);

	//if part small enough, check if is valid
	if(isValid(pizza,r0,c0,r1,c1))
		sum = area;
	if(area <= H && !isValid(pizza,r0,c0,r1,c1))
		sum = 0;
	if (area > H){
		for(int i = r0; i <= r1; i++)
			for(int j = c0; j<= c1; j++){
				int count1 = 0;
				int count2 = 0;
				int count3 = 0;
				int count4 = 0;
				count1 = getMaxCut(pizza, r0, c0, i, j);
				if(i+1<=r1)
					count2 = getMaxCut(pizza, i+1, c0, r1, j);
				if(j+1 <=c1)
					count3 = getMaxCut(pizza, r0, j+1, i, c1);
				if(i+1<=r1 && j+1 <=c1)
					count4 = getMaxCut(pizza, i+1, j+1, r1, c1);
				int temp_sum = count1 + count2 + count3 + count4;
			    //std::cout<<count1<<" "<<count2<<" "<<count3<<" "<<count4<<std::endl;
				sum = (sum > temp_sum)?sum:temp_sum;
			}
	}
    std::cout<<"pizza cut"<<r0<<" "<<c0<<" "<<r1<<" "<<c1<<std::endl;
    std::cout<<"pizza part "<<sum<<std::endl;

    return sum;

}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, HashCode!\n";
    std::vector< std::vector<int> > pizza = {{1, 1, 1, 1, 1},{1, 0, 0, 0, 1},{1,1, 1, 1, 1}};

    int res = getMaxCut(pizza,0,0,2,2);
    std::cout<<"Max num is "<<res<<std::endl;
    return 0;
}

