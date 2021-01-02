//
// Created by Esteban Lanter on 24.12.20.
//

#ifndef MYCPPLOB4_PRICENODE_H
#define MYCPPLOB4_PRICENODE_H

#include <unordered_map>
#include "../tsl/ordered_map.h"
#include "../tsl/ordered_set.h"
#include <set>
#include <map>

// this is a forward declaration
class Order;

class PriceNode : public std::enable_shared_from_this<PriceNode>{
private:
    const int price;

    // id -> order
    //tsl::ordered_map<int, std::shared_ptr<Order>> orders_queue;

    // id -> order
    tsl::ordered_set<std::shared_ptr<Order>> orders_queue;
    //std::set<std::shared_ptr<Order>> orders_queue;
    static std::map<int, std::shared_ptr<PriceNode>> all_orders;

public:
    PriceNode(int price):
        price(price){};
    std::shared_ptr<Order> get_order(const int &order_id);
    std::shared_ptr<Order> add_order(const int &order_id, const int &volume);
    std::shared_ptr<Order> remove_order(const int &order_id);
    std::shared_ptr<Order> remove_order(std::shared_ptr<Order> order);
    std::shared_ptr<Order> decrease_order_volume(const int &order_id, const int &volume, const bool &penalize);
    std::shared_ptr<Order> replace_order(const int &order_id, const int &order_id_new, const int &volume_new, const int &penalize);
    int get_total_volume();
    int get_price();
    int clear_quantity(const int &volume);
    std::vector<int> empty_price_node();
    std::vector<int> get_order_ids();
    static std::shared_ptr<PriceNode> get_price_via_order(const int &order_id);
    tsl::ordered_set<std::shared_ptr<Order>> get_orders_queue();
    void remove_order_references();
    void print_queue();
};

// bids: largest on top
// large to small
struct PriceNodeComparatorBids{
    bool operator() (std::shared_ptr<PriceNode> const& lhs, int const& rhs ) const
    {
        return lhs->get_price() > rhs;
    }
    bool operator() (int const& lhs, std::shared_ptr<PriceNode> const& rhs ) const
    {
        return lhs > rhs->get_price();
    }
    bool operator() (std::shared_ptr<PriceNode> const& p, std::shared_ptr<PriceNode> const& o ) const
    {
        return p->get_price() > o->get_price();
    }
};

// asks: smallest on top
// small to large

// return true if the first argument is considered to go before the second
struct PriceNodeComparatorAsks{
    bool operator() (std::shared_ptr<PriceNode> const& lhs, int const& rhs ) const
    {
        return lhs->get_price() < rhs;
    }
    bool operator() (int const& lhs, std::shared_ptr<PriceNode> const& rhs ) const
    {
        return lhs < rhs->get_price();
    }
    bool operator() (std::shared_ptr<PriceNode> const& p, std::shared_ptr<PriceNode> const& o ) const
    {
        return p->get_price() < o->get_price();
    }
};

#endif //MYCPPLOB4_PRICENODE_H
