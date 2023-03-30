#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"

#include "ros/ros.h"
#include "std_msgs/Int8.h"

#define PORT    8080
#define MAXLINE 1024

int nilai;

void pesanCB(const std_msgs::Int8::ConstPtr& msg){
    nilai = msg->data;
    // printf("%d", nilai);
    std::cout << nilai << std::endl;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "nowadays");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("topik", 1000, pesanCB);
    ros::spin();
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "hehehe";
    struct sockaddr_in servaddr, cliaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM , 0)) < 0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    socklen_t len, n;

    len = sizeof(cliaddr);
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct  sockaddr *) &cliaddr, &len);
    buffer[n] = '\0';

    printf("Client : %s\n", buffer);
    sendto(sockfd,(const char *)hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&cliaddr, len);
    printf("message hello sent");
    return 0;
}