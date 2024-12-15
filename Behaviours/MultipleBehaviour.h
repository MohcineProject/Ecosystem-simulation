#ifndef MULTIPLEBEHAVIOUR_H
#define MULTIPLEBEHAVIOUR_H

#include <memory>
#include <set>
#include <vector>

#include "Behaviour.h"
#include "../Bestiole.h"

/**
 * @class MultipleBehaviour
 * @brief Represents a Bestiole that can switch between multiple behaviors dynamically.
 *
 */
class MultipleBehaviour : public Behaviour {
    /**
     * @brief A list of available behaviors for the Bestiole.
     *
     * This vector holds unique pointers to the behaviors that the Bestiole can adopt.
     */
    std::vector<std::unique_ptr<Behaviour>> behaviours;

    /**
     * @brief Names of the behaviors associated with this class.
     *
     * This vector stores the names of each behavior, helping to identify and initialize them.
     */
    std::vector<std::string> behaviourNames;

    /**
     * @brief Pointer to the currently active behaviour.
     *
     * This points to the behaviour that the Bestiole is currently using.
     */
    Behaviour* currentBehaviour;

    /**
     * @brief Number of steps after which the behaviour switches.
     *
     * This static variable defines the number of steps before a new behaviour is randomly chosen.
     */
    static int switchInterval;

    /**
     * @brief Counter for tracking simulation steps.
     *
     * This counter increments at every step and is used to determine when to switch behaviors.
     */
    int stepCounter;

    /**
     * @brief Switches the current behavior to a randomly selected one.
     *
     * This method chooses a random behavior from the list of available behaviours
     * and updates the `currentBehaviour` pointer.
     */
    void switchToRandomBehaviour();

public:
    /**
     * @brief Constructor for the `MultipleBehaviour` class.
     *
     * This constructor initializes the `MultipleBehaviour` object with a list of behavior names
     * and the associated Bestiole. It uses the behaviours names to assign them internally.
     *
     * @param bestiole Pointer to the Bestiole using this behaviour.
     * @param behaviourNames A vector containing the names of the behaviours to include.
     */
    MultipleBehaviour(Bestiole* bestiole, const std::vector<std::string>& behaviourNames);

    /**
     * @brief Constructor for the `MultipleBehaviour` class.
     *
     * This constructor initializes the `MultipleBehaviour` object with the associated Bestiole
     * and all behaviours.
     *
     * @param bestiole Pointer to the Bestiole using this behavior.
     */
    MultipleBehaviour(Bestiole* bestiole);

    /**
     * @brief Executes the active behavior of the Bestiole.
     *
     * This method allows the Bestiole to interact with its neighbors based on the currently active
     * behavior. If the step counter reaches the switch interval, the behavior is switched randomly.
     *
     * @param neighbors A set of pointers to neighboring Bestioles.
     */
    void doBehaviour(std::set<Bestiole*>& neighbors) override;

    /**
     * @brief Gets the currently active behavior.
     *
     * @return A pointer to the currently active `Behaviour` object.
     */
    Behaviour* getBehaviour() const;
};

#endif // MULTIPLEBEHAVIOUR_H
