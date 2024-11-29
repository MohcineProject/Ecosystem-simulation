//
// Created by mouha1505 on 28/11/24.
//

#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "Behaviour.h"

class Bestiole;

class Fearful : public Behaviour{
  static const int DENSITE_BESTIOLE;
  static const double COEF_FPEUR;

  double calculateNewDirection(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) ;

  public:
  void doBehaviour(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) override;
  Fearful() = default;

  };


#endif //PEUREUSE_H
