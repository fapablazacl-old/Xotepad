
#include <catch2/catch.hpp>

#include "WindowsUtils.hpp"

TEST_CASE("Wildcards must be matched", "[wildcard]") {
    REQUIRE(wildcard_match("*.cpp", "main.cpp"));
    REQUIRE(wildcard_match("*.?pp", "main.Xpp"));
    REQUIRE(wildcard_match("????.cpp", "main.cpp"));
    REQUIRE(wildcard_match("CMakeLists.txt", "CMakeLists.txt"));
    REQUIRE(wildcard_match("*.cmake", "FindBoost.cmake"));
}


TEST_CASE("Find function should", "[find]") {
    REQUIRE(find("Hi there", 0, "hi", FF_DEFAULT) == 0);

    REQUIRE(find("hi there", 0, "Hi", FF_DEFAULT) == 0);
    REQUIRE(find("hi there", 0, "hi", FF_DEFAULT) == 0);
    REQUIRE(find("Hi there", 0, "there", FF_MATCH_CASE) == 3);
    REQUIRE(find("Hi there", 0, "There", FF_MATCH_CASE) == std::string::npos);
    REQUIRE(find("Hi there", 3, "hi", FF_DEFAULT) == std::string::npos);
    REQUIRE(find("hi there", 3, "hi", FF_DEFAULT) == std::string::npos);

    REQUIRE(find("Hi there", 0, "hi", FF_MATCH_CASE) == std::string::npos);
    REQUIRE(find("hi there", 0, "Hi", FF_MATCH_CASE) == std::string::npos);
    REQUIRE(find("hi there", 0, "hi", FF_MATCH_CASE) == 0);
    REQUIRE(find("Hi there", 0, "there", FF_MATCH_CASE) == 3);
    REQUIRE(find("Hi there", 0, "There", FF_MATCH_CASE) == std::string::npos);
    REQUIRE(find("Hi there", 3, "hi", FF_MATCH_CASE) == std::string::npos);
    REQUIRE(find("hi there", 3, "hi", FF_MATCH_CASE) == std::string::npos);
}
