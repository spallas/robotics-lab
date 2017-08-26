# Artificial Intelligence Laboratory
Homeworks for the artificial intelligence laboratory at Sapienza, B.Sc. Engineering in Computer Science

## Homeworks index

Each folder in this repository contains the source code requested for the various homeworks. 
The number of the homework doesn't correspond exactly to the ones assigned in class. 
The following are the specifications that correspond to each homework.

### homework 0

- Run the STAGE simulator
- Write a node that:
  - subscribes the /base_scan topic and...
  - for each incoming LaserScan message computes the minimum distance from
the obstacles and...
  - publishes the minimum distance on another topic

### homework 2

Write a ros node that writes in a text format the 2D location of the laser (x,y,theta) when laser messages arrive, and the timestamp. 
</br></br> 
Format:
- One line per message
- LASER <timestamp.sec>.<timestamp.usec> <laser pose w.r.t. odom frame (x,y,theta)>

### homework 4

- Run the STAGE simulator
- Write a node that:
  - subscribes the /base_scan topic and...
  - for each incoming LaserScan message computes the minimum distance from the obstacles and...
  -  creates an image using OpenCV showing the laser data, highlighting the nearest obstacle point with a red circle.

### homework 5

Consider the action of moving the robot forward for a certain distance with a desired speed.

- Define an ad-hoc ROS action:
  - Goal: desired_speed, distance (float64)
  - Result: odom_pose (nav_msgs/Odometry)
  - Feedback: empty
- Implement a SimpleActionClient that requests the execution of the action, providing the desired speed and distance.
- Implement a SimpleActionServer that:
  - Receives the desired speed and distance values
  - Executes the forward motion of the robot until the requested traveled distance is reached
  - Returns as result the robot odometry pose at the end of the execution
  
  ### homework 6
  
  
Implement a ROS node that:
- Subscribes on the kinect /cloud topic
- Convert the incoming sensor_msgs/PointCloud2 messages in the pcl::PointCloud data structure
- Apply a voxelization in order to reduce the dimension of the cloud
- Filter the cloud in order to remove points outside a specified range
- Visualize the resulting point cloud using the PCL viewer

