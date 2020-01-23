/*
 * Structure.h
 *
 *  Created on: 20 gen 2020
 *      Author: paolo
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_
#include <iostream>



struct components
{   // per leggere le informazioni sui componenti nei file dei modelli
    int id;                               // [model1.dat] (esempio)
    std::string name;
    int quantity;
    int status;// 0 da orinare 1 ordinato 2 pronto
    int monthsLeft;


    //std::ostream& os, const components& c
};

struct orderInit {   // per leggere gli ordini su orders.dat
    //order(int t, int m, int q) : time_stamp{t}, model_id{m}, quantity_ordered{q} {}

    int time_stamp;
    int model_id;
    int quantity_ordered;
    std::string model_name;
    std::vector<components> orderComponents;
};

struct model
{   // per leggere il nome del modello e l'id
    int model_id;                                       // [model1.dat] (esempio)
    std::string model_name;
};

struct component_info
{   // per leggere le informazioni dei componenti su components_info.dat
    int component_id;                                   // components_info.dat
    std::string component_name;
    double delivery_time;
};


inline std::ostream& operator<< (std::ostream& os, const orderInit& o ) {
    os << " time stamp: " << o.time_stamp << " model_id: "
       << o.model_id      << " quantity: " << o.quantity_ordered
       << " model_name: " << o.model_name << "\n";
    return os;
}

inline std::ostream& operator<< (std::ostream& os,const components& o ) {
    os << " C.ID("<<o.id << ") C.Name: " << o.name
       << " Quantit�: "<< o.quantity <<  "\n"
       <<"                                          "
	   << "Status: " << o.status <<" Mesi: "<< o.monthsLeft;
    return os;
}


#endif /* STRUCTURE_H_ */
