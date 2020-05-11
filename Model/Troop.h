#ifndef TROOP_H
#define TROOP_H

#include "Card.h"

class Troop:virtual public Card{
private:
    unsigned int shield;
    unsigned int troopHealth;
    double hitxSec;
    double damagexSec;
    unsigned int spawnDD; //SpawnDeathDamage
    double range;
    unsigned int count;
public:
    // CONSTRUCTORS/DESTRUCTORS
    Troop();
    Troop(string, unsigned int, rarity, unsigned int,string ,
          unsigned int, unsigned int, double, double, unsigned int, double, unsigned int);
    Troop(const Troop&);
    // GETTERS
    unsigned int getShield() const;
    unsigned int getTroopHealth() const;
    double getHitxSec() const;
    double getDamagexSec() const;
    unsigned int getSpawnDD() const;
    double getRange() const;
    unsigned int getCount() const;
    // SETTERS
    void setShield(unsigned int);
    void setTroopHealth(unsigned int);
    void setHitxSec(double);
    void setDamagexSec(double);
    void setSpawnDD(unsigned int);
    void setRange(double);
    void setCount(unsigned int);
    // METHODS
    double damage() const;
};

//test







#endif // TROOP_H
