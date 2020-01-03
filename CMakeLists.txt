cmake_minimum_required(VERSION 3.5)

project(DateHelper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include_directories("headers")
AUX_SOURCE_DIRECTORY("classes" SOURCES)
AUX_SOURCE_DIRECTORY("src" SOURCES)

add_executable(simple-date-example ${SOURCES})
