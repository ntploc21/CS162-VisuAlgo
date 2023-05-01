#include "Core/Deque.hpp"
#include "doctest.h"

TEST_CASE("Core::Deque functionality") {
    Core::Deque< int > list;

    CHECK(list.empty());

    SUBCASE("construct") {
        list = {1, 2, 3};
        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        list.clear();

        CHECK(list.empty());
    }

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

    SUBCASE("iterator") {
        list.push_back(2);
        list.push_back(10);
        list.push_back(4);

        auto it = list.begin();
        CHECK(*it == 2);
        CHECK(*(++it) == 10);
        CHECK(*(++it) == 4);
        CHECK(++it == list.end());

        list.clear();
    }

    SUBCASE("assign") {
        list.assign(3, 1);

        CHECK(list.size() == 3);
        CHECK(list.front() == 1);
        CHECK(list.back() == 1);

        list.clear();

        Core::Deque< int > list2 = {4, 7, 10};  // Move constructor

        list.assign(list2.begin(), list2.end());

        CHECK(list.size() == 3);
        CHECK(list.front() == 4);
        CHECK(list.back() == 10);
        list.clear();
    }

    SUBCASE("access") {
        list.push_back(5);
        list.push_back(9);
        list.push_back(3);

        CHECK(list[0] == 5);
        CHECK(list[1] == 9);
        CHECK(list[2] == 3);

        list.clear();
    }

    SUBCASE("operator =") {
        list.push_back(5);
        list.push_back(9);
        list.push_back(3);

        Core::Deque< int > list2 = list;

        CHECK(list2.size() == 3);
        CHECK(list2.front() == 5);
        CHECK(list2.back() == 3);

        list.clear();
    }

    SUBCASE("reverse") {
        list.push_back(5);
        list.push_back(9);
        list.push_back(3);

        list.reverse();

        CHECK(list.size() == 3);
        CHECK(list.front() == 3);
        CHECK(list.back() == 5);

        list.clear();
    }

    SUBCASE("unique") {
        list.push_back(5);
        list.push_back(5);
        list.push_back(5);

        list.unique();

        CHECK(list.size() == 1);
        CHECK(list.front() == 5);
        CHECK(list.back() == 5);

        list.clear();
    }

    SUBCASE("remove") {
        list.push_back(5);
        list.push_back(9);
        list.push_back(3);

        list.remove(9);

        CHECK(list.size() == 2);
        CHECK(list.front() == 5);
        CHECK(list.back() == 3);

        list.clear();
    }

    SUBCASE("idk") {
        Core::Deque< int > list2({});

        list2.push_back(5);
        list2.push_back(9);
        list2.push_back(3);

        CHECK(list2[0] == 5);
        CHECK(list2[1] == 9);
        CHECK(list2[2] == 3);
    }
}