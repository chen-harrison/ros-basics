#include <ros/ros.h>
#include "ros_tutorials_topic/MsgTutorial.h"    // generated from MsgTutorial.msg


int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic_publisher");   // node name = "topic_publisher"
    ros::NodeHandle nh;
    // publisher ros_tutorial_pub publishes MsgTutorial type messages to the topic "ros_tutorial_msg"
    // queue is set to 100
    ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg", 100);
    ros::Rate loop_rate(10);    // rate set to 10 Hz
    ros_tutorials_topic::MsgTutorial msg;   // initialize MsgTutorial type message (aka struct)
    int count = 0;

    while(ros::ok()) {
        // set values in struct
        msg.stamp = ros::Time::now();
        msg.data = count;

        // send prints to terminal?
        ROS_INFO("send msg = %d", msg.stamp.sec);
        ROS_INFO("send msg = %d", msg.stamp.nsec);
        ROS_INFO("send msg = %d", msg.data);

        ros_tutorial_pub.publish(msg);   // publish to topic
        loop_rate.sleep();              // sleep according to set frequency

        ++count;
    }

    return 0;
}