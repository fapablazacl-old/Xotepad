
#include <catch2/catch.hpp>

#include "WindowsUtils.hpp"

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE(wildcard_match("*.cpp", "main.cpp"));
    REQUIRE(wildcard_match("*.?pp", "main.Xpp"));
    REQUIRE(wildcard_match("????.cpp", "main.cpp"));
    REQUIRE(wildcard_match("CMakeLists.txt", "CMakeLists.txt"));
    REQUIRE(wildcard_match("*.cmake", "FindBoost.cmake"));
}
