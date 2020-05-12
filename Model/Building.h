#ifndef BUILDING_H
#define BUILDING_H
#include "Card.h"

class Building: virtual public Card{
private:
    unsigned int buildHealth;
    unsigned int lifeTime;
public:
    Building();
    Building(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, unsigned int bHealth, unsigned int lTime);
    Building(const Building& b);
    unsigned int getBuildHealth() const;
    void setBuildHealth(unsigned int bHealth);
    unsigned int getLifeTime() const;
    void setLifeTime(unsigned int lTime);
};
#endif // BUILDING_H
