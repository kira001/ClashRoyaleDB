#include"BuildingTroopSpawner.h"


BuildingTroopSpawner::BuildingTroopSpawner(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, unsigned int bHealth, unsigned int lTime, unsigned int shld, unsigned int tHealth, double hxSec, double dxSec, unsigned int sDD, double rng, unsigned int cnt, double sSpeed):
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

void BuildingTroopSpawner::lvlUpgrade()
{

}

void BuildingTroopSpawner::lvlDowngrade()
{

}

BuildingTroopSpawner* BuildingTroopSpawner::clone() const{
    return new BuildingTroopSpawner(*this);
}
