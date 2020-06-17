## Camera Processing

This repository contains everything needed to install drivers for the Intel Realsense Camera and to run the processing for it. 
The code was tested with ROS Melodic and Ubuntu 18.04

### Installation
Run `setup.sh` and `install_librealsense.sh` to install everything which is needed, then run catkin_make to build the ROS Module. 

### Run
Launch the software by using `roslaunch depth_detection depth_detection.launch`


## Publishes:
* `/uav1/camera/depth` (sensor_msgs::Image)

## Maintainer
Christoph Endner - christoph@ducklabs.de
Tobias Maier - me@maiertobi.de
