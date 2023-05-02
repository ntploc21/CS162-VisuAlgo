#include "Core/Queue.hpp"

#include "doctest.h"

TEST_CASE("Core::Queue functionality") {
    Core::Queue< int > list;

    CHECK(list.empty());

    SUBCASE("construct") {
        list = {1, 2, 3};
        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        list.clear();

        CHECK(list.empty());
    }

    SUBCASE("push") {
        list.push(1);
        list.push(2);
        list.push(3);

        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);
        list.clear();
    }

    SUBCASE("pop") {
        list.push(1);
        list.push(2);
        list.push(3);

        list.pop();

        CHECK(list.size() == 2);
        CHECK(list.front() == 2);
        CHECK(list.back() == 3);

        list.clear();
    }

    SUBCASE("swap") {
        list.push(1);
        list.push(2);
        list.push(3);

        Core::Queue< int > list2;
        list2.push(4);
        list2.push(5);
        list2.push(6);

        list.swap(list2);

        CHECK(list.size() == 3);
        CHECK(list.front() == 4);
        CHECK(list.back() == 6);

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 1);
        CHECK(list2.back() == 3);

        list.clear();
        list2.clear();
    }

    SUBCASE("copy") {
        list.push(1);
        list.push(2);
        list.push(3);

        Core::Queue< int > list2(list);

        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 1);
        CHECK(list2.back() == 3);

        list.clear();
        list2.clear();
    }

    SUBCASE("move") {
        list.push(1);
        list.push(2);
        list.push(3);

        Core::Queue< int > list2(std::move(list));

        CHECK(list.empty());

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 1);
        CHECK(list2.back() == 3);

        list.clear();
        list2.clear();
    }

    SUBCASE("assign") {
        list.push(1);
        list.push(2);
        list.push(3);

        Core::Queue< int > list2;
        list2.push(4);
        list2.push(5);
        list2.push(6);

        list2 = list;

        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 1);
        CHECK(list2.back() == 3);

        list.clear();
        list2.clear();
    }

    SUBCASE("assign move") {
        list.push(1);
        list.push(2);
        list.push(3);

        Core::Queue< int > list2;
        list2.push(4);
        list2.push(5);
        list2.push(6);

        list2 = std::move(list);

        CHECK(list.empty());

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 1);
        CHECK(list2.back() == 3);

        list.clear();
        list2.clear();
    }

    SUBCASE("front") {
        list.push(1);
        list.push(2);
        list.push(3);

        CHECK(list.front() == 1);

        list.clear();
    }

    SUBCASE("back") {
        list.push(1);
        list.push(2);
        list.push(3);

        CHECK(list.back() == 3);

        list.clear();
    }

    SUBCASE("empty") {
        list.push(1);
        list.push(2);
        list.push(3);

        CHECK(!list.empty());

        list.clear();

        CHECK(list.empty());
    }

    SUBCASE("size") {
        list.push(1);
        list.push(2);
        list.push(3);

        CHECK(list.size() == 3);

        list.clear();

        CHECK(list.size() == 0);
    }

    SUBCASE("clear") {
        list.push(1);
        list.push(2);
        list.push(3);

        list.clear();

        CHECK(list.empty());
    }
}