//
// Created by Esteban Lanter on 01.01.21.
//

#include "Engine.h"
#include "OrderBook.h"



//outwards
// cancels
void Engine::cancel_limit_order_bid(int order_id, int volume, bool  penalize){
    lob.cancel_limit_order_bid(order_id, volume, penalize);
};
void Engine::cancel_limit_order_ask(int order_id, int volume, bool  penalize){
    lob.cancel_limit_order_ask(order_id, volume, penalize);
};

// deletes
void Engine::delete_limit_order_bid(int order_id){
    lob.delete_limit_order_bid(order_id);
};
void Engine::delete_limit_order_ask(int order_id){
    lob.delete_limit_order_ask(order_id);
};

// match market
void Engine::match_market_order_bid(int volume){
    lob.match_market_order_bid(volume);
};
void Engine::match_market_order_ask(int volume){
    lob.match_market_order_ask(volume);
};

// replacements
void Engine::replace_limit_order_bid(int order_id_old, int order_id_new, int volume_new, int penalize){
    lob.replace_limit_order_bid(order_id_old, order_id_new, volume_new, penalize);
};
void Engine::replace_limit_order_ask(int order_id_old, int order_id_new, int volume_new, int penalize){
    lob.replace_limit_order_ask(order_id_old, order_id_new, volume_new, penalize);
};

// match and book book
void Engine::match_book_limit_order_bid(int price, int volume, int order_id){
    lob.match_book_limit_order_bid(price, volume, order_id);
};
void Engine::match_book_limit_order_ask(int price, int volume, int order_id){
    lob.match_book_limit_order_ask(price, volume, order_id);
};

void Engine::print_book(int maxdepth){
    return lob.print_book(maxdepth);
};
int * Engine::get_book(int maxdepth){
    return lob.get_book(maxdepth);
};

