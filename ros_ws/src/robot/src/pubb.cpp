/*
    Publish 1 Byte array
    https://www.theconstructsim.com/dealing-bytemultiarray-messages-video-tutorial/
*/

#include "ros/ros.h"

#include "vector"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/ByteMultiArray.h"

int wkwk = -1945;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "kocak");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::ByteMultiArray>("topic", 20);

    while(ros::ok()){
        std_msgs::ByteMultiArray array;
        array.data.clear();
        array.data.push_back('!');
        array.data.push_back(wkwk >> 24);
        array.data.push_back(wkwk >> 16);
        array.data.push_back(wkwk >> 8);
        array.data.push_back(wkwk);
        // array.data[0] = '!';
        // array.data[1] = wkwk >> 24;
        // array.data[2] = wkwk >> 16;
        // array.data[3] = wkwk >> 8;
        // array.data[4] = wkwk;

        pub.publish(array);

        ros::spinOnce();
        sleep(2);
    }
    return 0;
}
