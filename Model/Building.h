#ifndef BUILDING_H
#define BUILDING_H
#include "Card.h"

class Building: virtual public Card{
private:
    double buildHealth;
    double lifeTime;
protected:
    void upgradeStats();
    void downgradeStats();

public:

    Building()=default;
    Building(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, double bHealth, double lTime);
    Building(const Building& b);

    double getBuildHealth() const;
    void setBuildHealth(double bHealth);
    double getLifeTime() const;
    void setLifeTime(double lTime);

    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual Building* clone() const;


};
#endif // BUILDING_H
