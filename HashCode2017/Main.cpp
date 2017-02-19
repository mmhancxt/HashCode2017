#include <iostream>
#include "InputLoader.h"
#include "SimpleOrder.h"
#include "FindWareHouses.h"
using namespace std;

int main()
{
	InputLoader loader;
	loader.LoadFromFile("D:\\Codes\\HashCode2017\\HashCode2017\\input\\busy_day.in");
	for (int i = 0; i < 10; i++) {
		vector<vector<int>> ret = GetWareHouseOperations(loader.orders[i], loader);
		for (int j = 0; j < ret.size(); j++)
			cout << "warehouse " << ret[j][0] << " get " << ret[j][1] << " quatity " << ret[j][2] << endl;;
	}
	cout << "delivery" << endl;
	std::cin.get();
}
