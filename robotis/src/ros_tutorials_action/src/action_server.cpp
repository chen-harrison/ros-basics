#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "ros_tutorials_action/FibonacciAction.h"

class FibonacciAction
{
protected:
    ros::NodeHandle nh_;                                                        // node handle
    actionlib::SimpleActionServer<ros_tutorials_action::FibonacciAction> as_;   // action server
    std::string action_name_;

    // action feedback, result to publish
    ros_tutorials_action::FibonacciFeedback feedback_;
    ros_tutorials_action::FibonacciResult result_;

public:
    // initalize action server (node handle, action name, action callback function)
    FibonacciAction(std::string name) : as_(nh_, name, boost::bind(&FibonacciAction::executeCB, this, _1), false), action_name_(name)
    {
        as_.start();
    }

    ~FibonacciAction(void)
    {
    }

    void executeCB(const ros_tutorials_action::FibonacciGoalConstPtr &goal)
    {
        ros::Rate r(1);         // frequency = 1 Hz
        bool success = true;    // used to monitor status of action

        // setting first two numbers of sequence
        feedback_.sequence.clear();
        feedback_.sequence.push_back(0);
        feedback_.sequence.push_back(1);

        // notify the user of action name, goal, initial two values of Fibonacci sequence
        ROS_INFO("%s: executing, creating Fibonacci sequence of order %i with seeds %i, %i", action_name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

        for (int i = 1; i <= goal->order; i++) {
            if (as_.isPreemptRequested() || !ros::ok()) {
                ROS_INFO("%s: preempted", action_name_.c_str());    // cancellation msg
                as_.setPreempted();
                success = false;
                break;
            }
            // append next number in Fibonacci sequence to the end, then publish it
            feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i-1]);
            as_.publishFeedback(feedback_);
            r.sleep();
        }

        if(success) {
            // set result equal to final feedback and print
            result_.sequence = feedback_.sequence;
            ROS_INFO("%s: succeeded", action_name_.c_str());
            as_.setSucceeded(result_);
        }
    }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "action_server");             // node name = "action_server"
    FibonacciAction fibonacci("ros_tutorial_action");   // Fibonacci declaration
    ros::spin();                                        // wait
    return 0;
}