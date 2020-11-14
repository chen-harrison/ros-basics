#include <ros/ros.h>
#include <cstdlib>
#include "ros_tutorials_service/SrvTutorial.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "service_client");    // node name = "service_client"

    // error check (incorrect use)
    if (argc != 3) {
        ROS_INFO("cmd : rosrun ros_tutorials_service client arg0 arg1");
        ROS_INFO("arg0: double number, arg1: double number");
        return 1;
    }

    ros::NodeHandle nh;
    // service name is ros_tutorial_srv
    ros::ServiceClient ros_tutorials_service_client = nh.serviceClient<ros_tutorials_service::SrvTutorial>("ros_tutorial_srv");

    // initialize service variable and assign inputs
    ros_tutorials_service::SrvTutorial srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    if (ros_tutorials_service_client.call(srv)) {
        ROS_INFO("send srv, srv.request.a and b: %ld, %ld", (long int)srv.request.a, (long int)srv.request.b);
        ROS_INFO("receive srv, srv.response.result: %ld", (long int)srv.response.result);
    } else {
        ROS_ERROR("failed to call service ros_tutorial_srv");
        return 1;
    }

    return 0;
}
