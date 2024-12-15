#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include "CImg.h"
#include <functional>

using namespace std;
using namespace cimg_library;


class Milieu;

/**
 * @class Aquarium
 * @brief Represents an Aquarium environment where bestioles interact and simulate behaviours.
 *
 * This class extends `CImgDisplay` and provides functionalities to manage the aquarium, such as
 * simulating interactions, collect statistics, killing bestioles and more.
 */
class Aquarium : public CImgDisplay
{

    private :
       Milieu       * flotte; ///< Pointer to the Milieu managing bestioles in the aquarium.

    float distance_vision_max; ///< Maximum vision distance of bestioles.
    float distance_vision_min; ///< Minimum vision distance of bestioles.
    float distance_hearing_max; ///< Maximum hearing distance of bestioles.
    float distance_hearing_min; ///< Minimum hearing distance of bestioles.
    float angle_vision_min; ///< Minimum angle of vision for bestioles.
    float angle_vision_max; ///< Maximum angle of vision for bestioles.
    float cap_detection_h_max; ///< Maximum hearing detection capability.
    float cap_detection_h_min; ///< Minimum hearing detection capability.
    float cap_camouflage_min; ///< Minimum camouflage capability.
    float cap_camouflage_max; ///< Maximum camouflage capability.
    float multi_speed_max; ///< Maximum multiplier for speed.
    float red_speed_max; ///< Maximum reduction in speed.
    float resistance_max; ///< Maximum resistance capability of bestioles.
    int delay; ///< Delay between simulation steps.
    float cap_detection_v_max; ///< Maximum vision detection capability.
    float cap_detection_v_min; ///< Minimum vision detection capability.

    /**
 * @brief Query a parameter based on user input and a condition.
 * @param user_query A description of the parameter being queried.
 * @param condition A pointer to a function that validates the query condition.
 * @param a Lower bound for the parameter.
 * @param b Upper bound for the parameter.
 * @return The queried parameter value.
 */
    static float query_parameter(const char user_query[] , const function<bool(float , float , float )> *condition , float a , float b  ) ;


   int stepsBeforeStats; ///< Number of steps before collecting statistics.
    int stepCount; ///< Current step count in the simulation.


    public :

   /**
  * @brief Constructs an Aquarium object.
  * @param width The width of the aquarium.
  * @param height The height of the aquarium.
  * @param _delay The delay between simulation steps.
  */
    Aquarium(int width, int height, int _delay);


    /**
     * @brief Destructor for the Aquarium class.
     */
    ~Aquarium();

   /**
 * @brief Gets a reference to the Milieu object managing the bestioles.
 * @return Reference to the Milieu object.
 */
    Milieu & getMilieu() const { return *flotte; }

    float get_detec_v_max() const; ///< Gets the maximum vision detection capability.
    float get_detec_v_min() const; ///< Gets the minimum vision detection capability.
    float get_detec_h_max() const; ///< Gets the maximum horizontal detection capability.
    float get_detec_h_min() const; ///< Gets the minimum horizontal detection capability.
    float get_camouflage_min() const; ///< Gets the minimum camouflage capability.
    float get_camouflage_max() const; ///< Gets the maximum camouflage capability.
    float get_resistance_max() const; ///< Gets the maximum resistance capability.
    float get_mult_speed_max() const; ///< Gets the maximum speed multiplier.
    float get_red_speed_max() const; ///< Gets the maximum speed reduction.
    float get_distance_vision_max() const; ///< Gets the maximum vision distance.
    float get_distance_vision_min() const; ///< Gets the minimum vision distance.
    float get_distance_hearing_max() const; ///< Gets the maximum hearing distance.
    float get_distance_hearing_min() const; ///< Gets the minimum hearing distance.
    float get_angle_vision_min() const; ///< Gets the minimum angle of vision.
    float get_angle_vision_max() const; ///< Gets the maximum angle of vision.


    /**
     * @brief Runs the simulation for the aquarium.
     */
    void run();

    /**
 * @brief Creates bestioles with specified behaviours.
 * @param per_fear Percentage of bestioles with fear behaviour.
 * @param per_greg Percentage of bestioles with gregarious behaviour.
 * @param per_caut Percentage of bestioles with cautious behaviour.
 * @param per_kami Percentage of bestioles with kamikaze behaviour.
 * @param per_mult Percentage of bestioles with multi-personality.
 * @param total Total number of bestioles to create.
 */
    void createBestioles(float per_fear, float per_greg, float per_caut, float per_kami, float per_mult, int total) const;

    /**
 * @brief Collects and prints statistics about the aquarium and its bestioles.
 */
    void collectAndPrintStatistics() const;

};


#endif