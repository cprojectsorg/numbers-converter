cmake_minimum_required(VERSION 3.12)
project(NumbersConverter C)

SET(CMAKE_C_STANDARD 99)
SET(MATH_LIBS -lm)
SET(EXE -no-pie)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(NumbersConverter src/main.c src/main.h src/converter.c src/converter.h src/about.c src/about.h)

TARGET_LINK_LIBRARIES(NumbersConverter ${GTK3_LIBRARIES} ${MATH_LIBS} ${EXE})
