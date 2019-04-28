#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "subway_route.h"

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
    route_set routes = 0b0000000000000000000000000000011111111111111111111111111111111111;
    CHECK(str_from_routeset(routes) == "1 2 3 4 5 6 7 FS GS A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ");
  }
}
