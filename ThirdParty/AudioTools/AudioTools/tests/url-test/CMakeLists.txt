cmake_minimum_required(VERSION 3.20)

# set the project name
project(url-test)
set (CMAKE_CXX_STANDARD 11)
set (DCMAKE_CXX_FLAGS "-Werror")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

include(FetchContent)

# build sketch as executable
add_executable (url-test url-test.cpp ../main.cpp)
# set preprocessor defines
target_compile_definitions(url-test PUBLIC -DARDUINO -DEXIT_ON_STOP -DIS_DESKTOP)

# OS/X might need this setting for core audio
#target_compile_definitions(portaudio PUBLIC -DPA_USE_COREAUDIO=1)

# specify libraries
target_link_libraries(url-test arduino_emulator arduino-audio-tools)

