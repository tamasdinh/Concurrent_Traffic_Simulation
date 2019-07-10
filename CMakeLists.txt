cmake_minimum_required(VERSION 3.14)

project(23_Concurrent_Traffic_Simulation_Cpp)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

#get_directory_property(_vars_before VARIABLES)
find_package(OpenCV 4.1 REQUIRED)
#get_directory_property(_vars VARIABLES)

#list(REMOVE_ITEM _vars _vars_before ${_vars_before})
#foreach(_var IN LISTS _vars)
#    message(STATUS "${_var} = ${${_var}}")
#endforeach()

#include_directories(${OpenCV_INCLUDE_DIRS})
#add_executable(23_Concurrent_Traffic_Simulation_Cpp DT-include-test.cpp)

#link_directories(${OpenCV_LIBRARY_DIRS})
#add_definitions(${OpenCV_DEFINITIONS})

#add_executable(23_Concurrent_Traffic_Simulation_Cpp DT_TrafficLightTest.cpp DT_TrafficLightTest.cpp)

add_executable(23_Concurrent_Traffic_Simulation_Cpp
        src/Graphics.cpp
        src/Graphics.h
        src/Intersection.cpp
        src/Intersection.h
        src/Street.cpp
        src/Street.h
        src/TrafficLight.cpp
        src/TrafficLight.h
        src/TrafficObject.cpp
        src/TrafficObject.h
        src/TrafficSimulator-Final.cpp
        src/Vehicle.cpp
        src/Vehicle.h)

target_link_libraries(23_Concurrent_Traffic_Simulation_Cpp ${OpenCV_LIBS})




