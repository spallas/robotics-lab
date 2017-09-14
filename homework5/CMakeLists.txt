cmake_minimum_required(VERSION 2.8.3)
project(homework5)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  nav_msgs
  message_generation
  message_runtime
  roscpp
  rospy
  std_msgs
)


## Generate actions in the 'action' folder
add_action_files(
   DIRECTORY action
   FILES     Forward.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   actionlib_msgs std_msgs nav_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES actionlib_example
  CATKIN_DEPENDS actionlib_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(homework5_server src/homework5_server.cpp)
add_executable(homework5_client src/homework5_client.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(
	homework5_server	
	${catkin_LIBRARIES}
)

target_link_libraries(
	homework5_client	
	${catkin_LIBRARIES}
)

add_dependencies(
	homework5_server
	homework5_client
 	${homework5_EXPORTED_TARGETS}
)



