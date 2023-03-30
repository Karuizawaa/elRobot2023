# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include".split(';') if "${prefix}/include" != "" else []
PROJECT_CATKIN_DEPENDS = "message_runtime;roscpp;std_msgs".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lrt;-lpthread;-lusb-1.0;-ljsoncpp".split(';') if "-lrt;-lpthread;-lusb-1.0;-ljsoncpp" != "" else []
PROJECT_NAME = "ros_odrive"
PROJECT_SPACE_DIR = "/home/barelang/ros_ws/install"
PROJECT_VERSION = "0.0.1"
