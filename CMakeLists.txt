cmake_minimum_required(VERSION 3.21)
project(CGMath VERSION 1.0 LANGUAGES CXX)

# Ustaw standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCE_FILES 
	 src/*.c
	 src/*.cpp)

file(GLOB_RECURSE HEADER_FILES 
	 include/*.h
	 include/*.hpp)

add_executable(CGMath ${HEADER_FILES} ${SOURCE_FILES}
		src/Vector4f.cpp
		include/Vector4f.h
		src/Matrix4x4.cpp
		include/Matrix4x4.h)

target_include_directories(CGMath PRIVATE include)