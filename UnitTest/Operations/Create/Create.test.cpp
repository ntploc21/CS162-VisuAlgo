#include "../../../src/Core/Operations/Create/Create.hpp"

#include "doctest.h"

TEST_CASE("Base Create functionality") {
    Create createOp = Create();
    SUBCASE("Testing Create::RandomFixedSize") {
        std::map< std::string, std::string > params;
        params["nSize"] = "5";
        std::vector< int > output =
            createOp.CreateInput(CreateOperation::RandomFixedSize, params);

        CHECK(output.size() == 5);
    }

    SUBCASE("Testing Create::UserDefined") {
        std::map< std::string, std::string > params;
        params["input"] = "5,10,3,5,9";
        std::vector< int > output =
            createOp.CreateInput(CreateOperation::UserDefined, params);

        CHECK(output.size() == 5);
    }
}