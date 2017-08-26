#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <homework5/ForwardAction.h>

int main(int argc, char** argv) {

	ros::init(argc, argv, "test_goforward");
	
	// create the action client
	// true causes the client to spin its own thread
	actionlib::SimpleActionClient<homework5::ForwardAction> actionClient("goforward", true);

	ROS_INFO("Waiting for action server to start.");
	// wait for the action server to start
	actionClient.waitForServer(); //will wait for infinite time
	
	ROS_INFO("Action server started, sending goal.");
	
	homework5::ForwardGoal goal;
	
	goal.desired_speed = 1;
	goal.distance = 2;
	
	actionClient.sendGoal(goal);
	
	//wait for the action to return
	bool finished_before_timeout = actionClient.waitForResult(ros::Duration(30.0));

	if (finished_before_timeout) {
		actionlib::SimpleClientGoalState state = actionClient.getState();
		ROS_INFO("Action finished: %s",state.toString().c_str());
	} else
		ROS_INFO("Action did not finish before the time out.");

	//exit
	return 0;
}
