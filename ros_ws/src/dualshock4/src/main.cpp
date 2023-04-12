#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <linux/input.h>

#include <ros/ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32.h>



const char* buttonNames[32] = {
	"TRIGGER",
	"THUMB",
	"THUMB2",
	"TOP",
	"TOP2",
	"PINKIE",
	"BASE",
	"BASE2",
	"BASE3",
	"BASE4",
	"BASE5",
	"BASE6",
	"","","",
	"DEAD",

	"SOUTH",
	"EAST",
	"C",
	"NORTH",
	"WEST",
	"Z",
	"TL",
	"TR",
	"TL2",
	"TR2",
	"SELECT",
	"START",
	"MODE",
	"THUMBL",
	"THUMBR"
};

const char* axisNames[32] = {
	"X",
	"Y",
	"Z",
	"RX",
	"RY",
	"RZ",
	"THROTTLE",
	"RUDDER",
	"WHEEL",
	"GAS",
	"BRAKE",
	"","","","","",
	"HAT0X",
	"HAT0Y",
	"HAT1X",
	"HAT1Y",
	"HAT2X",
	"HAT2Y",
	"HAT3X",
	"HAT3Y",
	"PRESSURE",
	"DISTANCE",
	"TILT_X",
	"TILT_Y",
	"TOOL_WIDTH"
};

struct Axis
{
	int min;
	int max;
	float value;
};

struct Joystick
{
	static const unsigned int maxButtons = 32;
	static const unsigned int maxAxes = 32;

	bool connected;
	bool buttons[maxButtons];
	Axis axes[maxAxes];
	char name[128];
	int file;
	bool hasRumble;
	short rumbleEffectID;
};

void openJoysticks(Joystick out_joysticks[], unsigned int maxJoysticks)
{
	char fileName[32];
	for (int i=0; i<32; ++i) {
		sprintf(fileName, "/dev/input/event%d", i);
		int file = open(fileName, O_RDWR | O_NONBLOCK);
		if (file != -1)
		{
			Joystick j = {0};
			j.connected = true;
			j.file = file;

			// Get name
			ioctl(file, EVIOCGNAME(sizeof(j.name)), j.name);

			// Setup axes
			for (unsigned int i=0; i<Joystick::maxAxes; ++i)
			{
				input_absinfo axisInfo;
				if (ioctl(file, EVIOCGABS(i), &axisInfo) != -1)
				{
					j.axes[i].min = axisInfo.minimum;
					j.axes[i].max = axisInfo.maximum;
				}
			}

			// Setup rumble
			ff_effect effect = {0};
			effect.type = FF_RUMBLE;
			effect.id = -1;
			if (ioctl(file, EVIOCSFF, &effect) != -1) {
				j.rumbleEffectID = effect.id;
				j.hasRumble = true;
			}

			out_joysticks[i] = j;
		}
	}
}

void closeJoysticks(Joystick joysticks[], unsigned int maxJoysticks)
{
	for (int i=0; i<32; ++i) {
		if (joysticks[i].connected) {
			close(joysticks[i].file);
			joysticks[i].connected = false;
		}
	}
}

void readJoystickInput(Joystick* joystick)
{
	input_event event;
	while (read(joystick->file, &event, sizeof(event)) > 0)
	{
		if (event.type == EV_KEY && event.code >= BTN_JOYSTICK && event.code <= BTN_THUMBR) {
			joystick->buttons[event.code-0x120] = event.value;
		}
		if (event.type == EV_ABS && event.code < ABS_TOOL_WIDTH) {
			Axis* axis = &joystick->axes[event.code];
			float normalized = (event.value - axis->min) / (float)(axis->max - axis->min) * 2 - 1;
			joystick->axes[event.code].value = normalized;
		}
	}
}

void setJoystickRumble(Joystick joystick, short weakRumble, short strongRumble)
{
	if (joystick.hasRumble)
	{
		ff_effect effect = {0};
		effect.type = FF_RUMBLE;
		effect.id = joystick.rumbleEffectID;
		effect.replay.length = 5000;
		effect.replay.delay = 0;
		effect.u.rumble.weak_magnitude = weakRumble;
		effect.u.rumble.strong_magnitude = strongRumble;
		ioctl(joystick.file, EVIOCSFF, &effect);

		input_event play = {0};
		play.type = EV_FF;
		play.code = joystick.rumbleEffectID;
		play.value = 1;
		write(joystick.file, &play, sizeof(play));
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dualshock");
	ros::NodeHandle nh;
	ros::Publisher pubButton = nh.advertise<std_msgs::UInt8>("button", 1000);
	ros::Publisher pubLX = nh.advertise<std_msgs::Float32>("leftX", 1000);
	ros::Publisher pubLY = nh.advertise<std_msgs::Float32>("leftY", 1000);
	ros::Publisher pubRR = nh.advertise<std_msgs::Float32>("RR", 1000);
	ros::Publisher pubLL = nh.advertise<std_msgs::Float32>("LL", 1000);

	std_msgs::Float32 LX, LY, RR, LL;
	std_msgs::UInt8 tombol;


	const unsigned int maxJoysticks = 32;
	Joystick joysticks[maxJoysticks] = {0};
	openJoysticks(joysticks, maxJoysticks);

	int deviceChangeNotify = inotify_init1(IN_NONBLOCK);
	inotify_add_watch(deviceChangeNotify, "/dev/input", IN_ATTRIB);

	while (ros::ok())
	{
		tombol.data = 0;
		// Update which joysticks are connected
		inotify_event event;
		if (read(deviceChangeNotify, &event, sizeof(event)+16) != -1)
		{
			closeJoysticks(joysticks, maxJoysticks);
			openJoysticks(joysticks, maxJoysticks);
		}

		// Update and print inputs for each connected joystick
		for (int i=0; i<maxJoysticks; ++i)
		{
			if (joysticks[i].connected)
			{
				readJoystickInput(&joysticks[i]);
				// printf("Joystick - %d\t", i);
				// printf("%s - Axes: ", joysticks[i].name);
				for (char axisIndex=0; axisIndex<Joystick::maxAxes; ++axisIndex) {
					// if (joysticks[i].axes[axisIndex].max-joysticks[i].axes[axisIndex].min) printf("%s:% f ", axisNames[axisIndex], joysticks[i].axes[axisIndex].value);
					// axisindex 0 == leftX mentok kiri -1, mentok kanan 1
					if(joysticks[i].axes[0].value > 0.12 || joysticks[i].axes[0].value < -0.12) LX.data = joysticks[i].axes[0].value;
					else LX.data = 0.0;
					// axisindex 1 == leftY //mentok bawah 1, mentok atas -1
					if(joysticks[i].axes[1].value > 0.12 || joysticks[i].axes[1].value < -0.12) LY.data = -joysticks[i].axes[1].value;
					else LY.data = 0.0;
					// axisindex 2 == L2 //mentok bawah 1, mentok atas -1
					if(joysticks[i].axes[2].value != -1) LL.data = joysticks[i].axes[2].value+1;
					else LL.data = 0.0;
					// axisindex 3 == rightX mentok kiri -1, mentok kanan 1
					// axisindex 4 == rightY //mentok bawah 1, mentok atas -1
					// axisindex 5 == R2 //mentok bawah 1, mentok atas -1
					if(joysticks[i].axes[5].value != -1) RR.data = joysticks[i].axes[5].value+1;
					else RR.data = 0.0;
					// printf("%s:% f ", axisNames[6], joysticks[i].axes[6].value);

				}
				// printf("Buttons: ");
				for (uint8_t buttonIndex=0; buttonIndex<Joystick::maxButtons; ++buttonIndex) {
					// if (joysticks[i].buttons[buttonIndex]) printf("%s ", buttonNames[buttonIndex]);
					if(joysticks[i].buttons[buttonIndex]){
						
						if(buttonNames[buttonIndex] == "WEST") tombol.data = 1; // petak
						if(buttonNames[buttonIndex] == "SOUTH") tombol.data = 2; // silang
						if(buttonNames[buttonIndex] == "EAST") tombol.data = 3; // bulet
						if(buttonNames[buttonIndex] == "NORTH") tombol.data = 4; // segitiga
						if(buttonNames[buttonIndex] == "TR") tombol.data = 5; // R1
						if(buttonNames[buttonIndex] == "TL") tombol.data = 6; // L1
						if(buttonNames[buttonIndex] == "TR2") tombol.data = 7; // R2
						if(buttonNames[buttonIndex] == "TL2") tombol.data = 8; // L2
						if(buttonNames[buttonIndex] == "SELECT") tombol.data = 9; // select
						if(buttonNames[buttonIndex] == "START") tombol.data = 10; // start
						if(buttonNames[buttonIndex] == "MODE") tombol.data = 11; // start

						// if(buttonNames[buttonIndex] == "WEST") printf("petak"); // petak
						// if(buttonNames[buttonIndex] == "SOUTH") printf("silang"); // silang
						// if(buttonNames[buttonIndex] == "EAST") printf("bulet"); // bulet
						// if(buttonNames[buttonIndex] == "NORTH") printf("segitiga"); // segitiga
						// if(buttonNames[buttonIndex] == "TR") printf("R1"); // R1
						// if(buttonNames[buttonIndex] == "TL") printf("L1"); // L1
						// if(buttonNames[buttonIndex] == "TR2") printf("R2"); // R1
						// if(buttonNames[buttonIndex] == "TL2") printf("L2"); // L1
						// if(buttonNames[buttonIndex] == "SELECT") printf("select"); // select
						// if(buttonNames[buttonIndex] == "START") printf("start"); // start
					}
					// if (joysticks[i].buttons[buttonIndex]) printf("%d ", buttonIndex);
				}
				// printf("\n");

				// short weakRumble   = fabsf(joysticks[i].axes[ABS_X].value) * 0xFFFF;
				// short strongRumble = fabsf(joysticks[i].axes[ABS_Y].value) * 0xFFFF;
				// setJoystickRumble(joysticks[i], weakRumble, strongRumble);
			}
		}
		pubButton.publish(tombol);
		pubLX.publish(LX);
		pubLY.publish(LY);
		pubRR.publish(RR);
		pubLL.publish(LL);
		fflush(stdout);
		usleep(1); //original 16000
	}
}
