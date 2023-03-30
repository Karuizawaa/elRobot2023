#!/usr/bin/env python3
"""
Example usage of the ODrive python library to monitor and control ODrive devices
"""

from __future__ import print_function

import odrive
from odrive.enums import *
import time
import math

import rospy
from std_msgs.msg import Int16

vel = Int16('0')

def cb(data):
    vel = data

def listener():
    rospy.init_node('ODrive', anonymous=True)
    rospy.Subscriber("brushless", Int16, cb)


if __name__ == '__main__':
    listener()
    # Find a connected ODrive (this will block until you connect one)
    print("finding an odrive...")
    my_drive = odrive.find_any()


    #config

    my_drive.axis1.motor.config.current_lim = 50
    my_drive.axis1.controller.config.vel_limit = 100
    my_drive.axis1.motor.config.pole_pairs = 7
    my_drive.axis1.motor.config.torque_constant = 8.27 / 150
    my_drive.axis1.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT
    my_drive.axis1.encoder.config.cpr = 8192

    # Calibrate motor and wait for it to finish
    print("starting calibration...")
    my_drive.axis1.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE
    while my_drive.axis1.current_state != AXIS_STATE_IDLE:
        time.sleep(0.1)

    time.sleep(3)

    my_drive.axis1.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL
    my_drive.axis1.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
    while True:
        my_drive.axis1.controller.input_vel = 10
        my_drive.clear_errors()