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
#include "time.h"
#include "string"
#include "cmath"
#include "chrono"
#include <bits/stdc++.h>

// #include "ros/ros.h"
// #include "std_msgs/UInt8.h"
// #include "std_msgs/Bool.h"

#define PORT	 8080
#define MAXLINE 1024

#define RADIUSMTR 0.35145 //satuan meter
#define RADIUSBAN 0.1/2
#define KBAN 2*M_PI*RADIUSBAN

#define PPR 200*19.2

#define POSM1   45
#define POSM2   135
#define POSM3   225
#define POSM4   315


#define KPx		1
#define KIx		1
#define KPy		1
#define KIy		1
#define KPt		1
#define KIt		1
std::string convertToString(char* a, int size);

class Device{
	public:
	struct sockaddr_in alamat, cli_addr;
	long int enc, lastenc, prevenc;
	char buffer[MAXLINE];
	char terima[MAXLINE];
	char terimaSpesifik[MAXLINE];
	int sizeReceive;
	float sum;
	float hadap;
	std::string deviceIP;
	socklen_t len;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	Device(char *IP, unsigned long port){
		memset(&alamat, 0, sizeof(alamat));
		memset(&cli_addr, 0, sizeof(cli_addr));
		deviceIP = IP;
		Device::alamat.sin_family = AF_INET;
		inet_pton(AF_INET, IP, &alamat.sin_addr.s_addr);
		alamat.sin_port = htons(port);
		len = sizeof(alamat);
		
	}

	/* Send UDP */
	void send(int soket, std::string pesan){
		sendto(soket, pesan.c_str(), strlen(pesan.c_str()),
			MSG_CONFIRM, (const struct sockaddr *) &alamat,
				len);
	}
	/* Receive UDP */
	void receive(int soket){
		socklen_t sender_addr_len = sizeof(cli_addr);
		sizeReceive = recvfrom(soket, (char *)buffer, MAXLINE,
					0, ( struct sockaddr *) &cli_addr,
					&sender_addr_len);
		buffer[sizeReceive] = '\0';
		std::string senderIP = inet_ntoa(cli_addr.sin_addr);
		if(senderIP == deviceIP){
			strncpy(terima, buffer, MAXLINE);
			enc = atoi(terima);
		}
		if(senderIP == "192.168.0.99"){
			strncpy(terima, buffer, MAXLINE);
			hadap = atof(strtok(terima+11, "~"));
		}

	}

	/* PID Process alamat */
	float PID(int KP, int KI, float setradPS, int PULSEPERREV){
		begin = std::chrono::steady_clock::now();
		float nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		float second = nanosec * pow(10,9);
		float radps = ((enc - lastenc) * 2 * M_PI / PULSEPERREV) / second;
		lastenc = enc;
		float error = setradPS - radps;
		sum += error;
		end = std::chrono::steady_clock::now();
		// this->send(sockfd, std::to_string())
		return(KP * error + KI * sum);
	}
};

float XSmoothed, YSmoothed, TSmoothed;
float XPrev, YPrev, TPrev;
float setX, setY, setT;
float x,y;
float x_temp, y_temp;
float setradPS1, setradPS2, setradPS3, setradPS4;
float sumX, sumY, sumT;
bool l1;

int8_t lantai;
uint8_t indexTiang;

std::chrono::steady_clock::time_point mulai;
std::chrono::steady_clock::time_point akhir;

int sockfd;
int caseRobot;

Device roda1("192.168.0.11", 5555);
Device roda2("192.168.0.12", 5555);
Device roda3("192.168.0.13", 5555);
Device roda4("192.168.0.14", 5555);
Device falcon("192.168.0.15", 5555);
Device MEGA("192.168.0.99", 8888);

// void caseCB(const std_msgs::UInt8::ConstPtr& msg)
// {
// 	caseRobot = msg->data;
// }

// void bacaL1(const std_msgs::Bool::ConstPtr& msg)
// {
// 	l1 = msg->data;
// 	if(l1 == true) lantai++;
// 	if(lantai > 10) lantai = 0;
// }

// void bacaO(const std_msgs::Bool::ConstPtr& msg)
// {
// 	if(msg->data == true) indexTiang++;
// }

// void bacaTr(const std_msgs::Bool::ConstPtr& msg)
// {
// 	if(msg->data == true) indexTiang--;
// }

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void delayms(int millisec){
	clock_t start_time = clock();
	while (clock()  < millisec + start_time);
}

float toRad(float degree) {
  return degree * M_PI / 180;
}

void smoothing() {
  //smoothing
  XSmoothed = (setX * 0.000007) + (XPrev * 0.999993);
  XPrev = XSmoothed;
  YSmoothed = (setY * 0.000007) + (YPrev * 0.999993);
  YPrev = YSmoothed;
  TSmoothed = (setT * 0.000007) + (TPrev * 0.999993);
  TPrev = TSmoothed;
}

void kinematic(float vX, float vY, float theta, float heading) {
	float setradPS1 = (-sin(toRad(POSM1 + heading)) * vX + cos(toRad(POSM1 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS2 = (-sin(toRad(POSM2 + heading)) * vX + cos(toRad(POSM2 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS3 = (-sin(toRad(POSM3 + heading)) * vX + cos(toRad(POSM3 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS4 = (-sin(toRad(POSM4 + heading)) * vX + cos(toRad(POSM4 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;

	roda1.send(sockfd, std::to_string(roda1.PID(1,1,setradPS1,PPR)));
	roda2.send(sockfd, std::to_string(roda1.PID(1,1,setradPS2,PPR)));
	roda3.send(sockfd, std::to_string(roda1.PID(1,1,setradPS3,PPR)));
	roda4.send(sockfd, std::to_string(roda1.PID(1,1,setradPS4,PPR)));  
}

void calculatePos() {
	//displacement
	float v1 = (roda1.enc - roda1.prevenc) * KBAN / (PPR);
	float v2 = (roda2.enc - roda2.prevenc) * KBAN / (PPR);
	float v3 = (roda3.enc - roda3.prevenc) * KBAN / (PPR);
	float v4 = (roda4.enc - roda4.prevenc) * KBAN / (PPR);

	roda1.prevenc = roda1.enc;
	roda2.prevenc = roda2.enc;
	roda3.prevenc = roda3.enc;
	roda4.prevenc = roda4.enc;

	float Vx = -sin(toRad(MEGA.enc + POSM1)) * v1 + -sin(toRad(MEGA.enc + POSM2)) * v2 + -sin(toRad(MEGA.enc + POSM3)) * v3 + -sin(toRad(MEGA.enc + POSM4)) * v4;
	float Vy = cos(toRad(MEGA.enc + POSM1)) * v1 + cos(toRad(MEGA.enc + POSM2)) * v2 + cos(toRad(MEGA.enc + POSM3)) * v3 + cos(toRad(MEGA.enc + POSM4)) * v4;

	x += Vx;
	y += Vy;
}

void setPos(float POSX, float POSY, float HADAP) {
	mulai = std::chrono::steady_clock::now();
	float nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (akhir - mulai).count();
	float deltaT = nanosec * pow(10,9);
	setX = POSX;
	setY = POSY;
	setT = HADAP;
	calculatePos();
	MEGA.receive(sockfd);
	smoothing();
	//PID Posisi
	float errX = XSmoothed - x;
	sumX += errX;
	float PIDx = KPx * errX + KIx * sumX * deltaT;
	//  PIDx = fmaxf(-7.3, fminf(PIDx,7.3));

	float errY = YSmoothed - y;
	sumY += errY;
	float PIDy = KPy * errY + KIy * sumY * deltaT;
	//  PIDy = fmaxf(-7.3, fminf(PIDy, 7.3));


	float errT = TSmoothed - MEGA.enc;
	if(errT > 180 || errT < -180){
	errT = MEGA.enc - TSmoothed;
	}
	sumT += errT;
	float PIDt = KPt * errT + KIt * sumT * deltaT;
	PIDt = fmaxf(-3.7, fminf(PIDt, 3.7));
	kinematic(PIDx, PIDy, PIDt, MEGA.enc);
	akhir = std::chrono::steady_clock::now();
}

float tiangtoRPM(uint8_t tiang){
	if(tiang == 1) return 200;
	else if(tiang == 2) return 200;
	else if(tiang == 3) return 200;
	else if(tiang == 4) return 200;
	else return 0;
}

// Driver code
int main(int argc, char **argv) {
	// ros::init(argc, argv, "elephantRobot", ros::InitOption::NoSigintHandler);
	// ros::NodeHandle n;
	// ros::Subscriber subCase = n.subscribe("/case", 1000, caseCB);
	// ros::Subscriber subBulet = n.subscribe("/bulet", 1000, bacaO);
	// ros::Subscriber subTr = n.subscribe("/lupis", 1000, bacaTr);

	
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	// extern Device roda1;
	// extern Device roda2;
	// extern Device roda3;
	// extern Device roda4;

	// Device roda1("192.168.0.11", 5555);
	// Device roda2("192.168.0.12", 5555);
	Device roda3("192.168.0.13", 5555);
	// Device roda4("192.168.0.14", 5555);
	// Device falcon("192.168.0.15", 5555);
	// Device MEGA("192.168.0.99", 8888);
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	// inet_pton(AF_INET,"192.168.0.55",&servaddr.sin_addr);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(5555);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	while (1){
		// MEGA.receive(sockfd);
		// roda1.receive(sockfd);
		// roda2.receive(sockfd);
		roda3.receive(sockfd);
		// usleep(16000);
		// roda4.receive(sockfd);
		// roda3.send(sockfd,"-250");
		// roda3.send(sockfd, std::to_string(123));
		// std::cout << roda1.enc << "\t" <<roda2.enc << "\t" <<roda3.enc << "\t" <<roda4.enc << std::endl;
		std::cout << roda3.terima << std::endl;
	}
	//s ros::spin();
	// while(1) 
	// {
	// 	if (caseRobot == 1){
	// 		if (y > -9.2) {
	// 			setPos(0, -10.0, 0);
	// 		}
	// 		if (y < -9.2) {
	// 			roda1.sum = 0;
	// 			roda2.sum = 0;
	// 			roda3.sum = 0;
	// 			roda4.sum = 0;
	// 			kinematic(0,0,0,0);
	// 			delayms(1000);

	// 			//nyender fence belakang
	// 			while (!(MEGA.limitSwitch[0] == 0 && MEGA.limitSwitch[1] == 0)) {
	// 				calculatePos();
	// 				kinematic(2.5, 0, 0, 0);
	// 				MEGA.receive(sockfd);
	// 				x_temp = x;
	// 			}
	// 			kinematic(0, 0, 0, 0);
	// 			delayms(1500);
				
	// 			//nyender fence samping
	// 			while (!(MEGA.limitSwitch[2] == 0 && MEGA.limitSwitch[5] == 0)) {
	// 				calculatePos();
	// 				MEGA.receive(sockfd);
	// 				kinematic(0, -3, 0, 0);
	// 			}
	// 			roda1.sum = 0;
	// 			roda2.sum = 0;
	// 			roda3.sum = 0;
	// 			roda4.sum = 0;
	// 			XSmoothed = x;
	// 			YSmoothed = y;
	// 			XPrev = x;
	// 			YPrev = y;
	// 			x_temp = x;
	// 			y_temp = y;
	// 			while (caseRobot == 1) {
	// 				calculatePos();
	// 				kinematic(0, 0, 0, 0);
	// 			}
	// 		}
	// 	}

	// 	if(caseRobot == 2){
	// 		if(x > x_temp - 3){
	// 			setPos(x_temp - 3, y_temp + 3, 45);
	// 		}
	// 		else {
      
	// 			clock_t start_time = clock();
	// 			while (clock()  < 1500 + start_time)
	// 			{
	// 				MEGA.receive(sockfd);
	// 				calculatePos();
	// 				kinematic(0,0,(45 - MEGA.enc) * 0.6 , 0);
	// 			}
				

	// 			while(!(MEGA.limitSwitch[6] == 0 && MEGA.limitSwitch[7] == 0)){
	// 				MEGA.receive(sockfd);
	// 				calculatePos();
	// 				if(MEGA.limitSwitch[6] == 0 && MEGA.limitSwitch[7] == 1){
	// 					kinematic(0,0,2.5,0);
	// 					roda1.sum = 0;
	// 					roda2.sum = 0;
	// 					roda3.sum = 0;
	// 					roda4.sum = 0;
	// 					sumX = 0;
	// 					sumY = 0;
	// 					sumT = 0;
	// 				}
	// 				else if(MEGA.limitSwitch[7] == 0 && MEGA.limitSwitch[6] == 1){
	// 					kinematic(0,0,-2.5,0);
	// 					roda1.sum = 0;
	// 					roda2.sum = 0;
	// 					roda3.sum = 0;
	// 					roda4.sum = 0;
	// 					sumX = 0;
	// 					sumY = 0;
	// 					sumT = 0;
	// 				}
	// 				else if(MEGA.limitSwitch[6] == 1 && MEGA.limitSwitch[7] == 1){
	// 					kinematic(0,2,0,0);

	// 				}
	// 				}
	// 			}
	// 			kinematic(0,0,0,0);
	// 			lantai = 0;
	// 			while(caseRobot == 2){
	// 				calculatePos();
	// 				if (l1 == true) MEGA.send(sockfd, std::to_string(lantai));
	// 				falcon.send(sockfd, std::to_string(tiangtoRPM(indexTiang)));
	// 			}
	// 	}

  	// 	//ambil ring kanan
	// 	if (caseRobot == 8) {
	// 		if (y < 11) {
	// 			setPos(0, 11.8, 178.9);
	// 		}
	// 		if (y > 11 ) {
	// 			roda1.sum = 0;
	// 			roda2.sum = 0;
	// 			roda3.sum = 0;
	// 			roda4.sum = 0;
	// 			kinematic(0,0,0,0);
	// 			delayms(1000);

	// 			//nyender fence belakang
	// 			while (!(MEGA.limitSwitch[3] == 0 && MEGA.limitSwitch[4] == 0)) {
	// 				calculatePos();
	// 				MEGA.receive(sockfd);
	// 				kinematic(-2.5, 0, 0, 0);
	// 				x_temp = x;
	// 			}
	// 			kinematic(0, 0, 0, 0);
	// 			delayms(1500);

	// 			//nyender fence samping
	// 			while (!(MEGA.limitSwitch[5] == 0 && MEGA.limitSwitch[2] == 0)) {
	// 				calculatePos();
	// 				MEGA.receive(sockfd);
	// 				kinematic(0, -3, 0, 0);
	// 			}
	// 			roda1.sum = 0;
	// 			roda2.sum = 0;
	// 			roda3.sum = 0;
	// 			roda4.sum = 0;
	// 			XSmoothed = x;
	// 			YSmoothed = y;
	// 			XPrev = x;
	// 			YPrev = y;
	// 			while (caseRobot == 8) {
	// 				kinematic(0, 0, 0, 0);
	// 			}
	// 		}


	// 	}
	// }	
	return 0;
}