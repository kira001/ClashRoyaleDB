#include"BuildingTroopSpawner.h"


BuildingTroopSpawner::BuildingTroopSpawner(std::string p,std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime, double shld, double tHealth, double hxSec, double dxSec, double sDD, double rng, unsigned int cnt, double sSpeed):
                                         Card(p,n,mana,rar,cLevel,desc),
                                         Building(p,n,mana,rar,cLevel,desc,bHealth,lTime),
                                         Troop(p,n,mana,rar,cLevel,desc, shld, tHealth, hxSec, dxSec, sDD, rng, cnt), spawnSpeed(sSpeed){}


BuildingTroopSpawner::BuildingTroopSpawner(const BuildingTroopSpawner &bts):
Card(bts),Building(bts),Troop(bts), spawnSpeed(bts.getSpawnSpeed()){}

double BuildingTroopSpawner::getSpawnSpeed() const{
    return spawnSpeed;
}

void BuildingTroopSpawner::setSpawnSpeed(double sSpeed){
    spawnSpeed = sSpeed;
}

bool BuildingTroopSpawner::operator==(const BuildingTroopSpawner & bts) const
{
    return Building::operator==(bts) &&
           Troop::operator==(bts) &&
           spawnSpeed == bts.spawnSpeed;
}

bool BuildingTroopSpawner::operator!=(const BuildingTroopSpawner & bts) const
{
    return Building::operator!=(bts) ||
           Troop::operator!=(bts) ||
           spawnSpeed != bts.spawnSpeed;
}

void BuildingTroopSpawner::lvlUpgrade(){
    if(Card::isUpgradable()){
        Card::lvlUpgrade();
        Building::upgradeStats();
        Troop::upgradeStats();
    }
}
void BuildingTroopSpawner::lvlDowngrade(){
    if(Card::isDowngradable()){
       Building::downgradeStats();
       Troop::downgradeStats();
       Card::lvlDowngrade();
    }
}
string BuildingTroopSpawner::getType() const{return "Building-Troop Spawner";}
BuildingTroopSpawner* BuildingTroopSpawner::clone() const{
    return new BuildingTroopSpawner(*this);
}
