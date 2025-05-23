// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <sstream>

TEST_CASE("deserializeJson(const std::string&)") {
  DynamicJsonDocument doc(4096);

  SECTION("should accept const string") {
    const std::string input("[42]");

    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("should accept temporary string") {
    DeserializationError err = deserializeJson(doc, std::string("[42]"));

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("should duplicate content") {
    std::string input("[\"hello\"]");

    DeserializationError err = deserializeJson(doc, input);
    input[2] = 'X';  // alter the string tomake sure we made a copy

    JsonArray array = doc.as<JsonArray>();
    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(std::string("hello") == array[0]);
  }
}

TEST_CASE("deserializeJson(std::istream&)") {
  DynamicJsonDocument doc(4096);

  SECTION("array") {
    std::istringstream json(" [ 42 /* comment */ ] ");

    DeserializationError err = deserializeJson(doc, json);
    JsonArray arr = doc.as<JsonArray>();

    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(1 == arr.size());
    REQUIRE(42 == arr[0]);
  }

  SECTION("object") {
    std::istringstream json(" { hello : 'world' // comment\n }");

    DeserializationError err = deserializeJson(doc, json);
    JsonObject obj = doc.as<JsonObject>();

    REQUIRE(err == DeserializationError::Ok);
    REQUIRE(1 == obj.size());
    REQUIRE(std::string("world") == obj["hello"]);
  }

  SECTION("Should not read after the closing brace of an empty object") {
    std::istringstream json("{}123");

    deserializeJson(doc, json);

    REQUIRE('1' == char(json.get()));
  }

  SECTION("Should not read after the closing brace") {
    std::istringstream json("{\"hello\":\"world\"}123");

    deserializeJson(doc, json);

    REQUIRE('1' == char(json.get()));
  }

  SECTION("Should not read after the closing bracket of an empty array") {
    std::istringstream json("[]123");

    deserializeJson(doc, json);

    REQUIRE('1' == char(json.get()));
  }

  SECTION("Should not read after the closing bracket") {
    std::istringstream json("[\"hello\",\"world\"]123");

    deserializeJson(doc, json);

    REQUIRE('1' == char(json.get()));
  }

  SECTION("Should not read after the closing quote") {
    std::istringstream json("\"hello\"123");

    deserializeJson(doc, json);

    REQUIRE('1' == char(json.get()));
  }
}

#ifdef HAS_VARIABLE_LENGTH_ARRAY
TEST_CASE("deserializeJson(VLA)") {
  int i = 9;
  char vla[i];
  strcpy(vla, "{\"a\":42}");

  StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
  DeserializationError err = deserializeJson(doc, vla);

  REQUIRE(err == DeserializationError::Ok);
}
#endif
