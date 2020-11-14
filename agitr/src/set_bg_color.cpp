// changes background color of turtlesim
#include <ros/ros.h>
#include <std_srvs/Empty.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "set_bg_color");
    ros::NodeHandle nh;

    // wait until clear service is available, which means turtlesim is up
    ros::service::waitForService("clear");

    // set background color
    ros::param::set("turtlesim/background_r", 255);
    ros::param::set("turtlesim/background_g", 255);
    ros::param::set("turtlesim/background_b", 0);

    // get turtllesim to pick up new parameter values
    ros::ServiceClient clearClient = nh.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty srv;
    clearClient.call(srv);
}