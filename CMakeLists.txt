cmake_minimum_required(VERSION 2.8.3)
project(depth_detection)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
include_directories(${OpenCV_INCLUDE_DIRS}
                    )

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  cv_bridge
  image_transport
  tf
)

find_package(OpenCV REQUIRED)


catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
  ${base_INCLUDE_DIRS}

)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#include/depth_detection.h
#  ${base_INCLUDE_DIRS}
# )

add_executable(${PROJECT_NAME} src/depth_detection.cpp)


## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
 realsense2
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${OpenCV_LIBS}
 )


add_dependencies(depth_detection ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})