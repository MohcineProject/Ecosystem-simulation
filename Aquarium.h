#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{

    private :
       Milieu       * flotte;

    int            delay;

    public :
       void assign(const Milieu & milieu, const char * str);

       Aquarium( int width, int height, int _delay );
    ~Aquarium( void );

    private:
        double finsSpeedFactor;
        double carapaceOmega, carapaceMu;
        double camouflageMin, camouflageMax;

    public:
        void setAccessoryParams(double finsSF, double omega, double mu, double camoMin, double camoMax) {
            finsSpeedFactor = finsSF;
            carapaceOmega = omega;
            carapaceMu = mu;
            camouflageMin = camoMin;
            camouflageMax = camoMax;
    }


    Milieu & getMilieu( void ) { return *flotte; }

    void run( void );

};


#endif
