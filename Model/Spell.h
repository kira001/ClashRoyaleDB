#ifndef SPELL_H
#define SPELL_H

#include "Card.h"

class Spell:virtual public Card{
private:
    unsigned int spellDamage;
    unsigned int crownTowerDamage;
    double radius;

public:
    // CONSTRUCTORS/DESTRUCTORS
    Spell();
    Spell(string, unsigned int, rarity, unsigned int,string
          ,unsigned int,unsigned int,double);
    Spell(const Spell&);
    // GETTERS
    unsigned int getSpellDamage() const;
    unsigned int getCrownTowerDamage() const;
    double getRadius() const;
    // SETTERS
    void setSpellDamage(unsigned int);
    void setCrownTowerDamage(unsigned int);
    void setRadius(double);
};


#endif // SPELL_H
