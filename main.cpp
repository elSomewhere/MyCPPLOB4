#include <iostream>
#include "Engine.h"

int main() {

    int max_book_width = 100;
    int max_order_capacity = 100;
    Engine lob(&max_book_width, &max_order_capacity);

    // fill
    lob.match_book_limit_order_ask(200, 100, 1);
    lob.match_book_limit_order_ask(100, 100, 2);
    lob.match_book_limit_order_ask(300, 100, 3);
    lob.match_book_limit_order_bid(50, 100, 4);
    lob.match_book_limit_order_bid(150, 50, 5);
    lob.match_book_limit_order_bid(350, 200, 6);
    std::cout<<"After additions"<<std::endl;
    lob.print_book(10);

    // removal
    std::cout<<"start removal"<<std::endl;
    lob.delete_limit_order_ask(3);
    std::cout<<"After removal"<<std::endl;
    lob.print_book(10);

    //cancellation
    std::cout<<"start cancellation"<<std::endl;
    lob.cancel_limit_order_bid(4, 30, true);
    std::cout<<"After cancellation"<<std::endl;
    lob.print_book(10);

    std::cout<<"Done."<<std::endl;

    return 0;
}