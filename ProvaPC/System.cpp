//std::string FindFile(fMain.model_id);
//1 funzione che scopre il nome del file dove guardare FG
//1.2 Tramite il vettore formato
//2 funzione che associa al componente il tempo e la quantità e viene moltiplicata
//3 e poi carica tutto

//bisogna anche far tornare normali i target e aggiungere txt dopo!

//inizializzo model_name (per accedere ai file con i componenti)


//ARRIVAre allo stesso punto di oggi con una classe order

#include <vector>
#include <fstream>
#include <iostream>
#include "System.h"
#include "Order.h"
#include "orderInit.h"
//#include "component.h"

using namespace std;
namespace System {

class Invalid {};
class TargetNotFound{};

Warehouse::Warehouse()
: month{0},orderList{0}
{

}
//Sincronizzo il mese del main con quello della classe Warehouse
void Warehouse::Syncrnize(int month){


}
//Inizializzo un nuovo ordine
void Warehouse::addOrder(orderInit fMain){
Order newOrder(fMain);
newOrder.PrintOrder();
orderList.push_back(newOrder);

}
//Scorro i vari ordini e aggiorno la situzione del magazzino
void Warehouse::Updates(){


}
//Stampo situazione del magazzino (da definire)
void Warehouse::PrintAll(){

}
