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
string AttackingBuilding::dimRange() const
{
    if(range>2) return "Ranged";
    if(range>=1.6) return "Melee: Long";
    if(range>=1.2) return "Melee: Medium";
    return "Melee: Short";
}

bool AttackingBuilding::operator==(const AttackingBuilding & ab) const
{
    return Building::operator==(ab) &&
           hitPerSecond == ab.hitPerSecond &&
           damagePerSecond == ab.damagePerSecond &&
           range == ab.range;
}

bool AttackingBuilding::operator!=(const AttackingBuilding & ab) const
{
    return Building::operator!=(ab) ||
           hitPerSecond != ab.hitPerSecond ||
           damagePerSecond != ab.damagePerSecond ||
           range != ab.range;
}

void AttackingBuilding::lvlUpgrade(){
    if(Card::isUpgradable()){
        Building::lvlUpgrade();
        upgradeStats();
    }
}

void AttackingBuilding::lvlDowngrade(){
    if(Card::isDowngradable()){
        downgradeStats();
        Building::lvlDowngrade();
    }
}

AttackingBuilding *AttackingBuilding::clone() const{
    return new AttackingBuilding(*this);
}

double AttackingBuilding::damage() const{
    return getDamagePerSecond()*getHitPerSecond();
}

string AttackingBuilding::getType() const{return "Attacking Building";}
void AttackingBuilding::upgradeStats(){
    damagePerSecond= (damagePerSecond*(100+2*Card::getCardLevel()))/100;
}

void AttackingBuilding::downgradeStats(){
    damagePerSecond= (damagePerSecond*100/(100+2*Card::getCardLevel()));
}

AttackingBuilding::AttackingBuilding(std::string p,std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc,double bHealth, double lTime, double hPerSecond, double dPerSecond, double rng):
    Card(p,n,mana,rar,cLevel,desc),Building(p,n,mana,rar,cLevel,desc, bHealth, lTime), hitPerSecond(hPerSecond), damagePerSecond(dPerSecond), range(rng){}

AttackingBuilding::AttackingBuilding(const AttackingBuilding &ab):
                    Card(ab),Building(ab), hitPerSecond(ab.getHitPerSecond()), damagePerSecond(ab.getDamagePerSecond()), range(ab.getRange()){}
