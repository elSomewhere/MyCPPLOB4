//
// Created by Esteban Lanter on 24.12.20.
//

#include "PriceNode.h"
#include "Order.h"
#include <algorithm>

tsl::ordered_set<std::shared_ptr<Order>> PriceNode::get_orders_queue(){
    return orders_queue;
};


std::map<int, std::shared_ptr<PriceNode>> PriceNode::all_orders;



std::shared_ptr<Order> PriceNode::decrease_order_volume(const int &order_id, const int &volume, const bool &penalize){
    std::shared_ptr<Order> to_be_modified = get_order(order_id);
    int to_modify = std::min(volume, to_be_modified->get_volume());
    if(to_modify == to_be_modified->get_volume()){
        // volume too high, we instead remove completely
        std::shared_ptr<Order> res = PriceNode::remove_order(order_id);

        return res;
    }else{
        to_be_modified->set_volume(to_be_modified->get_volume()-to_modify);
        if(penalize){
            std::shared_ptr<Order> res = remove_order(order_id);
            PriceNode::orders_queue.insert(res);
        }
        return to_be_modified;
    }
};


void PriceNode::remove_order_references(){
    std::vector<int> all_order_ids = get_order_ids();
    for(std::vector<int>::iterator it = all_order_ids.begin(); it != all_order_ids.end(); ++it){
        // deletes shared pointer to this...
        all_orders.erase(*it);
    }
}

std::shared_ptr<PriceNode> PriceNode::get_price_via_order(const int &order_id){
    return PriceNode::all_orders[order_id];
};

std::shared_ptr<Order> PriceNode::get_order(const int &order_id){
    //print_queue();
    // this is supposed to be log in size actually

    auto pair = std::equal_range(orders_queue.begin(),orders_queue.end(), order_id, OrderComparator());
    tsl::ordered_set<std::shared_ptr<Order>>::iterator it = pair.first;
    return *it;
};

std::shared_ptr<Order> PriceNode::add_order(const int &order_id, const int &volume){
    // note: price node inherits from enable_shared_from_this
    // this will allow the class to return a shared pointer of self
    // important: this pattern willl only work if the corresponding pricenode object wil be managed itself (e.g. encapsulated) in a shared pointer
    // else you'll get a weird "weak pionter" exception
    std::shared_ptr<Order> order = std::make_shared<Order>(volume, order_id);
    PriceNode::orders_queue.insert(order);
    all_orders.insert({order_id, shared_from_this()});
    return order;
};

std::shared_ptr<Order> PriceNode::remove_order(const int &order_id){
    //std::cout<<"start remove, all orders size is "<<all_orders.size()<<" and queue size is "<<PriceNode::orders_queue.size()<<std::endl;
    std::shared_ptr<Order> order = PriceNode::get_order(order_id);
    PriceNode::orders_queue.erase(order);
    all_orders.erase(order_id);
    return order;
};

std::shared_ptr<Order> PriceNode::remove_order(std::shared_ptr<Order> order){
    PriceNode::orders_queue.erase(order);
    all_orders.erase(order->get_order_id());
    return order;
};


std::shared_ptr<Order> PriceNode::replace_order(const int &order_id, const int &order_id_new, const int &volume_new, const int &penalize){
    if(penalize){
        // delete old one and add new one which naturally falls into the end
        remove_order(order_id);
        add_order(order_id_new, volume_new);
    }else{
        // get position of old order
        auto pair = std::equal_range(orders_queue.begin(),orders_queue.end(), order_id, OrderComparator());
        remove_order(order_id);
        // Insert the value before pos shifting all the elements on the right of pos (including pos) one position to the right.
        std::shared_ptr<Order> order = std::make_shared<Order>(volume_new, order_id);
        PriceNode::orders_queue.insert_at_position(pair.first, order);
    }
};

int PriceNode::get_total_volume(){
    int total = 0;
    for(tsl::ordered_set<std::shared_ptr<Order>>::iterator it=orders_queue.begin(); it!=orders_queue.end(); ++it){
        std::shared_ptr<Order> order = *it;
        total += order->get_volume();
    }
    return total;
};

int PriceNode::get_price(){
    return PriceNode::price;
};


std::vector<int> PriceNode::get_order_ids(){

    std::vector<int> orders_ids_in_node;
    int order_id;
    tsl::ordered_set<std::shared_ptr<Order>>::iterator it;
    //orders_queue.size();
    it = orders_queue.begin();
    for(it=orders_queue.begin(); it!=orders_queue.end(); ++it){

        std::shared_ptr<Order> order = *it;
        order_id = order->get_order_id();
        orders_ids_in_node.push_back(order_id);
    }
    return orders_ids_in_node;
}

int PriceNode::clear_quantity(const int &volume){

    int remaining_volume = volume;
    std::vector<int> consumed_orders_order_id;
    for(tsl::ordered_set<std::shared_ptr<Order>>::iterator it=PriceNode::orders_queue.begin(); it!=PriceNode::orders_queue.end() && remaining_volume>0; ++it){
        std::shared_ptr<Order> order = *it;
        int to_fill = std::min(remaining_volume, order->get_volume());
        order->set_volume(order->get_volume()-to_fill);
        if(order->get_volume()==0){
            int order_id = order->get_order_id();
            consumed_orders_order_id.push_back(order_id);
        }
        remaining_volume = remaining_volume - to_fill;
        if(remaining_volume==0){
            break;
        }
    }
    // erase the order id
    for (std::vector<int>::iterator it = consumed_orders_order_id.begin(); it != consumed_orders_order_id.end(); it++ ){
        // remove from sorted orders list
        remove_order(*it);
    }
    return remaining_volume;
}

void PriceNode::print_queue(){
    std::vector<int> all_order_ids = get_order_ids();
    for(std::vector<int>::iterator it = all_order_ids.begin(); it != all_order_ids.end(); ++it){
    }
}