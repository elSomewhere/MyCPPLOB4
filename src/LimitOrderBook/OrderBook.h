//
// Created by Esteban Lanter on 24.12.20.
//

#ifndef MYCPPLOB4_ORDERBOOK_H
#define MYCPPLOB4_ORDERBOOK_H
#include "PriceNode.h"
#include <map>
#include <unordered_set>
class OrderBook {
private:

    // price to price
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids> orderbook_bids;
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks> orderbook_asks;

    // order id to price
    const int * max_book_width;
    const int * max_order_capacity;

public:
    OrderBook(int *max_book_width, int *max_order_capacity):
            max_book_width(max_book_width), max_order_capacity(max_order_capacity){};

    // lowlevel
    // getters
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids> get_orderbook_bids();
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks> get_orderbook_asks();
    // Additions
    std::shared_ptr<PriceNode> add_pricenode_bid(int price);
    std::shared_ptr<PriceNode> add_pricenode_ask(int price);
    // removals
    void remove_pricenode_bid(std::shared_ptr<PriceNode> pricenode);
    void remove_pricenode_ask(std::shared_ptr<PriceNode> pricenode);
    // match limit
    int match_limit_order_bid(int price, int volume);
    int match_limit_order_ask(int price, int volume);
    // bookings
    std::shared_ptr<Order> book_limit_order_bid(int price, int volume, int order_id);
    std::shared_ptr<Order> book_limit_order_ask(int price, int volume, int order_id);



    //outwards
    // cancels
    std::shared_ptr<Order> cancel_limit_order_bid(int order_id, int volume, bool  penalize);
    std::shared_ptr<Order> cancel_limit_order_ask(int order_id, int volume, bool  penalize);

    // deletes
    std::shared_ptr<Order> delete_limit_order_bid(int order_id);
    std::shared_ptr<Order> delete_limit_order_ask(int order_id);

    // match market
    int match_market_order_bid(int volume);
    int match_market_order_ask(int volume);

    // replacements
    std::shared_ptr<Order> replace_limit_order_bid(int order_id_old, int order_id_new, int volume_new, int penalize);
    std::shared_ptr<Order> replace_limit_order_ask(int order_id_old, int order_id_new, int volume_new, int penalize);

    // match and book book
    std::shared_ptr<Order> match_book_limit_order_bid(int price, int volume, int order_id);
    std::shared_ptr<Order> match_book_limit_order_ask(int price, int volume, int order_id);
};


#endif //MYCPPLOB4_ORDERBOOK_H
