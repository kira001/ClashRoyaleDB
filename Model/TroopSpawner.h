#ifndef TROOPSPAWNER_H
#define TROOPSPAWNER_H

#include "Troop.h"

class TroopSpawner: public Troop {
private:
    float time;
    string description;
public:
    // CONSTRUCTORS/DESTRUCTORS
    TroopSpawner();
    TroopSpawner(string,unsigned int,rarity,unsigned int,string,unsigned int,
                 unsigned int,double,double,unsigned int,double,unsigned int,
                 float,string);
    TroopSpawner(const TroopSpawner&);
    // GETTERS
    float getTime()const;
    string getWhy()const;
    // SETTERS
    void setTime(float);
    void setWhy(string);

};













#endif // TROOPSPAWNER_H
