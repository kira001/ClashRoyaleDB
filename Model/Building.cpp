#include "Building.h"

double Building::getBuildHealth() const{
    return buildHealth;
}

void Building::setBuildHealth(double bHealth){
    buildHealth = bHealth;
}

double Building::getLifeTime() const{
    return lifeTime;
}

void Building::setLifeTime(double lTime){
    lifeTime = lTime;
}

void Building::lvlUpgrade(){
    Card::lvlUpgrade();
    buildHealth= (buildHealth*(100+7*Card::getCardLevel()))/100;
    lifeTime= (lifeTime*(100+5*Card::getCardLevel()))/100;
}

void Building::lvlDowngrade(){
    Card::lvlDowngrade();
    buildHealth= (buildHealth*100/(100+7*Card::getCardLevel()));
    lifeTime= (lifeTime*100/(100+5*Card::getCardLevel()));
}

Building* Building::clone() const{
    return new Building(*this);
}


Building::Building(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime):
    Card(n,mana,rar,cLevel,desc), buildHealth(bHealth), lifeTime(lTime){}

Building::Building(const Building &b): Card(b), buildHealth(b.getBuildHealth()), lifeTime(b.getLifeTime()){}
