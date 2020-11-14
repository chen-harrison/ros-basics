#include <ros/ros.h>
#include "ros_tutorials_topic/MsgTutorial.h"    // generated from MsgTutorial.msg


// message callback function
void msgCallback(const ros_tutorials_topic::MsgTutorial::ConstPtr& msg)
{
    ROS_INFO("receive msg = %d", msg->stamp.sec);
    ROS_INFO("receive msg = %d", msg->stamp.nsec);
    ROS_INFO("receive msg = %d", msg->data);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic_subscriber");  // node name = "topic_subscriber"
    ros::NodeHandle nh;
    // subscriber ros_tutorial_sub retrieves MsgTutorial type messages from the topic "ros_tutorial_msg"
    // queue is set to 100 to match publisher
    // callback function used in nh.subscribe
    ros::Subscriber ros_tutorial_sub = nh.subscribe("ros_tutorial_msg", 100, msgCallback);

    ros::spin();    // waits for message and executes callback when received

    return 0;
}