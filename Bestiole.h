#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include "Accessoire.h"
#include <vector>
#include <set>
#include <memory>

#include "CapteurS.h"
#include "CapteurV.h"
#include <memory>
#include <iostream>
#include "Behaviours/Behaviour.h"
#include "Behaviours/Cautious.h"
#include "Behaviours/Fearful.h"
#include "Behaviours/Gregarious.h"
#include "Behaviours/Kamikaze.h"
#include "Behaviours/MultipleBehaviour.h"

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
   static const int        AGE_LIMIT_MAX;
   static const int        AGE_LIMIT_MIN;

   static int              next;

private :
   int               identite;
   double            cumulX, cumulY;
   float            orientation;
   double            vitesse;




   std::unique_ptr<T[]> couleur;

    double baseSpeed;





    float resistance;
public:
   std :: vector <std::shared_ptr<Accessoire> > accessoires;
   int x, y;
   CapteurS* captor = nullptr;
   CapteurV* captorV = nullptr;
   std::vector<std::pair<double, double>>* coordvector;
   std::set<Bestiole*> detected;
   bool deathflag = false;

   float detectionCapability = 0;

   bool seeCaptorsBool = false;

   float deathProbability;
   int myAgeLimit;
   int myAge;

   Behaviour* behaviour = nullptr;

   std::string type = "";

    private :
       void bouge( int xLim, int yLim );

public:
   Bestiole(double baseSpeed);                               // Default constructor
   Bestiole(const Bestiole &b);                  // Copy constructor
   Bestiole(Bestiole&& b) noexcept;
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

   void die() { this->deathflag = true; }

    double getActualSpeed() const;
    void addAccessory( shared_ptr<Accessoire> accessoire);
    float getDetectionCapability() const;
    float getResistance() const;

   void seeCaptors(UImg &support) const;

   void attachCaptorV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin);

   void attachCaptorS(float capSMax, float capSMin, float distMax, float distMin);

   void updatematrix(std::vector<std::pair<double, double>>&, int, std::vector<std::unique_ptr<Bestiole>>&);

   friend bool operator==(const Bestiole &b1, const Bestiole &b2) { return (b1.identite == b2.identite); }
   friend ostream& operator<<(ostream& os, const Bestiole& b);
   int getIdentite() const {
      return identite;
   }
   void setOrientation( float orientation );
   float getOrientation() const;

   bool operator<(const Bestiole& other) const {
      return identite < other.identite;
   }

   Bestiole& operator=(const Bestiole& b);

   Bestiole& operator=(Bestiole&& b) noexcept;

   bool amIOld() const;
   void grow();
};


#endif
