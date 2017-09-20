# Emergency stop ROS node

To start the node put this folder in the src location of your catkin workspace, then compile it through catkin_make.
The only requirement is that the robot hardware listens to a cmd_vel topic named `/cmd_vel_filtered`, all other cmd_vel messages will be caught by the emergency stop node. Once you are ready run:

`rosrun emergency_stop emergency_stop_node`

### Use on MARRtino robot

You are not sure your project is working? Are you afraid to destroy the robots from the DIAG laboratory?
Your code can go mad and make the robot go straight against a wall?
This ROS node is just the thing for you!

Remember that in order to use it you have to make the robot listen to a different cmd_vel topic so that it has the exclusive control of the robot motion. To do so on MARRtino just set the parameter as following:

`rosrun srrg_orazio_ros orazio_robot_node _command_vel_topic:=/cmd_vel_filtered _serial_device:=/dev/ttyACM1`
(Always check the actual serial port your arduino is connected to)

To start other nodes useful for testing on the MARRtino robot, run the following commands (these will require the installation of relative packages):

- joystick: `rosrun thin_joystick_teleop joy_teleop_node`
- transforms: `rosrun srrg_core_ros srrg_state_publisher_node errazio_transforms.txt`
- hokuyo laser: `rosrun thin_hokuyo thin_hokuyo_node _serial_port:=/dev/lidar_hokuyo  _topic:=/base_scan`.
Remember that the node subscribes base_scan even if you are using a kinect, in that case you would need to run the depthimage_to_laserscan node.
