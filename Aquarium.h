
#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{

    private :
       Milieu       * flotte;

    int            delay;

    public :
       Aquarium( int width, int height, int _delay );
    ~Aquarium( void );
    float         cap_detection_max;
    float         cap_detection_min;
    float         cap_camouflage_min;
    float         cap_camouflage_max;
    float         mult_vitesse_max;
    float         red_vitesse_max;
    float         resistance_max;
    Milieu & getMilieu( void ) { return *flotte; }

    void run( void );

};


#endif
