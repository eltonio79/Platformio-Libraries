cmake_minimum_required(VERSION 3.20)

# set the project name
project(aac-helix)
set (CMAKE_CXX_STANDARD 11)
set (DCMAKE_CXX_FLAGS "-Werror")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()
include(FetchContent)

# Build with libhelix
FetchContent_Declare(helix GIT_REPOSITORY "https://github.com/pschatzmann/arduino-libhelix.git" GIT_TAG main )
FetchContent_GetProperties(helix)
if(NOT helix_POPULATED)
    FetchContent_Populate(helix)
    add_subdirectory(${helix_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/helix)
endif()

# build sketch as executable
add_executable (aac-helix aac-helix.cpp ../main.cpp)

# set preprocessor defines
target_compile_definitions(aac-helix PUBLIC -DARDUINO -DEXIT_ON_STOP -DUSE_HELIX -DUSE_PORTAUDIO -DIS_DESKTOP)

# OS/X might need this setting for core audio
#target_compile_definitions(portaudio PUBLIC -DPA_USE_COREAUDIO=1)

# specify libraries
target_link_libraries(aac-helix portaudio arduino_emulator arduino_helix arduino-audio-tools)

