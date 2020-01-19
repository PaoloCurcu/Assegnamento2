//============================================================================
// Name        : ProvaPC.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include "orderInit.h"
#include "System.h"

using namespace std;

class Invalid {};

bool finished(int m, const vector<orderInit>& o); //controlla se il main deve terminare
void fill_orders(vector<orderInit>& o, istream& i);   //riempre il vector da orders.dat



int main() {
//variabili
int month = 0; //tengo traccia del mese corrente
System::Warehouse syst; //sistema di gestione degli ordini
vector<orderInit> orders; //per inserire ordini da orders.dat

ifstream ist {"orders.txt"};    // input main: orders
if (!ist)
	throw Invalid();

//riempio orders dal orders.dat
fill_orders(orders, ist);

//LOOP principale del programma!
int index = 0;
for (month = 0; ! finished(month, orders); month++) {
	while(orders[month + index].time_stamp == month) {
		cout << "Aggiungo gli ordini\n" << endl;//passo gli ordini mese per mese al System
		syst.addOrder(orders[month + index]);
		index++;
	}

	ist.close();
	index--;
	//syst.check_situation(); //invocata una volta per ogni mese -> incrementa il mese del System
}

syst.PrintAll();
return 0;

}


bool finished(int m, const vector<orderInit>& o) {
return m > o[o.size() - 1].time_stamp + 12;  //il +12 è per indicare che lasciamo un anno a partire
											 //dal time_stamp dell'ULTIMO ORDINE per completarne la
											 //consegna, ma si può scegliere un criterio migliore
}

void fill_orders(vector<orderInit>& o, istream& i) {
int time_stamp;
int model_id;
int quantity_ordered;
while (i >> time_stamp >> model_id >> quantity_ordered)
	o.push_back(orderInit{time_stamp, model_id, quantity_ordered});
}

