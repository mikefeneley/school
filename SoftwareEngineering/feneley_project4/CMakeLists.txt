CMake_minimum_required(VERSION 2.8)
project(QtMarkup CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
find_package(Qt4 REQUIRED QtGui QtWebKit QtTest)

add_executable(VirtualTennis main.cpp Window.cpp TennisView.cpp TennisModel.cpp TennisController.cpp)  
TARGET_LINK_LIBRARIES(VirtualTennis Qt4::QtGui Qt4::QtWebKit Qt4::QtTest)