#ifndef ATTACKINGBUILDING_H
#define ATTACKINGBUILDING_H
#include "Building.h"

class AttackingBuilding: public Building{
private:
    double hitPerSecond;
    double damagePerSecond;
    double range;
public:
    AttackingBuilding()=default;
    AttackingBuilding(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, double hPerSecond, double dPerSecond, double rng);
    AttackingBuilding(const AttackingBuilding& ab);

    double getHitPerSecond() const;
    void setHitPerSecond(double hPerSecond);
    double getDamagePerSecond() const;
    void setDamagePerSecond(double dPerSecond);
    double getRange() const;
    void setRange(double rng);

    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual AttackingBuilding* clone() const;

    double damage() const;
    // Metodo damage()
};
#endif // ATTACKINGBUILDING
