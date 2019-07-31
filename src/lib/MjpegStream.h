#pragma once

#include <cscore.h>
#include <opencv2/core/mat.hpp>
#include <string>

/*
  Classe pour créer un stream video facilement
  - Possibilité de connaître l'url du stream
  - Un seul objet à créer
*/

class MjpegStream {
 public:
  /*
    name : nom du stream
    width, height et fps : parametres du stream
  */
  MjpegStream(const std::string name, int width, int height, int fps);

  /*
    Put a new frame to the stream
  */
  void PutFrame(cv::Mat frame);

  /*
    Return stream url : "mjpg:http://<hostname>.local:<port>/?action=stream"
  */
  std::string GetStreamAddress();

 private:
  cs::CvSource    m_streamSrc;
  cs::MjpegServer m_streamServer;
};
