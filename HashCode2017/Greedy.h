#include "InputLoader.h"

class Greedy
{
public:
   Greedy(InputLoader& input) : loader(input)
   {
      loader.LoadFromFile("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/input/busy_day.in");
   }

   void CalculateOrderPoints(vector<Order>& orders)
   {
          
   }

   void Load(int dId, int wId, int pId, int pNb, Order& order)
   {
      cout << dId << " L " << wId << " " << pId << " " << pNb << endl;
      for (Product& p : order.purchasedProducts)
      {
         if (p.id == pId && p.status ==  UNPROCESSED)
         {
            p.status = INDELIVERING;
         }
      }
   }

   void Run()
   {
      vector<Order> orders = loader.orders;
      CalculateOrderPoints(orders);
      int current = 0;
      while (current < loader.const_totalTurns)
      {
         for (int i = 0 ; i < loader.const_droneNum; i++)
         {
            Drone& drone = loader.drones[i];
            CalculateOrderPoints(orders);      
            Order& orderToDeliver = orders[0];
            int pId = orderToDeliver.nextProductToDeliver;
            int wId = orderToDeliver.wareHouseIdToLoad;
            int pNb = orderToDeliver.GetUndeliveredProduct(pId);
            int availableCap = loader.const_maxDroneLoad;
            while (availableCap > 0)
            {
               int nb = std::min(availableCap, pNb);
               Load(drone.id, wId, pId, pNb, orderToDeliver);
               
            }
         }
         current++;
      }
   }

   InputLoader& loader;
};
