#include"BuildingTroopSpawner.h"

BuildingTroopSpawner::BuildingTroopSpawner(){}

BuildingTroopSpawner::BuildingTroopSpawner(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, unsigned int bHealth, unsigned int lTime, unsigned int shld, unsigned int tHealth, double hxSec, double dxSec, unsigned int sDD, double rng, unsigned int cnt, double sSpeed):
                                        Troop(n,mana,rar,cLevel,desc, shld, tHealth, hxSec, dxSec, sDD, rng, cnt),
                                         Building(n,mana,rar,cLevel,desc,bHealth,lTime), spawnSpeed(sSpeed){}


BuildingTroopSpawner::BuildingTroopSpawner(const BuildingTroopSpawner &bts):
Building(bts),Troop(bts), spawnSpeed(bts.getSpawnSpeed()){}

double BuildingTroopSpawner::getSpawnSpeed() const
{
    return spawnSpeed;
}

void BuildingTroopSpawner::setSpawnSpeed(double sSpeed)
{
    spawnSpeed = sSpeed;
}
