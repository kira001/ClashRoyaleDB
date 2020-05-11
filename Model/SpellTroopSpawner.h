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
    SpellTroopSpawner();
    SpellTroopSpawner(string, unsigned int, rarity, unsigned int,string,unsigned int,unsigned int,double
                      , unsigned int, unsigned int, double, double, unsigned int, double, unsigned int,string);
    SpellTroopSpawner(const SpellTroopSpawner&);
    // GETTERS
    string getTimeSpawn() const;
    // SETTERS
    void setTimeSpawn(string);
};

#endif // SPELLTROOPSPAWNER_H
