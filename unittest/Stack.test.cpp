#include "Core/Stack.hpp"

#include "doctest.h"

TEST_CASE("Core::Stack functionality") {
    Core::Stack< int > stack;

    CHECK(stack.empty());

    SUBCASE("construct") {
        stack = {3, 2, 1};
        CHECK(stack.size() == 3);
        CHECK(stack.top() == 3);

        stack.clear();

        CHECK(stack.empty());
    }

    SUBCASE("top") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        CHECK(stack.size() == 3);
        CHECK(stack.top() == 3);

        stack.clear();
    }

    SUBCASE("push") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        CHECK(stack.size() == 3);
        CHECK(stack.top() == 3);
        stack.clear();
    }

    SUBCASE("pop") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        stack.pop();

        CHECK(stack.size() == 2);
        CHECK(stack.top() == 2);

        stack.clear();
    }

    SUBCASE("swap") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        Core::Stack< int > stack2;
        stack2.push(4);
        stack2.push(5);
        stack2.push(6);

        stack.swap(stack2);

        CHECK(stack.size() == 3);
        CHECK(stack.top() == 6);
    }

    SUBCASE("move") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        Core::Stack< int > stack2(std::move(stack));

        CHECK(stack2.size() == 3);
        CHECK(stack2.top() == 3);
        CHECK(stack.empty());
    }

    SUBCASE("copy") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        Core::Stack< int > stack2(stack);

        CHECK(stack2.size() == 3);
        CHECK(stack2.top() == 3);
        CHECK(stack.size() == 3);
        CHECK(stack.top() == 3);
    }

    SUBCASE("copy assign") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        Core::Stack< int > stack2;
        stack2 = stack;

        CHECK(stack2.size() == 3);
        CHECK(stack2.top() == 3);
        CHECK(stack.size() == 3);
        CHECK(stack.top() == 3);
    }

    SUBCASE("move assign") {
        stack.push(1);
        stack.push(2);
        stack.push(3);

        Core::Stack< int > stack2;
        stack2 = std::move(stack);

        CHECK(stack2.size() == 3);
        CHECK(stack2.top() == 3);
        CHECK(stack.empty());
    }
}