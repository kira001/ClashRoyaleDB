#include"BuildingTroopSpawner.h"

BuildingTroopSpawner::BuildingTroopSpawner(){}

BuildingTroopSpawner::BuildingTroopSpawner(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double sSpeed){}

BuildingTroopSpawner::BuildingTroopSpawner(const BuildingTroopSpawner &bts){}

double BuildingTroopSpawner::getSpawnSpeed() const
{
    return spawnSpeed;
}

void BuildingTroopSpawner::setSpawnSpeed(double sSpeed)
{
    spawnSpeed = sSpeed;
}
