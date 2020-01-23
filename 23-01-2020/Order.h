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
#include "Structure.h"


using namespace std;
class Order {

public:

Order();
Order(orderInit fMainstd,const vector<vector<components>> &models_infos,const vector<component_info> &components_infos);
void PrintOrder();
int order_components();
bool updates();

//Funzioni per la stampa
string modelName();
int timeStamp();
int modelId();
int quantityOrdered();

private:

int time_stamp;
int model_id;
int quantity_ordered;
double price;
string model_name;
vector<components> orderComponents;

};
#endif



