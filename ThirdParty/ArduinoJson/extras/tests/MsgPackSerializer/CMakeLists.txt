# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(MsgPackSerializerTests
	destination_types.cpp
	measure.cpp
	misc.cpp
	serializeArray.cpp
	serializeObject.cpp
	serializeVariant.cpp
)

target_link_libraries(MsgPackSerializerTests catch)
add_test(MsgPackSerializer MsgPackSerializerTests)
