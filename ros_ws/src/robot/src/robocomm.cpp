// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include "stdint.h"

#include "ros/ros.h"
#include "stdio.h"
#include "iostream"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"

// std_msgs::Float32 posX, posY;


uint8_t pesantoSTM[20];
union{
    float nilai;
    uint8_t bytes[4];
}x, y, actX, actY, camDepth;

int16_t hadapRobot;

void kecX(const std_msgs::Float32::ConstPtr & pesan){
    x.nilai = pesan->data;
    pesantoSTM[1] = x.bytes[0];
    pesantoSTM[2] = x.bytes[1];
    pesantoSTM[3] = x.bytes[2];
    pesantoSTM[4] = x.bytes[3];
}

void kecY(const std_msgs::Float32::ConstPtr & pesan){
    y.nilai = pesan->data;
    pesantoSTM[5] = y.bytes[0];
    pesantoSTM[6] = y.bytes[1];
    pesantoSTM[7] = y.bytes[2];
    pesantoSTM[8] = y.bytes[3];
}

void draco(const std_msgs::Bool::ConstPtr & pesan){
    if(pesan -> data == 0){
        pesantoSTM[0] = '!';
    }
    else if(pesan -> data){
        pesantoSTM[0] = '#';
    }
}

void ngadap(const std_msgs::Int32::ConstPtr & hadap){
    pesantoSTM[9] = (hadap->data) >> 8;
    pesantoSTM[10] = hadap->data;
}

//Pesan camera nanti ke arduino kemungkinan
void camerax(const std_msgs::Int32::ConstPtr & sumbux){
    pesantoSTM[11] = (sumbux->data) >> 8;
    pesantoSTM[12] = sumbux->data;
}
void cameray(const std_msgs::Int32::ConstPtr & sumbuy){
    pesantoSTM[13] = (sumbuy->data) >> 8;
    pesantoSTM[14] = sumbuy->data;
}
void cameradepth(const std_msgs::Float32::ConstPtr & dalam){
    camDepth.nilai = dalam->data;
    pesantoSTM[15] = camDepth.bytes[0];
    pesantoSTM[16] = camDepth.bytes[1];
    pesantoSTM[17] = camDepth.bytes[2];
    pesantoSTM[18] = camDepth.bytes[3];
}


int main(int argc, char **argv) {
    //ROS initialize
    ros::init(argc, argv , "robotcomm");
    ros::NodeHandle nh;


    ros::Subscriber spX = nh.subscribe("spX", 100, kecX);
    ros::Subscriber spY = nh.subscribe("spy", 100, kecY);
    ros::Subscriber hadap = nh.subscribe("hadap", 100, ngadap);
    ros::Subscriber mode = nh.subscribe("mode", 100, draco);
    ros::Subscriber camx = nh.subscribe("camx", 100, camerax);
    ros::Subscriber camy = nh.subscribe("camy", 100, cameray);
    ros::Subscriber camd = nh.subscribe("camd", 100, cameradepth);


    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    int serial_port = open("/dev/ttyACM0", O_RDWR); //port stm32f4 /dev/ttyACM0

    // Create new termios struct, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, __MAX_BAUD);
    cfsetospeed(&tty, __MAX_BAUD);

    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return 1;
    }

    // Write to serial port
    // unsigned char msg[] = { 'H', 'e', 'l', 'l', 'o', '\r' };
    // write(serial_port, msg, sizeof(msg));
    

    // Allocate memory for read buffer, set size according to your needs
    //   char read_buf [256];
    uint8_t read_buf[256];

    // Normally you wouldn't do this memset() call, but since we will just receive
    // ASCII data for this example, we'll set everything to 0 so we can
    // call printf() easily.
    memset(&read_buf, '\0', sizeof(read_buf));

    // Read bytes. The behaviour of read() (e.g. does it block?,
    // how long does it block for?) depends on the configuration
    // settings above, specifically VMIN and VTIME
    int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    if (num_bytes < 0) {
        printf("Error reading: %s", strerror(errno));
        return 1;
    }

    // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
    // print it to the screen like this!)
    printf("Read %i bytes. Received message: %s", num_bytes, read_buf);
    while (ros::ok()){
        write(serial_port, pesantoSTM, sizeof(pesantoSTM));
        read(serial_port, &read_buf, sizeof(read_buf));

        //parsing data yang diterima dulu
        if(read_buf[0] == '*'){
            actX.bytes[0] = read_buf[1];
            actX.bytes[1] = read_buf[2];
            actX.bytes[2] = read_buf[3];
            actX.bytes[3] = read_buf[4];
            actY.bytes[0] = read_buf[5];
            actY.bytes[1] = read_buf[6];
            actY.bytes[2] = read_buf[7];
            actY.bytes[3] = read_buf[8];
            hadapRobot = (read_buf[9] << 8 | read_buf[10]);

        }
        
        //clear
        memset(&read_buf, '\0', sizeof(read_buf));

    }
    close(serial_port);
    return 0; // success
}
