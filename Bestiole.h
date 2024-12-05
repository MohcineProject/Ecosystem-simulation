#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"
#include "Accessoire.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{

    private :
       static const double     AFF_SIZE;
    static const double     MAX_VITESSE;
    static const double     LIMITE_VUE;

    static int              next;

    private :
       int               identite;
    int               x, y;
    double            cumulX, cumulY;
    double            orientation;
    double            vitesse;

    T               * couleur;

    double *baseSpeed;


    vector <shared_ptr<Accessoire> > *accessoires;
    float detectionCapability;
    float resistance;

    private :
       void bouge( int xLim, int yLim );

    public :                                           // Forme canonique :
       Bestiole( double baseSpeed );                               // Constructeur par defaut
       Bestiole();

    Bestiole( const Bestiole & b );                             // Constructeur de copies
    ~Bestiole( void );                              // Destructeur
    // Operateur d'affectation binaire par defaut
    void action( Milieu & monMilieu );
    void draw( UImg & support );

    bool jeTeVois( const Bestiole & b ) const;

    void initCoords( int xLim, int yLim );

    double getActualSpeed() const;
    void addAccessory( shared_ptr<Accessoire> accessoire );
    float getDetectionCapability() const;
    float getResistance() const;

    friend bool operator==( const Bestiole & b1, const Bestiole & b2 );
   friend ostream& operator<<(ostream& os, const Bestiole& b);

};


#endif
