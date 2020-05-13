#ifndef TROOPSPAWNER_H
#define TROOPSPAWNER_H

#include "Troop.h"

class TroopSpawner: public Troop {
private:
    string TimeDesc; //time and description
public:
    // CONSTRUCTORS/DESTRUCTORS
    TroopSpawner();
    TroopSpawner(string,unsigned int,rarity,unsigned int,string,unsigned int,
                 unsigned int,double,double,unsigned int,double,unsigned int,
                 string);
    TroopSpawner(const TroopSpawner&);
    // GETTERS
    string getTimeDesc()const;
    // SETTERS
    void setTimeDesc(string);
};













#endif // TROOPSPAWNER_H
