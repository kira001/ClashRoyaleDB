#include"BuildingTroopSpawner.h"


BuildingTroopSpawner::BuildingTroopSpawner(std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime, double shld, double tHealth, double hxSec, double dxSec, double sDD, double rng, unsigned int cnt, double sSpeed):
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
    if(Card::getCardLevel()<Card::getMaxLevel()){
        Card::lvlUpgrade();
        Building::upgradeStats();
        Troop::upgradeStats();
    }
}

void BuildingTroopSpawner::lvlDowngrade(){
    if(Card::getCardLevel()>1){

       Building::downgradeStats();
       Troop::downgradeStats();
       Card::lvlDowngrade();
    }
}

BuildingTroopSpawner* BuildingTroopSpawner::clone() const{
    return new BuildingTroopSpawner(*this);
}
