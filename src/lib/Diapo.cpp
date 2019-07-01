#include "diapo.h"
#include <opencv2/videoio.hpp>

Diapo::Diapo(std::string foldername, std::string extention, int nombreDePhotos) {
  m_foldername     = checkFolderName(foldername);
  m_extention      = checkExtension(extention);
  m_nombreDePhotos = nombreDePhotos;
  m_iterator       = 0;
}

bool Diapo::read(cv::OutputArray image) {
  cv::VideoCapture capture(m_foldername + std::to_string(m_iterator) + m_extention);
  incrementation();
  return capture.read(image);
}

void Diapo::incrementation() {
  m_iterator++;
  if (m_iterator >= m_nombreDePhotos) {
    m_iterator = 0;
  }
}

std::string Diapo::checkFolderName(std::string foldername) {
  if (foldername.back() != '/') {
    foldername = foldername + "/";
  }
  return foldername;
}

std::string Diapo::checkExtension(std::string extention) {
  if (extention.front() != '.') {
    extention = "." + extention;
  }
  return extention;
}