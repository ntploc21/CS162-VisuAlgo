#include "Core/List.hpp"

#include "doctest.h"

TEST_CASE("Core::List functionality") {
    Core::List< int > list;

    CHECK(list.empty());

    SUBCASE("push_back") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
        list.clear();
    }

    SUBCASE("push_front") {
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);

        CHECK(list.size() == 3);
        CHECK(list.front() == 3);
        CHECK(list.back() == 1);
        list.clear();
    }

    SUBCASE("pop_back") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.pop_back();

        CHECK(list.size() == 2);
        CHECK(list.front() == 1);
        CHECK(list.back() == 2);

        list.clear();
    }

    SUBCASE("pop_front") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.pop_front();

        CHECK(list.size() == 2);
        CHECK(list.front() == 2);
        CHECK(list.back() == 3);
    }

    
}