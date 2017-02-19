#pragma once
#include "InputLoader.h"
#include "Objects.h"
#include <vector>
#include <numeric>

using namespace std;

static string buildDeliveryCommand(int drone_index, int order_id, int product_id, int product_nubmer)
{
    return to_string(drone_index) + " " + "D" + " " +  to_string(order_id) + " " + to_string(product_id) + " " + to_string(product_nubmer);
}

static string buildLoadCommand(int drone_index, int warehouse_id, int product_id, int product_number)
{
    return to_string(drone_index) + " " + "L" + " " +  to_string(warehouse_id) + " " + to_string(product_id) + " " + to_string(product_number);
}

static void outputCommands(vector<string> commands)
{
    for (auto command : commands)
    {
        cout << command << endl;
    }
}

void deleteOrder(InputLoader& input, int order_id)
{
    auto orders = input.orders;
    auto it = input.orders.begin();
    for (; it != input.orders.end(); ++it)
    {
        if (it->id == order_id) break;
    }
    if (it == input.orders.end()) return ;
    
    input.orders.erase(it);
}

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


vector<string> loadAndDeliverSimpleOrders(InputLoader& input, vector<Order>& simple_orders)
{
    int drone_index = 0;
    vector<string> commands;
    
    for (auto& simple_order : simple_orders)
    {
        for (auto& product : simple_order.purchasedProducts)
        {
            for (auto& warehouse : input.warehouses)
            {
                if (warehouse.containsProduct(product.id))
                {
                    warehouse.availableProducts[product.id]--;
                    commands.emplace_back(buildLoadCommand(drone_index, warehouse.id, product.id, 1));
                    commands.emplace_back(buildDeliveryCommand(drone_index, simple_order.id, product.id, 1));
                    drone_index = (drone_index+1) % input.const_droneNum;
                }
            }
        }
        deleteOrder(input, simple_order.id);
    }
    return commands;
}

