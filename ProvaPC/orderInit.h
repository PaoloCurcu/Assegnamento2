#ifndef ORDER_H
#define ORDER_H

#include "component.h"
#include <iostream>
#include <vector>

struct orderInit {   // per leggere gli ordini su orders.dat
    //order(int t, int m, int q) : time_stamp{t}, model_id{m}, quantity_ordered{q} {}

    int time_stamp;
    int model_id;
    int quantity_ordered;
    std::string model_name;
    std::vector<component> orderComponents;

};


inline std::ostream& operator<< (std::ostream& os, const orderInit& o) {
    os << " time stamp: " << o.time_stamp << " model_id: " << o.model_id << " quantity: " << o.quantity_ordered
    		<< " model_name: " << o.model_name << "\n";
    return os;
};

#endif
