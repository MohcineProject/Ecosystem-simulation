#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"
#include <vector>
using namespace std;

/**
 * @class Milieu
 *
 * @brief The Milieu class represents an environment for the bestioles.
 * It contains functionalities to execute the simulation step by step, as well
 * executing each bestiole behaviour and handling collisions and deaths.
 *
 * It inherits from the class UImg to provide a visual representation of the simulation.
 *
 */
class Milieu : public UImg
{

private :
   /**
 * @brief This class T represents an "unsigned char" as defined in the UImg class.
 * It is used to define a color for the environment of simulation as pixels values.
 *
 */
   static const T          white[];
    /**
 * @brief Represents the dimensions of the simulation graphical interface.
 */
   int                     width, height;
   /**
 * @brief Stores all bestioles of a simulation in a list.
 */
   std::vector<std::unique_ptr<Bestiole>>   listeBestioles;
    /**
 * @brief Represents the number of bestioles in the simulation
 */
   int n = 0;
    /**
 * @brief Represents the minimum distance between two bestioles where a collision will be considered
 */
   int r=20;
    /**
 * @brief The CoordMatrix attribute is designed to store matrix data for the bestioles positions.
 * It is used to determine collisions in the simulation. Check the .cpp file for implementation.
 */
   static std::vector<std::vector<std::pair<double, double>>> coordmatrix;

public :
    /**
 * @brief A function to retrieve the list of all bestioles in the simulation
 */
   const std::vector<std::unique_ptr<Bestiole>>& getBestioles() const;
    /**
     * @brief The constructor of the Milieu class.
     * @param _width the width of the GUI
     * @param _height the height of the GUI
     */
   Milieu( int _width, int _height );
    /**
 * @brief The destructor of the class Milieu
 */
   ~Milieu( );

    /**
     * @brief Retrieves the width of simulation GUI.
     * @return The width of the GUI.
     */
   int getWidth(  ) const { return width; };
    /**
 * @brief Retrieves the height of simulation GUI.
 * @return The height of the GUI.
 */
   int getHeight(  ) const { return height; };


    /**
     * @brief Represents a single step in the simulation. It handles executing bestioles behaviours at each step, as well as handling
     * their death, and redrawing.
     */

   void step(  );
    /**
     * @brief Adds a new bestiole to the vector of bestioles, and initializes its cooridnates.
     *
     * @param b The bestiole passed as an rvalue to be added to the simulation.
     */
   void addMember( std::unique_ptr<Bestiole>&& b ) {
      listeBestioles.push_back(std::move(b));
      listeBestioles.back()->initCoords(width, height);
      n++;

   }

    /**
     * @brief Computes the number of neighbors for a given bestiole in the simulation .
     * @param b a reference to the bestiole to compute its neighbors.
     * @return The number of neighboring of a bestiole.
     */
   int nbVoisins( const Bestiole & b ) const;
    /**
 * @brief Detects and handles collisions in the simulation.
 *
 * This method processes all potential collisions between
 * bestioles and kills them randomly as a consequence of the impact.
 * Check the algorithm description in the .cpp file.
 *
 */
   void detectCollisions();
    /**
    * @brief A helper function to print the coordinations matrix
    * @param matrix the coordinations matrix containing distances and angles between the bestioles
    */
   static void printMatrix(const std::vector<std::vector<std::pair<int, double>>>& matrix);

    /**
     * @brief destroys and remove a bestiole from the list of bestioles of the simulation.
     * @param position the bestiole poisition in the vector of bestioles to be destroyed and removed from the simulation
     */
   void kill(int position);
};


#endif
