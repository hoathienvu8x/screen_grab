/*
 * Copyright (c) 2013 Lucas Walter
 * November 2013
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SCREEN_GRAB_SCREEN_GRAB_H
#define SCREEN_GRAB_SCREEN_GRAB_H

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/region_of_interest.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <X11/Xlib.h>

class ScreenGrab : public rclcpp::Node
{
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr screen_pub_;

  rclcpp::Subscription<sensor_msgs::msg::RegionOfInterest>::SharedPtr roi_sub_;

  void onInit();
  void roiCallback(const sensor_msgs::msg::RegionOfInterest::SharedPtr msg);
  void updateConfig();
  double update_rate_;

  // TODO(lucasw) need custom message to replace dynamic reconfigure

  void checkRoi(int& x_offset, int& y_offset, int& width, int& height);

  int x_offset_;
  int y_offset_;
  int width_;
  int height_;

  int screen_w_;
  int screen_h_;

  void spinOnce();
  bool first_error_;

  rclcpp::TimerBase::SharedPtr timer_;

  // X resources
  Display* display;
  Screen* screen;
  XImage* xImageSample;
  XColor col;

public:
  ScreenGrab();

  bool spin();
};

#endif  // SCREEN_GRAB_SCREEN_GRAB_H