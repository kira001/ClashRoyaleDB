#include "Building.h"

unsigned int Building::getBuildHealth() const{
    return buildHealth;
}

void Building::setBuildHealth(unsigned int bHealth){
    buildHealth = bHealth;
}

unsigned int Building::getLifeTime() const{
    return lifeTime;
}

void Building::setLifeTime(unsigned int lTime){
    lifeTime = lTime;
}

void Building::lvlUpgrade(){
    Card::lvlUpgrade();
    buildHealth*= 107/100;
    lifeTime*= 105/100;
}

void Building::lvlDowngrade(){
    Card::lvlDowngrade();
    buildHealth*= 100/107;
    lifeTime*= 100/105;
}

Building *Building::clone() const{
    return new Building(*this);
}

Building::Building(){}

Building::Building(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, unsigned int bHealth, unsigned int lTime):
    Card(n,mana,rar,cLevel,desc), buildHealth(bHealth), lifeTime(lTime){}

Building::Building(const Building &b): Card(b), buildHealth(b.getBuildHealth()), lifeTime(b.getLifeTime()){}
