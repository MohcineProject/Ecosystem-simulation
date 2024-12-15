#include "Aquarium.h"

#include <array>

#include "CImg.h"
#include "Milieu.h"
#include <iostream>

#include "Carapace.h"
#include "Fins.h"

// Constructor for the Aquarium class
Aquarium::Aquarium(const int width, const int height, const int _delay) :
 delay(_delay), stepsBeforeStats(1000), stepCount(0)
{
   // Set screen width and height constants
   constexpr int screenWidth = 1280;
   constexpr int screenHeight = 1024;

   // Define a lambda function for validating parameter values within bounds
   const function<bool(float, float, float)> condition = [](const float value, const float a, const float b) {
       return (value <= a && value >= b);
   };

   // Query simulation parameters from the user using the defined condition
   this->cap_detection_v_max = query_parameter("max vision capacity", &condition, 1, 0);
   this->cap_detection_v_min = query_parameter("min vision capacity", &condition, this->cap_detection_v_max, 0);
   this->angle_vision_max = query_parameter("max vision angle", &condition, 360, 0);
   this->angle_vision_min = query_parameter("min vision angle", &condition, this->angle_vision_max, 0);
   this->distance_vision_max = query_parameter("max vision distance", &condition, 200, 0);
   this->distance_vision_min = query_parameter("min vision distance", &condition, this->distance_vision_max, 0);
   this->distance_hearing_max = query_parameter("max hearing distance", &condition, 120, 0);
   this->distance_hearing_min = query_parameter("min hearing distance", &condition, this->distance_hearing_max, 0);
   this->cap_detection_h_max = query_parameter("max hearing capacity", &condition, 1, 0);
   this->cap_detection_h_min = query_parameter("min hearing capacity", &condition, this->cap_detection_h_max, 0);
   this->cap_camouflage_max = query_parameter("max camouflage capacity", &condition, 1, 0);
   this->cap_camouflage_min = query_parameter("min camouflage capacity", &condition, this->cap_camouflage_max, 0);
   this->multi_speed_max = query_parameter("max speed multiplier", &condition, 3, 1);
   this->red_speed_max = query_parameter("max speed reductor", &condition, 3, 1);
   this->resistance_max = query_parameter("max resistance", &condition, 3, 1);

   // Print initialization message
   cout << "Constructing the Aquarium" << endl;

   // Initialize the Milieu object with specified width and height
   flotte = new Milieu(width, height);

   // Assign the Milieu instance to the CImgDisplay interface
   assign(*flotte, "Simulation d'ecosysteme");

   // Center the aquarium display on the screen
   move(static_cast<int>((screenWidth - width) / 2), static_cast<int>((screenHeight - height) / 2));
}

// Method to query user for a parameter value and validate it
float Aquarium::query_parameter(const char user_query[], const function<bool(float, float, float)> *condition, const float a, const float b) {
   float value;
   while (true) {
      std::cout << "Enter a " << user_query << std::endl;
      cin >> value;
      // Ensure the value is within the valid range
      if (!(*condition)(value, a, b)) {
         std::cout << "Value out of bound, please enter a valid value" << std::endl;
      } else {
         break;
      }
   }
   return value;
}

// Destructor for the Aquarium class
Aquarium::~Aquarium()
{
   // Clean up memory allocated for the ecosystem
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



// Main loop to run the simulation
void Aquarium::run() {
   cout << "Running Aquarium" << endl;

   while (!is_closed()) {
      // Update the ecosystem and display it
      flotte->step();
      display(*flotte);
      wait(delay);
      stepCount++;

      // Periodically collect and print statistics
      if (stepCount >= stepsBeforeStats) {
         collectAndPrintStatistics();
         stepCount = 0;

         // Check for user key input and close the simulation when escape is pressed
         if (is_key()) {
            cout << "You pressed key " << static_cast<unsigned char>(key());
            cout << " (" << key() << ")" << endl;
            if (is_keyESC()) close();
         }

         flotte->step();
         display(*flotte);
         wait(delay);
      }
   }
}


// Method for creating the bestioles in the beginning of the simulation
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
   // Define a threshold for attaching captors and accessories randomly to bestioles
   float randomizer = 0.3;

   // Loop over all types of the bestioles
   for (int i = 0; i < 5; ++i) {
      // Loop over the number of bestioles of this type
      for (int j = 0; j < numBestioles[i]; ++j) {

         // Creating the bestiole object
         Bestiole b = Bestiole(5.0);
         b.setBehaviour(bestioleTypes[i]);

         // Specifying its detection capability
         float detectionCapabilityDraw = static_cast<float>(std::rand()) / RAND_MAX;
         float detectionCapability = cap_camouflage_min + detectionCapabilityDraw * (cap_camouflage_max - cap_camouflage_min);
         b.detectionCapability = detectionCapability;

         // Assigning accessories and captors randomly
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

         // Adding the created bestiole to the milieu
         this->flotte->addMember(b);
      }
   }
}


// A helper function to calculate statistics of the simulation
void Aquarium::collectAndPrintStatistics() const {
    const Milieu& milieu = getMilieu();
    const std::vector<Bestiole>& bestioles = milieu.getBestioles();

    // Containers to hold counts
    int totalSurvived = 0;
    int survivedFearful = 0;
    int survivedGregarious = 0;
    int survivedCautious = 0;
    int survivedKamikaze = 0;
    int survivedMultiple = 0;

    int finsCount = 0;
    int carapaceCount = 0;
    int camouflageCount = 0;
    int captorSCount = 0;
    int captorVCount = 0;

    for (const Bestiole& b : bestioles) {
        if (!b.deathflag) {
            totalSurvived++;
            // Count behaviors
            if (b.type == "Fearful") survivedFearful++;
            else if (b.type == "Gregarious") survivedGregarious++;
            else if (b.type == "Cautious") survivedCautious++;
            else if (b.type == "Kamikaze") survivedKamikaze++;
            else if (b.type == "Multiple") survivedMultiple++;

            // Count accessories
            for (const auto& acc : b.accessoires) {
                if (acc && acc->getType() == "Fins") finsCount++;
                else if (acc && acc->getType() == "Carapace") carapaceCount++;
                else if (acc && acc->getType() == "Camouflage") camouflageCount++;
            }

            // Count captors
            if (b.captor) captorSCount++;
            if (b.captorV) captorVCount++;
        }
    }

    // Calculate survival rates
    float totalBestioles = static_cast<float>(bestioles.size());
    float survivalRate = (totalSurvived / 100.0) * 100.0f;

    // Print statistics
    cout << "Statistics after " << stepsBeforeStats << " steps:" << endl;
    cout << "Total Bestioles: " << totalBestioles << endl;
    cout << "Total Survived: " << totalSurvived << " (" << survivalRate << "%)" << endl;
    cout << "Survived by Behavior:" << endl;
    cout << " - Fearful: " << survivedFearful << endl;
    cout << " - Gregarious: " << survivedGregarious << endl;
    cout << " - Cautious: " << survivedCautious << endl;
    cout << " - Kamikaze: " << survivedKamikaze << endl;
    cout << " - Multiple: " << survivedMultiple << endl;
    cout << "Accessories in Survivors:" << endl;
    cout << " - Fins: " << finsCount << endl;
    cout << " - Carapace: " << carapaceCount << endl;
    cout << " - Camouflage: " << camouflageCount << endl;
    cout << "Captors in Survivors:" << endl;
    cout << " - CaptorS: " << captorSCount << endl;
    cout << " - CaptorV: " << captorVCount << endl;
}