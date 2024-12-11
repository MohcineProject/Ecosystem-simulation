#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

std::vector<std::vector<std::pair<double, double>>> Milieu::coordmatrix;

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg(_width, _height, 1, 3),
                                            width(_width), height(_height) {
   cout << "const Milieu" << endl;
   listeBestioles.reserve(20);

   std::srand(time(NULL));
}


Milieu::~Milieu( void )
{

   cout << "dest Milieu" << endl;

}


void Milieu::step( void )
{

   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   detectCollisions();
   std::vector<Bestiole*> toDie;
   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {
      it->action( *this );
      it->draw( *this );

   }

   for (auto& it : listeBestioles) {
      if (it.deathflag) toDie.push_back(&it);
   }
   for (auto b : toDie) {
      kill(*b);
   }
   toDie.clear();
}


int Milieu::nbVoisins( const Bestiole & b )
{

   int         nb = 0;


   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b.jeTeVois(*it) )
         ++nb;

   return nb;

}


void Milieu::kill(Bestiole& b) {
   if (!b.deathflag) return;
   /*
   std::cout << "Bestiole to kill " << b.getIdentite() << std::endl;
   std::cout << "liste bestioles ";
   for (auto& it : listeBestioles) {
      std::cout << it.getIdentite() << "_" << it.deathflag << " ";
   }
   std::cout << std::endl;
   */
   // Remove the Bestiole from the list
   listeBestioles.erase(
       std::remove_if(listeBestioles.begin(), listeBestioles.end(),
                      [&b](const Bestiole& other) { return other.getIdentite() == b.getIdentite(); }),
       listeBestioles.end()
   );

   // Reduce the count after removal
   n--;

   b.deathflag = false;
   /*
   std::cout << "after death   ";
   for (auto& it : listeBestioles) {
      std::cout << it.getIdentite() << "_" << it.deathflag << " ";
   }
   std::cout << std::endl;
   */
}

void Milieu::detectCollisions() {
   coordmatrix.clear();
   coordmatrix.resize(n);
   for (int i = 0; i < n; ++i) {
      coordmatrix[i].clear();
      coordmatrix[i].resize(n);
   }

   int k = 0; // Row index
   for (Bestiole& i : listeBestioles) {
      int l = 0; // Column index
      for (Bestiole& it : listeBestioles) {
         int dx = i.x - it.x;
         int dy = i.y - it.y;
         int distSquared = dx * dx + dy * dy;

         double dotProduct = i.x * it.x + i.y * it.y;

         // Compute magnitudes
         double magnitude1 = std::sqrt(i.x * i.x + i.y * i.y);
         double magnitude2 = std::sqrt(it.x * it.x + it.y * it.y);

         if (magnitude1 == 0 || magnitude2 == 0) {
            std::cerr << "Error: Zero-length vector detected!" << std::endl;
            continue; // Skip this pair
         }

         // Compute cosine of the angle
         double cosTheta = dotProduct / (magnitude1 * magnitude2);

         // Clamp to [-1, 1] for numerical stability
         cosTheta = std::max(-1.0, std::min(1.0, cosTheta));
         double theta = std::acos(cosTheta);
         double thetaDegrees = theta * (180.0 / M_PI);

         // Store the pair in the matrix
         auto myPair = std::make_pair(distSquared, thetaDegrees);
         coordmatrix[k][l] = myPair; // Assign to the correct position
         l++;
         if (&it != &i) {
            if (coordmatrix[k][l-1].first < r * r) {
               T color[3] = {255, 0, 0};
               draw_circle(i.x, i.y, 10, color);
               float randDraw = static_cast<float>(std::rand()) / RAND_MAX;
               if (randDraw < 0.1) {
                  i.die();
                  //std::cout << i.getIdentite() << " collided with " << it.getIdentite() << std::endl;
               }
            }
         }
      }
      k++;
      i.updatematrix(coordmatrix[k-1], k-1, listeBestioles);
   }
}


void printMatrix(const std::vector<std::vector<std::pair<int, double>>>& matrix) {
   for (size_t i = 0; i < matrix.size(); ++i) {
      std::cout << "Row " << i << ": ";
      for (size_t j = 0; j < matrix[i].size(); ++j) {
         std::cout << "(" << matrix[i][j].first << ", " << matrix[i][j].second << ") ";
      }
      std::cout << std::endl;
   }
}


