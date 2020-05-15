#ifndef SPELL_H
#define SPELL_H

#include "Card.h"

class Spell:virtual public Card{
private:
    double spellDamage;
    unsigned int crownTowerDamage;
    double radius;

public:
    // CONSTRUCTORS/DESTRUCTORS
    Spell()=default;
    Spell(string, unsigned int, rarity, unsigned int,string
          ,double,unsigned int,double);
    Spell(const Spell&);
    // GETTERS
    double getSpellDamage() const;
    unsigned int getCrownTowerDamage() const;
    double getRadius() const;
    // SETTERS
    void setSpellDamage(double);
    void setCrownTowerDamage(unsigned int);
    void setRadius(double);

    //METHODS
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual Spell* clone() const;
};


#endif // SPELL_H
