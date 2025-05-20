cmake_minimum_required(VERSION 3.0)
project(TrafficLightController)

find_package(gazebo REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(TrafficLightController SHARED plugins/TrafficLightController.cc)
target_link_libraries(TrafficLightController ${GAZEBO_LIBRARIES})