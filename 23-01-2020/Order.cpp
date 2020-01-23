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

//Costruttore di default di order
Order::Order()
: time_stamp{0}, model_id{0}, quantity_ordered{0}, price{0}{
}

//costruttore di Order: Inizializza un ordine composto da un numero di un certo tipo di modello
//es 4 lavatrici.
//La parte più importante è l'inizializzazione del vettore di componenti al suo interno
Order::Order(orderInit fMain,const vector<vector<components>> &models_infos,const vector<component_info> &components_infos)
: time_stamp{fMain.time_stamp},
model_id{fMain.model_id},
quantity_ordered{fMain.quantity_ordered},
price{0}
{
for(auto mod : models_infos ){//scorro il vettore con le info sui modelli
	if(model_id==mod[0].id){
		model_name =mod[0].name;
		//price = mod[0].quantity;//Trovo il modello che mi serve
	//DEVO SALTARE IL PRIMO che non è un componente vero ma per riconoscere il modello
		for(unsigned int i=1; i<mod.size();i++){//scorro i componenti all'interno del file saltando il primo

			mod[i].quantity=mod[i].quantity*quantity_ordered;
			for(auto info : components_infos){  //scoroo il vettore con le informazioni dei componenti
//cerco all' interno del vettore con le informazioni dei vari componenti il componente che mi serve (tramite l'id)
				if(mod[i].id==info.component_id)
					mod[i].monthsLeft=info.delivery_time;
			}
		orderComponents.push_back(mod[i]);
		}
//Metto al primo posto dell'array di componenti del modello il componente che ci mette più tempo ad arrivare:
//questo perchè mi serve come riferimento. Così so dove trovarlo qualunque sia il modello.
	components tmp;
	int indexMax = 0;
	//Trovo quello che ci mette più tempo
	for(unsigned int i =0; i<orderComponents.size();i++){
		 if(orderComponents[i].monthsLeft>orderComponents[indexMax].monthsLeft)
			 indexMax=i;
	}
	//Effettuo lo scambio
	tmp = orderComponents[0];
	orderComponents[0] = orderComponents[indexMax];
	orderComponents[indexMax]= tmp;
	}
}

}
//Si occupa di aggiornare il tempo di arrivo dei componenti di un modello e il loro stato una volta arrivati.
//Ritorna true quando tutti i componenti del modello sono pronti ormai da un mese.
//Come faccio a capirlo? Vado per esclusione. Se entra in una qualsiasi delle casistiche elencate
//significa che almeno un componente non è pronto e metto "verify" false.
//Tutti pronti: verify true.

bool Order::updates(){
bool verify=true;
for(unsigned int i=0;i<orderComponents.size();i++){
	if(orderComponents[i].status==1){
		if(orderComponents[i].monthsLeft==0)
			orderComponents[i].status=2;
		else{
			orderComponents[i].monthsLeft--;
			verify = false;
		}
	}
	if(orderComponents[i].status==0)
		verify = false;
}
return verify;
}

//Si occupa di ordinare i componenti necessari secondo la politica "scalata"
//ovvero ordino prima i più vecchi e poi procedo in modo che tutti i componenti arrivino lo stesso mese
//Questa strategia consente di distibuire le spese nel tempo per mettendo di incassare i soldi dei
//modelli finiti.

//ritorna un intero con il numero totale di pezzi ordinati per questo Order
//(Serve per fare il conto degli ordini totali del mese e usare il prezzo giusto)

int Order::order_components(){
int tmp=0;//Per contare i componenti ordinati per questo ordine
if(orderComponents[0].status==0){
	orderComponents[0].status=1;
	tmp = orderComponents[0].quantity;
}
	//ordina il componente più vecchio
for(unsigned int i=0;i<orderComponents.size();i++){
	if(orderComponents[i].monthsLeft==orderComponents[0].monthsLeft)
		if(orderComponents[i].status==0){
			orderComponents[i].status=1;
			tmp = orderComponents[i].quantity;
		}
}
return tmp;
}

//Stampa le variabili esemplare di un ordine
void Order::PrintOrder(){
	cout <<  " " << quantity_ordered << " "
		 <<  model_name
		 << " Al mese " << time_stamp
	     << " (ID: "        << model_id <<")"
		 << ":\n  Componenti:"
		 << endl;
	for(components ro: orderComponents)
	cout<< "     °" <<  ro    << endl;
}
//Funzioni che ritornano lo stato delle variabili esemplare
// al di fuori della classe Order.

string Order::modelName(){return model_name;}
int Order::timeStamp(){return time_stamp;}
int Order::modelId(){return model_id;}
int Order::quantityOrdered(){return quantity_ordered;}







