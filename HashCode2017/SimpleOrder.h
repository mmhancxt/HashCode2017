#pragma once
#include "InputLoader.h"
#include "Objects.h"
#include <vector>
#include <numeric>

using namespace std;

std::vector<Order> find_one_drone_order(InputLoader& input)
{
	std::vector<Order>& cur_orders = input.orders;
	std::vector<Order> one_drone_order;
	for (int i = 0; i < cur_orders.size(); i++) {
		//int weight = 0;
		//for (const auto& product : cur_orders[i].purchasedProducts)
		//{
		//	weight += product.weight;
		//}
		int weight = std::accumulate(cur_orders[i].purchasedProducts.begin(), cur_orders[i].purchasedProducts.end(), 0, [](int weight, const Product& p1)
			{ return p1.weight + weight;  }
		);

		if (weight <= input.const_maxDroneLoad){
			one_drone_order.push_back(cur_orders[i]);
			//cout << "weight " << weight << endl;
		}
	}
	return one_drone_order;
}