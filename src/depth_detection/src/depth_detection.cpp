/**
 * @attention Copyright (C) 2019
 * @attention For License information please see the LICENSE file in the root directory.
 * @author: Christoph Endner <christoph@ducklabs.de>
 */


#include <ros/console.h>

#include <opencv2/opencv.hpp>
//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
//#include <sensor_msgs/image_encodings.h>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include "depth_detection/depth_detection.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/LaserScan.h>

double paddingperson; //Padding in centimeters
double baseline; // Distance between the stereo cameras centers

int main(int argc, char **argv)
{
  ros::init(argc, argv, "depth_detection");
  ros::NodeHandle n;
  n.param("paddingperson", paddingperson, 200.0);
  n.param("baseline", baseline, 49.970);
  Depth_Detection b;
  b.init(n);
  ros::spin();

  return 0;
}



void Depth_Detection::publishDepthVector(sensor_msgs::Image img)
//void Depth_Detection::publishDepthVector(const sensor_msgs::ImageConstPtr& img, const sensor_msgs::ImageConstPtr& seg)
{
  if (got_cam_info)
  {
    cv_bridge::CvImagePtr in;
    in = cv_bridge::toCvCopy(img);
    cv::Mat depth(in->image);

    depth.convertTo(depth, CV_16SC1);
    cv::resize(depth, depth, cv::Size(), 0.25, 0.25, CV_INTER_AREA);

    cv::medianBlur(depth, depth, 3);
    cv::medianBlur(depth, depth, 3);

    cv_bridge::CvImagePtr inc;
    inc = cv_bridge::toCvCopy(seg, "rgb8");
    cv::Mat segmented = inc->image;

    int person = 220; //red value for person
    int grass = 255;  //green value for grass
    

    cv::Mat persons(depth.rows, depth.cols, CV_8UC1); //Matrix to safe obstacle classes
    
    for (int x = 0; x < segmented.cols; x++)
    {
      for (int y = 0; y < segmented.rows; y++)
      { 
        double current_depth = depth.at<double>(x,y); //speed up processing by static adressing
        if(segmented.at<int>(x,y,0)==person && ((x+cx)*current_depth/f) && persons.at<int>(x,y) != 0){  //Start of Person and Height in rover range
          if(persons.at<int>(x,y-1) == 1 && depth.at<double>(x,y-1) < current_depth){
          current_depth = current_depth + paddingperson;                  // Just add padding if left pixel is larger and already added padding
          }else{
            double pstart = ((y+cy)*current_depth/f) - paddingperson;           //Get the outer bound of left safty radius (world)
            int startp = nearbyint((pstart*f/current_depth)-cy);               //Get coordinate of outer bound
              if(startp> 0){                                                          //Check if coordinsate is in picture bound                                        
                if(depth.at<double>(x,startp) > current_depth){              //Checks if current value is larger (further away) new value
                  depth.at<double>(x,startp) = current_depth;               //Set new value
                  persons.at<int>(x,startp) = 1;                                   //Mark pixel as person
                }
              }else{
                startp = 0;
              }
              for(int i = startp+1 ; i < y; i++){
                double ne = depth.at<double>(x,i) - sqrt(pow(paddingperson,2)-pow(((x+cx)*depth.at<double>(x,i)/f)-((x+cx)*current_depth/f),2))+((i+cy)*depth.at<double>(x,i)/f);  //Caclulates the new distance  
                if(ne < depth.at<double>(x,i)){
                  depth.at<double>(x,i) = ne;            //Set new value
                  persons.at<int>(x,i) = 1;              //Mark pixel as occupied
                }
              } 
            }
          persons.at<int>(x,y) = 1;               //Mark pixel as occupied
          if(persons.at<int>(x,y+1) != 0){        //Check if person occupied area is over
            double pend = ((y+cy)*current_depth/f) + paddingperson; 
            int endp = nearbyint((pend*f/current_depth)-cy);
            if(endp < segmented.rows){                                       //Check if coordinsate is in picture bound  
              if(depth.at<double>(x,endp) > current_depth && persons.at<int>(x,endp) != 1){          //Checks if current value is larger (further away) new value
                depth.at<double>(x,endp) = current_depth;            //Set new value
                persons.at<int>(x,endp) = 1;                                //Mark pixel as person
              }
            }else{
              endp = segmented.rows;
            }    
            for(int i = y+1 ; i < endp +1; i++){
              if(persons.at<int>(x,i) == 1 && current_depth < depth.at<double>(x,i)){         //Checks if there is a another person closer to the rover. if true the radius does not be calculated yet
                i = endp + 1;                                                                         //Break the for i -loop
              }else{
                double ne = depth.at<double>(x,i) - sqrt(pow(paddingperson,2)-pow(((x+cx)*depth.at<double>(x,i)/f)-((x+cx)*current_depth/f),2))+((i+cy)*depth.at<double>(x,i)/f); //Caclulates the new distance   
                if(ne < depth.at<double>(x,i)){          //Check if new value is closer
                  depth.at<double>(x,i) = ne;            //Set new value
                  persons.at<int>(x,i) = 1;              //Mark pixel as occupied
                }//end if(ne < depth.at<double>(x,i))
              }  //end else(persons.at<int>(x,i) == 1 && depth.at<double>(x,y) < depth.at<double>(x,i))
            }    //end for i                                                                           
          }      //end if(persons.at<int>(x,y+1) != 0)
        }        //end if(segmented.at<int>(x,y,0)==person && ((x+cx)*depth.at<double>(x,y)/f) && persons.at<int>(x,y) != 0)
        depth.at<double>(x,y)= current_depth;
      }          //end for y
    }            //end for x
 


  cv::Mat out;

  for (int y = 0; y < segmented.rows; y++)
    {
      double max = 0;
      cv::Mat temp;
      for (int x = 0; x < segmented.cols; x++)
      {
        if(segmented.at<cv::Vec3b>(x,y)[1] != grass && ((x+cx)*depth.at<double>(x,y)/f) < 120){
           temp.push_back(depth.at<double>(x,y));
        }
      }
       cv::minMaxIdx(temp, NULL, &max, NULL, NULL);
       out.push_back(max);
    }

      // out.convertTo(inimg, CV_16UC1);
      // cv::FileStorage file("/home/christoph/dhbw/Rasenmaeher/kamera/out.txt", cv::FileStorage::WRITE);
      // file << "Vector" << out;
     cv_bridge::CvImage imgout;
        imgout.encoding = sensor_msgs::image_encodings::TYPE_16UC1;
        imgout.header.frame_id = "/uav1/camera/depth";
        imgout.header.stamp = ros::Time::now();
        imgout.header.seq = seq++;
        imgout.image = out.t();
    crop_pub.publish(imgout);
    publishLaserscan(out);
    ROS_ERROR("Verarbeitet");
  }
}

void Depth_Detection::publishLaserscan(cv::Mat in){
  int cy = nearbyint(cam_info.K.at(5)); //cy
  sensor_msgs::LaserScan scan_msg;
  scan_msg.header.frame_id = "/uav1/camera/depth";
  scan_msg.header.seq = seq;
  scan_msg.header.stamp = ros::Time::now();
  scan_msg.angle_min = angle_between_rays(0, in.at<double>(0), cy, in.at<double>(cy));
  scan_msg.angle_max = angle_between_rays( in.cols -1, in.at<double>(in.cols -1), cy, in.at<double>(cy));
  scan_msg.angle_increment = (scan_msg.angle_max - scan_msg.angle_min) / in.cols;
  scan_msg.range_min = 0.1;
  scan_msg.range_max = 10;
  scan_msg.ranges = in;
  scan_msg.time_increment = 0;
  laser_pub.publish(scan_msg);
}

double Depth_Detection::angle_between_rays(int y1, double z1, int y2, double z2){
  double d = abs(((y1+cy)*z1/f)-((y2+cy)*z2/f));
  return atan2(z2, d);
}

  cv::Vec3f Depth_Detection::picturetoWorld(cv::Vec3f in)
  {
    cv::Vec3f out;
    out[0] = (in[0]+cx)*in[2]/f;
    out[1] = (in[1]+cy)*in[2]/f;
    out[2] = in[2];
    return out;
  }

  cv::Vec3f Depth_Detection::worldtoPicture(cv::Vec3f in)
  {
    cv::Vec3f out;
    out[0] = nearbyint((in[0]*f/in[2])-cx);
    out[1] = nearbyint((in[1]*f/in[2])-cy);
    out[2] = in[2];
    return out;
  }


void Depth_Detection::reciveCameraInfo(sensor_msgs::CameraInfo info)
{
  if (!got_cam_info)
  {
    ROS_ERROR("Got CAM info");
    cam_info = info;
    double cx = cam_info.K.at(2); //cx
    double cy = cam_info.K.at(5); //cy
    double f = cam_info.K.at(0); //Focal
    double b = 1.0 / baseline; //1.0/BaseLine
    got_cam_info = true;
  }
}

void Depth_Detection::receiveSegmented(sensor_msgs::Image segm){
  ROS_ERROR("Got seg");
  seg = segm;
  
}

void Depth_Detection::init(ros::NodeHandle n)
{

  //Initialize the Publishers
  crop_pub = n.advertise<sensor_msgs::Image>("/uav1/camera/depth", 100);
  laser_pub = n.advertise<sensor_msgs::LaserScan>("/uav1/camera/laser", 10);
  
  //Initalize the Subscriber
  seg_sub = n.subscribe("/bonnetal/segmentation/color", 1, &Depth_Detection::receiveSegmented, this);
  image_sub = n.subscribe("/uav1/camera/depth/image_rect_raw", 1, &Depth_Detection::publishDepthVector, this);
  info_sub = n.subscribe("/uav1/camera/depth/camera_info", 1, &Depth_Detection::reciveCameraInfo, this);

  // message_filters::Subscriber<sensor_msgs::Image> image_sub(n, "/uav1/camera/depth/image_rect_raw", 10000);
  // message_filters::Subscriber<sensor_msgs::Image> seg_sub(n, "/bonnetal/segmentation/color", 10000);
  //message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(image_sub, seg_sub, 100);
  // typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  // message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10000), image_sub, seg_sub);
  // //sync.setAgePenalty(1.0);
  // sync.setInterMessageLowerBound(ros::Duration(2));
  // sync.registerCallback(boost::bind(&Depth_Detection::publishDepthVector, this,  _1, _2)); //, _1, _2
}

Depth_Detection::Depth_Detection()
{
}

Depth_Detection::~Depth_Detection()
{
}
