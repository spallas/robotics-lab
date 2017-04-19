cmake_minimum_required(VERSION 2.8.3)
project(homework4)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui imgcodecs)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(laser2img src/laser2img.cpp)
target_link_libraries(laser2img ${catkin_LIBRARIES} ${OpenCV_LIBS})


