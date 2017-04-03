cmake_minimum_required(VERSION 2.8.3)
project(homework2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  tf
)

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(laser_position src/laser_position.cpp)
target_link_libraries(laser_position ${catkin_LIBRARIES})
#add_dependencies(laser_position laser_generate_messages_cpp tf_cpp)


