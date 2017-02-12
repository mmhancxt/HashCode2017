//
//  main.cpp
//  HashCode2017
//
//  Created by Liang LIU on 07/02/2017.
//  Copyright © 2017 Liang LIU. All rights reserved.
//

#include <iostream>
#include <vector>
#include "InputLoader.h"

// 1 tomator 0 muschroom

struct cut_path_point{
	int r0;
	int c0;
	int r1;
	int c1;
};

struct return_stuff{
	std::vector<cut_path_point> cut_path;
	int value;
};

bool isValid(const std::vector< std::vector<int> >& pizza, int r0, int c0, int r1, int c1, int L, int H){
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

return_stuff getMaxCut(const std::vector< std::vector<int> >& pizza, int r0, int c0, int r1, int c1, int L, int H){
	int sum = 0;
	int area =(c1-c0+1)*(r1-r0+1);
	int max_i = 0;
	int max_j = 0;
	std::vector<cut_path_point> path;
	//if part small enough, check if is valid
	if(isValid(pizza,r0,c0,r1,c1, L, H)){
		sum = area;
		path.resize(0);
		path.push_back({r0,c0,r1,c1});
	}
	if(area <= H && !isValid(pizza,r0,c0,r1,c1, L, H)){
		sum = 0;
		path.resize(0);
	}
	if (area > H){
		for(int i = r0; i <= r1; i++)
			for(int j = c0; j<= c1; j++){
				return_stuff return1, return2, return3, return4;
				return1.value = 0;
				return2.value = 0;
				return3.value = 0;
				return4.value = 0;

				std::vector<cut_path_point> temp_path;
				if(i==r1&&j==c1)
					break;
				return1 = getMaxCut(pizza, r0, c0, i, j, L, H);
				if(i+1<=r1)
					return2 = getMaxCut(pizza, i+1, c0, r1, j, L, H);
				if(j+1 <=c1)
					return3 = getMaxCut(pizza, r0, j+1, i, c1, L, H);
				if(i+1<=r1 && j+1 <=c1)
					return4 = getMaxCut(pizza, i+1, j+1, r1, c1, L, H);
				int temp_sum = return1.value + return2.value + return3.value + return4.value;
			    //std::cout<<count1<<" "<<count2<<" "<<count3<<" "<<count4<<std::endl;
				temp_path.insert(temp_path.end(), return1.cut_path.begin(), return1.cut_path.end());
				temp_path.insert(temp_path.end(), return2.cut_path.begin(), return2.cut_path.end());
				temp_path.insert(temp_path.end(), return3.cut_path.begin(), return3.cut_path.end());
				temp_path.insert(temp_path.end(), return4.cut_path.begin(), return4.cut_path.end());
				if(temp_sum > sum){
					sum = temp_sum;
					max_i = i;
					max_j = j;
					path = temp_path;
				}

			}
	}
	return_stuff res;
	res.cut_path = path;
	res.value = sum;
    return res;

}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, HashCode!\n";
    InputLoader loader("/home/qian/HashCode2017/HashCode2017/medium.in");

    //std::vector< std::vector<int> > pizza = {{1, 1, 1, 1, 1},{1, 0, 0, 0, 1},{1,1, 1, 1, 1}};
    int size = 7;
    int value = 0;
    std::vector<cut_path_point> path;
    for(int i = 0; i < loader.const_row/size;i++)
        for(int j = 0; j < loader.const_column/size;j++){
        	std::cout<<i*size<<","<<j*size<<std::endl;
        	return_stuff res = getMaxCut(loader.pizza,i*size,j*size,(i+1)*size-1,(j+1)*size-1, loader.const_min_ingredient, loader.const_max_cells_in_slice);
        	value+= res.value;
        	path.insert(path.end(),res.cut_path.begin(),res.cut_path.end());
        }
	std::cout<<path.size()<<std::endl;
    for(int i = 0; i< path.size();i++)
        std::cout<<path[i].r0<<" "<<path[i].c0<<" "<<path[i].r1<<" "<<path[i].c1<<std::endl;
    return 0;
}

