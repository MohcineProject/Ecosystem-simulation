#include "Aquarium.h"

#include <array>

#include "Milieu.h"
#include <iostream>
#include "../Accessories/Carapace.h"
#include "../Accessories/Fins.h"
#include <fstream>
#include <map>
#include "../Bestioles/BestioleFactory.h"

// A helper function to parse data from a config file
map<std::string, std::string> readConfig(const std::string& filename) {
   // Define the map to hold the data
   std::map<std::string, std::string> config;
   // Define a file stream to get the data
   ifstream file(filename);
   // Define a string to store the lines of the file
   std::string line;

   // If the file is not open, print an error and exit the program
   if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << filename << std::endl;
      exit(1);
   }
   while (std::getline(file, line)) {
      // Ignore comments and empty lines
      if (line.empty() || line[0] == '#') continue;

      // Get the position of the seperator of data
      const size_t pos = line.find('=');
      // If the seperator was found assign the value to the key in the map
      if (pos != std::string::npos) {
         std::string key = line.substr(0, pos);
         // Remove spaces from the key
         key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
         std::string value = line.substr(pos + 1);
         // Remove spaces from the value
         value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
         config[key] = value;
      }
   }
   return config;
}

void Aquarium::validateAndAssign(const std::string& key, float value, float minValue, float maxValue)
{
   // Check if the value is within the acceptable range
   if (value < minValue || value > maxValue) {
      std::cerr << "Error: " << key << " value " << value << " out of range [" << minValue << ", " << maxValue << "]" << std::endl;
      exit(1);  // Exit the program if invalid value is not bounded
   }
}

// Constructor for the Aquarium class
Aquarium::Aquarium(const int width, const int height, const int _delay) :
 delay(_delay), stepsBeforeStats(1000), stepCount(0)
{
   // Set screen width and height constants
   constexpr int screenWidth = 1280;
   constexpr int screenHeight = 1024;


   // Read configuration file and retrieve the data
   const map<std::string, std::string> config = readConfig("config.txt");

   // Validate and assign the parameters based on the config file
   cap_detection_v_max = std::stof(config.at("max_vision_capacity"));
   validateAndAssign("max_vision_capacity", cap_detection_v_max, 0, 10);
   cout << "Max vision capacity: " << cap_detection_v_max << endl;

   cap_detection_v_min = std::stof(config.at("min_vision_capacity"));
   validateAndAssign("min_vision_capacity", cap_detection_v_min, 0, cap_detection_v_max);
   cout << "Min vision capacity: " << cap_detection_v_min << endl;

   angle_vision_max = std::stof(config.at("max_vision_angle"));
   validateAndAssign("max_vision_angle", angle_vision_max, 0, 360);
   cout << "Max vision angle: " << angle_vision_max << endl;

   angle_vision_min = std::stof(config.at("min_vision_angle"));
   validateAndAssign("min_vision_angle", angle_vision_min, 0, angle_vision_max);
   cout << "Min vision angle: " << angle_vision_min << endl;

   distance_vision_max = std::stof(config.at("max_vision_distance"));
   validateAndAssign("max_vision_distance", distance_vision_max, 0, 200);
   cout << "Max vision distance: " << distance_vision_max << endl;

   distance_vision_min = std::stof(config.at("min_vision_distance"));
   validateAndAssign("min_vision_distance", distance_vision_min, 0, distance_vision_max);
   cout << "Min vision distance: " << distance_vision_min << endl;

   distance_hearing_max = std::stof(config.at("max_hearing_distance"));
   validateAndAssign("max_hearing_distance", distance_hearing_max, 0, 120);
   cout << "Max hearing distance: " << distance_hearing_max << endl;

   distance_hearing_min = std::stof(config.at("min_hearing_distance"));
   validateAndAssign("min_hearing_distance", distance_hearing_min, 0, distance_hearing_max);
   cout << "Min hearing distance: " << distance_hearing_min << endl;

   cap_detection_h_max = std::stof(config.at("max_hearing_capacity"));
   validateAndAssign("max_hearing_capacity", cap_detection_h_max, 0, 1);
   cout << "Max hearing capacity: " << cap_detection_h_max << endl;

   cap_detection_h_min = std::stof(config.at("min_hearing_capacity"));
   validateAndAssign("min_hearing_capacity", cap_detection_h_min, 0, cap_detection_h_max);
   cout << "Min hearing capacity: " << cap_detection_h_min << endl;

   cap_camouflage_max = std::stof(config.at("max_camouflage_capacity"));
   validateAndAssign("max_camouflage_capacity", cap_camouflage_max, 0, 1);
   cout << "Max camouflage capacity: " << cap_camouflage_max << endl;

   cap_camouflage_min = std::stof(config.at("min_camouflage_capacity"));
   validateAndAssign("min_camouflage_capacity", cap_camouflage_min, 0, cap_camouflage_max);
   cout << "Min camouflage capacity: " << cap_camouflage_min << endl;

   multi_speed_max = std::stof(config.at("max_speed_multiplier"));
   validateAndAssign("max_speed_multiplier", multi_speed_max, 1, 3);
   cout << "Max speed multiplier: " << multi_speed_max << endl;

   red_speed_max = std::stof(config.at("max_speed_reductor"));
   validateAndAssign("max_speed_reductor", red_speed_max, 1, 3);
   cout << "Max speed reductor: " << red_speed_max << endl;

   resistance_max = std::stof(config.at("max_resistance"));
   validateAndAssign("max_resistance", resistance_max, 1, 3);
   cout << "Max resistance: " << resistance_max << endl;


   // Print initialization message
   cout << "Constructing the Aquarium" << endl;

   // Initialize the Milieu object with specified width and height
   flotte = new Milieu(width, height);

   // Assign the Milieu instance to the CImgDisplay interface
   assign(*flotte, "Ecosystem simulation");

   // Center the aquarium display on the screen
   move(static_cast<int>((screenWidth - width) / 2), static_cast<int>((screenHeight - height) / 2));
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
   return(cap_detection_v_max);
}
float Aquarium::get_detec_v_min() const {
   return(cap_detection_v_min);
}
float Aquarium::get_detec_h_max() const {
   return(cap_detection_h_max);
}
float Aquarium::get_detec_h_min() const {
   return(cap_detection_h_min);
}
float Aquarium::get_camouflage_max() const {
   return(cap_camouflage_max);
}
float Aquarium::get_camouflage_min() const {
   return(cap_camouflage_min);
}
float Aquarium::get_mult_speed_max() const {
   return(multi_speed_max);
}
float Aquarium::get_red_speed_max() const {
   return(red_speed_max);
}
float Aquarium::get_resistance_max() const {
   return(resistance_max);
}
float Aquarium::get_angle_vision_max() const {
   return(angle_vision_max);
}
float Aquarium::get_angle_vision_min() const {
   return(angle_vision_min);
}
float Aquarium::get_distance_hearing_max() const {
   return(distance_hearing_max);
}
float Aquarium::get_distance_hearing_min() const {
   return(distance_hearing_min);
}
float Aquarium::get_distance_vision_max() const {
   return(distance_vision_max);
}
float Aquarium::get_distance_vision_min() const {
   return(distance_vision_min);
}



// Main loop to run the simulation
void Aquarium::run() {
   cout << "Running Aquarium" << endl;
   display_menu();

   while (!is_closed()) {
      // Update the ecosystem and display it
      flotte->step();
      display(*flotte);
      wait(delay);
      stepCount++;

      // Check for user key input and close the simulation when escape is pressed
      if (is_key()) {
         unsigned int pressed_key = key();
         cout << "You pressed key " << static_cast<unsigned char>(pressed_key);
         cout << " (" << pressed_key << ")" << endl;
         if (pressed_key == cimg::keyESC) close();
      }

      // Periodically collect and print statistics
      if (stepCount >= stepsBeforeStats) {
         collectAndPrintStatistics();
         stepCount = 0;
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

   // Retrieve the bestiole_factory
   BestioleFactory* bestiole_factory = BestioleFactory::getBestioleFactory(this);

   // Loop over all types of the bestioles
   for (int i = 0; i < 5; ++i) {
      // Loop over the number of bestioles of this type
      for (int j = 0; j < numBestioles[i]; ++j) {
         // Creating the bestiole object and adding it to the flotte
         Bestiole* new_bestiole = bestiole_factory->createBestiole(bestioleTypes[i]);
         this->flotte->addMember((*new_bestiole));
      }
   }
}


// A helper function to calculate statistics of the simulation
void Aquarium::collectAndPrintStatistics() const {
    const Milieu& milieu = getMilieu();
    const std::vector<Bestiole>& bestioles = milieu.getBestioles();

    // Variables to hold counts
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
    float survivalRate = (totalSurvived / totalBestioles) * 100.0f;

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



void Aquarium::display_menu() {
    // Create the menu interface
    CImg<unsigned char> menu(1020, 640, 1, 3, 0);
    
    // Define colors 
    const unsigned char white[] = {255, 255, 255};  
    const unsigned char black[] = {0, 0, 0};        
    const unsigned char blue[] = {0, 100, 200};     
    
    // Fill the menu with white color
    menu.fill(white[0], white[1], white[2]);  
    
    // Draw the title of the simulation
    menu.draw_text(100, 100, "AQUARIUM SIMULATION", black, 0, 1, 32);
    
    // Draw an informative text
    menu.draw_text(100, 150, "Press any key to continue...", blue, 0, 1, 20);
    
    // Display the menu
    display(menu);
    
    // Keep the window open until the user presses a key
    while (!is_closed() && !is_key()) {
        wait(20);
    }
}