#include "Troop.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Troop::Troop(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, unsigned int s,
             unsigned int th, double hxs, double dxs, unsigned int sdd, double r, unsigned int c):
Card(n,mana,rar,cLevel,desc), shield(s), troopHealth(th), hitxSec(hxs), damagexSec(dxs), spawnDD(sdd),
  range(r),count(c){}
Troop::Troop(const Troop& x):Card(x),shield(x.getShield()),troopHealth(x.getTroopHealth()),hitxSec(x.getHitxSec()),
damagexSec(x.getDamagexSec()),spawnDD(x.getSpawnDD()),range(x.getRange()),count(x.getCount())
{}

/******************** GETTERS/SETTERS ********************/

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


/******************** METHODS ********************/

   double Troop::damage() const{return hitxSec*damagexSec;}

   string Troop::DimRange(double s) const
   {
       if(s>1) return "Medium Range";
       if(s>2) return "Large Range";
           return "Short Range";
   }

   void Troop::lvlUpgrade(){
      Card::lvlUpgrade();
      shield*=(100*8*Card::getCardLevel())/100;
      troopHealth*=(100*10*Card::getCardLevel())/100;
      hitxSec*=(100*5*Card::getCardLevel())/100;
       damagexSec= (damagexSec*(100+5*Card::getCardLevel()))/100;

      spawnDD*=(100*6*Card::getCardLevel())/100;

   }
   void Troop::lvlDowngrade(){
      if(Card::getCardLevel()>1){
      shield*=100/(100*8*Card::getCardLevel());
      troopHealth*=100/(100*10*Card::getCardLevel());
      hitxSec*=100/(100*5*Card::getCardLevel());
      damagexSec*=100/(100*5*Card::getCardLevel());
      spawnDD*=100/(100*6*Card::getCardLevel());
      Card::lvlDowngrade();
      }
   }
   Troop* Troop::clone() const{return new Troop(*this);}
