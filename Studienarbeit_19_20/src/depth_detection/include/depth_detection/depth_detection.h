/**
 * @attention Copyright (C) 2019
 * @attention For License information please see the LICENSE file in the root directory.
 * 
 * @author: Christoph Endner <christoph@ducklabs.de>
 */

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <sstream>


class Depth_Detection {
private:
  Depth_Detection* depth_detection;

  ros::Publisher crop_pub, laser_pub;
  //ros::Subscriber info_sub;
  ros::Subscriber info_sub, image_sub, seg_sub;
  sensor_msgs::CameraInfo cam_info;
  sensor_msgs::Image seg;
  uint seq = 0;
  bool got_cam_info = false;
  double cx;  //cx
  double cy;  //cy
  double f;  //Focal
  double b;
  

public:
 
  //void publishDepthVector(const sensor_msgs::ImageConstPtr& img, const sensor_msgs::ImageConstPtr& seg);
  void publishDepthVector(sensor_msgs::Image img);
  void reciveCameraInfo(sensor_msgs::CameraInfo info);
  void receiveSegmented(const sensor_msgs::Image segm);
  void publishLaserscan(cv::Mat in);
  double angle_between_rays(int y1, double z1, int y2, double z2);
  cv::Vec3f picturetoWorld(cv::Vec3f in);
  cv::Vec3f worldtoPicture(cv::Vec3f in);
  void init(ros::NodeHandle n);
  Depth_Detection();
  ~Depth_Detection();
  
};
