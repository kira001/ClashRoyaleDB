#ifndef SPELL_H
#define SPELL_H

#include "Card.h"

class Spell:virtual public Card{
private:
    double spellDamage;
    double crownTowerDamage;
    double radius;
protected:
    void upgradeStats();
    void downgradeStats();
public:
    // CONSTRUCTORS/DESTRUCTORS
    Spell()=default;
    Spell(string, unsigned int, rarity, unsigned int,string
          ,double,double,double);
    Spell(const Spell&);
    // GETTERS
    double getSpellDamage() const;
    double getCrownTowerDamage() const;
    double getRadius() const;
    // SETTERS
    void setSpellDamage(double);
    void setCrownTowerDamage(double);
    void setRadius(double);

    //METHODS
    virtual QJsonObject serializeJson() const;
    virtual void deserializeJson(const QJsonObject& obj);
    virtual string getType() const;
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual Spell* clone() const;
};


#endif // SPELL_H
