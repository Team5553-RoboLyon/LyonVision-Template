#pragma once

#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>

/*
  Classe pour lire une à une les images d'un dossier
  Exemple, faire défiler les images en appuyant sur le clavier :

    Diapo my_diapo("directory/folder/", ".jpg");
    cv::Mat img;
    while (true) {
      my_diapo.read(img);
      cv::imshow("Img", img);
      cv::waitKey(0);
    }
*/

class Diapo {
 public:
  /*
    foldername : nom du fichier dans lequel sont les images (ex: "data/images/")
    extention : type des images (ex: ".png")
  */
  Diapo(std::string foldername, std::string extention);

  /*
    Récupère la prochaine image présente dans le dossier
    Si on arrive à la fin, le diapo recommence au début
  */
  bool read(cv::OutputArray image);

 private:
  /*
   Incrémente le compteur et retourne à zéro si il a atteint le nombre d'images
  */
  void incrementation();

  /*
    Vérifie (et corrige) si le chemin se termine par "/"
  */
  std::string checkFolderName(std::string foldername);

  /*
  Vérifie (et corrige) si l'extension commence par "."
  */
  std::string checkExtension(std::string extention);

  // Liste des noms de fichiers
  std::vector<cv::String> m_imagesNames;

  // Nombre d'images trouvées dans le dossier
  int m_nombreDePhotos;

  // Compteur pour "naviguer" à travers les images
  int m_iterator;
};