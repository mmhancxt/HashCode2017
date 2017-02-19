#include "SimpleOrder.h"
std::vector<Order> find_one_drone_order(InputLoader& input) {
	std::vector<Order>& cur_orders = input.orders;
	std::vector<Order> one_drone_order;
	for (int i = 0; i < cur_orders.size(); i++) {
		int weight = 0;
		for (const auto& pair : cur_orders[i].purchasedProducts)
		{
			int index = pair.first;
			int prod_weight = pair.second;
			int unit_weight = input.products[index].weight;
			weight += unit_weight * prod_weight;
		}
		if (weight <= input.const_maxDroneLoad){
			one_drone_order.push_back(cur_orders[i]);
			//cout << "weight " << weight << endl;
		}
	}
	return one_drone_order;
}