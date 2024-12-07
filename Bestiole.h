#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include "Accessoire.h"
#include <vector>
#include <set>

#include "CapteurS.h"
#include "CapteurV.h"
#include <memory>
#include <iostream>
#include "Behaviours/Behaviour.h"
#include "Behaviours/Behaviour.h"
#include "Behaviours/Fearful.h"

using namespace std;


class Milieu;
class Behaviour;
class Behaviour;


class CapteurS;

class CapteurV;

class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

private :
   int               identite;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;

   CapteurS* captor;
   CapteurV* captorV;

   T *couleur;

    double baseSpeed;

    Behaviour* behaviour = nullptr;

    std::string type = "";


    std :: vector <std::shared_ptr<Accessoire> > accessoires;
    float detectionCapability;
    float resistance;
public:
   int x, y;
   std::vector<std::pair<double, double>>* coordvector;
   std::set<Bestiole*> detected;

   boolean seeCaptorsBool = true;

    private :
       void bouge( int xLim, int yLim );

public:
   Bestiole(double baseSpeed);                               // Default constructor
   Bestiole(const Bestiole &b);                  // Copy constructor
   ~Bestiole(void);                              // Destructor
   void action(Milieu &monMilieu);
   void draw(UImg &support);

   void setColor(Behaviour *behaviour);

   bool jeTeVois( const Bestiole & b ) const;

   int getCoordx() const;

   int getCoordy() const;

   void setCoordx(int newx);

   void setCoordy(int newy);


   double getBaseSpeed() const;

   double getMaxSpeed() const;

   void setVitesse(double newv);

   void initCoords( int xLim, int yLim );

   void setBehaviour(std::string s);

   void doBehaviour();

    double getActualSpeed() const;
    void addAccessory( shared_ptr<Accessoire> accessoire );
    float getDetectionCapability() const;
    float getResistance() const;

   void seeCaptors(UImg &support);

   void updatematrix(std::vector<std::pair<double, double>>&, int, std::vector<Bestiole>&);

   friend bool operator==(const Bestiole &b1, const Bestiole &b2);
   friend ostream& operator<<(ostream& os, const Bestiole& b);
   int getIdentite() const {
      return identite;
   }
   void setOrientation( double orientation );
   double getOrientation() const;

   bool operator<(const Bestiole& other) const {
      return identite < other.identite;
   }

   Bestiole& operator=(const Bestiole& b) {
      if (this != &b) {
         this->x = b.x;
         this->y = b.y;
         this->identite = b.identite;
         this->orientation = b.orientation;
         this->cumulX = b.cumulX;
         this->cumulY = b.cumulY;
         this->vitesse = b.vitesse;
         this->behaviour = b.behaviour;
         this->accessoires = b.accessoires;
         this->detectionCapability = b.detectionCapability;
         this->resistance = b.resistance;
         this->captor = b.captor;
         this->captorV = b.captorV;
         this->couleur = new T[3];
         memcpy(couleur, b.couleur, 3 * sizeof(T));
      }
      return *this;
   }

};


#endif
