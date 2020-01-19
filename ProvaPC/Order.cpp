//std::string FindFile(fMain.model_id);
//1 funzione che scopre il nome del file dove guardare FG
//1.2 Tramite il vettore formato
//2 funzione che associa al componente il tempo e la quantità e viene moltiplicata
//3 e poi carica tutto

//bisogna anche far tornare normali i target e aggiungere txt dopo!

//inizializzo model_name (per accedere ai file con i componenti)


#include <vector>
#include <fstream>
#include <iostream>
#include "Order.h"

using namespace std;

class fileNameNotFound{};
class TargetNotFound{};
class Invalid {};

//Costruttore di default di order(Per ora non viene usato)
Order::Order()
: time_stamp{0}, model_id{0}, quantity_ordered{0} //ci vorrebbe qualcos'altro
{

}

//costruttore di Order
Order::Order(orderInit fMain)
:time_stamp{fMain.time_stamp},
model_id{fMain.model_id},
quantity_ordered{fMain.quantity_ordered}
//orderComponents{0}
{
  fileName =FindModelFile(model_id);
  model_name=FindModelName(fileName);//fuzione che mette il model_name
  FillComponents(fileName, orderComponents);
}

//Stampa le variabili esemplare di un ordine
void Order::PrintOrder(){
	cout <<  " " << quantity_ordered << " "
		 <<  model_name
		 << " Al mese " << time_stamp
	     << " (ID: "        << model_id <<")"
		 << ":\n  Componenti:"
		 << endl;
	for(component ro: orderComponents)
	cout<< "     °" <<  ro    << endl;


}


//Cerca tramite l'ID dell'order il file dove estrarre i componenti
string Order::FindModelFile(int model_id){
string model;
string fileName;
int tmp;//La stringa d'appoggio attraverso la quale copio i nomi dal file al vettore
ifstream ist {"models.txt"};    // input main: orders
if (!ist)
throw Invalid();

while (ist >> model){
	ifstream ist2{model};
	if (!ist2)
		throw Invalid();
	ist2 >> tmp;
	if(tmp==model_id){
		ist >> fileName;
		break;
	}
	ist2.close();
}
ist.close();
if(tmp==model_id)
	return fileName;
else
	throw fileNameNotFound();
}


//riempie l'array di <component> dell'oggetto Order da inizializzare
void Order::FillComponents(string file, vector<component>& input){
	int component_id;
	string component_name;
	int component_quantity;
	ifstream ist{file};
		if (!ist)
			throw Invalid();
		  ist >> component_id >> component_name;//Butto via la prima riga (da trovare un modo più elegante)
	while(ist >> component_id >> component_name >> component_quantity ){
		//cout << "Vediamo se ripete\n" ;
		input.push_back(component{component_id, component_name, component_quantity});
	}
}

//Tramite il nome del file inizializza la variabile esempare di Order "model_name"
string Order::FindModelName(string file){
	int id_inutile;//Versione provvisoria
	string model_name;
	ifstream ist2{file};
		if (!ist2)
			throw Invalid();
		ist2 >> id_inutile >> model_name ;
		return model_name;
}












