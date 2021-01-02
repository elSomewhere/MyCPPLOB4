#include <iostream>
#include "Order.h"
#include "Engine.h"

int main() {

//    std::shared_ptr<PriceNode> p1 = std::make_shared<PriceNode>(100);
//    p1->add_order(1, 100);
//    p1->add_order(2, 100);
//    p1->add_order(3, 100);
//    std::cout<<p1->get_total_volume()<<std::endl;



    int max_book_width = 100;
    int max_order_capacity = 100;
    Engine lob(&max_book_width, &max_order_capacity);
//    // asks
//    std::cout<<"========Add asks"<<std::endl;
//    lob.book_limit_order_ask(100, 1, 1);
//    lob.print_book(10);
//    lob.book_limit_order_ask(50, 2, 2);
//    lob.print_book(10);
//    lob.book_limit_order_ask(100, 3, 3);
//    lob.print_book(10);
//    lob.book_limit_order_ask(50, 4, 4);
//    lob.print_book(10);
//    lob.book_limit_order_ask(150, 5, 5);
//    lob.print_book(10);
//    lob.book_limit_order_ask(25, 6, 6);
//    lob.print_book(10);
//    lob.book_limit_order_ask(25, 16, 7);
//    lob.print_book(10);
//    lob.book_limit_order_ask(100, 56, 8);
//    lob.print_book(10);
//    lob.book_limit_order_ask(150, 156, 9);
//    lob.print_book(10);
//    lob.book_limit_order_ask(200, 256, 9);
//    lob.print_book(10);
//    lob.book_limit_order_ask(111, 111, 9);
//    lob.print_book(10);
//    // bids
//    std::cout<<"========Add bids"<<std::endl;
//    lob.book_limit_order_bid(100, 1, 1);
//    lob.print_book(10);
//    lob.book_limit_order_bid(50, 2, 2);
//    lob.print_book(10);
//    lob.book_limit_order_bid(100, 3, 3);
//    lob.print_book(10);
//    lob.book_limit_order_bid(50, 4, 4);
//    lob.print_book(10);
//    lob.book_limit_order_bid(150, 5, 5);
//    lob.print_book(10);
//    lob.book_limit_order_bid(25, 6, 6);
//    lob.print_book(10);
//    lob.book_limit_order_bid(25, 16, 7);
//    lob.print_book(10);
//    lob.book_limit_order_bid(100, 56, 8);
//    lob.print_book(10);
//    lob.book_limit_order_bid(150, 156, 9);
//    lob.print_book(10);
//    lob.book_limit_order_bid(200, 256, 9);
//    lob.print_book(10);
//    lob.book_limit_order_bid(111, 111, 9);
//    lob.print_book(10);



    lob.match_book_limit_order_ask(200, 100, 1);
    lob.match_book_limit_order_ask(100, 100, 2);
    lob.match_book_limit_order_ask(300, 100, 3);
    lob.print_book(10);
    lob.match_book_limit_order_bid(50, 100, 4);
    lob.print_book(10);
    lob.match_book_limit_order_bid(150, 50, 5);
    lob.print_book(10);
    lob.match_book_limit_order_bid(350, 200, 6);
    std::cout<<lob.get_book(10)<<std::endl;
    lob.print_book(10);
    // removal
    lob.delete_limit_order_ask(3);
    lob.print_book(10);
    //cancellation
    lob.cancel_limit_order_bid(4, 30, true);
    lob.print_book(10);
    std::cout<<"Thru__________________"<<std::endl;




    return 0;
}