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
#include "std_msgs/Float32.h"

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


#define KPx		2.1
#define KIx		0
#define KPy		2.1
#define KIy		0
#define KPt		0.4
#define KIt		0
std::string convertToString(char* a, int size);

class Device{
	public:
	struct sockaddr_in alamat, cli_addr;
	// struct timeval t1, t2;
	long long enc, lastenc, prevenc;
	char buffer[MAXLINE];
	char terima[MAXLINE];
	char terimaSpesifik[MAXLINE];
	int sizeReceive;
	float sum;
	float hadap;
	float radps;
	std::string deviceIP, senderIP;
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
		do{

			socklen_t sender_addr_len = sizeof(cli_addr);
			sizeReceive = recvfrom(soket, (char *)buffer, MAXLINE,
						0, ( struct sockaddr *) &cli_addr,
						&sender_addr_len);
			buffer[sizeReceive] = '\0';
			senderIP = inet_ntoa(cli_addr.sin_addr);
		}
		while(senderIP != deviceIP);
			
		
		strncpy(terima, buffer, MAXLINE);
		
		if(senderIP == "192.168.0.99"){
			// strncpy(terima, buffer, MAXLINE);
			hadap = atof(strtok(terima+11, "~"));
		}
		else {
			enc = atoi(terima);
		}

	}

	/* PID Process alamat */
	int PID(float KP, float KI, float setradPS, float PULSEPERREV){
		begin = std::chrono::steady_clock::now();
		double nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (begin - end).count();
		radps = ((enc - lastenc) * 2 * M_PI / PULSEPERREV) / (nanosec*pow(10,-9));
		lastenc = enc;
		float error = setradPS - radps;
		sum += error;
		end = std::chrono::steady_clock::now();
		return(KP * error + KI * sum);
	}
};

float XSmoothed, YSmoothed, TSmoothed;
float XPrev, YPrev, TPrev;
float setX, setY, setT;
float x,y,lx,ly,LL,RR;
float x_temp, y_temp;
float setradPS1, setradPS2, setradPS3, setradPS4;
float sumX, sumY, sumT;
bool l1;

int8_t lantai;
uint8_t indexTiang;

bool mode; //false semi auto, true manual stik

std::chrono::steady_clock::time_point mulai;
std::chrono::steady_clock::time_point akhir;

int sockfd;
int caseRobot, prevCase;
uint8_t tombol, prevTombol;

Device roda1("192.168.0.11", 5555);
Device roda2("192.168.0.12", 5555);
Device roda3("192.168.0.13", 5555);
Device roda4("192.168.0.14", 5555);
Device falcon("192.168.0.15", 5555);
Device MEGA("192.168.0.99", 8888);



void readButton(const std_msgs::UInt8::ConstPtr& msg){
	tombol = msg->data;
	if(tombol == 1) caseRobot = 1;
	if(tombol == 2){ 
		caseRobot = 2;
		MEGA.send(sockfd,"#");
	}
	tombol == 6 ? l1 = true: l1 = false;
	if(tombol != prevTombol){
		if(tombol == 3) indexTiang++;
		if(tombol == 4) indexTiang--;
		if(tombol == 6) lantai++;
	
	}
	if(tombol == 9) mode = false;
	if(tombol == 10) mode = true;
	
	prevTombol = tombol;
}

void readLX(const std_msgs::Float32::ConstPtr& msg){
	lx = msg->data;
}
void readLY(const std_msgs::Float32::ConstPtr& msg){
	ly = msg->data;
}
void readLL(const std_msgs::Float32::ConstPtr& msg){
	LL = msg->data;
}
void readRR(const std_msgs::Float32::ConstPtr& msg){
	RR = msg->data;
}

// void delayms(int millisec){
// 	clock_t start_time = clock();
// 	while (clock()  < millisec + start_time);
// }

float toRad(float degree) {
  return degree * M_PI / 180;
}

void smoothing() {
  //smoothing
  XSmoothed = (setX * 0.0009) + (XPrev * 0.9991);
  XPrev = XSmoothed;
  YSmoothed = (setY * 0.0009) + (YPrev * 0.9991);
  YPrev = YSmoothed;
  TSmoothed = (setT * 0.0009) + (TPrev * 0.9991);
  TPrev = TSmoothed;
//   std::cout << YSmoothed << std::endl;
}

void kinematic(float vX, float vY, float theta, float heading) {
	float setradPS1 = (-sin(toRad(POSM1 + heading)) * vX + cos(toRad(POSM1 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS2 = (-sin(toRad(POSM2 + heading)) * vX + cos(toRad(POSM2 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS3 = (-sin(toRad(POSM3 + heading)) * vX + cos(toRad(POSM3 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	float setradPS4 = (-sin(toRad(POSM4 + heading)) * vX + cos(toRad(POSM4 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
	// std::cout << setradPS1 << std::endl;
	roda1.send(sockfd, std::to_string(roda1.PID(5,0.2,setradPS1,PPR)));
	roda2.send(sockfd, std::to_string(roda2.PID(5,0.2,setradPS2,PPR)));
	roda3.send(sockfd, std::to_string(roda3.PID(5,0.2,setradPS3,PPR)));
	roda4.send(sockfd, std::to_string(roda4.PID(5,0.2,setradPS4,PPR)));  
}
void rodamati(){
	roda1.send(sockfd,"0");
	roda2.send(sockfd,"0");
	roda3.send(sockfd,"0");
	roda4.send(sockfd,"0");
	roda1.sum = 0;
	roda2.sum = 0;
	roda3.sum = 0;
	roda4.sum = 0;
	
}

void calculatePos() {
	MEGA.receive(sockfd);
	roda1.receive(sockfd);
	roda2.receive(sockfd);
	roda3.receive(sockfd);
	roda4.receive(sockfd);

	//displacement
	float v1 = (roda1.enc - roda1.prevenc) * KBAN / (PPR);
	float v2 = (roda2.enc - roda2.prevenc) * KBAN / (PPR);
	float v3 = (roda3.enc - roda3.prevenc) * KBAN / (PPR);
	float v4 = (roda4.enc - roda4.prevenc) * KBAN / (PPR);

	roda1.prevenc = roda1.enc;
	roda2.prevenc = roda2.enc;
	roda3.prevenc = roda3.enc;
	roda4.prevenc = roda4.enc;

	float Vx = -sin(toRad(MEGA.hadap + POSM1)) * v1 + -sin(toRad(MEGA.hadap + POSM2)) * v2 + -sin(toRad(MEGA.hadap + POSM3)) * v3 + -sin(toRad(MEGA.hadap + POSM4)) * v4;
	float Vy = cos(toRad(MEGA.hadap + POSM1)) * v1 + cos(toRad(MEGA.hadap + POSM2)) * v2 + cos(toRad(MEGA.hadap + POSM3)) * v3 + cos(toRad(MEGA.hadap + POSM4)) * v4;

	x += Vx;
	y += Vy;
	// std::cout << x << "\t" << y << std::endl;
}

void setPos(float POSX, float POSY, float HADAP) {
	mulai = std::chrono::steady_clock::now();
	int nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (mulai - akhir).count();
	double deltaT = nanosec * pow(10,-9);
	calculatePos();
	//PID Posisi
	float errX = POSX - x;
	sumX += errX;
	float PIDx = KPx * errX + KIx * sumX * deltaT;
	//  PIDx = fmaxf(-7.3, fminf(PIDx,7.3));

	float errY = POSY - y;
	sumY += errY;
	float PIDy = KPy * errY + KIy * sumY * deltaT;
	//  PIDy = fmaxf(-7.3, fminf(PIDy, 7.3));


	float errT = HADAP - MEGA.hadap;
	if(errT > 180 || errT < -180){
	errT = MEGA.hadap - HADAP;
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

void terimaUDP(int soket){
	char buffer[MAXLINE];
	sockaddr_in sender;
	memset(&sender, 0, sizeof(sender));
	socklen_t sender_len = sizeof(sender);
	int sizeReceive = recvfrom(soket, (char *)buffer, MAXLINE,
						0, ( struct sockaddr *) &sender,
						&sender_len);
	buffer[sizeReceive] = '\0';
	std::string senderIP = inet_ntoa(sender.sin_addr);
	// std::cout << buffer << std::endl;
	if(senderIP == roda1.deviceIP){
		// roda1.enc = atoi(buffer);
		strncpy(roda1.terima, buffer, MAXLINE);
		roda1.enc = atoi(roda1.terima);
	}
	if(senderIP == roda2.deviceIP){
		strncpy(roda2.terima, buffer, MAXLINE);
		roda2.enc = atoi(roda2.terima);
	}
	if(senderIP == roda3.deviceIP){
		strncpy(roda3.terima, buffer, MAXLINE);
		roda3.enc = atoi(roda3.terima);
	}
	if(senderIP == roda4.deviceIP){
		strncpy(roda4.terima, buffer, MAXLINE);
		roda4.enc = atoi(roda4.terima);
	}
	if(senderIP == MEGA.deviceIP){
		strncpy(MEGA.terima, buffer, MAXLINE);
		MEGA.hadap = atof(strtok(MEGA.terima+11, "~"));
	}
}
int lantaitoStep(int tingkat){
	return tingkat * -1800;
}

// Driver code
int main(int argc, char **argv) {
	ros::init(argc, argv, "elephantRobot", ros::InitOption::NoSigintHandler);
	ros::NodeHandle n;
	ros::Subscriber subButton = n.subscribe("/button", 1000, readButton);
	ros::Subscriber subLX = n.subscribe("/leftX", 1000, readLX);
	ros::Subscriber subLY = n.subscribe("/leftY", 1000, readLY);
	ros::Subscriber subLL = n.subscribe("/LL", 1000, readLL);
	ros::Subscriber subRR = n.subscribe("/RR", 1000, readRR);
	// ros::Subscriber subCase = n.subscribe("/case", 1000, caseCB);
	// ros::Subscriber subLsat = n.subscribe("/lsatu", 1000, bacaL1);
	// ros::Subscriber subBulet = n.subscribe("/bulet", 1000, bacaO);
	// ros::Subscriber subTr = n.subscribe("/lupis", 1000, bacaTr);

	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));


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
	
	while(1) 
	{
		ros::spinOnce();
		if(mode == false){
			if (caseRobot == 1){
				if (y > -8.7) {
					setPos(0.1, -10.5, 0);
				}
				if (y < -8.7) {
					rodamati();
					//nyender fence belakang
					while (!(MEGA.terima[0] == '0' && MEGA.terima[1] == '0')) {
						calculatePos();
						kinematic(1.5, 0, 0, MEGA.hadap);
						MEGA.receive(sockfd);
					}
					
					//nyender fence samping
					while (!(MEGA.terima[2] == '0' && MEGA.terima[5] == '0')) {
						calculatePos();
						MEGA.receive(sockfd);
						kinematic(0, -1.5, 0, 0);
					}
					x_temp = x;
					y_temp = y;
					// while(caseRobot == 1){

					// 	ros::spinOnce();
					// 	calculatePos();
					// 	rodamati();
					// }
					rodamati();
					caseRobot = 2;
				}
			}
			if(caseRobot == 2){
				clock_t start_time = clock();
				do{

					setPos(x_temp - 2, y_temp + 2, 45);
				}
				while (!(clock() - start_time > 200000));
				
				while(!(MEGA.terima[6] == '0' && MEGA.terima[7] == '0')){
					// std::cout << "kedepan" << std::endl;
					MEGA.receive(sockfd);
					calculatePos();
					if(MEGA.terima[6] == '0' && MEGA.terima[7] == '1'){
						kinematic(0,0,-1.5,0);
					}
					else if(MEGA.terima[7] == '0' && MEGA.terima[6] == '1'){
						kinematic(0,0,1.5,0);
					}
					else if(MEGA.terima[6] == '1' && MEGA.terima[7] == '1'){
						kinematic(0,1.5,0,0);
					}
				}
				while (caseRobot == 2){
					rodamati();
					lantai = 0;
					ros::spinOnce();
					calculatePos();
					if (tombol == 6) MEGA.send(sockfd, std::to_string(lantaitoStep(lantai)));
					falcon.send(sockfd, std::to_string(tiangtoRPM(indexTiang)));
				}
			}
			
			//ambil ring kanan
			if (caseRobot == 8) {
				setPos(0,0,0);
			}
		}
		if(mode == true){
			calculatePos();
			kinematic(lx,ly,LL-RR,0);
		}
	}	
	return 0;
}