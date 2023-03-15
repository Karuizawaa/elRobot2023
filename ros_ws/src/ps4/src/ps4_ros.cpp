#include <string>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"
#include "std_msgs/UInt8.h"

class PS4_ROS {

public:

    /**
     * @brief      { PS4 to TWIST MESSAGES }
     *
     */
    PS4_ROS(ros::NodeHandle &n) {
        // get ros param
        ros::NodeHandle private_nh("~");
        private_nh.param("scale_linear", this->scale_linear, 1.0);
        private_nh.param("scale_angular", this->scale_angular, 1.0);
        private_nh.param<std::string>("pub_topic", this->pubName, "/searchbot/p3at/vel_cmd");

        this->chat = n.advertise<geometry_msgs::Twist>(pubName, 1000);
        this->sub = n.subscribe<sensor_msgs::Joy>("/joy", 1000, &PS4_ROS::subscribePS4, this);

        // this->pubpetak = n.advertise<std_msgs::Bool> ("petak", 10);
        // this->pubkali = n.advertise<std_msgs::Bool> ("kali", 10);
        // this->pubbulet = n.advertise<std_msgs::Bool> ("bulet", 10);
        // this->publupis = n.advertise<std_msgs::Bool> ("lupis", 10);
        this->pubL1 = n.advertise<std_msgs::Bool> ("lsatu", 10);
        // this->pubR1 = n.advertise<std_msgs::Bool> ("rsatu", 10);
        // this->publeft = n.advertise<std_msgs::Bool> ("left", 10);
        // this->pubdown = n.advertise<std_msgs::Bool> ("down", 10);
        // this->pubright = n.advertise<std_msgs::Bool> ("right", 10);
        // this->pubup = n.advertise<std_msgs::Bool> ("up", 10);
        // this->pubL2 = n.advertise<std_msgs::Float32> ("ldua", 10);
        // this->pubR2 = n.advertise<std_msgs::Float32> ("rdua", 10);
        // this->pubrightX = n.advertise<std_msgs::Float32> ("rx", 10);
        // this->pubrightY = n.advertise<std_msgs::Float32> ("ry", 10);
        // this->publeftX = n.advertise<std_msgs::Float32> ("lx", 10);
        // this->publeftY = n.advertise<std_msgs::Float32> ("ly", 10);
        this->pubCase = n.advertise<std_msgs::UInt8> ("case", 1000);
        
        /* set calibration counter to zero */
        this->calib1 = 0;
        this->calib2 = 0;
        this->calib = false;

        this->maxVel = this->scale_linear;
        this->maxVelR = this->scale_linear * -1;

        ROS_INFO("maxVelR: %f", this->maxVelR);

        ROS_INFO("scale_linear set to: %f", this->scale_linear);
        ROS_INFO("scale_angular set to: %f", this->scale_angular);
        ROS_INFO("PS4_ROS initialized");
    }

    ~PS4_ROS() {
        // std::cout << "Destroy the pointer" << std::endl;
    }

    void run() {
        if(this->calib) {
            this->publishTwistMsg();
        }
    }

    void prepareData()
    {
        // Normalize velocity between ]-1.0, 1.0[
        this->send_l2 = (-0.5 * this->l2) + 0.5;
        this->send_r2 = (this->r2 - 1.0) * 0.5;

        // Apply rosparam "scale_linear"
        this->send_l2 = this->scale_linear * this->send_l2;
        this->send_r2 = this->scale_linear * this->send_r2;

        // Apply rosparam "scale_angular"
        this->send_leftStickX = this->scale_angular * this->leftStickX;
    }

    void publishTwistMsg() {
        geometry_msgs::Twist msg;
        msg.linear.x = 0.0;
        msg.linear.y = 0.0;
        msg.linear.z = 0.0;

        msg.angular.x = 0.0;
        msg.angular.y = 0.0;
        msg.angular.z = 0.0;

        prepareData();

        //printRaw();
        if(!this->buttonTouch) {
            if ((this->send_l2 >= 0.1) && (this->send_l2 <= maxVel)) {
                msg.linear.x = this->send_l2;
            } else if ((this->send_r2 <= 0.0) && (this->send_r2 >= maxVelR)) {
                msg.linear.x = this->send_r2;
            }
            msg.angular.z = this->send_leftStickX;
        }
        else{
            //ROS_WARN("SENDING EMERGENCY STOP");

            /* To Do */
        }

        this->chat.publish(msg);
    }

    void subscribePS4(const sensor_msgs::Joy::ConstPtr &joy) {
        this->buttonSq = joy->buttons[0];
        petak.data = joy->buttons[0];
        if(petak.data == 1) caseRobot.data = 1;

        this->buttonX = joy->buttons[1];
        silang.data = joy->buttons[1];
        if(silang.data == 1) caseRobot.data = 2;

        this->buttonO = joy->buttons[2];
        bulet.data = joy->buttons[2];
        if(bulet.data == 1) caseRobot.data = 3;

        this->buttonTr = joy->buttons[3];
        lupis.data = joy->buttons[3];
        if(lupis.data == 1) caseRobot.data = 4;

        if(joy->buttons[11]) caseRobot.data = 5;

        this->buttonTouch = joy->buttons[13];

        this->l1 = joy->buttons[4];
        
        L1.data = joy->buttons[4];

        this->r1 = joy->buttons[5];
        R1.data = joy->buttons[5];
        if(R1.data == 1) caseRobot.data = 0;

        this->arrowsX = joy->axes[9];
        if (this->arrowsX == -1){
            left.data = 0;
            right.data = 1;
        }
        else if (this->arrowsX == 1){
            left.data = 1;
            right.data = 0;
        }
        else{
            left.data = 0;
            right.data = 0;
        }
        this->arrowsY = joy->axes[10];
        if(this->arrowsY == -1){
            up.data = 0;
            down.data = 1;
        }
        else if(this->arrowsY == 1){
            up.data = 1;
            down.data = 0;
        }
        else{
            up.data = 0;
            down.data = 0;
        }
        this->l2 = joy->axes[3];
        L2.data = joy->axes[3];

        this->r2 = joy->axes[4];
        R2.data = joy->axes[4];

        this->leftStickX = joy->axes[0];
        leftX.data = joy->axes[0];

        this->leftStickY = joy->axes[1];
        leftY.data = joy->axes[1];

        this->rightStickX = joy->axes[2];
        rightX.data = joy->axes[2];

        this->rightStickY = joy->axes[5];
        rightY.data = joy->axes[5];


        
        kirim();
        // printRaw();

    }

    void kirim(){
        // pubpetak.publish(petak);
        // pubkali.publish(silang);
        // pubbulet.publish(bulet);
        // publupis.publish(lupis);
        // pubL1.publish(L1);
        // pubR1.publish(R1);
        // publeft.publish(left);
        // pubdown.publish(down);
        // pubright.publish(right);
        // pubup.publish(up);
        // pubL2.publish(L2);
        // pubR2.publish(R2);
        // publeftX.publish(leftX);
        // publeftY.publish(leftY);
        if(caseRobot.data != prevCase){
            pubCase.publish(caseRobot);
            prevCase = caseRobot.data;
        }
        if(L1.data != prevL1){
            pubL1.publish(L1);
            prevL1 = L1.data;
        }
        
    }

    bool calibrate()
    {
        double progress = ((double) this->calib1 / this->calib_duration) * 100;
        if( (this->l2 == -1.0) && (this->r2 == -1.0) )
        {
            ROS_WARN("Press L2 and R2 to calibrate: %i%% ", (int) progress);
            this->calib1++;
            this->calib2++;
        }
        else{
            this->calib1 = 0;
            this->calib2 = 0;
        }

        if( (this->calib1 > this->calib_duration) && (this->calib2 > this->calib_duration))
        {
            this->calib = true;
            return true;
        }
        else
            return false;
    }

    bool waitForRelease()
    {
        if( (this->l2 == 1.0) && (this->r2 == 1.0) )
        {
            return true;
        }
        else{
            return false;
        }
    }

    void printSend()
    {

        ROS_INFO("#####################################");
        ROS_INFO("Send L2: %f", this->send_l2);
        ROS_INFO("Send R2: %f", this->send_r2);
        ROS_INFO("##################################### \n");
    }

    void printRaw()
    {

        ROS_INFO("#####################################");
        ROS_INFO("Squared Button pressed: %i", this->buttonSq);
        ROS_INFO("X Button pressed: %i", this->buttonX);
        ROS_INFO("O Button pressed: %i", this->buttonO);
        ROS_INFO("Triangel Button pressed: %i", this->buttonTr);
        ROS_INFO("Left/Right Button pressed: %i", this->arrowsX);
        ROS_INFO("Down/Up Button pressed: %i", this->arrowsY);
        ROS_INFO("Touch Button pressed: %i", this->buttonTouch);
        ROS_INFO("L1: %i", this->l1);
        ROS_INFO("R1: %i", this->r1);
        ROS_INFO("L2: %f", this->l2);
        ROS_INFO("R2: %f", this->r2);
        ROS_INFO("Left Stick Y: %f", this->leftStickY);
        ROS_INFO("Left Stick X: %f", this->leftStickX);
        ROS_INFO("Right Stick Y: %f", this->rightStickY);
        ROS_INFO("Right Stick X: %f", this->rightStickX);
        ROS_INFO("##################################### \n");
    }

private:
    ros::Publisher chat;
    ros::Publisher pubpetak;
    ros::Publisher pubkali;
    ros::Publisher pubbulet;
    ros::Publisher publupis;
    ros::Publisher pubL1;
    ros::Publisher pubR1;
    ros::Publisher pubL2;
    ros::Publisher pubR2;
    ros::Publisher publeft;
    ros::Publisher pubright;
    ros::Publisher pubup;
    ros::Publisher pubdown;
    ros::Publisher publeftX;
    ros::Publisher publeftY;
    ros::Publisher pubrightX;
    ros::Publisher pubrightY;
    ros::Subscriber sub;
    ros::Publisher pubCase;


    std_msgs::Bool petak, silang, bulet, lupis, L1, R1, left, right, up, down;
    std_msgs::Float32 R2, L2, leftX, leftY, rightX, rightY;

    std_msgs::UInt8 caseRobot;
    uint8_t prevCase;
    uint8_t prevL1;

    /* calibration variables */
    int calib_duration = 20; // 1/10 sec
    int calib1, calib2;
    bool calib;

    /* raw data */
    double leftStickY, leftStickX, rightStickY, rightStickX, l2, r2;
    int arrowsX, arrowsY, buttonSq, buttonX, buttonO, buttonTr,
        buttonTouch, l1, r1;

    /* rosparams */
    double scale_linear, scale_angular;
    std::string pubName;

    double maxVel, maxVelR;

    /* send data */
    double send_leftStickX, send_l2, send_r2;

};

int main(int argc, char **argv) {
	ros::init(argc, argv, "PS4_ROS");
    ros::NodeHandle n;

    // create ps4_ros object
    PS4_ROS *ps4_ros = new PS4_ROS(n);

    // calibrate
    ROS_WARN("Press L2 and R2 to calibrate");
    bool ready = false;
    while(!ready)
    {
        ready = ps4_ros->calibrate();
        ros::spinOnce();
        ros::Duration(0.1).sleep();
    }

    ROS_WARN("Release L2 and R2");
    ros::Duration(2.0).sleep();
    ready = false;
    while(!ready)
    {
        ready = ps4_ros->waitForRelease();
        ros::spinOnce();
        ros::Duration(0.1).sleep();
    }
    ROS_INFO("Calibrated - Ready to use");

    ros::Rate loop_rate(1000);
    while(ros::ok())
    {
        ps4_ros->run();
        ros::spinOnce();
        loop_rate.sleep();
    }

    delete ps4_ros;
	return 0;
}
