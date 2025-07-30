#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

std::vector<std::vector<std::pair<double, double>>> Milieu::coordmatrix;


const std::vector<Bestiole>& Milieu::getBestioles() const {
   return listeBestioles;
}

const T    Milieu::white[] = { static_cast<T>(255), static_cast<T>(255), static_cast<T>(255) };


Milieu::Milieu(const int _width, const int _height ) : UImg(_width, _height, 1, 3),
                                            width(_width), height(_height) {
   cout << "const Milieu" << endl;
   listeBestioles.reserve(500);
   std::srand(time(NULL));
}


Milieu::~Milieu( )
{
   listeBestioles.clear();
   cout << "dest Milieu" << endl;

}


void Milieu::step()
{
   // Draw the environment
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   // Detect the collisions and flag the dead bestioles
   detectCollisions();
   // A helper vector to store bestioles to kill
   std::vector<Bestiole*> toDie;
   // Loop through all the bestioles and execute the step
   for (auto & bestiole : listeBestioles)
   {
      // If a bestiole is flagged dead, destroy the object and remove it from the list
      if  (bestiole.deathflag || bestiole.amIOld()) {
         toDie.push_back(&bestiole);
      } else {
         // Else modify the state of the bestiole and redraw it
         bestiole.grow();
         bestiole.action( *this );
         bestiole.draw( *this );
      }
   }
   // Safely destroy the bestioles outside the iterator loop
   for (const auto& b : toDie) {
      kill(*b);
   }
   toDie.clear();
}





void Milieu::kill(Bestiole& b) {
   // Check if indeed the bestiole should be killed
   if (!b.deathflag) return;
   // Remove the Bestiole from the list
   listeBestioles.erase(
       std::remove_if(listeBestioles.begin(), listeBestioles.end(),
                      [&b](const Bestiole& other) { return other.getIdentite() == b.getIdentite(); }),
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
   int k = 0; // Row index
   for (Bestiole& i : listeBestioles) {
      int l = 0; // Column index
      for (Bestiole& it : listeBestioles) {

         // Calculate the distance vector coordinates between the two bestioles
         int dx = i.x - it.x;
         int dy = i.y - it.y;

         // Calculate the squared distance between the two bestioles
         int distSquared = dx * dx + dy * dy;

         // Calculate the dot product (used for the angle)
         double dotProduct = i.x * it.x + i.y * it.y;

         // Compute magnitudes of the coordinates of the bestioles
         double magnitude1 = std::sqrt(i.x * i.x + i.y * i.y);
         double magnitude2 = std::sqrt(it.x * it.x + it.y * it.y);

         if (magnitude1 == 0 || magnitude2 == 0) {
            std::cerr << "Error: Zero-length vector detected!" << std::endl;
            continue; // Skip this pair
         }

         // Compute cosine of the angle
         double cosTheta = dotProduct / (magnitude1 * magnitude2);

         // Ensure the cos Theta is between -1 and 1 ( it may exceed the bounds due the floating point
         // presentation ) and calculates the angle.
         cosTheta = std::max(-1.0, std::min(1.0, cosTheta));
         double theta = std::acos(cosTheta);
         double thetaDegrees = theta * (180.0 / M_PI);

         // Store the pair in the matrix
         auto myPair = std::make_pair(distSquared, thetaDegrees);
         coordmatrix[k][l] = myPair; // Assign to the correct position

         if (&it != &i && distSquared < r*r) {
               constexpr T color[3] = {255, 0, 0};
               draw_circle(i.x, i.y, 5, color);
               const float randDraw = static_cast<float>(std::rand()) / RAND_MAX;
               const float iOrientation = i.getOrientation();
               it.setOrientation(M_PI - iOrientation);
               if (randDraw <= i.deathProbability) {
                  i.die();

            }
         }
         l++;
      }
      i.updatematrix(coordmatrix[k], k, listeBestioles);
      k++;
   }
}


void printMatrix(const std::vector<std::vector<std::pair<int, double>>>& matrix) {
   // Nested loop to travers the coordination matrix and print its values to the user
   for (size_t i = 0; i < matrix.size(); ++i) {
      std::cout << "Row " << i << ": ";
      for (size_t j = 0; j < matrix[i].size(); ++j) {
         std::cout << "(" << matrix[i][j].first << ", " << matrix[i][j].second << ") ";
      }
      std::cout << std::endl;
   }
}


