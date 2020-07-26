#include <ros/ros.h>
#include <turtlesim/Spawn.h>

#define M_PI 3.14159265358979323846


int main(int argc, char **argv)
{
    ros::init(argc, argv, "spawn_turtle");
    ros::NodeHandle nh;

    // create client object for spawn service
    ros::ServiceClient spawnClient = nh.serviceClient<turtlesim::Spawn>("spawn");

    // create request and response objects
    turtlesim::Spawn::Request req;
    turtlesim::Spawn::Response resp;

    req.x = 2;
    req.y = 3;
    req.theta = M_PI / 2;
    req.name = "Leo";

    bool success = spawnClient.call(req, resp);

    // check if success
    if (success) {
        ROS_INFO_STREAM("Spawned a turtle named " << resp.name);
    } else {
        ROS_ERROR_STREAM("Failed to spawn");
    }
}