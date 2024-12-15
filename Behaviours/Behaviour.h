//
// Created by mouha1505 on 28/11/24.
//

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <cmath>
#include <set>
#include <string>


class Bestiole;

class Behaviour
{
protected:
    std::string type;
    public:
        Bestiole *bestiole = nullptr ;  ///> a pointer to the bestiole we want to apply the behaviour

    /**
     * @brief The default destructor of the behaviour
     */
        virtual ~Behaviour() = default;

    /**
     * The method to be implemented by child behaviours to apply their specifc actions
     * @param neighbors A set containing pointers to the neighbors detected by the bestiole
     */
    virtual void doBehaviour(std::set<Bestiole*>& neighbors) = 0;

    /**
 * @brief Finds the closest "Bestiole" (neighbor) to the current "Bestiole".
 *
 * @param neighbors A set of pointers to neighboring "Bestiole" objects.
 * @return A pointer to the closest "Bestiole", or nullptr if no neighbors are found.
 */
        Bestiole* closestBestiole(const std::set<Bestiole*>& neighbors);

    /**
     * @brief A helper function to get the type of behaviour
     * @return The type of the behaviour
     */
    std::string getType(){return type ;}
};

#endif //BEHAVIOUR_H
