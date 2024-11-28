//
// Created by mouha1505 on 28/11/24.
//

#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "Behaviour.h"

class Gregaire : public Behaviour{
public:
  void doComportement(Bestiole& self, const std::vector<Bestiole>& neighbors) override;
  };

#endif //GREGAIRE_H
