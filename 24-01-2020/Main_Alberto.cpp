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
#include "System.h"

using namespace std;

class Invalid {
};

bool finished(int m, const vector<orderInit> &o); //controlla se il main deve terminare
double fill_orders(vector<orderInit> &o, istream &i); //riempre il vector da orders.dat

int main() {
//variabili
	int month = 0; //tengo traccia del mese corrente
	//sistema di gestione degli ordini
	vector<orderInit> orders; //per inserire ordini da orders.dat

	ifstream ist { "orders.dat" };    // input main: orders
	if (!ist)
		throw Invalid();

//riempio orders dal orders.dat e ritorno il valore iniziale della cassa per inizializzare il magazzino
	System::Warehouse syst(fill_orders(orders, ist));
//LOOP principale del programma!
	int index = 0;
	syst.printAll();
	for (month = 0; !finished(month, orders); month++) {

		cout << "\nMese n: " << month
				<< "----------------------------------------\n" << endl;
		while (orders[month + index].time_stamp == month) {

			syst.addOrder(orders[month + index]);
			index++;
		}
		syst.check_situation();
		ist.close();
		index--;
		//syst.check_situation(); //invocata una volta per ogni mese -> incrementa il mese del System
	}

	return 0;

}

bool finished(int m, const vector<orderInit> &o) {
	return m > o[o.size() - 1].time_stamp + 12; //il +12 è per indicare che lasciamo un anno a partire
												//dal time_stamp dell'ULTIMO ORDINE per completarne la
												//consegna, ma si può scegliere un criterio migliore
}

double fill_orders(vector<orderInit> &o, istream &i) {
	int time_stamp;
	int model_id;
	int quantity_ordered;
	double cash_desk;
	i >> cash_desk;
	while (i >> time_stamp >> model_id >> quantity_ordered)
		o.push_back(orderInit { time_stamp, model_id, quantity_ordered });
	return cash_desk;
}

