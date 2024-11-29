//
// Created by mouha1505 on 28/11/24.
//

#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "Behaviour.h"

class Bestiole;

class Peureuse : public Behaviour{
  static const int DENSITE_BESTIOLE;
  static const double COEF_FPEUR;

  double getNouvelleDirection(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) ;

  public:
  void doComportement(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) override;
  Peureuse() = default;

  };


#endif //PEUREUSE_H
