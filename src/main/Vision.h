#pragma once

#include <opencv2/opencv.hpp>
#include "lib/MjpegStream.h"

class Vision {
 public:
  Vision();
  void Run();

 private:
  cv::Mat PrepareFrame(cv::Mat frame);

  cv::VideoCapture      m_camera;
  lyonlib::MjpegStream* m_streamServerOriginal;
  lyonlib::MjpegStream* m_streamServerTracking;

  const int m_resWidth;
  const int m_resHeight;

  float m_widthGoal;
  float m_heightGoal;
};