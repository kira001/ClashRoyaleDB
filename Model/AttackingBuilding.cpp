#include "AttackingBuilding.h"

double AttackingBuilding::getHitPerSecond() const{
    return hitPerSecond;
}

void AttackingBuilding::setHitPerSecond(double hPerSecond){
    hitPerSecond = hPerSecond;
}

double AttackingBuilding::getDamagePerSecond() const{
    return damagePerSecond;
}

void AttackingBuilding::setDamagePerSecond(double dPerSecond){
    damagePerSecond = dPerSecond;
}

double AttackingBuilding::getRange() const{
    return range;
}

void AttackingBuilding::setRange(double rng){
    range = rng;
}

void AttackingBuilding::lvlUpgrade(){
    damagePerSecond*=(100+5*Card::getCardLevel())/100;
}

void AttackingBuilding::lvlDowngrade(){
    damagePerSecond*=100/(100+5*Card::getCardLevel());
}

AttackingBuilding *AttackingBuilding::clone() const{
    return new AttackingBuilding(*this);
}

double AttackingBuilding::damage() const{
    return getDamagePerSecond()*getHitPerSecond();
}

AttackingBuilding::AttackingBuilding(){}

AttackingBuilding::AttackingBuilding(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double hPerSecond, double dPerSecond, double rng):
    Card(n,mana,rar,cLevel,desc), hitPerSecond(hPerSecond), damagePerSecond(dPerSecond), range(rng){}

AttackingBuilding::AttackingBuilding(const AttackingBuilding &ab):
                    Card(ab), hitPerSecond(ab.getHitPerSecond()), damagePerSecond(ab.getDamagePerSecond()), range(ab.getRange()){}
