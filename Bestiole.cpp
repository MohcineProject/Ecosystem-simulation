#include "Bestiole.h"

#include "Milieu.h"
#include "CapteurS.h"  // Include CapteurS definition
#include "CapteurV.h"  // Include CapteurV definition

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "Carapace.h"
#include "Accessoire.h"
#include "Behaviours/Fearful.h"
#include "Behaviours/Kamikaze.h"
#include "Behaviours/Cautious.h"
#include "Behaviours/Gregarious.h"
#include "Behaviours/MultipleBehaviour.h"

const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;
const int         Bestiole::AGE_LIMIT_MAX = 20000;
const int         Bestiole::AGE_LIMIT_MIN = 10000;

static T RED[3] = {255, 0, 0};
static T PURPLE[3] = {0, 255, 255};
static T BLUE[3] = {0, 0, 255};
static T GREEN[3] = {0, 255, 0};
static  T GRAY[3] = {128, 128, 128};    // RGB for Brown
static  T LIGHT_BLUE[3] = {180, 0, 255};

int               Bestiole::next = 0;

void debug_couleur(const char* context, T* ptr) {
    std::cout << context << ": couleur address = " << ptr << std::endl;
}

Bestiole::Bestiole(double baseSpeed)
:
  cumulX(0.0), cumulY(0.0),
  orientation(static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI), vitesse(static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE),
  baseSpeed(baseSpeed),
  accessoires(),
  detectionCapability(1.0),
  resistance(1.0),
  x(0),
  y(0), deathflag(false),
  deathProbability(static_cast<double>(rand()) / RAND_MAX),
  myAgeLimit(AGE_LIMIT_MIN + std::rand() % (AGE_LIMIT_MAX - AGE_LIMIT_MIN + 1)),
  myAge(0)
{


    identite = ++next;
    cout << "const Bestiole (" << identite << ") par defaut" << endl;
    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
    vitesse = static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI + 1;
    deathProbability = static_cast<double>(rand()) / RAND_MAX;

    couleur = std::make_unique<T[]>(3);
    couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
    couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

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
      resistance(b.resistance), type(b.type), deathflag(false), deathProbability(b.deathProbability),
      myAgeLimit(b.myAgeLimit), myAge(b.myAge)
{
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

    detectionCapability = b.detectionCapability;

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
    delete behaviour;

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

bool Bestiole::jeTeVois(const Bestiole& b) const {
   return false;
}

void Bestiole::action( Milieu & monMilieu )
{
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

    if (seeCaptorsBool) {
        seeCaptors(support);
    }
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
    double dist;
   x = newx;
}

void Bestiole::setCoordy(int newy)
{
   y = newy;
}



void Bestiole::addAccessory(shared_ptr<Accessoire> accessoire) {
   accessoires.push_back(accessoire);
   if (auto carapace = dynamic_pointer_cast<Carapace>(accessoire)) {
      detectionCapability *= carapace->getCapDetect();
      resistance *= carapace->getResistanceFactor();
   }
}

void Bestiole::updatematrix(std::vector<std::pair<double, double>> &coordmatrix, int i, std::vector<Bestiole> &listeBestioles) {
    this->detected.clear();
    this->coordvector = &coordmatrix;
    std::set<Bestiole*> sound;
    std::set<Bestiole*> vision;
    if (captor) {
        sound = this->captor->update(*this->coordvector, i, listeBestioles);  // Use pointer dereferencing
    }
    if (captorV) {
        vision = this->captorV->update(*this->coordvector, i, listeBestioles); // Use pointer dereferencing
    }

    std::set<Bestiole*> detectedptr = sound;
    detectedptr.insert(vision.begin(), vision.end());
    this->detected = detectedptr;
    /*
    for (Bestiole* it : detected) {
        std::cout << this->identite << " sees " << it->identite << std::endl;
    }
    */
    detectedptr.clear();
}
float Bestiole::getDetectionCapability() const {
        return detectionCapability;
}

float Bestiole::getResistance() const {
        return resistance;
}

ostream& operator<<(ostream& os, const Bestiole& b) {
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

double Bestiole::getMaxSpeed() const {
   return MAX_VITESSE;
}

void Bestiole::setVitesse(double newv) {
   vitesse = newv;
}

double Bestiole::getActualSpeed() const {
    double speedFactor = 1.0;
    for (const auto& acc : accessoires) {
        speedFactor = acc->getSpeedFactor();
    }
    return baseSpeed * speedFactor;
}

double Bestiole::getOrientation() const {
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


void Bestiole::setOrientation(double o) {

    orientation = o;
}

double Bestiole::getBaseSpeed() const {
    return this -> baseSpeed;
}

void Bestiole::setBehaviour(std::string s) {
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
    if (this->behaviour != nullptr) {
        /*
        for (Bestiole* it : detected) {
            std::cout <<this->type << " " << this->identite << " sees " << it->identite << std::endl;
        }
        */
        this->behaviour->doBehaviour(detected);
    }


}

void Bestiole::seeCaptors(UImg &support) {
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
        support.draw_circle(x, y, captor->getR(), couleur.get(), 0.2);  // Draw ears with partial opacity
    }
}

bool Bestiole::amIOld()const {
    if (myAge <myAgeLimit) {
        return false;
    }
    return true;
}

void Bestiole::grow() {
    if (myAge <myAgeLimit) {
        myAge++;
    }else {
        myAge = myAgeLimit;
    }
}



void Bestiole::attachCaptorS(float capSMax, float capSMin, float distMax, float distMin) {
    if (captor == nullptr) {
        this->captor = new CapteurS(capSMax, capSMin, distMax, distMin);
    }
}

void Bestiole::attachCaptorV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin) {
    if (captorV == nullptr) {
        this->captorV = new CapteurV(capVMax, capVMin, AngleMax, AngleMin, distMax, distMin);
    }
}

