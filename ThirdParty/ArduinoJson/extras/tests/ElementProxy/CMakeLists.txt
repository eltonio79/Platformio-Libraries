# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2019
# MIT License

add_executable(ElementProxyTests
	add.cpp
	clear.cpp
	compare.cpp
	remove.cpp
	set.cpp
	size.cpp
)

target_link_libraries(ElementProxyTests catch)
add_test(ElementProxy ElementProxyTests)
