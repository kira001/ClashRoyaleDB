#ifndef BUILDINGTROOPSPAWNER_H
#define BUILDINGTROOPSPAWNER_H
#include "Building.h"
#include "Troop.h"

class BuildingTroopSpawner: public Building, public Troop{
private:
    double spawnSpeed;
public:
    BuildingTroopSpawner();
    BuildingTroopSpawner(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, double sSpeed);
    BuildingTroopSpawner(const BuildingTroopSpawner& bts);

    double getSpawnSpeed() const;
    void setSpawnSpeed(double sSpeed);
};
#endif // BUILDINGTROOPSPAWNER_H
