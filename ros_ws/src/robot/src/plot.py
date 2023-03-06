#!/usr/bin/env python
import matplotlib.pyplot as plt
import math
import numpy as np
import rospy
from std_msgs.msg import Float32

GRAVITY = 9.80665

def toRad(degree):
    return degree * math.pi / 180

def talker():
    pub = rospy.Publisher('chatter', Float32, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(100) # 100hz
    while not rospy.is_shutdown():
        velShoot = 100
        # hello_str = "hello world %s" % rospy.get_time()
        # rospy.loginfo(hello_str)
        pub.publish(velShoot)
        rate.sleep()

def vshoot(x, y):
    plt.scatter(x, y, color='r', label='Target (tiang)')
    plt.text(x+0.1, y+0.1, "(" + str(x) + ", " + str(y) + ")")
    initVel = math.sqrt((GRAVITY * (x ** 2)) / ((math.tan(toRad(45)) * x - y) * 2 * (math.cos(toRad(45)) ** 2)))
    if initVel > 6500:
        return 0
    else:
        return initVel

def plot(initVel):
    plt.title("Trajektori penembak 45")
    d = np.arange(0, (initVel ** 2) * math.sin(toRad(2*45)) / GRAVITY , 0.001)
    h = math.tan(toRad(45)) * d - (GRAVITY * (d ** 2) / (2 * ((initVel * math.cos(toRad(45))) ** 2 )))
    plt.text(0, 0, str(initVel) + " m/s")
    plt.plot(d, h, color='b', label='Trajektori')
    plt.title("Trajektori penembak sudut 45°")
    plt.legend()
    plt.axis('equal')
    plt.show()

# plot(vshoot(7,1))
if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass