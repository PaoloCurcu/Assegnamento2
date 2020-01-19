#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include "orderInit.h"
#include "Order.h"
#include "component.h"

namespace System {

class Warehouse {

public:

class Invalid {};
// per lanciare eccezioni
Warehouse();
void Syncrnize(int month);
void addOrder(orderInit fromMain);
void Updates();
void PrintAll();

// segue
// (segue class Date)
private:
int month;
std::vector <Order> orderList;

void coupleList();
//void InitTarget(orderInit &newOrder);
//std::ostream& operator<<(std::ostream& os, const Warehouse& d);
};

}
#endif
