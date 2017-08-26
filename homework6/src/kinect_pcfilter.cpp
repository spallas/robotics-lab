#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

void callback(const sensor_msgs::PointCloud2::ConstPtr& pc_message) {
	
	pcl::PointCloud<pcl::PointXYZ>::Ptr pcloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
	
	pcl::fromROSMsg(*pc_message, *pcloud_ptr);
	
	pcl::VoxelGrid<T> voxel_grid; 
	voxel_grid.setInputCloud(pcloud_ptr); 
	voxel_grid.setLeafSize(0.01, 0.01, 0.01); // dimension of ...
	voxel_grid.filter(*pcloud_ptr);

	pcl::PassThrough<T> pass_through; 
	pass_through.setInputCloud (pcloud_ptr); 
	pass_through.setFilterLimits (0.0, 0.5); 
	pass_through.setFilterFieldName ("z"); 
	pass_through.filter(*pcloud_ptr);
	
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
	viewer->addPointCloud<pcl::PointXYZ>(pcloud_ptr, "Result cloud");
	viewer->initCameraParameters();
	viewer->addCoordinateSystem(1.0);
	
	while(!viewer->wasStopped()) 
		viewer->spinOnce(1);
	
}


int main(int argc, char **argv) {
	
	ros::init(argc, argv, "kinect_filter");
  
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("/camera/depth/points", 1000, callback);

	ros::spin();
	return 0;
  
}
