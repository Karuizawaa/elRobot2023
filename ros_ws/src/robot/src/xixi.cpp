// Server side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "iostream"
#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	long int encoder;
	const char *hello = "eak";
	int pwm;
	char strPWM[10];
	sprintf(strPWM, "%d", pwm);
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	// servaddr.sin_addr.s_addr = inet_addr("192.168.0.3");
	// servaddr.sin_addr.s_addr = INADDR_ANY;
	// servaddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET,"192.168.0.3",&servaddr.sin_addr);

	servaddr.sin_port = htons(5555);

	cliaddr.sin_family = AF_INET; // IPv4
	// cliaddr.sin_addr.s_addr = inet_addr("192.168.0.5");
	inet_pton(AF_INET,"192.168.0.3",&cliaddr.sin_addr);
	// inet_aton("192.168.0.5", &cliaddr.sin_addr.s_addr);

	cliaddr.sin_port = htons(8888);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	while(1)
	{

		socklen_t len;
		int n;
		len = sizeof(cliaddr); //len is value/result
		std::cin >> pwm;
		sprintf(strPWM, "%d", pwm);

		// n = recvfrom(sockfd, (long int *)buffer, MAXLINE,
		// 			0, ( struct sockaddr *) &cliaddr,
		// 			&len);
		// buffer[n] = '\0';
		// encoder = atoi(buffer);
		// // printf("Client : %s\n", buffer);
		// std::cout<<encoder<<std::endl;

		sendto(sockfd, (const int *)strPWM, strlen(strPWM),
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
				len);
		// std::cout<<"Hello message sent."<<std::endl;
	}	
	
	return 0;
}