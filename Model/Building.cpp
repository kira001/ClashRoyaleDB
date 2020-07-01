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


bool Building::operator==(const Building & b) const
{
    return Card::operator==(b) &&
           buildHealth == b.buildHealth &&
           lifeTime == b.lifeTime;

}
bool Building::operator!=(const Building & b) const
{
    return Card::operator!=(b) ||
           buildHealth != b.buildHealth ||
           lifeTime != b.lifeTime;
}

string Building::getType() const{return "Building";}
void Building::lvlUpgrade(){
    if(Card::isUpgradable()){
        Card::lvlUpgrade();
        upgradeStats();
    }

}

void Building::lvlDowngrade(){
    if(Card::isDowngradable()){
        downgradeStats();
        Card::lvlDowngrade();
    }
}

Building* Building::clone() const{
    return new Building(*this);
}


void Building::upgradeStats(){
    buildHealth= (buildHealth*(100+5*Card::getCardLevel()))/100;
}

void Building::downgradeStats(){
    buildHealth= (buildHealth*100/(100+5*Card::getCardLevel()));
}

Building::Building(std::string p, std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime):
    Card(p,n,mana,rar,cLevel,desc), buildHealth(bHealth), lifeTime(lTime){}

Building::Building(const Building &b): Card(b), buildHealth(b.getBuildHealth()), lifeTime(b.getLifeTime()){}
