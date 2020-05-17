#include"BuildingTroopSpawner.h"


BuildingTroopSpawner::BuildingTroopSpawner(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime, unsigned int shld, unsigned int tHealth, double hxSec, double dxSec, unsigned int sDD, double rng, unsigned int cnt, double sSpeed):
                                         Card(n,mana,rar,cLevel,desc),
                                         Building(n,mana,rar,cLevel,desc,bHealth,lTime),
                                         Troop(n,mana,rar,cLevel,desc, shld, tHealth, hxSec, dxSec, sDD, rng, cnt), spawnSpeed(sSpeed){}


BuildingTroopSpawner::BuildingTroopSpawner(const BuildingTroopSpawner &bts):
Building(bts),Troop(bts), spawnSpeed(bts.getSpawnSpeed()){}

double BuildingTroopSpawner::getSpawnSpeed() const{
    return spawnSpeed;
}

void BuildingTroopSpawner::setSpawnSpeed(double sSpeed){
    spawnSpeed = sSpeed;
}

void BuildingTroopSpawner::lvlUpgrade(){
    Building::lvlUpgrade();
    Card::lvlDowngrade();
    Troop::lvlUpgrade();
}

void BuildingTroopSpawner::lvlDowngrade(){
    Building::lvlDowngrade();
    Card::lvlUpgrade();
    Troop::lvlDowngrade();
}

BuildingTroopSpawner* BuildingTroopSpawner::clone() const{
    return new BuildingTroopSpawner(*this);
}
