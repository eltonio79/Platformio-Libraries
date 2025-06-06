// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <string>

void check(const JsonObject obj, const std::string &expected) {
  char actual[256];
  size_t actualLen = serializeJson(obj, actual);
  size_t measuredLen = measureJson(obj);

  REQUIRE(expected == actual);
  REQUIRE(expected.size() == actualLen);
  REQUIRE(expected.size() == measuredLen);
}

TEST_CASE("serializeJson(JsonObject)") {
  DynamicJsonDocument doc(4096);
  JsonObject obj = doc.to<JsonObject>();

  SECTION("EmptyObject") {
    check(obj, "{}");
  }

  SECTION("TwoStrings") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";

    check(obj, "{\"key1\":\"value1\",\"key2\":\"value2\"}");
  }

  SECTION("RemoveFirst") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key1");

    check(obj, "{\"key2\":\"value2\"}");
  }

  SECTION("RemoveLast") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key2");

    check(obj, "{\"key1\":\"value1\"}");
  }

  SECTION("RemoveUnexistingKey") {
    obj["key1"] = "value1";
    obj["key2"] = "value2";
    obj.remove("key3");

    check(obj, "{\"key1\":\"value1\",\"key2\":\"value2\"}");
  }

  SECTION("ReplaceExistingKey") {
    obj["key"] = "value1";
    obj["key"] = "value2";

    check(obj, "{\"key\":\"value2\"}");
  }

  SECTION("TwoIntegers") {
    obj["a"] = 1;
    obj["b"] = 2;
    check(obj, "{\"a\":1,\"b\":2}");
  }

  SECTION("serialized(const char*)") {
    obj["a"] = serialized("[1,2]");
    obj["b"] = serialized("[4,5]");
    check(obj, "{\"a\":[1,2],\"b\":[4,5]}");
  }

  SECTION("Two doubles") {
    obj["a"] = 12.34;
    obj["b"] = 56.78;
    check(obj, "{\"a\":12.34,\"b\":56.78}");
  }

  SECTION("TwoNull") {
    obj["a"] = static_cast<char *>(0);
    obj["b"] = static_cast<char *>(0);
    check(obj, "{\"a\":null,\"b\":null}");
  }

  SECTION("TwoBooleans") {
    obj["a"] = true;
    obj["b"] = false;
    check(obj, "{\"a\":true,\"b\":false}");
  }

  SECTION("ThreeNestedArrays") {
    DynamicJsonDocument b(4096);
    DynamicJsonDocument c(4096);

    obj.createNestedArray("a");
    obj["b"] = b.to<JsonArray>();
    obj["c"] = c.to<JsonArray>();

    check(obj, "{\"a\":[],\"b\":[],\"c\":[]}");
  }

  SECTION("ThreeNestedObjects") {
    DynamicJsonDocument b(4096);
    DynamicJsonDocument c(4096);

    obj.createNestedObject("a");
    obj["b"] = b.to<JsonObject>();
    obj["c"] = c.to<JsonObject>();

    check(obj, "{\"a\":{},\"b\":{},\"c\":{}}");
  }
}
