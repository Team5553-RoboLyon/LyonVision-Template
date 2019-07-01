#pragma once

#include <opencv2/core/mat.hpp>
#include <string>

/*
  Classe pour lire une à une les images d'un dossier
  Elles doivent être numérotées : 1.png, 2.png, ...
  */

class Diapo {
 public:
  /*
    foldername : nom du fichier dans lequel sont les images (ex: "data/images/")
    extention : type des images (ex: ".png")
    nombreDePhotos : nombre d'images dans le dossier
  */
  Diapo(std::string foldername, std::string extention, int nombreDePhotos);
  bool read(cv::OutputArray image);

 private:
  std::string m_foldername;
  std::string m_extention;
  int         m_nombreDePhotos;
  int         m_iterator;

  void incrementation();

  std::string checkFolderName(std::string foldername);
  std::string checkExtension(std::string extention);
};