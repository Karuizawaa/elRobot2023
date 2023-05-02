#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include "stdio.h"
#include "stdint.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"



std_msgs::Int8 x, y, tiang, rotate;

int8_t prevX, prevY, prevTiang, prevRotate;

struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int getch()
{
    int r;
    uint8_t c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void kirim(){
    
}

int main(int argc, char **argv)
{
    set_conio_terminal_mode();
    ros::init(argc, argv, "kibod");
    ros::NodeHandle n;

    ros::Publisher xPub = n.advertise<std_msgs::Int8>("x", 1000);
    ros::Publisher yPub = n.advertise<std_msgs::Int8>("y", 1000);
    ros::Publisher tiangPub = n.advertise<std_msgs::Int8>("poles", 1000);
    ros::Publisher rotatePub = n.advertise<std_msgs::Int8>("rotate", 1000);
    ros::Rate loop_rate(33);

    while(ros::ok()){
        uint8_t ip = 0;
        if(kbhit()){
            ip = getch();
            if (ip == '\033') { // if the first value is esc
                getch(); // skip the [
                switch(getch()) { // the real value
                    case 'A':
                        // code for arrow up
                        printf("atas\n");
                        y.data = 1;
                        break;
                    case 'B':
                        // code for arrow down
                        printf("bawah\n");
                        y.data = -1;
                        break;
                    case 'C':
                        // code for arrow right
                        printf("kanan\n");
                        x.data = 1;
                        break;
                    case 'D':
                        // code for arrow left
                        printf("kiri\n");
                        x.data = -1;
                        break;
                }
            } 
            else{
                if(ip == '1') tiang.data = 1;
                if(ip == '2') tiang.data = 2;
                if(ip == '3') tiang.data = 3;
                if(ip == '4') tiang.data = 4;
                if(ip == '0') tiang.data = 0;
                if(ip == 9) rotate.data = -1;
                if(ip == 92) rotate.data = 1;
                printf("%d\n", ip);
            }
        }
        if(ip == 0){
            x.data = 0;
            y.data = 0;
            rotate.data = 0;
            
        }
        ros::spinOnce();
        if(prevTiang != tiang.data) tiangPub.publish(tiang);
        prevTiang = tiang.data;

        if(prevX != x.data) xPub.publish(x);
        prevX = x.data;

        if(prevY != y.data) yPub.publish(y);
        prevY = y.data;

        if(prevRotate != rotate.data) rotatePub.publish(rotate);
        prevRotate = rotate.data;

        loop_rate.sleep();
    }
    (void)getch(); /* consume the character */
}