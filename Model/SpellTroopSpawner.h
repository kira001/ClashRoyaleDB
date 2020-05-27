#ifndef SPELLTROOPSPAWNER_H
#define SPELLTROOPSPAWNER_H

#include "Spell.h"
#include "Troop.h"
#include <string>
using std::string;

class SpellTroopSpawner:public Spell, public Troop{
private:
   string timeSpawn;

public:
    // CONSTRUCTORS/DESTRUCTORS
    SpellTroopSpawner()=default;
    SpellTroopSpawner(string, unsigned int, rarity, unsigned int,string,double,double,double
                      , double, double, double, double, double, double, unsigned int,string);
    SpellTroopSpawner(const SpellTroopSpawner&);
    // GETTERS
    string getTimeSpawn() const;
    // SETTERS
    void setTimeSpawn(string);

    // METHODS
    virtual string getType() const;
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual SpellTroopSpawner* clone() const;


};

#endif // SPELLTROOPSPAWNER_H
