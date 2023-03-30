#!/usr/bin/env python
# license removed for brevity
import os
import rospy
from std_msgs.msg import Int8
import pygame
from pygame.locals import *
import time

# hold_atas = 0
# hold_bawah = 0
# hold_kiri = 0
# hold_kanan = 0

# hello_int = 0

def talker():
    hello_int = 0
    pygame.init()
    pygame.joystick.init()
    joystick = pygame.joystick.Joystick(2)
    joysticks = [pygame.joystick.Joystick(i) for i in range(pygame.joystick.get_count())]
    pub = rospy.Publisher('stik', Int8, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(25) # 10hz
    while not rospy.is_shutdown():
        
        for event in pygame.event.get():
            if event.type == JOYBUTTONDOWN:
                if joystick.get_button(0):
                    # hello_str = "X ditekan"
                    hello_int = 1
                elif joystick.get_button(1):
                    # hello_int = "o ditekan"
                    hello_int = 2
                elif joystick.get_button(2):
                    # hello_int = "segitiga ditekan"
                    hello_int = 3
                elif joystick.get_button(3):
                    # hello_int = "kotak ditekan"
                    hello_int = 4
            else :
                hello_int = 0
            if event.type == JOYHATMOTION:
                if joystick.get_hat(0) == (-1, 0):
                    print("kiri")
                    hello_int = 11
                elif joystick.get_hat(0) == (1, 0):
                    print("kanan")
                    hello_int = 12
                elif joystick.get_hat(0) == (0, -1):
                    print("bawah")
                    hello_int = 13
                elif joystick.get_hat(0) == (0, 1):
                    print("atas")
                    hello_int = 14
            else :
                hello_int = 0   

	# rospy.loginfo(hello_int)
        pub.publish(hello_int)
        rate.sleep()

if __name__ == '__main__':
    os.system("echo 1 | sudo -S -k service bluetooth restart")
    time.sleep(3)
    os.system("bluetoothctl pair 49:FA:A3:81:1C:A5")
    os.system("bluetoothctl connect 49:FA:A3:81:1C:A5")
    # os.system("bluetoothctl pair D6:36:14:7F:6B:1B")
    # os.system("bluetoothctl connect D6:36:14:7F:6B:1B")
    time.sleep(1)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
