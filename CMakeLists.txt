cmake_minimum_required(VERSION 3.17)
project(MyCPPLOB4)

set(CMAKE_CXX_STANDARD 20)


set(LIB_DOMAIN ./src/LimitOrderBook)
set(EXT_DOMAIN ./src/tsl)

include_directories(${LIB_DOMAIN})
include_directories(${EXT_DOMAIN})

set(
        SOURCE_FILES
        main.cpp
        ${LIB_DOMAIN}/Engine.h
        ${LIB_DOMAIN}/Order.h
        ${LIB_DOMAIN}/OrderBook.h
        ${LIB_DOMAIN}/PriceNode.h
        ${EXT_DOMAIN}/ordered_hash.h
        ${EXT_DOMAIN}/ordered_set.h
        ${EXT_DOMAIN}/ordered_map.h
        ${LIB_DOMAIN}/Engine.cpp
        ${LIB_DOMAIN}/Order.cpp
        ${LIB_DOMAIN}/OrderBook.cpp
        ${LIB_DOMAIN}/PriceNode.cpp
)


add_executable(MyCPPLOB4 ${SOURCE_FILES})

target_link_libraries(MyCPPLOB4)