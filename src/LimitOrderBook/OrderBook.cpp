//
// Created by Esteban Lanter on 24.12.20.
//

#include <iostream>
#include "OrderBook.h"
#include "Order.h"
#include <typeinfo>



// cancels
std::shared_ptr<Order> OrderBook::cancel_limit_order_bid(int order_id, int volume, bool penalize){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id);
    std::shared_ptr<Order> res = pricenode->decrease_order_volume(order_id, volume, penalize);
    if(pricenode->get_total_volume() == 0){
        remove_pricenode_bid(pricenode);
    }
    return res;
};

std::shared_ptr<Order> OrderBook::cancel_limit_order_ask(int order_id, int volume, bool penalize){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id);
    std::shared_ptr<Order> res = pricenode->decrease_order_volume(order_id, volume, penalize);
    if(pricenode->get_total_volume() == 0){
        remove_pricenode_ask(pricenode);
    }
    return res;
};



// deletes
std::shared_ptr<Order> OrderBook::delete_limit_order_bid(int order_id){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id);
    std::shared_ptr<Order> res = pricenode->remove_order(order_id);
    if(pricenode->get_total_volume() == 0){
        remove_pricenode_bid(pricenode);
    }
    return res;
};

std::shared_ptr<Order> OrderBook::delete_limit_order_ask(int order_id){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id);
    std::shared_ptr<Order> res = pricenode->remove_order(order_id);
    if(pricenode->get_total_volume() == 0){
        remove_pricenode_ask(pricenode);
    }
    return res;
};



// removals
void OrderBook::remove_pricenode_bid(std::shared_ptr<PriceNode> pricenode){
    pricenode->remove_order_references();
    orderbook_bids.erase(pricenode);
};

void OrderBook::remove_pricenode_ask(std::shared_ptr<PriceNode> pricenode){
    pricenode->remove_order_references();
    orderbook_asks.erase(pricenode);
};

// removals
std::shared_ptr<PriceNode> OrderBook::add_pricenode_bid(int price){
    std::shared_ptr<PriceNode> pricenode = std::make_shared<PriceNode>(price);
    orderbook_bids.insert(pricenode);
    return pricenode;
};

std::shared_ptr<PriceNode> OrderBook::add_pricenode_ask(int price){
    std::shared_ptr<PriceNode> pricenode = std::make_shared<PriceNode>(price);
    orderbook_asks.insert(pricenode);
    return pricenode;
};



// markets
int OrderBook::match_market_order_bid(int volume){
    int remaining_volume = volume;
    std::vector<std::shared_ptr<PriceNode>> to_remove_pricenodes;
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator it;
    std::shared_ptr<PriceNode> pricenode;
    for(it=orderbook_asks.begin(); it!=orderbook_asks.end(); ++it){
        pricenode = *it;
        if(remaining_volume < 0){
            break;
        }
        remaining_volume = pricenode->clear_quantity(remaining_volume);
        if(pricenode->get_total_volume()==0){
            to_remove_pricenodes.push_back(pricenode);
        }
    }
    std::vector<std::shared_ptr<PriceNode>>::iterator it_to_remove_pricenodes;
    for(it_to_remove_pricenodes = to_remove_pricenodes.begin(); it_to_remove_pricenodes != to_remove_pricenodes.end(); it_to_remove_pricenodes++){
        OrderBook::remove_pricenode_ask(*it_to_remove_pricenodes);
    }
    return remaining_volume;
};


int OrderBook::match_market_order_ask(int volume){
    int remaining_volume = volume;
    std::vector<std::shared_ptr<PriceNode>> to_remove_pricenodes;
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator it;
    std::shared_ptr<PriceNode> pricenode;
    for(it=orderbook_bids.begin(); it!=orderbook_bids.end(); ++it){
        pricenode = *it;
        if(remaining_volume < 0){
            break;
        }
        remaining_volume = pricenode->clear_quantity(remaining_volume);
        if(pricenode->get_total_volume()==0){
            to_remove_pricenodes.push_back(pricenode);
        }
    }
    std::vector<std::shared_ptr<PriceNode>>::iterator it_to_remove_pricenodes;
    for(it_to_remove_pricenodes = to_remove_pricenodes.begin(); it_to_remove_pricenodes != to_remove_pricenodes.end(); it_to_remove_pricenodes++){
        OrderBook::remove_pricenode_bid(*it_to_remove_pricenodes);
    }
};




// limits
int OrderBook::match_limit_order_bid(int price, int volume){
    int remaining_volume = volume;
    std::vector<std::shared_ptr<PriceNode>> to_remove_pricenodes;
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator it;
    std::shared_ptr<PriceNode> pricenode;
    for(it=orderbook_asks.begin(); it!=orderbook_asks.end(); ++it){
        pricenode = *it;
        if(remaining_volume < 0){
            break;
        }
        if(pricenode->get_price()>price){
            break;
        }
        remaining_volume = pricenode->clear_quantity(remaining_volume);
        if(pricenode->get_total_volume()==0){
            to_remove_pricenodes.push_back(pricenode);
        }
    }
    std::vector<std::shared_ptr<PriceNode>>::iterator it_to_remove_pricenodes;
    for(it_to_remove_pricenodes = to_remove_pricenodes.begin(); it_to_remove_pricenodes != to_remove_pricenodes.end(); it_to_remove_pricenodes++){
        OrderBook::remove_pricenode_ask(*it_to_remove_pricenodes);
    }
    return remaining_volume;
};



int OrderBook::match_limit_order_ask(int price, int volume){
    int remaining_volume = volume;
    std::vector<std::shared_ptr<PriceNode>> to_remove_pricenodes;
    std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids>::iterator it;
    std::shared_ptr<PriceNode> pricenode;
    for(it=orderbook_bids.begin(); it!=orderbook_bids.end(); ++it){
        pricenode = *it;
        if(remaining_volume < 0){
            break;
        }
        if(pricenode->get_price()<price){
            break;
        }
        remaining_volume = pricenode->clear_quantity(remaining_volume);
        if(pricenode->get_total_volume()==0){
            to_remove_pricenodes.push_back(pricenode);
        }
    }
    std::vector<std::shared_ptr<PriceNode>>::iterator it_to_remove_pricenodes;
    for(it_to_remove_pricenodes = to_remove_pricenodes.begin(); it_to_remove_pricenodes != to_remove_pricenodes.end(); it_to_remove_pricenodes++){
        OrderBook::remove_pricenode_bid(*it_to_remove_pricenodes);
    }
    return remaining_volume;
};




std::shared_ptr<Order> OrderBook::book_limit_order_bid(int price, int volume, int order_id){
    if(volume > 0){
        std::shared_ptr<Order> order;
        std::pair<std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids>::iterator,std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids>::iterator> bounds;
        bounds = std::equal_range(orderbook_bids.begin(),orderbook_bids.end(), price, PriceNodeComparatorBids());
        std::set<std::shared_ptr<PriceNode>>::iterator it = bounds.first;
        std::shared_ptr<PriceNode> pricenode;
        if(bounds.first == bounds.second){
            pricenode = add_pricenode_bid(price);
            order = pricenode->add_order(order_id, volume);
        }else{
            pricenode = *(bounds.first);
            order = pricenode->add_order(order_id, volume);
        }
        // now check the size of the price set and drop last if necessary
        if(max_order_capacity!=NULL){
            if(pricenode->get_orders_queue().size()>*max_order_capacity){
                // get id of last order
                tsl::ordered_set<std::shared_ptr<Order>>::iterator it_orders_last;
                it_orders_last = std::prev(pricenode->get_orders_queue().end());
                pricenode->remove_order(*it_orders_last);
            }
        }
        if(max_book_width!=NULL){
            if(orderbook_bids.size()>*max_book_width){
                std::set<std::shared_ptr<PriceNode>>::iterator it;
                it = std::prev(orderbook_bids.end());
                remove_pricenode_bid(*it);
            }
        }
        return order;
    }
    return NULL;
};


std::shared_ptr<Order> OrderBook::book_limit_order_ask(int price, int volume, int order_id){
    if(volume > 0){
        std::shared_ptr<Order> order;
        std::pair<std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator,std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks>::iterator> bounds;
        bounds = std::equal_range(orderbook_asks.begin(),orderbook_asks.end(), price, PriceNodeComparatorAsks());
        std::set<std::shared_ptr<PriceNode>>::iterator it = bounds.first;
        std::shared_ptr<PriceNode> pricenode;
        if(bounds.first == bounds.second){
            pricenode = add_pricenode_ask(price);
            order = pricenode->add_order(order_id, volume);
        }else{
            pricenode = *(bounds.first);
            order = pricenode->add_order(order_id, volume);
        }
        // now check the size of the price set and drop last if necessary
        if(max_order_capacity!=NULL){
            if(pricenode->get_orders_queue().size()>*max_order_capacity){
                // get id of last order
                tsl::ordered_set<std::shared_ptr<Order>>::iterator it_orders_last;
                it_orders_last = std::prev(pricenode->get_orders_queue().end());
                pricenode->remove_order(*it_orders_last);
            }
        }
        if(max_book_width!=NULL){
            if(orderbook_asks.size()>*max_book_width){
                std::set<std::shared_ptr<PriceNode>>::iterator it;
                it = std::prev(orderbook_asks.end());
                remove_pricenode_ask(*it);
            }
        }
        return order;
    }
    return NULL;
};


std::shared_ptr<Order> OrderBook::match_book_limit_order_bid(int price, int volume, int order_id){
    int remaining_vol = match_limit_order_bid(price, volume);
    std::shared_ptr<Order> res = book_limit_order_bid(price, remaining_vol, order_id);
    return res;
};
std::shared_ptr<Order> OrderBook::match_book_limit_order_ask(int price, int volume, int order_id){
    int remaining_vol = match_limit_order_ask(price, volume);
    std::shared_ptr<Order> res = book_limit_order_ask(price, remaining_vol, order_id);
    return res;
};



// replacements
std::shared_ptr<Order> OrderBook::replace_limit_order_bid(int order_id_old, int order_id_new, int volume_new, int penalize){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id_old);
    std::shared_ptr<Order> res = pricenode->replace_order(order_id_old, order_id_new, volume_new, penalize);
    return res;
};
std::shared_ptr<Order> OrderBook::replace_limit_order_ask(int order_id_old, int order_id_new, int volume_new, int penalize){
    std::shared_ptr<PriceNode> pricenode = PriceNode::get_price_via_order(order_id_old);
    std::shared_ptr<Order> res = pricenode->replace_order(order_id_old, order_id_new, volume_new, penalize);
    return res;
};

std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorBids> OrderBook::get_orderbook_bids(){
    return orderbook_bids;
};
std::set<std::shared_ptr<PriceNode>, PriceNodeComparatorAsks> OrderBook::get_orderbook_asks(){
    return orderbook_asks;
};
