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

#include "ros/ros.h"
#include "std_msgs/UInt8.h"


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

class Device{
	public:
	struct sockaddr_in motor;
	long int enc, lastenc, prevenc;
	char encStr[MAXLINE];
	int sizeReceive;
	float sum;
	bool limitSwitch[10];
	float hadap;
	socklen_t len;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	Device(char *IP, unsigned long port){
		memset(&motor, 0, sizeof(motor));
		Device::motor.sin_family = AF_INET;
		inet_pton(AF_INET, IP, &Device::motor.sin_addr.s_addr);
		Device::motor.sin_port = htons(port);
		len = sizeof(Device::motor);
	}

	/* Send UDP */
	void send(int soket, std::string pesan){
		sendto(soket, pesan.c_str(), strlen(pesan.c_str()),
			MSG_CONFIRM, (const struct sockaddr *) &motor,
				len);
	}
	/* Receive UDP */
	std::string receive(int soket){
		sizeReceive = recvfrom(soket, (char *)encStr, MAXLINE,
					0, ( struct sockaddr *) &motor,
					&len);
		encStr[sizeReceive] = '\0';
		enc = atoi(encStr);

		for(int i = 0; i < 10; i++){
			limitSwitch[i] = atoi((const char*)encStr[i]);
		}
		hadap = atof(strtok(encStr+11,"#"));
		return(encStr);
	}

	/* PID Process motor */
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

std::chrono::steady_clock::time_point mulai;
std::chrono::steady_clock::time_point akhir;

int sockfd;
int caseRobot;

Device roda1("192.168.0.11", 8888);
Device roda2("192.168.0.12", 8888);
Device roda3("192.168.0.13", 8888);
Device roda4("192.168.0.14", 8888);
Device MEGA("192.168.0.15", 8888);

void caseCB(const std_msgs::UInt8::ConstPtr& msg)
{
	caseRobot = msg->data;
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

	roda1.send(sockfd, std::to_string(roda1.PID(14,8,setradPS1,PPR)));
	roda2.send(sockfd, std::to_string(roda1.PID(14,8,setradPS2,PPR)));
	roda3.send(sockfd, std::to_string(roda1.PID(14,8,setradPS3,PPR)));
	roda4.send(sockfd, std::to_string(roda1.PID(14,8,setradPS4,PPR)));  
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


	float errT = TSmoothed - MEGA.hadap;
	if(errT > 180 || errT < -180){
	errT = MEGA.hadap - TSmoothed;
	}
	sumT += errT;
	float PIDt = KPt * errT + KIt * sumT * deltaT;
	PIDt = fmaxf(-3.7, fminf(PIDt, 3.7));
	kinematic(PIDx, PIDy, PIDt, MEGA.hadap);
	akhir = std::chrono::steady_clock::now();
}

// Driver code
int main(int argc, char **argv) {
	ros::init(argc, argv, "elephantRobot");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("chatter", 1000, caseCB);

	
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	inet_pton(AF_INET,"192.168.0.3",&servaddr.sin_addr);
	servaddr.sin_port = htons(5555);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	ros::spin();
	while(1) 
	{
		if (caseRobot == 1){
			if (y > -9.2) {
				setPos(0, -10.0, 0);
			}
			if (y < -9.2) {
				roda1.sum = 0;
				roda2.sum = 0;
				roda3.sum = 0;
				roda4.sum = 0;
				kinematic(0,0,0,0);
				delayms(1000);

				//nyender fence belakang
				while (!(MEGA.limitSwitch[0] == 0 && MEGA.limitSwitch[1] == 0)) {
					calculatePos();
					kinematic(2.5, 0, 0, 0);
					MEGA.receive(sockfd);
					x_temp = x;
				}
				kinematic(0, 0, 0, 0);
				delayms(1500);
				
				//nyender fence samping
				while (!(MEGA.limitSwitch[2] == 0 && MEGA.limitSwitch[5] == 0)) {
					calculatePos();
					MEGA.receive(sockfd);
					kinematic(0, -3, 0, 0);
				}
				roda1.sum = 0;
				roda2.sum = 0;
				roda3.sum = 0;
				roda4.sum = 0;
				XSmoothed = x;
				YSmoothed = y;
				XPrev = x;
				YPrev = y;
				x_temp = x;
				y_temp = y;
				while (caseRobot == 1) {
					calculatePos();
					kinematic(0, 0, 0, 0);
				}
			}
		}

		if(caseRobot == 2){
			if(x > x_temp - 3){
				setPos(x_temp - 3, y_temp + 3, 45);
			}
			else {
      
				clock_t start_time = clock();
				while (clock()  < 1500 + start_time)
				{
					MEGA.receive(sockfd);
					calculatePos();
					kinematic(0,0,(45 - MEGA.enc) * 0.6 , 0);
				}
				

				while(!(MEGA.limitSwitch[6] == 0 && MEGA.limitSwitch[7] == 0)){
					MEGA.receive(sockfd);
					calculatePos();
					if(MEGA.limitSwitch[6] == 0 && MEGA.limitSwitch[7] == 1){
						kinematic(0,0,2.5,0);
						roda1.sum = 0;
						roda2.sum = 0;
						roda3.sum = 0;
						roda4.sum = 0;
						sumX = 0;
						sumY = 0;
						sumT = 0;
					}
					else if(MEGA.limitSwitch[7] == 0 && MEGA.limitSwitch[6] == 1){
						kinematic(0,0,-2.5,0);
						roda1.sum = 0;
						roda2.sum = 0;
						roda3.sum = 0;
						roda4.sum = 0;
						sumX = 0;
						sumY = 0;
						sumT = 0;
					}
					else if(MEGA.limitSwitch[6] == 1 && MEGA.limitSwitch[7] == 1){
						kinematic(0,2,0,0);

					}
					}
					kinematic(0,0,0,0);
					while(caseRobot == 2){
						calculatePos();
					}
				}
		}

  		//ambil ring kanan
		if (caseRobot == 8) {
			if (y < 11) {
				setPos(0, 11.8, 178.9);
			}
			if (y > 11 ) {
				roda1.sum = 0;
				roda2.sum = 0;
				roda3.sum = 0;
				roda4.sum = 0;
				kinematic(0,0,0,0);
				delayms(1000);

				//nyender fence belakang
				while (!(MEGA.limitSwitch[3] == 0 && MEGA.limitSwitch[4] == 0)) {
					calculatePos();
					MEGA.receive(sockfd);
					kinematic(-2.5, 0, 0, 0);
					x_temp = x;
				}
				kinematic(0, 0, 0, 0);
				delayms(1500);

				//nyender fence samping
				while (!(MEGA.limitSwitch[5] == 0 && MEGA.limitSwitch[2] == 0)) {
					calculatePos();
					MEGA.receive(sockfd);
					kinematic(0, -3, 0, 0);
				}
				roda1.sum = 0;
				roda2.sum = 0;
				roda3.sum = 0;
				roda4.sum = 0;
				XSmoothed = x;
				YSmoothed = y;
				XPrev = x;
				YPrev = y;
				while (caseRobot == 8) {
					kinematic(0, 0, 0, 0);
				}
			}


		}
	}	
	
	return 0;
}
