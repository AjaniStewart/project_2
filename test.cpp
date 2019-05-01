#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "subway_route.h"
#include "subway_portal.h"

using namespace std;

TEST_CASE("Testing Subway Routes") {
  SUBCASE("is_route_id") {
    CHECK(is_route_id("a") == true);
    CHECK(is_route_id("A") == true);
    CHECK(is_route_id("z") == true);
    CHECK(is_route_id("k") == true);
    CHECK(is_route_id("1") == true);
    CHECK(is_route_id("6") == true);
    CHECK(is_route_id("7") == true);
    CHECK(is_route_id("*") == false);
    CHECK(is_route_id("9") == false);
  }

  SUBCASE("str_from_routeset") {
    route_set routes = 0b11111111111111111111111111111111111;
    CHECK(str_from_routeset(routes) == "1 2 3 4 5 6 7 FS GS A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
    routes = 0;
    CHECK(str_from_routeset(routes) == "");
    routes = 32;
    CHECK(str_from_routeset(routes) == "6");
    routes = 0b1100000010001110010001000011011001;
    CHECK(str_from_routeset(routes) == "1 4 5 7 FS D H K L M Q X Y");
  }

  SUBCASE("routestring2int") {
    CHECK(routestring2int("3") == 3);
    CHECK(routestring2int("9") == -1);
    CHECK(routestring2int("0") == -1);
    CHECK(routestring2int("A") == 10);
    CHECK(routestring2int("a") == 10);
    CHECK(routestring2int("FS") == 8);
    CHECK(routestring2int("*") == -1);

  }

  SUBCASE("int2route_id") {
    CHECK(int2route_id(0) == "");
    CHECK(int2route_id(36) == "");
    CHECK(int2route_id(1) == "1");
    CHECK(int2route_id(5) == "5");
    CHECK(int2route_id(8) == "FS");
    CHECK(int2route_id(9) == "GS");
    CHECK(int2route_id(10) == "A");
    CHECK(int2route_id(17) == "H");
    CHECK(int2route_id(35) == "Z");
  }
}

//TODO: make test cases for subway portal
TEST_CASE("Testing Subway Portal") {

}