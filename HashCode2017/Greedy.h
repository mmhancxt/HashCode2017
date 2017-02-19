#include "InputLoader.h"
#include <algorithm>

class Greedy
{
public:
   Greedy(InputLoader& input) : loader(input)
   {
      loader.LoadFromFile("/Users/Xavier/Programs/c++/HashCode2017/HashCode2017/input/busy_day.in");
   }

   void CalculateOrderPoints(vector<Order>& orders)
   {
      std::sort(orders.begin(), orders.end(), [](const Order& o1, const Order& o2)
            {
               return o1.points > o2.points;
            });
   }

   void Load(WareHouse& house, Drone& drone, int wId, int pId, int pNb, Order& order, int current)
   {
      cout << drone.id << " L " << wId << " " << pId << " " << pNb << endl;
      for (Product& p : order.purchasedProducts)
      {
         if (p.id == pId && p.status ==  UNPROCESSED)
         {
            p.status = INDELIVERING;
            house.availableProducts[pId]--;
         }
      }
      drone.status = INWAREHOUSE;
      int dis = GetDistance(drone.position, house.position);
      drone.nextUsableTurn = current + dis + 1;
      drone.orderToDeliver = order.id;
   }

   void Deliver(Drone& drone, int current)
   {
      Order& order = loader.orders[drone.orderToDeliver];
      cout << drone.id << " D " << order.id << " " << order.nextProductToDeliver << " " << drone.gods[order.nextProductToDeliver] << endl;
      for (Product& p : order.purchasedProducts)
      {
         if (p.id == pId && p.status == INDELIVERING)
         {
            p.status = COMPLETED;
         }
      }
      drone.status = INORDER; 
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
            if (drone.nextUsableTurn == current)
            {
               if (drone.status == INORDER)
               {
                  CalculateOrderPoints(orders);      
                  Order& orderToDeliver = orders[0];
                  int pId = orderToDeliver.nextProductToDeliver;
                  int wId = orderToDeliver.wareHouseIdToLoad;
                  int pNb = orderToDeliver.GetUnprocessedProductNumber(pId);
                  int availableCap = loader.const_maxDroneLoad;
                  WareHouse& wh = loader.warehouses[wId];
                  int nb = std::min(std::min(availableCap, pNb), 
                        wh.availableProducts[pId]);
                  Load(wh, drone.id, wId, pId, nb, orderToDeliver, current);
               }
               else if (drone.status == INWAREHOUSE)
               {
                  Deliver(drone, current);
               }
            }
         }
         current++;
      }
   }

   InputLoader& loader;
};
