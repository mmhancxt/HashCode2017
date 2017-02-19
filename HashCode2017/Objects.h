#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <math.h>
#include <vector>

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

enum Status
{
    UNPROCESSED,
    INDELIVERING,
    COMPLETED
};

class Order
{
	int id;
   Status status;
	Position deliverPosition;
	vector<Product> purchasedProducts;
   int nextProductToDeliver;
   int wareHouseIdToLoad;
   
   int GetUndeliveredProduct(int pId)
   {
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
