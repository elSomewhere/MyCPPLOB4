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



//print
void Engine::print_book(int maxdepth){
    int counter = 0;
    std::shared_ptr<PriceNode> pricenode;
    std::cout<<"___ASKS___"<< std::endl;
    for(std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator it=lob.get_orderbook_asks().begin(); it!=lob.get_orderbook_asks().end() && counter < maxdepth; ++it){
        pricenode = *it;
        std::cout<<"price: "<< pricenode->get_price() << " volume: " << pricenode->get_total_volume()<<std::endl;
        counter += 1;
    }
    counter = 0;
    std::cout<<"___BIDS___"<< std::endl;
    for(std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids>::iterator it=lob.get_orderbook_bids().begin(); it!=lob.get_orderbook_bids().end() && counter < maxdepth; ++it){
        pricenode = *it;
        std::cout<<"price: "<< pricenode->get_price() << " volume: " << pricenode->get_total_volume()<<std::endl;
        counter += 1;
    }
    std::cout<<"==========="<< std::endl;
};

int * Engine::get_book(int maxdepth){
    int counter = 0;
    int res[maxdepth*2*2];
    std::shared_ptr<PriceNode> pricenode;
    for(std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator it=lob.get_orderbook_asks().begin(); it!=lob.get_orderbook_asks().end() && counter!=maxdepth*2; ++it){
        pricenode = *it;
        res[counter] = pricenode->get_price();
        res[counter+1] = pricenode->get_total_volume();
        counter += 2;
    }
    for(; counter < maxdepth*2; ++counter){
        res[counter] = -1;
        res[counter+1] = -1;
    }
    counter = maxdepth*2;
    for(std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids>::iterator it=lob.get_orderbook_bids().begin(); it!=lob.get_orderbook_bids().end() && counter!=(maxdepth*2*2); ++it){
        pricenode = *it;
        res[counter] = pricenode->get_price();
        res[counter+1] = pricenode->get_total_volume();
        counter += 2;
    }
    for(; counter < maxdepth*2*2; ++counter){
        res[counter] = -1;
        res[counter+1] = -1;
    }
    for (int i = 0; i<maxdepth*2*2; ++i){
        std::cout << res[i] << ' ';
    }
    return res;
};