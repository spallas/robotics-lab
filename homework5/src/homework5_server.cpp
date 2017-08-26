#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <homework5/ForwardAction.h>

class ForwardAction {
	protected:
		
		ros::NodeHandle NHandle;
		actionlib::SimpleActionServer<homework5::ForwardAction> actionServer;
		std::string actionName;
		homework5::ForwardResult result;
		homework5::ForwardFeedback feedback;
		
		bool success;
		
	public:
		ForwardAction(std::string name) : 
			actionServer(NHandle, name, boost::bind(&ForwardAction::executeCB, this, _1), false),
			actionName(name) // initialization list...
  		{
  			actionServer.start();
  		}
  		
  		
  		~ForwardAction(void) {}
  		
  		void executeCB(const homework5::ForwardGoalConstPtr &goal) {
			
			float distance = goal->distance;
			float desired_speed = goal->desired_speed;
			
			
		
  		}

};

int main(int argc, char** argv) {

	ros::init(argc, argv, "goforward");
	
	ForwardAction forwardAction("goforward");
	
	ros::spin();
	
	return 0;
}
