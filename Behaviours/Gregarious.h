//
// Created by mouha1505 on 28/11/24.
//

#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "Behaviour.h"

// Gregarious class inherits from Behaviour. Represents a behaviour where the Bestiole
//exhibits social behavior.
class Gregarious : public Behaviour{
public:
  void doBehaviour(std::set<Bestiole*>& neighbors) override;
  Gregarious(Bestiole *bestiole) ;
  std::string getType() override{return type;}
  };

#endif //GREGAIRE_H
