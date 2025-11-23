#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "Dependencies/UImg.h"
#include "Accessories/Accessoire.h"
#include <vector>
#include <set>
#include <memory>
#include "Captors/CapteurS.h"
#include "Captors/CapteurV.h"
#include "Behaviours/Behaviour.h"


using namespace std;

// Forward declarations
class Milieu;
class Behaviour;
class CapteurS;
class CapteurV;

/**
 * @class Bestiole
 * @brief Represents an individual creature in the simulation with various behaviors, accessories, and captors.
 */
class Bestiole
{
private:
    /**
     * @brief A constant that defines the size of a Bestiole in the simulation GUI.
     */
    static const double AFF_SIZE;

    /**
     * @brief The maximum possible speed for a Bestiole.
     */
    static const double MAX_VITESSE;

    /**
     * @brief The maximum vision distance for a Bestiole.
     */
    static const double LIMITE_VUE;

    /**
     * @brief The maximum age a Bestiole can reach.
     */
    static const int AGE_LIMIT_MAX;

    /**
     * @brief The minimum age a Bestiole can have
     */
    static const int AGE_LIMIT_MIN;

    /**
     * @brief Counter used to assign unique IDs to Bestioles.
     */
    static int next;

    /**
     * @brief Unique identifier for the Bestiole.
     */
    int identite;

    /**
     * @brief Cumulative x and y cooridnates used to ensure a smooth movement during the simulation
     */
    double cumulX, cumulY;

    /**
     * @brief Orientation angle of the Bestiole in radians.
     */
    float orientation;

    /**
     * @brief Speed of the Bestiole, a modified base speed due to presence of accessories and behaviors.
     */
    double vitesse;

    /**
     * @brief The base speed of the Bestiole,
     */
    double baseSpeed;

    /**
     * @brief Resistance of the Bestiole to collisions.
     */
    float resistance;

    /**
     * @brief The color of the bestiole (depends on its behaviour).
     */
    std::unique_ptr<T[]> couleur;

private:
    /**
     * @brief Updates the position of the Bestiole within the given simulation bounds.
     * @param xLim Maximum X boundary.
     * @param yLim Maximum Y boundary.
     */
    void move(int xLim, int yLim);

public:
    /**
     * @brief List of accessories attached to the Bestiole.
     */
    std::vector<std::shared_ptr<Accessoire>> accessoires;

    /**
     * @brief X and Y coordinates of the Bestiole.
     */
    int x, y;

    /**
     * @brief Pointer to the sound captor attached to the Bestiole.
     */
    CapteurS* captor = nullptr;

    /**
     * @brief Pointer to the vision captor attached to the Bestiole.
     */
    CapteurV* captorV = nullptr;

    /**
     * @brief Pointer to a vector containing the distances and angles between the bestiole and the rest
     * of bestioles in the simulation.
     */
    std::vector<std::pair<double, double>>* coordvector;

    /**
     * @brief A set of detected Bestioles within its range of detection.
     */
    std::set<Bestiole*> detected;

    /**
     * @brief Flag indicating whether the Bestiole is dead.
     */
    bool deathflag = false;

    /**
     * @brief Capability of the Bestiole to detect others.
     */
    float detectionCapability = 0;

    /**
     * @brief Boolean to display or remove captors visuals on the GUI.
     */
    bool seeCaptorsBool = false;

    /**
     * @brief Probability of the Bestiole dying.
     */
    float deathProbability;

    /**
     * @brief  The age limit specific to this Bestiole.
     */
    int myAgeLimit;

    /**
     * @brief Current age of the Bestiole.
     */
    int myAge;

    /**
     * @brief Pointer to the behavior of the Bestiole.
     */
    Behaviour* behaviour = nullptr;

    /**
     * @brief Type name of the Bestiole (used for identifying bestiole behavior).
     */
    std::string type = "";

public:
    /**
     * @brief Constructor to create a Bestiole with a specified base speed.
     * @param baseSpeed The base speed of the Bestiole.
     */
    explicit Bestiole(double baseSpeed);

    /**
     * @brief Copy constructor.
     * @param b The Bestiole to copy.
     */
    Bestiole(const Bestiole &b);

    /**
     * @brief Move constructor.
     * @param b The Bestiole to move.
     */
    Bestiole(Bestiole&& b) noexcept;

    /**
     * @brief Destructor for cleaning up resources.
     */
    ~Bestiole();

    /**
     * @brief Perform behavior of the Bestiole in the simulation.
     * @param monMilieu Reference to the simulation environment.
     */
    void action(const Milieu &monMilieu);

    /**
     * @brief Draw the Bestiole on the simulation canvas.
     * @param support The canvas on which to draw.
     */
    void draw(UImg &support);

    /**
     * @brief Set the color of the Bestiole based on its behavior.
     * @param behaviour Pointer to the behavior influencing the color.
     */
    void setColor(Behaviour *behaviour);


    /**
     * @brief Get the X coordinate of the Bestiole.
     * @return X coordinate.
     */
    int getCoordx() const;

    /**
     * @brief Get the Y coordinate of the Bestiole.
     * @return Y coordinate.
     */
    int getCoordy() const;

    /**
     * @brief Set the X coordinate of the Bestiole.
     * @param newx The new X coordinate.
     */
    void setCoordx(int newx);

    /**
     * @brief Set the Y coordinate of the Bestiole.
     * @param newy The new Y coordinate.
     */
    void setCoordy(int newy);

    /**
     * @brief Get the base speed of the Bestiole.
     * @return Base speed.
     */
    double getBaseSpeed() const;

    /**
     * @brief Get the maximum speed of the Bestiole.
     * @return Maximum speed.
     */
    static double getMaxSpeed() ;

    /**
     * @brief Set the speed of the Bestiole.
     * @param newv The new speed.
     */
    void setVitesse(double newv);

    /**
     * @brief Initialize the Bestiole's coordinates within simulation bounds.
     * @param xLim Maximum X boundary.
     * @param yLim Maximum Y boundary.
     */
    void initCoords(int xLim, int yLim);

    /**
     * @brief Set the behavior of the Bestiole based on a string identifier.
     * @param s The string identifier for the behavior.
     */
    void setBehaviour(const std::string &s);

    /**
     * @brief Perform the behavior-specific action.
     */
    void doBehaviour();

    /**
     * @brief Mark the Bestiole as dead.
     */
    void die() { this->deathflag = true; }

    /**
     * @brief Get the actual speed of the Bestiole considering accessories.
     * @return Actual speed.
     */
    double getActualSpeed() const;

    /**
     * @brief Add an accessory to the Bestiole.
     * @param accessoire The accessory to add.
     */
    void addAccessory(const shared_ptr<Accessoire>& accessoire);

    /**
     * @brief Get the detection capability of the Bestiole.
     * @return Detection capability.
     */
    float getDetectionCapability() const;

    /**
     * @brief Get the resistance of the Bestiole.
     * @return Resistance value.
     */
    float getResistance() const;

    /**
     * @brief Visualize the captors attached to the Bestiole.
     * @param support The canvas on which to draw the captors.
     */
    void seeCaptors(UImg &support) const;

    /**
     * @brief Attach a visual captor to the Bestiole.
     * @param capVMax Maximum visual captor capability.
     * @param capVMin Minimum visual captor capability.
     * @param AngleMax Maximum angle of detection.
     * @param AngleMin Minimum angle of detection.
     * @param distMax Maximum detection distance.
     * @param distMin Minimum detection distance.
     */
    void attachCaptorV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin);

    /**
     * @brief Attach a sound captor to the Bestiole.
     * @param capSMax Maximum sound captor capability.
     * @param capSMin Minimum sound captor capability.
     * @param distMax Maximum detection distance.
     * @param distMin Minimum detection distance.
     */
    void attachCaptorS(float capSMax, float capSMin, float distMax, float distMin);

    /**
     * @brief Update the coordinates vector with the new data.
     * @param coordvector A reference to the new coordinates vector.
     * @param i Position of the current bestiole in the bestioles list
     * @param bestioleList List of all Bestioles in the simulation.
     */
    void updatematrix(std::vector<std::pair<double, double>> &coordvector, int i, std::vector<Bestiole> &bestioleList);

    /**
     * @brief  Equality operator for the bestioles.
     * @param b1 First Bestiole.
     * @param b2 Second Bestiole.
     * @return True if the Bestioles are equal, false otherwise.
     */
    friend bool operator==(const Bestiole &b1, const Bestiole &b2) { return (b1.identite == b2.identite); }

    /**
     * @brief Output stream operator.
     * @param os Output stream.
     * @param b The Bestiole to output.
     * @return The updated output stream.
     */
    friend ostream &operator<<(ostream &os, const Bestiole &b);

    /**
     * @brief Get the unique identifier of the Bestiole.
     * @return Unique ID.
     */
    int getIdentite() const { return identite; }

    /**
     * @brief Set the orientation of the Bestiole.
     * @param orientation The new orientation angle.
     */
    void setOrientation(float orientation);

    /**
     * @brief Get the current orientation of the Bestiole.
     * @return Orientation angle.
     */
    float getOrientation() const;

    /**
     * @brief Less-than operator for sorting Bestioles.
     * @param other The Bestiole to compare against.
     * @return True if this Bestiole has a smaller ID, false otherwise.
     */
    bool operator<(const Bestiole &other) const { return identite < other.identite; }

    /**
     * @brief Assignment operator.
     * @param b The Bestiole to assign.
     * @return A reference to this Bestiole.
     */
    Bestiole &operator=(const Bestiole &b);

    /**
     * @brief Move assignment operator.
     * @param b The Bestiole to move.
     * @return A reference to this Bestiole.
     */
    Bestiole &operator=(Bestiole &&b) noexcept;

    /**
     * @brief Check if the Bestiole has reached its age limit.
     * @return True if the Bestiole is old, false otherwise.
     */
    bool amIOld() const;

    /**
     * @brief Increase the age of the Bestiole.
     */
    void grow();
};

#endif
