//
// Created by Esteban Lanter on 01.01.21.
//

#include "Engine.h"
#include "OrderBook.h"



//outwards
// cancels
void Engine::cancel_limit_order_bid(int order_id, int volume, bool  penalize){
    try {
        lob.cancel_limit_order_bid(order_id, volume, penalize);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};
void Engine::cancel_limit_order_ask(int order_id, int volume, bool  penalize){
    try{
        lob.cancel_limit_order_ask(order_id, volume, penalize);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};


// deletes
void Engine::delete_limit_order_bid(int order_id){
    try{
        lob.delete_limit_order_bid(order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

};
void Engine::delete_limit_order_ask(int order_id){
    try{
        lob.delete_limit_order_ask(order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};

// match market
void Engine::match_market_order_bid(int volume){
    try{
        lob.match_market_order_bid(volume);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};
void Engine::match_market_order_ask(int volume){
    try{
        lob.match_market_order_ask(volume);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};

// replacements
void Engine::replace_limit_order_bid(int order_id_old, int order_id_new, int volume_new, int penalize){
    try{
        lob.replace_limit_order_bid(order_id_old, order_id_new, volume_new, penalize);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};
void Engine::replace_limit_order_ask(int order_id_old, int order_id_new, int volume_new, int penalize){
    try{
        lob.replace_limit_order_ask(order_id_old, order_id_new, volume_new, penalize);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};

// match and book book
void Engine::match_book_limit_order_bid(int price, int volume, int order_id){
    try{
        lob.match_book_limit_order_bid(price, volume, order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};
void Engine::match_book_limit_order_ask(int price, int volume, int order_id){
    try{
        lob.match_book_limit_order_ask(price, volume, order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

};
void Engine::book_limit_order_bid(int price, int volume, int order_id){
    try{
        lob.book_limit_order_bid(price, volume, order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};
void Engine::book_limit_order_ask(int price, int volume, int order_id){
    try{
        lob.book_limit_order_ask(price, volume, order_id);
    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
};

void Engine::print_book(int maxdepth){
    return lob.print_book(maxdepth);
};

int * Engine::get_book(int maxdepth){
    return lob.get_book(maxdepth);
};

std::vector<int> Engine::get_book_bids(int maxdepth){
    return lob.get_book_bids(maxdepth);
};
std::vector<int> Engine::get_book_asks(int maxdepth){
    return lob.get_book_asks(maxdepth);
};

