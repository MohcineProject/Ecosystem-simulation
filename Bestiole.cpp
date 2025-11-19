#include "Bestiole.h"

#include "Milieu.h"
#include "CapteurS.h"
#include "CapteurV.h"

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "Behaviours/Cautious.h"
#include "Behaviours/Fearful.h"
#include "Behaviours/Gregarious.h"
#include "Behaviours/Kamikaze.h"
#include "Behaviours/MultipleBehaviour.h"
#include "Carapace.h"
#include "Accessoire.h"


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;
const int         Bestiole::AGE_LIMIT_MAX = 20000;
const int         Bestiole::AGE_LIMIT_MIN = 10000;

static T RED[3] = {255, 0, 0};
static T PURPLE[3] = {0, 255, 255};
static T BLUE[3] = {0, 0, 255};
static T GREEN[3] = {0, 255, 0};
static  T GRAY[3] = {128, 128, 128};  
static  T LIGHT_BLUE[3] = {180, 0, 255};

int               Bestiole::next = 0;


// A helper function to debug bestioles colors
void debug_couleur(const char* context, const T* ptr) {
    std::cout << context << ": couleur address = " << ptr << std::endl;
}

Bestiole::Bestiole(const double baseSpeed)
    : cumulX(0.0), cumulY(0.0),
      orientation(static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI),
      vitesse(static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE),
      baseSpeed(baseSpeed),
      resistance(1.0),
      x(0),
      y(0),
      coordvector(nullptr), detectionCapability(1.0),
      deathProbability(static_cast<double>(rand()) / RAND_MAX),
      myAgeLimit(AGE_LIMIT_MIN + std::rand() % (AGE_LIMIT_MAX - AGE_LIMIT_MIN + 1)),
      myAge(0) {
    identite = ++next;
    cout << "const Bestiole (" << identite << ") par defaut" << endl;

    couleur = std::make_unique<T[]>(3);
    couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
}

Bestiole::Bestiole(const Bestiole& b)
    : identite(++next),
      x(b.x), y(b.y),
      cumulX(b.cumulX), cumulY(b.cumulY),
      orientation(b.orientation),
      vitesse(b.vitesse),
      baseSpeed(b.baseSpeed),
      accessoires(b.accessoires),
      detectionCapability(b.detectionCapability),
      resistance(b.resistance), type(b.type), deathProbability(b.deathProbability),
      myAgeLimit(b.myAgeLimit), myAge(b.myAge)
{
    // Use a deep copy to assign the behaviour attribute
    if (b.behaviour != nullptr) {
        if (type == "Fearful") {
            behaviour = new Fearful(this);
        } else if (type == "Kamikaze") {
            behaviour = new Kamikaze(this);
        } else if (type == "Gregarious") {
            behaviour = new Gregarious(this);
        } else if (type == "Cautious") {
            behaviour = new Cautious(this);
        } else if (type == "Multiple") {
            behaviour = new MultipleBehaviour(this);
        }
    }

    // Allocate captor and captorV using new
    if (b.captor) {
        captor = new CapteurS(*b.captor);
    } else {
        captor = nullptr;
    }

    if (b.captorV) {
        captorV = new CapteurV(*b.captorV);
    } else {
        captorV = nullptr;
    }

    // Allocate and copy couleur
    couleur = std::make_unique<T[]>(3);
    std::copy(b.couleur.get(), b.couleur.get() + 3, couleur.get());

    std::cout << "Copy Construct Bestiole (" << identite << ") from (" << b.identite << ")" << std::endl;
}

Bestiole::Bestiole(Bestiole&& b) noexcept
    : identite(b.identite), x(b.x), y(b.y),
      cumulX(b.cumulX), cumulY(b.cumulY),
      orientation(b.orientation), vitesse(b.vitesse),
      baseSpeed(b.baseSpeed), accessoires(std::move(b.accessoires)),
      detectionCapability(b.detectionCapability),
      resistance(b.resistance), deathflag(b.deathflag), deathProbability(b.deathProbability),
      myAgeLimit(b.myAgeLimit), myAge(b.myAge){
    type = b.type;
    couleur = std::move(b.couleur);
    detectionCapability = b.detectionCapability;
    captor = b.captor;
    captorV = b.captorV;

    // Use a deep copy to assign the behaviour attribute
    if (b.behaviour != nullptr) {
        if (type == "Fearful") {
            behaviour = new Fearful(this);
        } else if (type == "Kamikaze") {
            behaviour = new Kamikaze(this);
        } else if (type == "Gregarious") {
            behaviour = new Gregarious(this);
        } else if (type == "Cautious") {
            behaviour = new Cautious(this);
        } else if (type == "Multiple") {
            behaviour = new MultipleBehaviour(this);
        }
    }

}

Bestiole::~Bestiole() {
    // Delete all captors and accessories associated with the bestiole
    if (behaviour) {
        delete behaviour;
    }
    if (captor) {
        delete captor;
    }
    if (captorV) {
        delete captorV;
    }


    std::cout << "dest Bestiole (" << identite << ")" << std::endl;
}

void Bestiole::initCoords(int xLim, int yLim)
{
    // Use rand to randomly initialize the cooridnates x and y
    x = rand() % xLim;
    y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim)
{
    double nx, ny;
    double dx = cos(orientation) * vitesse;
    double dy = -sin(orientation) * vitesse;
    int cx, cy;

    cx = static_cast<int>(cumulX);
    cumulX -= cx;
    cy = static_cast<int>(cumulY);
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 1) || (nx > xLim - 1))
    {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else
    {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 1) || (ny > yLim - 1))
    {
        orientation = -orientation;
        cumulY = 0.;
    }
    else
    {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}



void Bestiole::action(const Milieu & monMilieu )
{
    // Move the bestiole and execute its behaviour
    bouge(monMilieu.getWidth(), monMilieu.getHeight());
    this->doBehaviour();
}

void Bestiole::draw(UImg &support) {
    // Assign color based on the behavior type
    if (behaviour) {
        if (auto *multiBehaviour = dynamic_cast<MultipleBehaviour *>(behaviour)) {
            setColor(multiBehaviour->getBehaviour());
        }else {
            setColor(this-> behaviour);
        }
    }

    // Calculate head position
    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    // Draw body and head
    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.0, -orientation / M_PI * 180.0, couleur.get());
    support.draw_circle(xt, yt, AFF_SIZE / 2.0, couleur.get());

    // If seeCaptors is true, draw the captors visuals as well
    if (seeCaptorsBool) {
        seeCaptors(support);
    }

    // Loop trough available accessories and draw them
    for (const auto &accessoire : accessoires) {
        if (!accessoire) continue; // Skip null pointers

        if (accessoire->getType() == "Carapace") {
            // Draw a circle
            support.draw_circle(x, y, AFF_SIZE * 2 , GRAY,0.4);
        } else if (accessoire->getType() == "Fins") {
            // Draw two lines representing fins
            int angle = 10;
            int r = 10;
            support.draw_line(x, y, x + cos(orientation + angle) * r, y - sin(orientation + angle) * r, LIGHT_BLUE);
            support.draw_line(x, y, x + cos(orientation - angle) * r, y - sin(orientation - angle) * r, LIGHT_BLUE);
        }
    }


}

void Bestiole::setColor(Behaviour *behaviour) {
    // Set the color attribute of the bestiole based its behaviour
    if (dynamic_cast<Kamikaze *>(behaviour)) {
        couleur = std::make_unique<T[]>(3);
        std::copy(std::begin(RED), std::end(RED), couleur.get());
    } else if (dynamic_cast<Cautious *>(behaviour)) {
        couleur = std::make_unique<T[]>(3);
        std::copy(std::begin(PURPLE), std::end(PURPLE), couleur.get());
    } else if (dynamic_cast<Fearful *>(behaviour)) {
        couleur = std::make_unique<T[]>(3);
        std::copy(std::begin(BLUE), std::end(BLUE), couleur.get());
    } else if (dynamic_cast<Gregarious *>(behaviour)) {
        couleur = std::make_unique<T[]>(3);
        std::copy(std::begin(GREEN), std::end(GREEN), couleur.get());
    }
}

int Bestiole::getCoordx() const
{
   return x;
}

int Bestiole::getCoordy() const
{
   return y;
}

void Bestiole::setCoordx(int newx)
{
   x = newx;
}

void Bestiole::setCoordy(int newy)
{
   y = newy;
}



void Bestiole::addAccessory(const shared_ptr<Accessoire>& accessoire) {
    // Adds an accessory to the bestiole and modify its attributes accordingly
   accessoires.push_back(accessoire);
   if (const auto carapace = dynamic_pointer_cast<Carapace>(accessoire)) {
      detectionCapability *= carapace->getCapDetect();
      resistance *= carapace->getResistanceFactor();
   }
}

void Bestiole::updatematrix(std::vector<std::pair<double, double>> &coordvector, int i, std::vector<Bestiole> &listeBestioles) {
    // Clear the detected attribute from previous detected bestioles
    this->detected.clear();

    // Update the coordinates vector of the bestiole that holds distances and angles between it and all other bestioles
    this->coordvector = &coordvector;

    // Capture all detected bestioles from the attached captors
    std::set<Bestiole*> sound;
    std::set<Bestiole*> vision;
    if (captor) {
        sound = this->captor->update(*this->coordvector, i, listeBestioles);  // Use pointer dereferencing
    }
    if (captorV) {
        vision = this->captorV->update(*this->coordvector, i, listeBestioles); // Use pointer dereferencing
    }

    // Update the detected attribute on the bestiole
    std::set<Bestiole*> detectedptr = sound;
    detectedptr.insert(vision.begin(), vision.end());
    this->detected = detectedptr;
    detectedptr.clear();
}
float Bestiole::getDetectionCapability() const {
        return detectionCapability;
}

float Bestiole::getResistance() const {
        return resistance;
}

ostream& operator<<(ostream& os, const Bestiole& b) {
    // Defining the stream operator to print the bestiole to the console
    os << "Bestiole ID: " << b.identite
       << ", Base Speed: " << b.baseSpeed
       << ", Actual Speed: " << b.getActualSpeed()
       << ", Detection Capability: " << b.getDetectionCapability()
       << ", Resistance: " << b.getResistance() << " (";
    for (const auto& acc : b.accessoires) {
        os << acc->getType() << " ";
    }
    os << ")";
    return os;
}

double Bestiole::getMaxSpeed()  {
   return MAX_VITESSE;
}

void Bestiole::setVitesse(const double newv) {
   vitesse = newv;
}

double Bestiole::getActualSpeed() const {
    // Return the modified speed depending on the existence of the fins
    double speedFactor = 1.0;
    for (const auto& acc : accessoires) {
        speedFactor = acc->getSpeedFactor();
    }
    return baseSpeed * speedFactor;
}

float Bestiole::getOrientation() const {
    return orientation;
}

Bestiole & Bestiole::operator=(const Bestiole &b) {
    if (this != &b) {
        // Delete old behaviour if it exists
        delete this -> behaviour;

        this -> myAgeLimit = b.myAgeLimit;
        this -> myAge = b.myAge;

        this->x = b.x;
        this->y = b.y;
        this->identite = b.identite;
        this->orientation = b.orientation;
        this->cumulX = b.cumulX;
        this->cumulY = b.cumulY;
        this->vitesse = b.vitesse;
        this->detectionCapability = b.detectionCapability;

        // Deep copy behaviour
        if (b.behaviour != nullptr) {
            if (b.type == "Fearful") {
                this -> behaviour = new Fearful(this);
            } else if (b.type == "Kamikaze") {
                this -> behaviour = new Kamikaze(this);
            } else if (b.type == "Gregarious") {
                this -> behaviour = new Gregarious(this);
            } else if (b.type == "Cautious") {
                this -> behaviour = new Cautious(this);
            } else if (b.type == "Multiple") {
                this -> behaviour = new MultipleBehaviour(this);
            }
        }

        this->accessoires = b.accessoires;
        this->detectionCapability = b.detectionCapability;
        this->resistance = b.resistance;

        // Allocate captor and captorV using new
        if (b.captor) {
            this -> captor = new CapteurS(*b.captor);
        } else {
            this -> captor = nullptr;
        }

        if (b.captorV) {
            this -> captorV = new CapteurV(*b.captorV);
        } else {
            this -> captorV = nullptr;
        }
        couleur = std::make_unique<T[]>(3);
        memcpy(couleur.get(), b.couleur.get(), 3 * sizeof(T));
    }
    return *this;
}

Bestiole & Bestiole::operator=(Bestiole &&b) noexcept {
    if (this != &b) {
        // Transfer ownership from source
        this -> myAgeLimit = b.myAgeLimit;
        this -> myAge = b.myAge;
        identite = b.identite;
        x = b.x;
        y = b.y;
        cumulX = b.cumulX;
        cumulY = b.cumulY;
        orientation = b.orientation;
        vitesse = b.vitesse;
        baseSpeed = b.baseSpeed;
        accessoires = std::move(b.accessoires);
        detectionCapability = b.detectionCapability;
        resistance = b.resistance;
        deathflag = b.deathflag;
        detectionCapability = b.detectionCapability;
        type = std::move(b.type);

        // Allocate and copy couleur
        couleur = std::make_unique<T[]>(3);
        std::copy(b.couleur.get(), b.couleur.get() + 3, couleur.get());

        // Allocate captor and captorV using new
        if (b.captor) {
            captor = new CapteurS(*b.captor);
        } else {
            captor = nullptr;
        }

        if (b.captorV) {
            captorV = new CapteurV(*b.captorV);
        } else {
            captorV = nullptr;
        }
        // Deep copy behaviour
        if (b.behaviour != nullptr) {
            if (type == "Fearful") {
                behaviour = new Fearful(this);
            } else if (type == "Kamikaze") {
                behaviour = new Kamikaze(this);
            } else if (type == "Gregarious") {
                behaviour = new Gregarious(this);
            } else if (type == "Cautious") {
                behaviour = new Cautious(this);
            } else if (type == "Multiple") {
                behaviour = new MultipleBehaviour(this);
            }
        }

        // Nullify the source object
        b.couleur = nullptr;
        b.captor = nullptr;
        b.captorV = nullptr;
        b.behaviour = nullptr;

    }
    return *this;
}


void Bestiole::setOrientation(float o) {

    orientation = o;
}

double Bestiole::getBaseSpeed() const {
    return this -> baseSpeed;
}

void Bestiole::setBehaviour(const std::string &s) {
    // Set behaviour according to the passed string
    if (s == "Fearful") {
        this->behaviour = new Fearful(this);
        this->type = "Fearful";
    }
    else if (s == "Kamikaze") {
        behaviour = new Kamikaze(this);
        this->type = "Kamikaze";
    }
    else if (s == "Gregarious") {
        behaviour = new Gregarious(this);
        this->type = "Gregarious";
    }
    else if (s == "Cautious") {
        behaviour = new Cautious(this);
        this->type = "Cautious";
    }
    else if (s == "Multiple"){
        behaviour = new MultipleBehaviour(this);
        this->type = "Multiple";
    }
}

void Bestiole::doBehaviour() {
    // Check if behaviour is attached to the bestiole and executes it
    if (this->behaviour != nullptr) {
        this->behaviour->doBehaviour(detected);
    }


}

void Bestiole::seeCaptors(UImg &support) const {
    if (captorV) {
        double angle = captorV->getTheta() * M_PI / 180; // Convert degrees to radians
        int radius = captorV->getR();
        int num_segments = 100; // Number of segments to approximate the arc

        std::vector<int> coords = {x, y};

        for (int i = 0; i <= num_segments; ++i) {
            double current_angle = orientation + angle * i / num_segments - angle / 2;
            int px = x + static_cast<int>(radius * cos(current_angle));
            int py = y - static_cast<int>(radius * sin(current_angle));
            coords.push_back(px);
            coords.push_back(py);
        }

        // Convert the vector to a CImg object
        CImg<int> points(coords.size() / 2, 2); // 2 columns (x, y) and as many rows as needed

        for (size_t i = 0; i < coords.size(); i += 2) {
            points(i / 2, 0) = coords[i];     // x coordinate
            points(i / 2, 1) = coords[i + 1]; // y coordinate
        }

        // Draw the sector (filled area)
        support.draw_polygon(points, couleur.get(), 0.2);
    }

    if (captor) {
        // Draw a circle around the bestiole to visualize the sound captor
        support.draw_circle(x, y, captor->getR(), couleur.get(), 0.2);  // Draw ears with partial opacity
    }
}

bool Bestiole::amIOld()const {
    // Check if the bestiole has reached its age limit
    if (myAge <myAgeLimit) {
        return false;
    }
    return true;
}

void Bestiole::grow() {
    // Increment the age of the bestiole by 1
    if (myAge <myAgeLimit) {
        myAge++;
    }else {
        myAge = myAgeLimit;
    }
}



void Bestiole::attachCaptorS(const float capSMax, const float capSMin, const float distMax, const float distMin) {
    // Attach a sound captor to the bestiole if the bestiole doesn't already have one
    if (captor == nullptr) {
        this->captor = new CapteurS(capSMax, capSMin, distMax, distMin);
    }
}

void Bestiole::attachCaptorV(const float capVMax, const float capVMin, const float AngleMax, const float AngleMin, const float distMax, const float distMin) {
    // Attach a vision captor to the bestiole if the bestiole doesn't already have one
    if (captorV == nullptr) {
        this->captorV = new CapteurV(capVMax, capVMin, AngleMax, AngleMin, distMax, distMin);
    }
}

