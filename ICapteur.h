#ifndef ICAPTEUR_H
#define ICAPTEUR_H

#include <vector>

class Bestiole;

class ICapteur {
private:
    std::vector<Bestiole*> nearbyObjects;
public:
    ICapteur() = default;
    virtual ~ICapteur() = default;
    virtual void update(std::vector<std::pair<double, double>>& coordvector) = 0;
};

#endif // ICAPTEUR_H
