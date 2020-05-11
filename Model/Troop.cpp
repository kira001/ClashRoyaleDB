#include "Troop.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Troop::Troop():Card(){}
Troop::Troop(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, unsigned int s,
             unsigned int th, double hxs, double dxs, unsigned int sdd, double r, unsigned int c):
Card(n,mana,rar,cLevel,desc), shield(s), troopHealth(th), hitxSec(hxs), damagexSec(dxs), spawnDD(sdd),
  range(r),count(c){}
Troop::Troop(const Troop& x):Card(x),shield(x.getShield()),troopHealth(x.getTroopHealth()),hitxSec(x.getHitxSec()),
damagexSec(x.getDamagexSec()),spawnDD(x.getSpawnDD()),range(x.getRange()),count(x.getCount())
{}

/******************** METHODS ********************/

//GETTERS
   unsigned int Troop::getShield() const{return shield;}
   unsigned int Troop::getTroopHealth() const{return troopHealth;}
   double Troop::getHitxSec()const{return hitxSec;}
   double Troop::getDamagexSec()const{return damagexSec;}
   unsigned int Troop::getSpawnDD()const{return spawnDD;}
   double Troop::getRange()const{return range;}
   unsigned int Troop::getCount()const{return count;}

//SETTERS
   void Troop::setShield(unsigned int s){shield=s;}
   void Troop::setTroopHealth(unsigned int th){troopHealth=th;}
   void Troop::setHitxSec(double hxs){hitxSec=hxs;}
   void Troop::setDamagexSec(double dxs){damagexSec=dxs;}
   void Troop::setSpawnDD(unsigned int sdd){spawnDD=sdd;}
   void Troop::setRange(double r){range=r;}
   void Troop::setCount(unsigned int c){count=c;}

//METHODS
   double Troop::damage() const{return hitxSec*damagexSec;}
