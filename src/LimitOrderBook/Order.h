//
// Created by Esteban Lanter on 24.12.20.
//

#ifndef MYCPPLOB4_ORDER_H
#define MYCPPLOB4_ORDER_H

#include "PriceNode.h"
#include <memory>
#include <unordered_set>
//https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c
class PriceNode;

class Order{
private:
    int volume;
    const int order_id;

public:
    Order(int volume, int order_id):
        volume(volume), order_id(order_id){}
    int get_volume();
    int get_order_id();
    void set_volume(int volume);
};


struct OrderComparator{
    bool operator() (std::shared_ptr<Order> const& o, int const& p ) const
    {
        return o->get_order_id() < p;
    }
    bool operator() (int const& p, std::shared_ptr<Order> const& o ) const
    {
        return p < o->get_order_id();
    }
    bool operator() (std::shared_ptr<Order> const& p, std::shared_ptr<Order> const& o ) const
    {
        return p->get_order_id() == o->get_order_id();
    }
};


#endif //MYCPPLOB4_ORDER_H
