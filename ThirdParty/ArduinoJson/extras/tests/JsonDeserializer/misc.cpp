// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2019
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("deserializeJson(DynamicJsonDocument&)") {
  DynamicJsonDocument doc(4096);

  SECTION("Edge cases") {
    SECTION("null char*") {
      DeserializationError err = deserializeJson(doc, static_cast<char*>(0));

      REQUIRE(err != DeserializationError::Ok);
    }

    SECTION("null const char*") {
      DeserializationError err =
          deserializeJson(doc, static_cast<const char*>(0));

      REQUIRE(err != DeserializationError::Ok);
    }

    SECTION("Empty input") {
      DeserializationError err = deserializeJson(doc, "");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("issue #628") {
      DeserializationError err = deserializeJson(doc, "null");
      REQUIRE(err == DeserializationError::Ok);
      REQUIRE(doc.is<float>() == false);
    }

    SECTION("Garbage") {
      DeserializationError err = deserializeJson(doc, "%*$£¤");

      REQUIRE(err == DeserializationError::InvalidInput);
    }
  }

  SECTION("Booleans") {
    SECTION("True") {
      DeserializationError err = deserializeJson(doc, "true");

      REQUIRE(err == DeserializationError::Ok);
      REQUIRE(doc.is<bool>());
      REQUIRE(doc.as<bool>() == true);
    }

    SECTION("False") {
      DeserializationError err = deserializeJson(doc, "false");

      REQUIRE(err == DeserializationError::Ok);
      REQUIRE(doc.is<bool>());
      REQUIRE(doc.as<bool>() == false);
    }
  }

  SECTION("Comments") {
    SECTION("Just a trailing comment") {
      DeserializationError err = deserializeJson(doc, "// comment");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("Just a block comment") {
      DeserializationError err = deserializeJson(doc, "/*comment*/");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("Just a slash") {
      DeserializationError err = deserializeJson(doc, "/");

      REQUIRE(err == DeserializationError::InvalidInput);
    }
  }

  SECTION("Premature null-terminator") {
    SECTION("In escape sequence") {
      DeserializationError err = deserializeJson(doc, "\"\\");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In block comment") {
      DeserializationError err = deserializeJson(doc, "/* comment");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In double quoted string") {
      DeserializationError err = deserializeJson(doc, "\"hello");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In single quoted string") {
      DeserializationError err = deserializeJson(doc, "'hello");

      REQUIRE(err == DeserializationError::IncompleteInput);
    }
  }

  SECTION("Premature end of input") {
    SECTION("In escape sequence") {
      DeserializationError err = deserializeJson(doc, "\"\\n\"", 2);

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In block comment") {
      DeserializationError err = deserializeJson(doc, "/* comment */", 10);

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In double quoted string") {
      DeserializationError err = deserializeJson(doc, "\"hello\"", 6);

      REQUIRE(err == DeserializationError::IncompleteInput);
    }

    SECTION("In single quoted string") {
      DeserializationError err = deserializeJson(doc, "'hello'", 6);

      REQUIRE(err == DeserializationError::IncompleteInput);
    }
  }

  SECTION("Should clear the JsonVariant") {
    deserializeJson(doc, "[1,2,3]");
    deserializeJson(doc, "{}");

    REQUIRE(doc.is<JsonObject>());
    REQUIRE(doc.memoryUsage() == JSON_OBJECT_SIZE(0));
  }
}
