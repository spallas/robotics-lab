#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

#include <math.h>
#include <iostream>


ros::Publisher finalvel_pub;
geometry_msgs::Twist set_vel;

float stop_param = 0.1;
float robot_width = 0.20;
/**
 * choose your stop_param
 * STAGE: 0.03
 * MARRTINO with laser: ??
 * MARRTINO with kinect: ??
 * 
 */
float base_emergency_dist = 0.25;
float smooth_params[8] = {0.75, 0.5, 0.2, 0.2, 0.1, 0.05, 0.01, 0};
volatile bool stopping = true;


float getAngleParam(float theta) {
	
	int itheta = rint((theta)*100);
	int pi_3 = rint((M_PI/3.0)*100);
	int pi_6 = rint((M_PI/6.0)*100);
	
	float angle_param;
	if(itheta < pi_6)	
		angle_param = 1;
	else if(itheta < pi_3)
		angle_param = 0.66;
	else
		angle_param = 0.33;
		
	return angle_param;
}

void publishFilteredVel(geometry_msgs::Twist current_vel) {
	
	geometry_msgs::Twist filtered_vel = current_vel;
	
	for(int j=0; j<8; j++) {
		filtered_vel.linear.x = current_vel.linear.x*smooth_params[j];
		finalvel_pub.publish(filtered_vel);
	}
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan_info) {
	
	if(stopping) return;
	
	geometry_msgs::Twist current_vel = set_vel;
	geometry_msgs::Twist filtered_vel = current_vel;
	float edist_max = base_emergency_dist + (stop_param * current_vel.linear.x);
	
	for (size_t i = 0; i < scan_info->ranges.size(); i++) {
		float dist = scan_info->ranges[i];
		
		float theta = scan_info->angle_min + (i*scan_info->angle_increment);
		
		if(abs(theta) > M_PI_2) continue;
		
		float angle_pram = getAngleParam(theta);
		
		float emergency_dist;
		float side_angle = M_PI_2 - acos(robot_width/dist);
		if(abs(theta) < side_angle) {
			emergency_dist = edist_max;
		} else {
			emergency_dist = robot_width/cos(M_PI_2 - abs(theta));
		}
		
		
		if(dist < emergency_dist) {
			stopping = true;
			ROS_INFO("Stopping smoothly...");

			// publishFilteredVel(current_vel);
			
			filtered_vel.linear.x = 0;
			finalvel_pub.publish(filtered_vel);
			
			return;
		}
	}
	finalvel_pub.publish(filtered_vel); // no danger, just republish
}


void velCallback(const geometry_msgs::Twist::ConstPtr& vel) {
	stopping = false;
	set_vel = *vel;
	if((*vel).linear.x == 0) return;
	if((*vel).linear.x < 0) {
		finalvel_pub.publish(*vel);
	}
}


int main(int argc, char** argv) {

#ifdef SYM
	const char* cmd_vel = "my_cmd_vel";
	const char* filtered_vel = "cmd_vel";
#else
	const char* cmd_vel = "cmd_vel";
	const char* filtered_vel = "cmd_vel_filtered";
#endif
	
	ros::init(argc, argv, "emergency_stop");
	ros::NodeHandle nodeHandle;
	ros::Rate loop_rate(40);
	
	ros::Subscriber laser_sub = nodeHandle.subscribe<sensor_msgs::LaserScan>(
		"base_scan", 10, laserCallback);
		
	ros::Subscriber vel_sub = nodeHandle.subscribe<geometry_msgs::Twist>(
		cmd_vel, 10, velCallback);
		
	finalvel_pub = nodeHandle.advertise<geometry_msgs::Twist>(
		filtered_vel, 10);
		
	ros::spin();

 	return 0;
}
