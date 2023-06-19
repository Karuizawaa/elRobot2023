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
#include "std_msgs/Int8.h"
#include "std_msgs/UInt16.h"
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


#define KPx		1.3
#define KIx		0
#define KPy		1.3
#define KIy		0
#define KPt		1.3
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

	//lowpass
	float vFilt, vPrev;

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

	/* PID P000]rocess alamat */
	int PID(float KP, float KI, float setradPS, float PULSEPERREV){
		begin = std::chrono::steady_clock::now();
		double nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (begin - end).count();
		radps = ((enc - lastenc) * 2 * M_PI / PULSEPERREV) / (nanosec*pow(10,-9));
		lastenc = enc;

		vFilt = 0.854 * vFilt + 0.0728 * radps + 0.0728 * vPrev;
		vPrev = radps;

		float error = setradPS - radps;
		sum += error;
		end = std::chrono::steady_clock::now();
		if(setradPS == 0){
			sum = 0;
			return 0;
		}
		else return(KP * error + KI * sum);
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

int lantai;
int indexTiang, offsetFalcon = 0;

bool mode; //false semi auto, true manual stik

std::chrono::steady_clock::time_point mulai;
std::chrono::steady_clock::time_point akhir;
clock_t startcount;

int sockfd;
int caseRobot, prevCase;
int8_t tombol, prevTombol;
int16_t keys;

float errX, PIDx, errY, PIDy;

Device roda1("192.168.0.11", 5555);
Device roda2("192.168.0.12", 5555);
Device roda3("192.168.0.13", 5555);
Device roda4("192.168.0.14", 5555);
// Device falcon("192.168.0.15", 5555);
Device MEGA("192.168.0.99", 8888);
// Device extend("192.168.0.20", 5555);



void readButton(const std_msgs::Int8::ConstPtr& msg){
	tombol = msg->data;
	// std::cout << tombol << std::endl;
	if(tombol == 1){
		caseRobot = 1;
	}

	if(tombol == 2){ 
		lantai = 0;
		MEGA.send(sockfd,"1");
	}
	tombol == 6 ? l1 = true: l1 = false;
	if(tombol != prevTombol){
		if(tombol == 6) lantai++;
	
	}
	if(tombol == 9) mode = false;
	if(tombol == 10) {
		mode = true;
		caseRobot = 0;
	}
	
	prevTombol = tombol;
}

void readKibod(const std_msgs::UInt16::ConstPtr& key){
	keys = key->data;
	if(keys == 91) caseRobot = 1;
	if(keys == 47) caseRobot = 7;
	if(keys == 59) caseRobot = 8;
	if(keys == 32){ 
		lantai = 0;
		MEGA.send(sockfd,"1");
		MEGA.send(sockfd,"1");
		MEGA.send(sockfd,"1");
		MEGA.send(sockfd,"1");
		MEGA.send(sockfd,"1");
		MEGA.send(sockfd,"1");
	}           
	if(keys == 119 || keys == 87) lantai++;
	if(keys == 111 || keys == 79) {
		for(int i = 0; i < 1000; i++){
			MEGA.send(sockfd,"F");
		}
	}
	if(keys == 112 || keys == 80) {
		for(int i = 0; i < 1000; i++){
			MEGA.send(sockfd,"B");
		}
	}
	if(keys == 117 || keys == 85) {
		for(int i = 0; i < 1000; i++){
			MEGA.send(sockfd,"S");
		}
	}
	if(keys == 122 || keys == 90){
		for(int i = 0; i < 1000; i++){
			MEGA.send(sockfd,"G");
		}
	}
	if(keys == 100 || keys == 68) offsetFalcon++;
	if(keys == 99 || keys == 67) offsetFalcon--;
	if(keys == 13) {
		mode = true;
		caseRobot = 0;
		offsetFalcon = 0;
		// for(int i = 0; i < 1000; i++){
		// 	MEGA.send(sockfd,"1");
		// }
	}
	if(keys == 126){
		lantai = 0;
		for(int i = 0; i < 1000; i++){
			MEGA.send(sockfd,"1");
		}
	}
	if(keys == 108 || keys == 76){
		mode = false;
		caseRobot = 2;
		indexTiang = 1;
	}
	if(keys == 107 || keys == 75){
		mode = false;
		caseRobot = 3;
		indexTiang = 2;
	}
	if(keys == 106 || keys == 74){
		mode = false;
		caseRobot = 4;
		indexTiang = 1;
	}
	if(keys  == 104 || keys == 72){
		mode = false;
		caseRobot = 5;
		indexTiang = 2;
	}
	if(keys == 103 || keys == 71){
		mode = false;
		caseRobot = 6;
		indexTiang = 1;
	}
}

void readLX(const std_msgs::Float32::ConstPtr& msg){
	lx = msg->data;
	// std::cout << lx << std::endl;
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
void readPole(const std_msgs::Int8::ConstPtr& msg){
	indexTiang = msg->data;
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
void kinematic(float vX, float vY, float theta, float heading, bool closedloop) {
	if(clock () - startcount > 10){
		float setradPS1 = (-sin(toRad(POSM1 + heading)) * vX + cos(toRad(POSM1 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
		float setradPS2 = (-sin(toRad(POSM2 + heading)) * vX + cos(toRad(POSM2 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
		float setradPS3 = (-sin(toRad(POSM3 + heading)) * vX + cos(toRad(POSM3 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
		float setradPS4 = (-sin(toRad(POSM4 + heading)) * vX + cos(toRad(POSM4 + heading)) * vY + theta * RADIUSMTR) / RADIUSBAN;
		// std::cout << setradPS1 << std::endl;
		roda1.send(sockfd, std::to_string(setradPS1));
		roda2.send(sockfd, std::to_string(setradPS2));
		roda3.send(sockfd, std::to_string(setradPS3));
		roda4.send(sockfd, std::to_string(setradPS4));
		startcount = clock();
	}
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
	// mulai = std::chrono::steady_clock::now();
	// int nanosec = std::chrono::duration_cast<std::chrono::nanoseconds> (mulai - akhir).count();
	// double deltaT = nanosec * pow(10,-9);
	calculatePos();
	//PID Posisi
	errX = POSX - x;
	PIDx = KPx * errX;
	//  PIDx = fmaxf(-6.3, fminf(PIDx,6.3));

	errY = POSY - y;
	PIDy = KPy * errY;
	//  PIDy = fmaxf(-6.3, fminf(PIDy, 6.3));


	float errT = HADAP - MEGA.hadap;
	if(errT > 180 || errT < -180){
	errT = MEGA.hadap - HADAP;
	}
	sumT += errT;
	float PIDt = KPt * errT;
	PIDt = fmaxf(-3.7, fminf(PIDt, 3.7));
	kinematic(PIDx, PIDy, PIDt, MEGA.hadap, 1);
	usleep(1000);
}


// ring lama pakai ban atas dooble (+7) / double tape (+3)
// int tiangtoFalcon(uint8_t tiang){
// 	if(tiang == 1) return 1654;
// 	// if(tiang == 1) return 1656; // tiang terdekat dari pojokan atau depan
// 	// else if(tiang == 2) return 1671; // tiang ke dua dari depan
// 	else if(tiang == 2) return 1676;
// 	// else if(tiang == 3) return 1704; // tiang tertinggi dari tengah
// 	else if(tiang == 3) return 1709;
// 	else if(tiang == 4) return 1710; // tiang terjauh dari depan
// 	else return 1500;
// }

//ring baru panitia double tape
int tiangtoFalcon(uint8_t tiang){
	if(tiang == 1) return 1641;
	else if(tiang == 2) return 1665;
	else if(tiang == 3) return 1714;
	else if(tiang == 4) return 1715; // tiang terjauh dari depan
	else return 1500;
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
	// if(tingkat == 0) MEGA.send(sockfd, "-0");
	if(tingkat == 1) return -1000;
	else if(tingkat == 2) return -2600;
	else if(tingkat == 3) return -4200;
	else if(tingkat == 4) return -5800;
	else if(tingkat == 5) return -7300;
	else if(tingkat == 6) return -8900;
	else if(tingkat == 7) return -10400;
	else if(tingkat == 8) return -11700;
	else if(tingkat == 9) return -13300;
	else if(tingkat == 10) return -14700;
	// else return 0`

	
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
	ros::Subscriber subPole = n.subscribe("/poles", 1000, readPole);
	ros::Subscriber subKeyy = n.subscribe("/keyy", 1000, readKibod);

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
	startcount = clock();
	
	
	// while (1){
	// 	if(clock () - startcount > 20000){
	// 		ros::spinOnce();
	// 		startcount = clock();
	// 	}
		
	// 	if (tombol == 6) {
	// 		if(lantai > 9) {
	// 		lantai = 0;
	// 		MEGA.send(sockfd, "-0");
	// 		}
	// 		MEGA.send(sockfd, std::to_string(lantaitoStep(lantai)));
	// 	}
	// }
	ros::Rate loop_rate(100);
	caseRobot = 99;
	indexTiang = 1;
	lantai = 0;
	while(1) 
	{
		// calculatePos();

		// std::cout << mode << "\t" << caseRobot << std::endl;
		// std::cout << x << "\t" << y  << "\t" << MEGA.hadap << std::endl;
		// std::cout << indexTiang << std::endl;
		// roda2.receive(sockfd);
		// std::cout << roda2.terima << std::endl;
		// roda2.send(sockfd, "9");
		// if(clock () - startcount > 20000){
			// ros::spinOnce();
		// 	startcount = clock();
		// }
		
		ros::spinOnce();
		if(caseRobot == 0){
			std::cout << tiangtoFalcon(indexTiang)<< std::endl;
			// calculatePos();
			// x_temp = x;
			if(lantai > 10){
				lantai = 0;
				// MEGA.send(sockfd, "1");
				// MEGA.send(sockfd, "1");
				// MEGA.send(sockfd, "1");
				// MEGA.send(sockfd, "1");
				// MEGA.send(sockfd, "1");
			}
			// if (tombol == 6 || keys == 119) MEGA.send(sockfd, std::to_string(lantaitoStep(lantai)));
			
			if(lantai > 0) MEGA.send(sockfd, std::to_string(lantaitoStep(lantai) - 800));

			else MEGA.send(sockfd, "-0");
			kinematic(lx * 3.7, ly * 3.7, (LL - RR) * 3,0,0);
			char pwmfalcon[10];
			// sprintf(pwmfalcon, "+%d", tiangtoFalcon(indexTiang) + 7 + offsetFalcon); //ring lama(MRI) roller atas double ban
			// sprintf(pwmfalcon, "+%d", tiangtoFalcon(indexTiang) + 3 + offsetFalcon); //ring lama(MRI) roller double tape
			sprintf(pwmfalcon, "+%d", tiangtoFalcon(indexTiang)+ offsetFalcon);
			MEGA.send(sockfd, pwmfalcon);
			// MEGA.send(sockfd, "+1665"); //tiang 2
			// MEGA.send(sockfd, "+1718"); //tiang 4
			// MEGA.send(sockfd, "+1642"); //tiang 1
			// MEGA.send(sockfd, "+1715"); //tiang 3
			char LEDDPOLES[10];
			sprintf(LEDDPOLES, " %d,", indexTiang);
			MEGA.send(sockfd, LEDDPOLES);
			// MEGA.send(sockfd, "+1706");
		
		}
		if (caseRobot == 1){
			if (y > -9.3) {
				setPos(-0.05, -10.0, 0);
			}
			if (y < -9.3) {

				// usleep(1000);
				//nyender fence belakang
				while (!(MEGA.terima[0] == '0' && MEGA.terima[1] == '0') && caseRobot == 1) {
					// calculatePos();
					// kinematic(3.0, 0, 0, MEGA.hadap, 1);
					setPos(x+1.5, y, 0);
					// MEGA.receive(sockfd);
				}
				for(int i = 0; i < 1000; i++){
					MEGA.send(sockfd,"1");
				}
				//nyender fence samping
				while (caseRobot == 1) {
					ros::spinOnce();
					setPos(0.5, -12.5, 0);
				}
				// usleep(10e3/2);
				// rodamati();
				// rodamati();
				// rodamati();
				// rodamati();
				// usleep(10e6/2);
				x_temp = x;
				y_temp = y;
				
				
				
				caseRobot = 2;
				// lantai = 1;
				
			}
		}
		else if(caseRobot == 2){
			setPos(x_temp - 2.64269, y_temp + 5.74584, 91.5);
		}
		else if(caseRobot == 3){
			// setPos(x_temp - 2.4456, y_temp + 9.38189, 91.0);
			setPos(x, y_temp + 10.38189, 91.5);
		}
		else if(caseRobot == 4){
			// setPos(x_temp - 2.56787, y_temp + 12.1718, 92.0);
			setPos(x, y_temp + 12.8718, 91.5);
		}
		else if(caseRobot == 5){
			// setPos(x_temp - 2.71012 , y_temp + 15.8931, 94.4);
			setPos(x, y_temp + 16.5931, 91.5);
		}
		else if(caseRobot == 6){
			// setPos(x_temp - 3.0 , y_temp + 18.5164, 95.9);
			setPos(x , y_temp + 20.1164, 91.5);
		}
		else if(caseRobot == 7){
			setPos(x + 1.3, y + 0.1, 91);
			x_temp = x;
			y_temp = y;
		}
		else if(caseRobot == 8){
			setPos(x_temp - 2.32, y_temp - 10.9, 91);

		}
		
		
		loop_rate.sleep();
	}
	
	return 0;
}