//
// Created by mouha1505 on 28/11/24.
//

#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "Behaviour.h"

class Bestiole;

class Fearful : public Behaviour {
  static const int DENSITE_BESTIOLE;
  static const double COEF_FPEUR;

  double calculateNewDirection(const std::set<Bestiole*>& neighbors) ;

  public:
  Fearful(Bestiole* bestiole);
  void doBehaviour(std::set<Bestiole*>& neighbors);


  };


#endif //PEUREUSE_H
