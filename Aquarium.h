#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include "CImg.h"
#include <functional>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{

    private :
       Milieu       * flotte;
    float         distance_vision_max;
    float         distance_vision_min;
    float         distance_hearing_max;
    float         distance_hearing_min;
    float         angle_vision_min;
    float         angle_vision_max;
    float         cap_detection_h_max;
    float         cap_detection_h_min;
    float         cap_camouflage_min;
    float         cap_camouflage_max;
    float         multi_speed_max;
    float         red_speed_max;
    float         resistance_max;
    int            delay;
    float         cap_detection_v_max;
    float         cap_detection_v_min;
    static float query_parameter(const char user_query[] , const function<bool(float , float , float )> *condition , float a , float b  ) ;

    public :


       Aquarium(int width, int height, int _delay);

    ~Aquarium();
    Milieu & getMilieu() const { return *flotte; }
    float get_detec_v_max() const;
    float get_detec_v_min() const;
    float get_detec_h_max() const;
    float get_detec_h_min() const;
    float get_camouflage_min() const;
    float get_camouflage_max() const;
    float get_resistance_max() const;
    float get_mult_speed_max() const;
    float get_red_speed_max() const;
    float get_distance_vision_max() const;
    float get_distance_vision_min() const;
    float get_distance_hearing_max() const;
    float get_distance_hearing_min() const;
    float get_angle_vision_min() const;
    float get_angle_vision_max() const;
    void run();
    void createBestioles(float per_fear, float per_greg, float per_caut, float per_kami, float per_mult, int total) const;
};


#endif