
#include <vector>
#include <fstream>
#include <iostream>
#include "System.h"
#include "Order.h"



using namespace std;
namespace System {

class Invalid {};
class TargetNotFound{};

Warehouse::Warehouse()
:month{0},cash_desk{0},differentPrice{0}
{
}

Warehouse::Warehouse(double initCash_desk)
: month{0},cash_desk{initCash_desk,initCash_desk,initCash_desk},differentPrice{0,0,0}
{
	fill_data();
}

//Inizializzo un nuovo ordine
void Warehouse::addOrder(orderInit fMain){
	Order newOrder(fMain, models_infos, components_infos);//Costruttore a cui passo i vettori con i dati dei file
	orderList.push_back(newOrder);//Aggiungo alla lista di ordini il nuovo ordine
	//newOrder.PrintOrder();
}

//Scorro i vari ordini e aggiorno la situzione del magazzino
void Warehouse::check_situation(){
Order tmp;
int componentToBuy=0; //tiene conto di tutti gli ordini che si vogliono effettuare per valutare il prezzo e aggiornare la cassa
for( auto p : orderList){    //Stampo la situzione per debug
		p.PrintOrder();
		cout << "\n"<< endl;
	}
int size = orderList.size(); // uso questa variabile temporanea perchè togliendo elementi da OrdeList la dimensione diminuisce
for(int i=0; i<size;i++){

	//POTREBBE ANDARE A PUTTANE
	componentToBuy = componentToBuy + orderList[i].order_components(); //Ordino i componenti necessari
	if(orderList[i].updates()){//Aggiorno le tempistiche e tolgo elettrodomestici completi
		cout << "\n" << "La " << orderList[i].modelName() << "E' pronta \n"<< endl ;
		orderReady.push_back( orderList[i]);//Inserisco l'elemento ultimato nella lista degli ordini finiti
		orderList.erase(orderList.begin()+i);//Rimuovo elemento ultimato dalla lista degli ordini in costruzione
		i--; size--;//Avendo tolto un elemento da un array che sto scorrendo (Gli elementi riempiono il buco)
		//devo aggiornare di conseguenza indice e dimensione dell'array
	}
}
/////////////////////////////////////////STAMPE DI DEBUG//////////////////////////////////////////////
cout << "Order List "<<endl;
for( auto p : orderList){
		cout<<"-" <<p.modelName()  << endl;
}

cout << "\nOrderReady  "<<endl;
for( auto p : orderReady){
		cout <<"-"<<p.modelName() << endl;
}

/////////////////////////////////////////////////ANCORA DEBUG//////////////////////////////////////
int i=0;//solo unicamente
if(componentToBuy>10)
	i=1;
if(componentToBuy>50)
	i=2;


cout << "\nComponenti ordinati: " << componentToBuy <<	" Al prezzo di " << differentPrice[i] <<"\n"

	 << "-------------------------------------------------\n"<<endl;
//return true;///////////////////////////////////////////////////////////////////
}

//Stampo situazione del magazzino (da definire)
void Warehouse::printAll(){
cout <<"La cassa iniziale è: " << cash_desk[0] << "\n"
     <<"I differenti prezzi sono: \n"
     << "-1 " << differentPrice[0] << "\n"
	 << "-2 " << differentPrice[1] << "\n"
	 << "-3 " << differentPrice[2] << "\n"<< endl;

}
//decide il prezzo in base a quanti componenti bisogna comprare e aggiorna la cassa
void Warehouse::cash_deskUpdate(int componentToBuy){
int i=0;
if(componentToBuy>50)
	i=2;
if(componentToBuy>10){
	i=1;
}
	double money = componentToBuy * differentPrice[i];
	cash_desk[0]= cash_desk[0]- money;

}



void Warehouse::fill_data(){
//(1) riempio model_types e models_infos
	std::ifstream ist {"models.dat"};
	if (!ist)
		throw Invalid();

	// store models
	std::vector<std::string> model_files;                   // questo Ã¨ il mio vettore con i model
	std::string file;

	while (ist >> file)
		model_files.push_back(std::string{file});

	ist.close();    // chiudo ist
////////////////////////////////////////////
	/* print models
	std::cout << "Dentro model_files:\n";                                           // ***** debug *****
	for (int i=0; i < model_files.size(); ++i)                                      // ***** debug *****
		std::cout << model_files[i] << std::endl;                                   // ***** debug *****
	std::cout << std::endl;*/                                                       // ***** debug *****
/////////////////////////////////////////
	// store model_id, model_name, component_id, component_name, quantity
	for (unsigned int i=0; i < model_files.size(); ++i){
		// input [model1.dat] (esempio)
		std::string input_name = model_files[i];
		std::ifstream ist2 {input_name};
		if (!ist2)
			throw Invalid();

		// store prima riga di [model1.dat] (esempio)
		int model_id;
		std::string model_name;

		ist2 >> model_id >> model_name;
		model_types.push_back(model{model_id, model_name}); // store prima riga

		// store seconda riga di [model1.dat] (esempio)
		int component_id;
		std::string component_name;
		int quantity;
		std::vector<components> tmp;
		////////////////////////////////////per riconoscere
		tmp.push_back(components{model_id, model_name});
		////////////////////////////
		while (ist2 >> component_id >> component_name >> quantity)
			tmp.push_back(components{component_id, component_name, quantity});   // store tutto il resto

		models_infos.push_back(tmp);
	}
//////////////////////////////////7
	// print model_id e model_name
/*	std::cout << "Dentro model_types:\n";                                           // ***** debug *****
	for (int j=0; j < model_types.size(); ++j)                                      // ***** debug *****
	{                                                                               // ***** debug *****
		std::cout << model_types[j].model_id << ", "                                // ***** debug *****
			<< model_types[j].model_name                                            // ***** debug *****
			<< std::endl;                                                           // ***** debug *****
	}                                                                               // ***** debug *****
	std::cout << std::endl;                                                        // ***** debug *****
//////////////////////////////7
///////////////////////////7
	// print component_id, component_name e quantity
	std::cout << "Dentro i vettori dentro models_infos:\n";                         // ***** debug *****
	for (auto vec : models_infos)                                                   // ***** debug *****
	{
		// ***** debug *****
		for (auto v : vec)                                                          // ***** debug *****
		{                                                                           // ***** debug *****
			std::cout << v.id << ", "                                     // ***** debug *****
				<< v.name << ", "                                         // ***** debug *****
				<< v.quantity << std::endl;                                         // ***** debug *****
		}                                                                           // ***** debug *****
		std::cout << std::endl;                                                     // ***** debug *****
	}         */                                                                      // ***** debug *****
//////////////////////////////////77
	//(2) riempio components_infos
	std::ifstream ist_info {"components_info.dat"};
	if (!ist_info)
		throw Invalid();

	// store component_id, component_name, delivery_time (file components_info.dat)
	int component_id;
	std::string component_name;
	double delivery_time;
	ist_info >> differentPrice[0] >> differentPrice[1]  >>differentPrice[2] ;
	while (ist_info >> component_id >> component_name >> delivery_time)
		components_infos.push_back(component_info{component_id, component_name, delivery_time});   // store

	ist_info.close();    // chiudo ist_info

	// print component_id, component_name, delivery_time
	/*std::cout << "Dentro components_infos:\n";                                      // ***** debug *****
	for (auto c : components_infos)                                                 // ***** debug *****
	{                                                                               // ***** debug *****
		std::cout << c.component_id << ", "                                         // ***** debug *****
			<< c.component_name << ", "                                             // ***** debug *****
			<< c.delivery_time << std::endl;                                        // ***** debug *****
	}                                                                               // ***** debug *****
	std::cout << std::endl;   */                                                    // ***** debug *****
}
}

