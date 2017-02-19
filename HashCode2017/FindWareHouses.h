#pragma once
#include "InputLoader.h"
#include "Objects.h"

// Orders that cannot be fulfilled by one warehouse will return -1
vector<vector<int>> GetWareHouseOperations(Order& od, InputLoader& input) {
	std::vector<WareHouse> sorted_warehouses(input.warehouses);

	cout << "ware " << sorted_warehouses.size() << endl;
	for(int i = 0; i <sorted_warehouses.size(); i++){
		int square_dis = pow(od.deliverPosition.x - sorted_warehouses[i].position.x, 2) +
			pow(od.deliverPosition.y - sorted_warehouses[i].position.y, 2);
		for (int j = i+1; j < sorted_warehouses.size(); j++) {
			int square_dis2 = pow(od.deliverPosition.x - sorted_warehouses[j].position.x, 2) +
				pow(od.deliverPosition.y - sorted_warehouses[j].position.y, 2);
			//cout << "del " << od.deliverPosition.x << " " << od.deliverPosition.y<< endl;
			//cout << "w1 " << sorted_warehouses[i].position.x << " " << sorted_warehouses[i].position.y << endl;
			//cout << "w2 " << sorted_warehouses[j].position.x << " " << sorted_warehouses[j].position.y << endl;

			//cout << "dis " << square_dis << " " << i << " " << square_dis2 << " " << j << endl;

			if (square_dis2 < square_dis) {
				WareHouse temp = sorted_warehouses[i];
				sorted_warehouses[i] = sorted_warehouses[j];
				sorted_warehouses[j] = temp;
			}
		}
	}
	//cout << "del " << od.deliverPosition.x << " " << od.deliverPosition.y<< endl;

	//for (int i = 0; i < input.warehouses.size(); i++) {
	//	cout << "w1 " << input.warehouses[i].position.x << " " << input.warehouses[i].position.y << endl;
	//}
	//for (int i = 0; i < input.warehouses.size(); i++) {
	//	cout << "w2 " << sorted_warehouses[i].position.x << " " << sorted_warehouses[i].position.y << endl;
	//}
	//cout << "del " << od.deliverPosition.x << " " << od.deliverPosition.y<< endl;
	//cout << "w1 " << sorted_warehouses[i].position.x << " " << sorted_warehouses[i].position.y << endl;
	//cout << "w2 " << sorted_warehouses[j].position.x << " " << sorted_warehouses[j].position.y << endl;

	//cout << "dis " << square_dis << " " << i << " " << square_dis2 << " " << j << endl;
	vector<pair<int, int>> products;
	for (int i = 0; i < input.products.size(); i++) {
		int count = od.GetProductNumber(input.products[i].id);
		if (count > 0)
			products.push_back(make_pair(input.products[i].id, count));
	}

	vector<vector<int>> retrieve_strategy;
	for (int i = 0; i < sorted_warehouses.size(); i++) {
		bool isOK = true;
		bool isSelected = false;
		for (int j = 0; j < products.size(); j++) {
			int p_id = products[j].first;
			int num = products[j].second;
			if (num == 0)
				continue;
			if (num > 0)
				isOK = false;
			int avail_num = sorted_warehouses[i].availableProducts[p_id];
			if (avail_num > num && avail_num > 0) {
				products[j].second = 0;
				isSelected = true;
				vector<int> rec(3);
				rec[0] = sorted_warehouses[i].id;
				rec[1] = p_id;
				rec[2] = num;
				//cout << i << "," << sorted_warehouses[i].id << endl;
				retrieve_strategy.push_back(rec);

			}
			else if(avail_num > 0 && avail_num  <= num) {
				products[j].second -= avail_num;
				isSelected = true;
				vector<int> rec(3);
				rec[0] = sorted_warehouses[i].id;
				rec[1] = p_id;
				rec[2] = num;
				//cout << i << "," << sorted_warehouses[i].id << endl;

				retrieve_strategy.push_back(rec);
			}
		}
		if (isOK == true)
			break;
	}
	return retrieve_strategy;
}
//Compute the minimally required turns for one drone to serve an order 
int GetRequiredTurns(Drone& d, Order& od, InputLoader& input) {
	if (d.status != COMPLETED) //only consider currently idle drone
		return -1;

}