# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MsgPackDeserializerTests
	deserializeArray.cpp
	deserializeObject.cpp
	deserializeStaticVariant.cpp
	deserializeVariant.cpp
	doubleToFloat.cpp
	incompleteInput.cpp
	input_types.cpp
	nestingLimit.cpp
	notSupported.cpp
)

target_link_libraries(MsgPackDeserializerTests catch)
add_test(MsgPackDeserializer MsgPackDeserializerTests)
