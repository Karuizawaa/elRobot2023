// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "ros/ros.h"

#include "vector"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/ByteMultiArray.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "otege");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::ByteMultiArray>("info", 1000);
}