cmake_minimum_required(VERSION 3.20)

# set the project name
project(mp3-metadata)
set (CMAKE_CXX_STANDARD 11)
set (DCMAKE_CXX_FLAGS "-Werror")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()


# build sketch as executable
add_executable (mp3-metadata mp3-metadata.cpp ../main.cpp)

# set preprocessor defines
target_compile_definitions(mp3-metadata PUBLIC -DEXIT_ON_STOP -DIS_DESKTOP)

# specify libraries
target_link_libraries(mp3-metadata portaudio arduino_emulator arduino-audio-tools)

