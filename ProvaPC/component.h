#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>


struct component
{   // per leggere le informazioni sui componenti nei file dei modelli
    int id;                               // [model1.dat] (esempio)
    std::string name;
    int quantity;
    int status;// 0 da orinare 1 ordinato 2 pronto
    int monthsLeft;
};

inline std::ostream& operator<< (std::ostream& os, const component& c) {
    os << " C.ID("<<c.id << ") C.Name: " << c.name << " Quantità: " << c.quantity ;
    return os;
};

#endif
