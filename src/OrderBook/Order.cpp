//
// Created by Esteban Lanter on 24.12.20.
//

#include "Order.h"

int Order::get_volume() {
    return Order::volume;
}

void Order::set_volume(int volume){
    Order::volume = volume;
}

int Order::get_order_id() {
    return Order::order_id;
}
