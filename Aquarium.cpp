#include "Aquarium.h"

#include <array>

#include "CImg.h"
#include "Milieu.h"
#include <iostream>
#include <numbers>

#include "Carapace.h"
#include "Fins.h"


Aquarium::Aquarium( const int width, const int height, const int _delay) : CImgDisplay(), delay( _delay )
{
   constexpr int screenWidth = 1280; //screen_width();
   constexpr int screenHeight = 1024; //screen_height();


   // Get parameters from user
   const function<bool(float , float , float )> condition = [](const float value , const float a , const float b) {return (value <=a && value >=b); }  ;
   
   this->cap_detection_v_max =  query_parameter("max vision capacity" , &condition , 1 , 0 ) ;
   this->cap_detection_v_min =  query_parameter("min vision capacity" , &condition , this->cap_detection_v_max , 0 ) ;
   this->angle_vision_max =  query_parameter("max vision angle" , &condition ,  360 , 0 ) ;
   this->angle_vision_min =  query_parameter("min vision angle" , &condition ,  this->angle_vision_max , 0 ) ;
   this->distance_vision_max =  query_parameter("max vision distance" , &condition ,  200 , 0 ) ;
   this->distance_vision_min =  query_parameter("min vision distance" , &condition ,  this->distance_vision_max , 0 ) ;
   this->distance_hearing_max =  query_parameter("max hearing distance" , &condition ,  120 , 0 ) ;
   this->distance_hearing_min =  query_parameter("min hearing distance" , &condition ,  this->distance_hearing_max , 0 ) ;
   this->cap_detection_h_max =  query_parameter("max hearing capacity" , &condition ,  1 , 0 ) ;
   this->cap_detection_h_min =  query_parameter("min hearing capacity" , &condition ,  this->cap_detection_h_max , 0 ) ;
   this->cap_camouflage_max =  query_parameter("max camouflage capacity" , &condition ,  1 , 0 ) ;
   this->cap_camouflage_min =  query_parameter("min camouflage capacity" , &condition ,  this->cap_camouflage_max, 0 ) ;
   this->multi_speed_max =  query_parameter("max speed multiplier" , &condition ,  3 , 1 ) ;
   this->red_speed_max = query_parameter("max speed reductor" , &condition , 3 , 1 ) ;
   this->resistance_max = query_parameter("max resistance" , &condition , 3 , 1 ) ;
   /*
   this->cap_detection_v_max =  0.8;
   this->cap_detection_v_min =  0.4 ;
   this->angle_vision_max =  180 ;
   this->angle_vision_min =  30 ;
   this->distance_vision_max =  150 ;
   this->distance_vision_min =  100;
   this->distance_hearing_max =  80 ;
   this->distance_hearing_min =  40 ;
   this->cap_detection_h_max =  1 ;
   this->cap_detection_h_min =  0.1 ;
   this->cap_camouflage_max =  1 ;
   this->cap_camouflage_min =  0.1 ;
   this->multi_speed_max =  1.5 ;
   this->red_speed_max = 2 ;
   this->resistance_max = 1.5 ;
*/

    cout << "Constructing the Aquarium" << endl;

    flotte = new Milieu( width, height );
    assign( *flotte, "Simulation d'ecosysteme" );
    move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}

float Aquarium::query_parameter(const char user_query[] , const function<bool(float , float , float )> *condition , const float a , const float b   ) {
   float value ;
   while ( true ) {
      std::cout<< "Enter a " <<  user_query <<std::endl;
      cin>>value;
      if (not (*condition)(value ,  a , b)) {
         std::cout<<"Value out of bound, please enter a valid value"<<std::endl;
      }
      else {
        break ;
      }
   }
   return value ;
}


Aquarium::~Aquarium()
{

    delete flotte;

    cout << "Aquarium Removed" << endl;

}
//implementing getters for each simulation parameter
float Aquarium::get_detec_v_max() const {
   return(this -> cap_detection_v_max);
}
float Aquarium::get_detec_v_min() const {
   return(this -> cap_detection_v_min);
}
float Aquarium::get_detec_h_max() const {
   return(this -> cap_detection_h_max);
}
float Aquarium::get_detec_h_min() const {
   return(this -> cap_detection_h_min);
}
float Aquarium::get_camouflage_max() const {
   return(this -> cap_camouflage_max);
}
float Aquarium::get_camouflage_min() const {
   return(this -> cap_camouflage_min);
}
float Aquarium::get_mult_speed_max() const {
   return(this -> multi_speed_max);
}
float Aquarium::get_red_speed_max() const {
   return(this -> red_speed_max);
}
float Aquarium::get_resistance_max() const {
   return(this -> resistance_max);
}
float Aquarium::get_angle_vision_max() const {
   return(this -> angle_vision_max);
}
float Aquarium::get_angle_vision_min() const {
   return(this -> angle_vision_min);
}
float Aquarium::get_distance_hearing_max() const {
   return(this -> distance_hearing_max);
}
float Aquarium::get_distance_hearing_min() const {
   return(this -> distance_hearing_min);
}
float Aquarium::get_distance_vision_max() const {
   return(this -> distance_vision_max);
}
float Aquarium::get_distance_vision_min() const {
   return(this -> distance_vision_min);
}



void Aquarium::run()
{

    cout << "running Aquarium" << endl;

    while ( ! is_closed() )
    {

        // cout << "iteration de la simulation" << endl;

        if ( is_key() ) {
            cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
            cout << " (" << key() << ")" << endl;
            if ( is_keyESC() ) close();
        }

        flotte->step();
        display( *flotte );

        wait( delay );

    } // while

}


//method for creating the bugs in the beginning of the simulation

void Aquarium::createBestioles(const float per_fear, const float per_greg, const float per_caut,
                               const float per_kami, const float per_mult, const int total) const {

   // Store percentages and bestiole types in arrays
   const std::array<float, 5> percentages = {per_fear, per_greg, per_caut, per_kami, per_mult};
   const std::array<std::string, 5> bestioleTypes = {"Fearful", "Gregaire", "Cautious", "Kamikaze", "Multiple"};

   // Convert total to float and compute the number of each bestiole type
   auto const float_total = static_cast<float>(total);
   std::array<int, 5> numBestioles = {0 , 0 , 0 , 0 , 0};

   for (int i = 0; i < 5; ++i) {
      numBestioles[i] = static_cast<int>(floor(float_total * percentages[i]));
   }

   // Loop over the bestiole types and add the members
   float randomizer = 0.3;
   for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < numBestioles[i]; ++j) {
         Bestiole b = Bestiole(5.0);
         b.setBehaviour(bestioleTypes[i]);
         float camouflageDraw = static_cast<float>(std::rand()) / RAND_MAX;
         float camouflage = cap_camouflage_min + camouflageDraw * (cap_camouflage_max - cap_camouflage_min);
         b.detectionCapability = camouflage;
         float captorSDraw = static_cast<float>(std::rand()) / RAND_MAX;
         if (captorSDraw <= randomizer) {
            b.attachCaptorS(this->cap_detection_h_max, this->cap_detection_h_min, this->distance_hearing_max, this->distance_hearing_min);
         }
         float captorVDraw = static_cast<float>(std::rand()) / RAND_MAX;
         if (captorVDraw <= randomizer) {
            b.attachCaptorV(this->cap_detection_v_max, this->cap_detection_v_min,this->angle_vision_max, this->angle_vision_min, this->distance_vision_max, this->distance_vision_min);
         }
         float finDraw = static_cast<float>(std::rand()) / RAND_MAX;
         if (finDraw <= randomizer) {
            float finMultDraw = static_cast<float>(std::rand()) / RAND_MAX;
            shared_ptr<Accessoire> f = make_shared<Fins>(1 + finMultDraw * (this->multi_speed_max - 1));
            b.addAccessory(f);
         }
         float shellDraw = static_cast<float>(std::rand()) / RAND_MAX;
         if (shellDraw <= randomizer) {
            float shellRedDraw = static_cast<float>(std::rand()) / RAND_MAX;
            float shellRed = 1 + shellRedDraw * (this->red_speed_max - 1);
            float shellResDraw = static_cast<float>(std::rand()) / RAND_MAX;
            float shellRes = 1 + shellResDraw * (this->resistance_max - 1);
            shared_ptr<Accessoire> s = make_shared<Carapace>(1, shellRes, shellRed);
            b.addAccessory(s);
            b.detectionCapability *= 0.5;
         }
         this->flotte->addMember(b);
      }
   }
}
