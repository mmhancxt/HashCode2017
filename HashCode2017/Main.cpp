#include <iostream>
#include "InputLoader.h"
#include "SimpleOrder.h"
#include "FindWareHouses.h"
using namespace std;

int main()
{
<<<<<<< HEAD
   InputLoader loader;
   //loader.LoadFromFile("D:\\Codes\\HashCode2017\\HashCode2017\\input\\busy_day.in");
   loader.LoadFromFile("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/input/busy_day.in");
   std::vector<Order> simple_order = find_one_drone_order(loader);
   for (int i = 0; i < simple_order.size(); i++) {
	   cout << "order " <<i<<":" << simple_order[i].id << ", (" << simple_order[i].deliverPosition.x << "," << simple_order[i].deliverPosition.y << ")"<< endl;
   }
   cout << "delivery" << endl;

   Greedy g(loader);
   g.Run();

   std::cin.get();
=======
	InputLoader loader;
	loader.LoadFromFile("D:\\Codes\\HashCode2017\\HashCode2017\\input\\busy_day.in");
	for (int i = 0; i < 10; i++) {
		vector<vector<int>> ret = GetWareHouseOperations(loader.orders[i], loader);
		for (int j = 0; j < ret.size(); j++)
			cout << "warehouse " << ret[j][0] << " get " << ret[j][1] << " quatity " << ret[j][2] << endl;;
	}
	cout << "delivery" << endl;
	std::cin.get();
>>>>>>> b1cbf6a88209951fef7ead1462265cd3dd23d6c2
}
