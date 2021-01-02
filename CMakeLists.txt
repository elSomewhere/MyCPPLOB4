cmake_minimum_required(VERSION 3.17)
project(MyCPPLOB4)

set(CMAKE_CXX_STANDARD 17)


set(ORDERBOOK_DOMAIN src/OrderBook)
set(EXT_DOMAIN ./src/tsl)
set(ENGINE_DOMAIN ./src/Engine)

include_directories(${ORDERBOOK_DOMAIN})
include_directories(${ENGINE_DOMAIN})
include_directories(${EXT_DOMAIN})

set(
        SOURCE_FILES
        main.cpp
        ${ENGINE_DOMAIN}/Engine.h
        ${ORDERBOOK_DOMAIN}/Order.h
        ${ORDERBOOK_DOMAIN}/OrderBook.h
        ${ORDERBOOK_DOMAIN}/PriceNode.h
        ${EXT_DOMAIN}/ordered_hash.h
        ${EXT_DOMAIN}/ordered_set.h
        ${EXT_DOMAIN}/ordered_map.h
        ${ENGINE_DOMAIN}/Engine.cpp
        ${ORDERBOOK_DOMAIN}/Order.cpp
        ${ORDERBOOK_DOMAIN}/OrderBook.cpp
        ${ORDERBOOK_DOMAIN}/PriceNode.cpp
)


add_executable(MyCPPLOB4 ${SOURCE_FILES})

target_link_libraries(MyCPPLOB4)