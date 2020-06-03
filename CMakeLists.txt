cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project (synth)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
	synth
	src/adsr_synth.cpp
	src/audio.cpp
	src/main.cpp
	src/midi_tools.cpp
	src/wave_synth.cpp
	src/wavtools.cpp
)

target_link_libraries (
	synth 
	${SDL2_LIBRARIES}
)  