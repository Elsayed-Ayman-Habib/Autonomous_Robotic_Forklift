#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <unistd.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//define overall status of robot
bool  FORKLIFTT;
//bool free;
 
char goalAL[] = "goalAL";
char goalMT[] = "goalMT";  
char goalMN[] = "goalMN";
char goalFORKLIFT23[] = "goalFORKLIFT23";

void move_FORKLIFT_to_goal(char* str)
{
 	MoveBaseClient ac("/move_base", true);
	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	move_base_msgs::MoveBaseGoal goal;
	 if(str == goalMT)
	{
		//we'll send a goal to the robot to move xx meter forward
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose.position.x = 10.9353990555;
		goal.target_pose.pose.position.y = -5.011335301399;
		goal.target_pose.pose.orientation.z = 0.000640425086;
		goal.target_pose.pose.orientation.w = 0.0;
	  ROS_INFO("Sending goalMT");
  	ac.sendGoal(goal);
	}
 if(str == goalAL)
	{
		//we'll send a goal to the robot to move xx meter forward
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose.position.x = 1.39353990555;
		goal.target_pose.pose.position.y = 0.211335301399;
		goal.target_pose.pose.orientation.z = 0.075640425086;
		goal.target_pose.pose.orientation.w = 0.0;
	  ROS_INFO("Sending goalAL");
  	ac.sendGoal(goal);
	}
 if(str == goalMN)
	{
		//we'll send a goal to the robot to move xx meter forward
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose.position.x = 0.0;
		goal.target_pose.pose.position.y = 0.211335301399;
		goal.target_pose.pose.orientation.z = 0.075640425086;
		goal.target_pose.pose.orientation.w = 0.0;
	  ROS_INFO("Sending goalMN");
  	ac.sendGoal(goal);
	}
 if(str == goalFORKLIFT23)
	{
		//we'll send a goal to the robot to move xx meter forward
		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose.position.x = 1.39353990555;
		goal.target_pose.pose.position.y = 0.211335301399;
		goal.target_pose.pose.orientation.z = 0.075640425086;
		goal.target_pose.pose.orientation.w = 0.0;
	  ROS_INFO("Sending goalFORKLIFT23");
  	ac.sendGoal(goal);
	}




} 

void send_goal(char* str)
{
	ROS_INFO("Function Send Goal");
	std::cout<<str<<std::endl;
	 if(str == goalMT)
	{
	      ROS_INFO("Going to goal MT"); // DA el goal btA3 tariq 
	       move_FORKLIFT_to_goal(goalMT);

	}
 if(str == goalAL)
	{
	      ROS_INFO("Going to goal AL"); // DA el goal bt3 tariq 
	       move_FORKLIFT_to_goal(goalAL);

	}
 if(str == goalMN)
	{
	      ROS_INFO("Going to goal MN"); // DA el goal bt3 tariq 
	       move_FORKLIFT_to_goal(goalMN);

	}
 if(str == goalFORKLIFT23)
	{
	      ROS_INFO("Going to goal FORKLIFT23"); // DA el goal bt3 tariq 
	       move_FORKLIFT_to_goal(goalFORKLIFT23);

	}

         

} 
void Callback(const std_msgs::String::ConstPtr& msg)
{
     if(msg->data== "MT")
      {
		ROS_INFO("the massage that was received was : %s" , msg->data.c_str());
		send_goal(goalMT); 
      }   
    if(msg->data== "AL")
      {
		ROS_INFO("the massage that was received was : %s" , msg->data.c_str());
		send_goal(goalAL);
      }   
     if(msg->data== "MN")
      {
		ROS_INFO("the massage that was received was : %s" , msg->data.c_str());
		send_goal(goalMN);
      }    
     if(msg->data== "FORKLIFT23")
      {
		ROS_INFO("the massage that was received was : %s" , msg->data.c_str());
		send_goal(goalFORKLIFT23);
      }   

}
int main(int argc, char** argv){

        ros::init(argc, argv, "simple_navigation_goals");
        ros::NodeHandle n ;

        ros::Subscriber sub = n.subscribe("barcode", 1000,Callback);  //goalA_request subscribe to this topic will call the function call back                       
        ros::spin();



  
  return 0;
}

