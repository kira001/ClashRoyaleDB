#ifndef TROOP_H
#define TROOP_H

#include "Card.h"

class Troop:virtual public Card{
private:
    double shield;
    double troopHealth;
    double hitxSec;
    double damagexSec;
    double spawnDD; //SpawnDeathDamage
    double range;
    unsigned int count;
protected:
    void upgradeStats();
    void downgradeStats();
public:
    // CONSTRUCTORS/DESTRUCTORS
    Troop()=default;
    Troop(string, string, unsigned int, rarity, unsigned int,string ,
          double, double, double, double, double, double, unsigned int);
    Troop(const Troop&);
    // GETTERS
    double getShield() const;
    double getTroopHealth() const;
    double getHitxSec() const;
    double getDamagexSec() const;
    double getSpawnDD() const;
    double getRange() const;
    unsigned int getCount() const;
    // SETTERS
    void setShield(double);
    void setTroopHealth(double);
    void setHitxSec(double);
    void setDamagexSec(double);
    void setSpawnDD(double);
    void setRange(double);
    void setCount(unsigned int);
    //OVERLOADING
    virtual bool  operator==(const Troop&) const;
    virtual bool  operator!=(const Troop&) const;
    // METHODS
    double damage() const;
    string dimRange() const;//METODO CHE RITORNA IN STRINGA LA PORTATA DEL RANGE (SHORT,MEDIUM,LONG)
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual string getType() const;
    virtual Troop* clone() const;

};
#endif // TROOP_H
