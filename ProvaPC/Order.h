/*
* Order1.h
*
*  Created on: 17 gen 2020
*      Author: paolo
*/

#ifndef ORDER_H_
#define ORDER_H_

#include <vector>
#include <iostream>
#include "orderInit.h"
#include "component.h"

using namespace std;
class Order {

public:

Order();
// per lanciare eccezioni

Order(orderInit fMain);
void PrintOrder();


// segue
// (segue class Date)
private:
//ostream& operator<<(ostream& os, Order& d);
int time_stamp;
int model_id;
int quantity_ordered;
string fileName;
string model_name;
vector<component> orderComponents;

string FindModelFile(int model_id);
string FindModelName(string file);
void FillComponents(string file,vector<component>& input);

};
#endif



