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
    damagePerSecond= (damagePerSecond*(100+5*Card::getCardLevel()))/100;
}

void AttackingBuilding::downgradeStats(){
    damagePerSecond= (damagePerSecond*100/(100+5*Card::getCardLevel()));
}
QJsonObject AttackingBuilding::writeJson() const
{
    QJsonObject abJson=Building::writeJson();
    abJson["Type"] = QString::fromStdString(getType());
    abJson["Hit per Second"] = getHitPerSecond();
    abJson["Damage per Second"] = getDamagePerSecond();
    abJson["Range"] = getRange();
    return abJson;

}
void AttackingBuilding::readJson(const QJsonObject &obj)
{
    Building::readJson(obj);

    if (obj.contains("Hit per Second") && obj["Hit per Second"].isDouble())
        setHitPerSecond(obj["Card Name"].toDouble());
    if (obj.contains("Damage per Second") && obj["Damage per Second"].isDouble())
        setDamagePerSecond(obj["Mana Cost"].toDouble());
    if (obj.contains("Range") && obj["Range"].isDouble())
        setRange(obj["Range"].toDouble());


}



AttackingBuilding::AttackingBuilding(std::string p,std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc,double bHealth, double lTime, double hPerSecond, double dPerSecond, double rng):
    Card(p,n,mana,rar,cLevel,desc),Building(p,n,mana,rar,cLevel,desc, bHealth, lTime), hitPerSecond(hPerSecond), damagePerSecond(dPerSecond), range(rng){}

AttackingBuilding::AttackingBuilding(const AttackingBuilding &ab):
                    Card(ab),Building(ab), hitPerSecond(ab.getHitPerSecond()), damagePerSecond(ab.getDamagePerSecond()), range(ab.getRange()){}
