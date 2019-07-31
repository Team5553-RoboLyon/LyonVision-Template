#include "lib/MjpegStream.h"
#include <cameraserver/CameraServer.h>
#include <iostream>

MjpegStream::MjpegStream(const std::string name, int width, int height, int fps) {
  m_streamSrc    = cs::CvSource(name, cs::VideoMode::PixelFormat::kUnknown, width, height, fps);
  m_streamServer = frc::CameraServer::GetInstance()->StartAutomaticCapture(m_streamSrc);

  std::cout << "Mjpeg Stream created at : " << GetStreamAddress() << std::endl;
}

void MjpegStream::PutFrame(cv::Mat frame) {
  m_streamSrc.PutFrame(frame);
}

std::string MjpegStream::GetStreamAddress() {
  return "mjpg:http://" + cs::GetHostname() + ".local:" + std::to_string(m_streamServer.GetPort()) +
         "/?action=stream";
}
