// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

struct CustomWriter {
  std::string str;

  size_t write(uint8_t c) {
    str.append(1, static_cast<char>(c));
    return 1;
  }

  size_t write(const uint8_t *s, size_t n) {
    str.append(reinterpret_cast<const char *>(s), n);
    return n;
  }
};

TEST_CASE("CustomWriter") {
  DynamicJsonDocument doc(4096);
  JsonArray array = doc.to<JsonArray>();
  array.add(4);
  array.add(2);

  SECTION("serializeJson()") {
    CustomWriter writer;
    serializeJson(array, writer);

    REQUIRE("[4,2]" == writer.str);
  }

  SECTION("serializeJsonPretty") {
    CustomWriter writer;
    serializeJsonPretty(array, writer);

    REQUIRE("[\r\n  4,\r\n  2\r\n]" == writer.str);
  }
}
