#include "ros/ros.h"
#include "std_msgs/String.h"
#include "tf/transform_listener.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>


void callback(const sensor_msgs::LaserScan::ConstPtr&, 
				tf::TransformListener* listener)
{

	tf::StampedTransform transform;
	try{
    	ros::Time now = ros::Time::now();
    	listener->waitForTransform("/base_laser_link", "/odom",
                              now, ros::Duration(3.0));
    	listener->lookupTransform("/base_laser_link", "/odom",
                             now, transform);
                             
        std::stringstream ss;
        ss << "LASER: " << transform.stamp_.toSec();
        ss << ", x = " << transform.getOrigin().x();
        ss << ", y = " << transform.getOrigin().y();
        ss << ", theta = " << transform.getRotation().getAngle();
        
        std_msgs::String msg;
        msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
        
    } catch(tf::TransformException ex){
    	ROS_ERROR("%s",ex.what());
    	ros::Duration(1.0).sleep(); 	
    }
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "laser_position");
	
	ros::NodeHandle nodeHandle;
	tf::TransformListener listener;
	
	// ros::Publisher pub = nodeHandle.advertise<std_msgs::String>("position", 1000);
	// ros::Rate loop_rate(10);
	ros::Subscriber sub = nodeHandle.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, 
												boost::bind(callback, _1, &listener));
	
	ros::spin();
	return 0;
}
