// ROS version of the standard "hello, world" program
#include <ros/ros.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "hello_ros");
    ros::NodeHandle nh;

    ROS_INFO_STREAM("Hello, ROS!");
}