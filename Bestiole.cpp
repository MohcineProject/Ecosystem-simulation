#include "Bestiole.h"
#include "Milieu.h"
#include "CapteurS.h"  // Include CapteurS definition
#include "CapteurV.h"  // Include CapteurV definition

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "Carapace.h"
#include "Accessoire.h"


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole(double baseSpeed)
: identite(++next),
  x(0), y(0),
  cumulX(0.0), cumulY(0.0),
  orientation(static_cast<double>(rand()) / RAND_MAX * 2.0 * M_PI),
  vitesse(static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE),
  baseSpeed(baseSpeed),
  accessoires(),
  detectionCapability(1.0),
  resistance(1.0)
{

    couleur = new T[3];
    couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

    captor = new CapteurS();
    captorV = new CapteurV();
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
      resistance(b.resistance)
{
    captor = new CapteurS(*b.captor);captorV = new CapteurV(*b.captorV);
    couleur = new T[3];
    memcpy(couleur, b.couleur, 3 * sizeof(T));
    std::cout << "Copy Construct Bestiole (" << identite << ") from (" << b.identite << ")" << std::endl;
}

Bestiole::~Bestiole(void)
{
    delete[] couleur;  // Delete color array
    delete captor;     // Delete the dynamically allocated CapteurS object
    delete captorV;    // Delete the dynamically allocated CapteurV object
    std::cout << "dest Bestiole" << std::endl;
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

    if ((nx < 0) || (nx > xLim - 1))
    {
        orientation = M_PI - orientation;
        cumulX = 0.;
    }
    else
    {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

    if ((ny < 0) || (ny > yLim - 1))
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

void Bestiole::action(Milieu &monMilieu)
{
    bouge(monMilieu.getWidth(), monMilieu.getHeight());
}

void Bestiole::draw(UImg &support)
{
    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5., -orientation / M_PI * 180., couleur);
    support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

bool operator==(const Bestiole &b1, const Bestiole &b2)
{
    return (b1.identite == b2.identite);
}

bool Bestiole::jeTeVois(const Bestiole &b) const
{
    double dist;

    dist = std::sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    return (dist <= LIMITE_VUE);
}

void Bestiole::addAccessory(shared_ptr<Accessoire> accessoire) {
   accessoires.push_back(accessoire);
   if (auto carapace = dynamic_pointer_cast<Carapace>(accessoire)) {
      detectionCapability *= carapace->getCapDetect();
      resistance *= carapace->getResistanceFactor();
   }
}

void Bestiole::updatematrix(std::vector<std::pair<double, double>> &coordmatrix, int i, std::vector<Bestiole> &listeBestioles) {
    this->coordvector = &coordmatrix;
    std::set<Bestiole*> sound = this->captor->update(*this->coordvector, i, listeBestioles);  // Use pointer dereferencing
    std::set<Bestiole*> vision = this->captorV->update(*this->coordvector, i, listeBestioles); // Use pointer dereferencing
    std::set<Bestiole*> detected = sound;
    detected.insert(vision.begin(), vision.end());
    this->detected = detected;
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

double Bestiole::getActualSpeed() const {
    double speedFactor = 1.0;
    for (const auto& acc : accessoires) {
        speedFactor = acc->getSpeedFactor();
    }
    return baseSpeed * speedFactor;
}