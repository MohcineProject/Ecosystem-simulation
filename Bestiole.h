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

using namespace std;

class Milieu;


class CapteurS;

class CapteurV;

class Bestiole
{
private:
   static const double AFF_SIZE;
   static const double MAX_VITESSE;
   static const double LIMITE_VUE;

   static int next;

private:
   int identite;

   double cumulX, cumulY;
   double orientation;
   double vitesse;

   CapteurS* captor;
   CapteurV* captorV;

   T *couleur;

    double baseSpeed;


    std :: vector <std::shared_ptr<Accessoire> > accessoires;
    float detectionCapability;
    float resistance;
public:
   int x, y;
   std::vector<std::pair<double, double>>* coordvector;
   std::set<Bestiole*> detected;

    private :
       void bouge( int xLim, int yLim );

public:
   Bestiole(double baseSpeed);                               // Default constructor
   Bestiole(const Bestiole &b);                  // Copy constructor
   ~Bestiole(void);                              // Destructor
   void action(Milieu &monMilieu);
   void draw(UImg &support);

   bool jeTeVois(const Bestiole &b) const;

   void initCoords(int xLim, int yLim);

    double getActualSpeed() const;
    void addAccessory( shared_ptr<Accessoire> accessoire );
    float getDetectionCapability() const;
    float getResistance() const;

   void updatematrix(std::vector<std::pair<double, double>>&, int, std::vector<Bestiole>&);

   friend bool operator==(const Bestiole &b1, const Bestiole &b2);
   friend ostream& operator<<(ostream& os, const Bestiole& b);

};

#endif // _BESTIOLES_H_
