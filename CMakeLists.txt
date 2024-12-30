cmake_minimum_required(VERSION 3.14)
project(RayTracerChallenge)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

# Include directories for both source files and tests
include_directories(
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/tests 
)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src) 
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE TEST_SOURCES "${TEST_DIR}/*.cpp")

set(CMAKE_BuILD_TYPE "Debug")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DNDEBUG)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ftree-vectorize -march=native") 
endif()

# Create a separate executable for tests
add_executable(allTests ${TEST_SOURCES} ${SOURCES} ${HEADERS}) 

# Link the test executable with GTest
target_link_libraries(allTests 
    ${GTEST_LIBRARIES} 
)
