#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

const std::vector<std::unique_ptr<Bestiole>>& Milieu::getBestioles() const {
   return listeBestioles;
}

const T    Milieu::white[] = { static_cast<T>(255), static_cast<T>(255), static_cast<T>(255) };


Milieu::Milieu( int _width, int _height ) : UImg(_width, _height, 1, 3),
                                            width(_width), height(_height) {
   cout << "const Milieu" << endl;
   listeBestioles.reserve(500);
   std::srand(time(NULL));
}


Milieu::~Milieu()
{
   cout << "dest Milieu" << endl;
}


void Milieu::step(  )
{
   // Draw the environment
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   // Detect the collision and flag the dead bestioles
   detectCollisions();
   std::vector<int> toDie ;
   // Loop through all the bestioles and execute the step
   for (const auto& bestiole : listeBestioles) {
      // If a bestiole is flagged dead, destroy the object and remove it from the liste
      if (bestiole->deathflag || bestiole->amIOld()) {
         toDie.push_back( bestiole->getIdentite() );
      } else {
         // Else modify the state of the bestiole and redraw it
         bestiole->grow();
         bestiole->action(*this);
         bestiole->draw(*this);
      }
   }
   // Safely destroy the bestioles outside the iterator loop
   for (const auto identity : toDie) {
      kill(identity);
   }

}


int Milieu::nbVoisins( const Bestiole & b ) const {
   // Loop through all the bestioles and check if bestiole b can see them
   int         nb = 0;
   for ( auto& bestiole : listeBestioles )
      if ( !(b == *bestiole) && b.jeTeVois(*bestiole) )
         ++nb;
   return nb;

}


void Milieu::kill(int position) {
   // Remove the Bestiole from the list
   listeBestioles.erase(
       std::remove_if(listeBestioles.begin(), listeBestioles.end(),
                      [&position](const Bestiole& other) { return other.getIdentite() == position; }),
       listeBestioles.end()
   );
   // Reduce the count after removal
   n--;
}

void Milieu::detectCollisions() {

   // Make the coordination Matrix size larger enough to store distances and angles
   // between all bestioles.
   coordmatrix.clear();
   coordmatrix.resize(n);
   for (int i = 0; i < n; ++i) {
      coordmatrix[i].clear();
      coordmatrix[i].resize(n);
   }
   // Do a nested loop to get every bestiole distances and angles with others
   for (int i = 0; i < n; ++i) {
      const auto& bestiole1 = listeBestioles[i];
      for (int j = 0; j < n; ++j) {
         const auto& bestiole2 = listeBestioles[j];

         // Calculate the distance vector coordinates between the two bestioles
         const int dx = bestiole1->x - bestiole2->x;
         const int dy = bestiole1->y - bestiole2->y;

         // Calculate the squared distance between the two bestioles
         int distSquared = dx * dx + dy * dy;

         // Calculate the dot product (used for the angle)
         double dotProduct = bestiole1->x * bestiole2->x + bestiole1->y * bestiole2->y;

         // Compute magnitudes of the coordinates of the bestioles
         double magnitude1 = std::sqrt(bestiole1->x * bestiole1->x + bestiole1->y * bestiole1->y);
         double magnitude2 = std::sqrt(bestiole2->x * bestiole2->x + bestiole2->y * bestiole2->y);

         if (magnitude1 == 0 || magnitude2 == 0) {
            std::cerr << "Error: Zero-length vector detected!" << std::endl;
            continue; // Skip this pair
         }

         // Compute cosine of the angle
         double cosTheta = dotProduct / (magnitude1 * magnitude2);

         // Ensure the cos Theta is between -1 and 1 ( it may exceed the bounds due the floating point
         // presentation ) and calculates the angle.
         cosTheta = std::max(-1.0, std::min(1.0, cosTheta));
         const double theta = std::acos(cosTheta);
         double thetaDegrees = theta * (180.0 / M_PI);

         // Store the pair in the matrix
         coordmatrix[i][j] = std::make_pair(distSquared, thetaDegrees);

         // If distance squared is less than radius squared, draw a circle and apply interactions
         if (i != j && distSquared < r * r) {
            constexpr T color[3] = {255, 0, 0};
            draw_circle(bestiole1->x, bestiole1->y, 5, color);

            const float randDraw = static_cast<float>(std::rand()) / RAND_MAX;
            const float iOrientation = bestiole1->getOrientation();
            bestiole1->setOrientation(M_PI - iOrientation);

            if (randDraw <= bestiole1->deathProbability) {
               bestiole1->die();
            }
         }
      }
      bestiole1->updatematrix(coordmatrix[i], i, listeBestioles);
   }
}


void Milieu::printMatrix(const std::vector<std::vector<std::pair<int, double>>>& matrix) {
   // Nested loop to travers the coordination matrix and print its values to the user
   for (size_t i = 0; i < matrix.size(); ++i) {
      std::cout << "Row " << i << ": ";
      for (size_t j = 0; j < matrix[i].size(); ++j) {
         std::cout << "(" << matrix[i][j].first << ", " << matrix[i][j].second << ") ";
      }
      std::cout << std::endl;
   }
}


