#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <homework5/ForwardAction.h>
#include <math.h>

class ForwardAction {
	protected:
		
		ros::NodeHandle NHandle;
		actionlib::SimpleActionServer<homework5::ForwardAction> actionServer;
		std::string actionName;
		homework5::ForwardResult result;
		homework5::ForwardFeedback feedback;
		ros::Subscriber position_sub;
		
		bool volatile success; // dear compiler do not optimize this var
		bool  started;
		float start_x;
		float start_y;
		float goal_distance;
		
	public:
		ForwardAction(std::string name) : 
			actionServer(NHandle, name, boost::bind(&ForwardAction::executeCB, this, _1), false),
			actionName(name) // initialization list...
  		{
  			actionServer.start();
  			position_sub = NHandle.subscribe("odom", 10, &ForwardAction::posistionCB, this);
  			started = false;
  			success = false;
  			goal_distance = 0;
  			
  		}
  		
  		
  		~ForwardAction(void) {}
  		
  		void posistionCB(const nav_msgs::Odometry::ConstPtr& msg) {
			float x = msg->pose.pose.position.x;
			float y = msg->pose.pose.position.y;
			if(!started) {
				start_x = x;
				start_y = y;
				started = true;
			} else if(goal_distance) {
				float completed_distance = sqrt(pow(x-start_x, 2)+pow(y-start_y,2));
				if(completed_distance >= goal_distance) {
					success = true;
					result.odom_pose = *msg;
				}
			}
		}
  		
  		void executeCB(const homework5::ForwardGoalConstPtr &goal) {
			
			goal_distance = goal->distance;
			float desired_speed = goal->desired_speed;
			
			ros::Publisher pub = NHandle.advertise<geometry_msgs::Twist>("cmd_vel", 100);
			
			geometry_msgs::Twist msg;
			
			while(!success) {
				msg.linear.x = desired_speed;
				pub.publish(msg);
				
				if (actionServer.isPreemptRequested() || !ros::ok()) {
					ROS_INFO("%s: Preempted", actionName.c_str());
					actionServer.setPreempted();
					success = false;
					break;
				}
			}

			if(success) {
				ROS_INFO("%s: Succeeded", actionName.c_str());
				actionServer.setSucceeded(result);
			}
			success = false;
			started = false;
  		}

};

int main(int argc, char** argv) {

	ros::init(argc, argv, "goforward");
	
	ForwardAction forwardAction("goforward");
	
	ros::spin();
	
	return 0;
}
