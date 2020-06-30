#ifndef TROOPSPAWNER_H
#define TROOPSPAWNER_H

#include "Troop.h"

class TroopSpawner: public Troop {
private:
    string TimeDesc; //time and description
public:
    // CONSTRUCTORS/DESTRUCTORS
    TroopSpawner()=default;
    TroopSpawner(string, string,unsigned int,rarity,unsigned int,string,double,
                 double,double,double,double,double,unsigned int,
                 string);
    TroopSpawner(const TroopSpawner&);
    // GETTERS
    string getTimeDesc()const;
    // SETTERS
    void setTimeDesc(string);
    //OVERLOADING
    virtual bool  operator==(const TroopSpawner&) const;
    virtual bool  operator!=(const TroopSpawner&) const;
    // METHODS
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    virtual string getType() const;
    virtual TroopSpawner* clone() const;

};













#endif // TROOPSPAWNER_H
