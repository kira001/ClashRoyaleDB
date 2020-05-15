#ifndef TROOPSPAWNER_H
#define TROOPSPAWNER_H

#include "Troop.h"

class TroopSpawner: public Troop {
private:
    string TimeDesc; //time and description
public:
    // CONSTRUCTORS/DESTRUCTORS
    TroopSpawner()=default;
    TroopSpawner(string,unsigned int,rarity,unsigned int,string,unsigned int,
                 unsigned int,double,double,unsigned int,double,unsigned int,
                 string);
    TroopSpawner(const TroopSpawner&);
    // GETTERS
    string getTimeDesc()const;
    // SETTERS
    void setTimeDesc(string);
    // METHODS
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual TroopSpawner* clone() const;

};













#endif // TROOPSPAWNER_H
