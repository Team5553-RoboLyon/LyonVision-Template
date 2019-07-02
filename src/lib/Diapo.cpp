#include "diapo.h"
#include <opencv2/videoio.hpp>

Diapo::Diapo(std::string foldername, std::string extention) {
  // Pattern pour trouver les images (le char '*' remplace n'importe quel nom de fichier)
  std::string pattern = checkFolderName(foldername) + "*" + checkExtension(extention);

  // Liste tous les fichiers qui correspondent au pattern
  cv::glob(pattern, m_imagesNames);

  // Recuperation du nombre d'images et mise à zéro du compteur
  m_nombreDePhotos = m_imagesNames.size();
  m_iterator       = 0;
}

bool Diapo::read(cv::OutputArray image) {
  cv::VideoCapture capture(m_imagesNames[m_iterator]);
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