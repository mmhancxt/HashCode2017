#include <iostream>
#include "Greedy.h"
#include "SimpleOrder.h"
using namespace std;

int main()
{
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
}
