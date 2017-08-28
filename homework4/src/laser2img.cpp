#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"

#include <opencv2/opencv.hpp>

#include <math.h>
#include <iostream>
#include <sstream>

#define RED Scalar(0, 0, 255)

int counter;

using namespace cv;
using namespace std;

void imageCallback(const sensor_msgs::LaserScan::ConstPtr& scan_info) {
	float min = 1000000000;
	int min_index = 0;
	int w = 800, h = 800;
	Mat image(w, h, CV_8UC3, Scalar::all(255));
	vector< vector<Point> > vertices(1, vector<Point>(scan_info->ranges.size()));
	int half = h/2;
	int down, right, cr, cd; down = right = cr = cd = 0;
	for (size_t i = 0; i < scan_info->ranges.size(); i++) {
	  	float dist = scan_info->ranges[i];
		if (dist < scan_info->range_min || dist > scan_info->range_max)
			continue;
		float theta = scan_info->angle_min + (i*scan_info->angle_increment);
		right = half - dist*lrint(cos(theta)*10);
		down  = half - dist*lrint(sin(theta)*10);
		vertices[0][i] = Point(right, down);
		if (dist < min) {
			min = dist;
	  		min_index = i;
			cr = right;
			cd = down;
  		}
		//ROS_INFO("right=%d, down=%d, dist=%f, theta=%f, cos=%f, sin=%f",
		//		  right, down, dist, theta, cos(theta), sin(theta));
	}
	ROS_INFO("min dist: %lf, at index: %d", min, min_index);

	polylines(image, vertices, 1, Scalar(255,0,0));
	circle(image, Point(cr, cd), 6, RED, 2);

	// show the first image in a window
	imshow("Display window", image);
	waitKey(20);

	// save images generated for each message
	stringstream ss;
	ss << "laser" << ++counter << ".jpg";
	//imwrite(ss.str(), image);
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "laser2img");
	ros::NodeHandle nodeHandle;
	ros::Rate loop_rate(5);
	ros::Subscriber sub = nodeHandle.subscribe<sensor_msgs::LaserScan>(
		"base_scan", 1000, imageCallback);

	ros::spin();

 	return 0;
}
