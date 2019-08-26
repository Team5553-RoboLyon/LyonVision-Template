#include "Vision.h"

#include <iostream>

int thresh = 100;

Vision::Vision() : m_resWidth(320), m_resHeight(240) {
  m_camera = cv::VideoCapture(0);

  m_camera.set(CV_CAP_PROP_FRAME_WIDTH, m_resWidth);
  m_camera.set(CV_CAP_PROP_FRAME_HEIGHT, m_resHeight);

  m_widthGoal  = m_resWidth / 2;
  m_heightGoal = m_resHeight / 2;

  std::cout << "Width: " << m_resWidth << " Height: " << m_resHeight << std::endl;
  std::cout << "Goals: " << m_widthGoal << "," << m_heightGoal << std::endl;

  // This lets us see the m_cameraera output on the robot dashboard. We give it a
  // name, and a width and height.
  m_streamServerOriginal = new lyonlib::MjpegStream("Original", m_resWidth, m_resHeight, 30);
  m_streamServerTracking = new lyonlib::MjpegStream("Tracking", m_resWidth, m_resHeight, 30);
}

// This is the main entrypoint into the Vision Program!
void Vision::Run() {
  cv::RNG  rng(12345);
  cv::Rect bounding_rect;
  float    height_offset;
  float    width_offset;
  cv::Mat  imgOriginal;

  while (true) {
    if (m_camera.read(imgOriginal)) {
      cv::Mat imgTracking = PrepareFrame(imgOriginal);

      /// Find contours
      std::vector<std::vector<cv::Point> > contours;
      std::vector<cv::Vec4i>               hierarchy;
      cv::threshold(imgTracking, imgTracking, thresh, 255, cv::THRESH_BINARY);
      cv::findContours(imgTracking, contours, hierarchy, cv::RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,
                       cv::Point(0, 0));

      /// Find the convex hull object for each contour
      std::vector<std::vector<cv::Point> > hull(contours.size());
      for (size_t i = 0; i < contours.size(); i++) {
        cv::convexHull(contours[i], hull[i]);
      }

      /// Draw contours + hull results
      imgTracking = cv::Mat::zeros(imgTracking.size(), CV_8UC3);
      std::vector<cv::Rect> boundRect(contours.size());

      for (size_t i = 0; i < contours.size(); i++) {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        cv::drawContours(imgTracking, contours, (int)i, color);
        cv::drawContours(imgTracking, hull, (int)i, color);
      }

      /// Detect edges using Threshold
      cv::threshold(imgTracking, imgTracking, thresh, 255, cv::THRESH_BINARY);
      /// Find contoursBox

      /// Approximate contoursBox to polygons + get bounding rects and circles
      std::vector<std::vector<cv::Point> > hull_poly(hull.size());
      std::vector<cv::Point2f>             center(hull.size());
      std::vector<float>                   radius(hull.size());

      for (int i = 0; i < hull.size(); i++) {
        cv::approxPolyDP(cv::Mat(hull[i]), hull_poly[i], 3, true);
        boundRect[i] = cv::boundingRect(cv::Mat(hull_poly[i]));
        cv::minEnclosingCircle((cv::Mat)hull_poly[i], center[i], radius[i]);
      }

      /// Draw polygonal contour + bonding rects + circles
      for (int i = 0; i < hull.size(); i++) {
        cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        cv::drawContours(imgTracking, hull_poly, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
        bounding_rect = boundingRect(contours[i]);  // Find the bounding rectangle for biggest contour
        cv::rectangle(imgTracking, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
        cv::circle(imgTracking, center[i], (int)radius[i], color, 2, 8, 0);
      }

      // get the moments
      std::vector<cv::Moments> mu(hull.size());
      for (int i = 0; i < hull.size(); i++) {
        mu[i] = cv::moments(hull[i], false);
      }

      // get the centroid of figures.
      std::vector<cv::Point2f> mc(hull.size());
      for (int i = 0; i < hull.size(); i++) {
        mc[i] = cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
      }

      for (int i = 0; i < hull.size(); i++) {
        cv::Scalar color = cv::Scalar(167, 151, 0);  // B G R values
        // drawContours(imgTracking, hull_poly, i, color, 2, 8, hierarchy, 0,
        // Point());
        cv::circle(imgTracking, mc[i], 4, color, -1, 8, 0);

        // offsets from center
        cv::Point center = cv::Point((mc[i].x), (mc[i].y));
        width_offset     = m_widthGoal - center.x;
        height_offset    = m_heightGoal - center.y;

        std::stringstream offsetY;
        offsetY << height_offset;
        std::stringstream offsetX;
        offsetX << width_offset;
        cv::putText(imgTracking, "xy(" + offsetX.str() + "," + offsetY.str() + ")",
                    mc[i] + cv::Point2f(-25, 25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1,
                    cv::Scalar(255, 0, 255));  // text with distance and angle on target
      }

#ifdef __DESKTOP__
      cv::imshow("Original Image", imgOriginal);
      cv::imshow("Output Image", imgTracking);
      cv::waitKey(30);
#endif
      m_streamServerOriginal->PutFrame(imgOriginal);
      m_streamServerTracking->PutFrame(imgTracking);

    } else {
      std::cout << "Cannot read a frame from video stream" << std::endl;
    }
  }
}

cv::Mat Vision::PrepareFrame(cv::Mat frame) {
  // Convert input image to HSV
  cv::cvtColor(frame, frame,
               cv::COLOR_BGR2HSV);  // Convert the captugreen frame from BGR to HSV

  // Threshold the HSV image, keep only the green pixels
  cv::inRange(frame, cv::Scalar(35, 100, 100), cv::Scalar(78, 255, 255), frame);

  // Forgets green pixels under a certain size. Good if you don't want many
  // errors
  cv::erode(frame, frame, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
  cv::dilate(frame, frame, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));

  // Detect edges using Canny
  cv::Canny(frame, frame, thresh, thresh * 2);

  return frame;
}