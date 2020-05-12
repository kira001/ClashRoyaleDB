#include "Building.h"

unsigned int Building::getBuildHealth() const
{
    return buildHealth;
}

void Building::setBuildHealth(unsigned int bHealth)
{
    buildHealth = bHealth;
}

unsigned int Building::getLifeTime() const
{
    return lifeTime;
}

void Building::setLifeTime(unsigned int lTime)
{
    lifeTime = lTime;
}

Building::Building(){}

Building::Building(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, unsigned int bHealth, unsigned int lTime):
    Card(n,mana,rar,cLevel,desc), buildHealth(bHealth), lifeTime(lTime){}

Building::Building(const Building &b): Card(b), buildHealth(b.getBuildHealth()), lifeTime(b.getLifeTime()){}
