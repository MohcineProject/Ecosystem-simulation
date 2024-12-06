//
// Created by mouha1505 on 28/11/24.
//

#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "Behaviour.h"

class Gregaire : public Behaviour{
public:
  void doBehaviour(std::set<Bestiole*>& neighbors) override;
  Gregaire(Bestiole *bestiole) ;
  };

#endif //GREGAIRE_H
