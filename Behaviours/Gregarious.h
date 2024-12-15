#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "Behaviour.h"

/**
 * @class Gregarious
 * @brief Represents the "gregarious" behaviour for a Bestiole.
 *
 * The Gregarious behavior encourages a Bestiole to follow and align its
 * movement with that of its neighbors.
 */
class Gregarious : public Behaviour {
public:

  /**
   * @brief Executes the Gregarious behavior.
   *
   * This method adjusts the direction of the Bestiole to align with the
   * average direction of its neighbors.
   *
   * @param neighbors A set of pointers to neighboring Bestioles.
   */
  void doBehaviour(std::set<Bestiole*>& neighbors) override;

  /**
   * @brief Constructor for the Gregarious class.
   *
   * Initializes a Gregarious behavior for a given Bestiole.
   *
   * @param bestiole A pointer to the Bestiole using this behavior.
   */
  Gregarious(Bestiole* bestiole);
};

#endif // GREGAIRE_H
