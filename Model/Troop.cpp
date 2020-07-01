#include "Troop.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Troop::Troop(string p,string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc, double s,
             double th, double hxs, double dxs, double sdd, double r, unsigned int c):
Card(p,n,mana,rar,cLevel,desc), shield(s), troopHealth(th), hitxSec(hxs), damagexSec(dxs), spawnDD(sdd),
  range(r),count(c){}
Troop::Troop(const Troop& x):Card(x),shield(x.getShield()),troopHealth(x.getTroopHealth()),hitxSec(x.getHitxSec()),
damagexSec(x.getDamagexSec()),spawnDD(x.getSpawnDD()),range(x.getRange()),count(x.getCount())
{}

/******************** GETTERS/SETTERS ********************/

//GETTERS
   double Troop::getShield() const{return shield;}
   double Troop::getTroopHealth() const{return troopHealth;}
   double Troop::getHitxSec()const{return hitxSec;}
   double Troop::getDamagexSec()const{return damagexSec;}
   double Troop::getSpawnDD()const{return spawnDD;}
   double Troop::getRange()const{return range;}
   unsigned int Troop::getCount()const{return count;}

//SETTERS
   void Troop::setShield(double s){shield=s;}
   void Troop::setTroopHealth(double th){troopHealth=th;}
   void Troop::setHitxSec(double hxs){hitxSec=hxs;}
   void Troop::setDamagexSec(double dxs){damagexSec=dxs;}
   void Troop::setSpawnDD(double sdd){spawnDD=sdd;}
   void Troop::setRange(double r){range=r;}
   void Troop::setCount(unsigned int c){count=c;}


 /******************** OVERLOADING ********************/
   bool Troop::operator==(const Troop & t) const
   {
       return Card::operator==(t) &&
              shield == t.shield &&
              troopHealth == t.troopHealth &&
              hitxSec == t.hitxSec  &&
              damagexSec == t.damagexSec &&
              spawnDD == t.spawnDD &&
              range == t.range &&
              count == t.count;
   }

   bool Troop::operator!=(const Troop & t) const
   {
       return Card::operator!=(t) ||
              shield != t.shield ||
              troopHealth != t.troopHealth ||
              hitxSec != t.hitxSec  ||
              damagexSec != t.damagexSec ||
              spawnDD != t.spawnDD ||
              range != t.range ||
              count != t.count;
   }


/******************** METHODS ********************/

   double Troop::damage() const{return hitxSec*damagexSec;}

   string Troop::dimRange() const
   {
       if(range>2) return "Large Range";
       if(range>=1.5) return "Melee: Long";
       if(range>=1) return "Melee: Medium";
       return "Melee: Short";
   }

   void Troop::upgradeStats(){
       shield= (shield*(100+2*Card::getCardLevel()))/100;
       troopHealth=(troopHealth*(100+2*Card::getCardLevel()))/100;
       damagexSec=(damagexSec*(100+3*Card::getCardLevel()))/100;
       spawnDD= (spawnDD*(100+1*Card::getCardLevel()))/100;
   }
   void Troop::downgradeStats(){
       shield= (shield*100/(100+2*Card::getCardLevel()));
       troopHealth=(troopHealth*100/(100+2*Card::getCardLevel()));
       damagexSec=(damagexSec*100/(100+3*Card::getCardLevel()));
       spawnDD=(spawnDD*100/(100+1*Card::getCardLevel()));
   }

   void Troop::lvlUpgrade(){
      if(Card::isUpgradable()){
            Card::lvlUpgrade();
            upgradeStats();
      }
   }
   void Troop::lvlDowngrade(){
       if(Card::isDowngradable()){
            downgradeStats();
            Card::lvlDowngrade();
       }
   }
   string Troop::getType() const{return "Troop";}

   Troop* Troop::clone() const{return new Troop(*this);}
