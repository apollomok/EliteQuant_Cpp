# the minimum version of CMake required
cmake_minimum_required(VERSION 2.8)
PROJECT(EliteQuantCpp C CXX)
# required for unit testing using CMake's ctest command
LIST(APPEND CMAKE_MODULE_PATH  ${EliteQuantCpp_SOURCE_DIR}/cmake/modules)

include(CTest)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(ExternalProject)
#Find Packages
find_package(ZLIB REQUIRED)
find_package(PkgConfig)
find_package(Boost REQUIRED COMPONENTS system filesystem regex thread python)
find_package(rapidjson REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(sodium REQUIRED)
# Sodium is required for zeromq
add_subdirectory(ThirdParty/zeromq)

find_package(yaml-cpp REQUIRED)
#find_package(Cereal REQUIRED)
find_package(nanomsg REQUIRED)
find_package(websocketpp REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/)
include_directories(${CMAKE_BINARY_DIR}/ThirdParty/seasocks/)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/cereal/include/)

add_subdirectory(ThirdParty/cereal)
add_subdirectory(ThirdParty/seasocks)

include_directories(${NANOMSG_INCLUDE_DIR})
ADD_DEFINITIONS("-std=gnu++17 -DIB_USE_STD_STRING")
subdirs(EliteQuant eqserver)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()


