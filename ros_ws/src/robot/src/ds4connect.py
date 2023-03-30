#!/usr/bin/env python
import os
import time

os.system("echo 1 | sudo -S -k service bluetooth restart")
os.system("bluetoothctl pair 49:FA:A3:81:1C:A5")
os.system("bluetoothctl connect 49:FA:A3:81:1C:A5")
# os.system("rosrun robot stik.py")