// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonArray::operator==()") {
  DynamicJsonDocument doc1(4096);
  JsonArray array1 = doc1.to<JsonArray>();
  JsonArrayConst array1c = array1;

  DynamicJsonDocument doc2(4096);
  JsonArray array2 = doc2.to<JsonArray>();
  JsonArrayConst array2c = array2;

  SECTION("should return false when arrays differ") {
    array1.add("coucou");
    array2.add(1);

    REQUIRE_FALSE(array1 == array2);
    REQUIRE_FALSE(array1c == array2c);
  }

  SECTION("should return false when LHS has more elements") {
    array1.add(1);
    array1.add(2);
    array2.add(1);

    REQUIRE_FALSE(array1 == array2);
    REQUIRE_FALSE(array1c == array2c);
  }

  SECTION("should return false when RKS has more elements") {
    array1.add(1);
    array2.add(1);
    array2.add(2);

    REQUIRE_FALSE(array1 == array2);
    REQUIRE_FALSE(array1c == array2c);
  }

  SECTION("should return true when arrays equal") {
    array1.add("coucou");
    array2.add("coucou");

    REQUIRE(array1 == array2);
    REQUIRE(array1c == array2c);
  }
}
