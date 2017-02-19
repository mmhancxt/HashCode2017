#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

enum Status
{
    UNPROCESSED,
    INDELIVERING,
    COMPLETED
};

struct Product
{
	int id;
	int weight;
	Status status;
};

struct Position
{
	int x;
	int y;
};

struct WareHouse
{
	int id;
	Position position;
	map<int, int> availableProducts;
	bool containsProduct(int productId) {
		return availableProducts[productId] > 0;
	}
};

class Order
{
public:
	int id;
   Status status;
	Position deliverPosition;
	vector<Product> purchasedProducts;
   int nextProductToDeliver;
   int wareHouseIdToLoad;
   
   // count unprocessed product given by an product id
   int GetUnprocessedProductNumber(int productId)
   {
	   return std::count_if(purchasedProducts.cbegin(), purchasedProducts.cend(),
		   [productId](const Product& p) { return p.id == productId && p.status == Status::UNPROCESSED; }
	   );
   }
};

enum DroneStatus
{
    FLY,
    WAIT,
    INORDER,
    INWAREHOUSE
};

struct Drone
{
    Drone(Position p, int i)
    {
		id = i;
        load = 0;
        position.x = p.x;
        position.y = p.y;
        status = INWAREHOUSE;
        nextUsableTurn = 0;
    }
	int id;
    int load;
    int nextUsableTurn;
    DroneStatus nextAction;
    DroneStatus status;
    Position position;
    map<int, int> gods;
};
