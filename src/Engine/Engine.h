//
// Created by Esteban Lanter on 01.01.21.
//

#ifndef MYCPPLOB4_ENGINE_H
#define MYCPPLOB4_ENGINE_H

#include "OrderBook.h"

class Engine {
private:
    OrderBook lob;
public:
    Engine(int *max_book_width, int *max_order_capacity):
            lob(max_book_width, max_order_capacity){};

    //outwards
    // cancels
    void cancel_limit_order_bid(int order_id, int volume, bool  penalize);
    void cancel_limit_order_ask(int order_id, int volume, bool  penalize);

    // deletes
    void delete_limit_order_bid(int order_id);
    void delete_limit_order_ask(int order_id);

    // match market
    void match_market_order_bid(int volume);
    void match_market_order_ask(int volume);

    // replacements
    void replace_limit_order_bid(int order_id_old, int order_id_new, int volume_new, int penalize);
    void replace_limit_order_ask(int order_id_old, int order_id_new, int volume_new, int penalize);

    // match and book book
    void match_book_limit_order_bid(int price, int volume, int order_id);
    void match_book_limit_order_ask(int price, int volume, int order_id);

    // match and book book
    void book_limit_order_bid(int price, int volume, int order_id);
    void book_limit_order_ask(int price, int volume, int order_id);

    void print_book(int maxdepth);
    int * get_book(int maxdepth);
    std::vector<int> get_book_bids(int maxdepth);
    std::vector<int> get_book_asks(int maxdepth);
};


#endif //MYCPPLOB4_ENGINE_H
