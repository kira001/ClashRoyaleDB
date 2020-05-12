#include "TroopSpawner.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
TroopSpawner::TroopSpawner():Troop(){};
TroopSpawner::TroopSpawner(string n,unsigned int mc,rarity cr, unsigned int cl,string desc,
                           unsigned int s,unsigned int th,double hxs,double dxs,
                           unsigned int sdd,double r,unsigned int c,float t,string d)
                           :Troop(n,mc,cr,cl,desc,s,th,hxs,dxs,sdd,r,c),time(t),description(d){}
TroopSpawner::TroopSpawner(const TroopSpawner& x):Troop(x),time(x.getTime()),description(x.getWhy()){}

/******************** METHODS ********************/

//GETTERS
   float TroopSpawner::getTime() const{return time;}
   string TroopSpawner::getWhy() const{return description;}

//SETTERS
   void TroopSpawner::setTime(float t){time=t;}
   void TroopSpawner::setWhy(string d){description=d;}
