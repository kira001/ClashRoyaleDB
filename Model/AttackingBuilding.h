#ifndef ATTACKINGBUILDING_H
#define ATTACKINGBUILDING_H
#include "Building.h"

class AttackingBuilding: public Building{
private:
    double hitPerSecond;
    double damagePerSecond;
    double range;
protected:
    void upgradeStats();
    void downgradeStats();
public:
    AttackingBuilding()=default;
    AttackingBuilding(string p,string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, double bHealth, double lTime, double hPerSecond, double dPerSecond, double rng);
    AttackingBuilding(const AttackingBuilding& ab);

    double getHitPerSecond() const;
    void setHitPerSecond(double hPerSecond);
    double getDamagePerSecond() const;
    void setDamagePerSecond(double dPerSecond);
    double getRange() const;
    void setRange(double rng);
    //OVERLOADING
    virtual bool  operator==(const AttackingBuilding&) const;
    virtual bool  operator!=(const AttackingBuilding&) const;

    virtual string getType() const;
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual AttackingBuilding* clone() const;
    double damage() const;

};
#endif // ATTACKINGBUILDING
