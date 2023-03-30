/*
    Subscribe 1Byte array
    https://www.theconstructsim.com/dealing-bytemultiarray-messages-video-tutorial/
*/
#include "ros/ros.h"

#include "stdio.h"
#include "iostream"
#include "vector"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/ByteMultiArray.h"

uint8_t Myvar[100];
int out;
void arrayCB(const std_msgs::ByteMultiArray::ConstPtr& array){
    int i = 0;
    for(std::vector<signed char>::const_iterator it = array->data.begin(); it != array->data.end(); it++){
        Myvar[i] = *it;
        ROS_INFO("%d",Myvar[i]);
        i++;
    }
    if(Myvar[0] == '!'){
        out = (Myvar[1] << 24 | Myvar[2] << 16 | Myvar[3] << 8 | Myvar [4]);
    }
    // printf(out);
    std::cout << out << std::endl;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "subreker");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topic", 20, arrayCB);

    ros::spin();
    return 0;
}