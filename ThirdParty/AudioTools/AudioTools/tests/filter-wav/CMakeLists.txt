cmake_minimum_required(VERSION 3.20)

# set the project name
project(filter-wav)
set (CMAKE_CXX_STANDARD 11)
set (DCMAKE_CXX_FLAGS "-Werror")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()


# build sketch as executable
add_executable (filter-wav filter-wav.cpp ../main.cpp )
target_include_directories(filter-wav PRIVATE "${arduino_emulator_SOURCE_DIR}/ArduinoCore-Linux/libraries/SdFat" )

# set preprocessor defines
target_compile_definitions(filter-wav PUBLIC -DEXIT_ON_STOP -DIS_DESKTOP)

# specify libraries
target_link_libraries(filter-wav portaudio arduino_emulator arduino-audio-tools)

