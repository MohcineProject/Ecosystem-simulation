
#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "Behaviour.h"

class Bestiole;

/**
 * @class Fearful
 * @brief Represents the "fearful" behaviour for a Bestiole.
 *
 * The Fearful behavior calculates a new direction for a Bestiole to
 * avoid its neighbors, and increase its speed.
 */
class Fearful : public Behaviour {
  /**
   * @brief Density threshold for nearby Bestioles.
   *
   * This constant defines the density of Bestioles that the Fearful behavior
   * considers for determining when to react.
   */
  static const int DENSITE_BESTIOLE;

  /**
   * @brief Coefficient for calculating the modified speed.
   */
  static const double COEF_FPEUR;

  /**
   * @brief Calculates a new direction to avoid neighbors.
   *
   * Based on the proximity and density of neighboring Bestioles, this
   * method computes a new direction for the Bestiole to escape.
   *
   * @param neighbors A set of pointers to nearby Bestioles.
   * @return The new direction for the Bestiole.
   */
  double calculateNewDirection(const std::set<Bestiole*>& neighbors);

public:
  /**
   * @brief Constructor for the Fearful class.
   *
   * Initializes a Fearful behaviour for a given Bestiole.
   *
   * @param bestiole A pointer to the Bestiole using this behavior.
   */
  Fearful(Bestiole* bestiole);

  /**
   * @brief Executes the Fearful behavior.
   *
   * This method updates the Bestiole's behavior by considering its neighbors
   * and modifying its orientation as well as increasing its speed to avoid them.
   *
   * @param neighbors A set of pointers to neighboring Bestioles.
   */
  void doBehaviour(std::set<Bestiole*>& neighbors);

};

#endif // PEUREUSE_H
