#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>

#include "CapteurS.h"

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;
   std::vector<Bestiole>   listeBestioles;
   int n = 0;
   int r=20;
   static std::vector<std::vector<std::pair<double, double>>> coordmatrix;

public :
   const std::vector<Bestiole> &getBestioles() const;

   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const Bestiole & b ) {
      listeBestioles.push_back(b);
      listeBestioles.back().initCoords(width, height);
      n++;

   }


   int nbVoisins( const Bestiole & b );
   void detectCollisions();
   void printMatrix();
   void kill(Bestiole & b);
};


#endif
