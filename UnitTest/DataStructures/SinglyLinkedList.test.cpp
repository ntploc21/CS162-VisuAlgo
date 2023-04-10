#include "../../src/Core/DataStructures/LinkedList/SinglyLinkedList.hpp"

#include "doctest.h"

TEST_CASE("SinglyLinkedList functionality") {
    SinglyLinkedList< int > SLL = SinglyLinkedList< int >();
    SUBCASE("Test Clear method") {
        SLL.Random();
        CHECK(SLL.Size() > 0);
        SLL.Clear();
        CHECK(SLL.Size() == 0);
    }
}