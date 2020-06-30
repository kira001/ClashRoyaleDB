#include "TroopSpawner.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
TroopSpawner::TroopSpawner(string p,string n,unsigned int mc,rarity cr, unsigned int cl,string desc,
                           double s,double th,double hxs,double dxs,
                           double sdd,double r,unsigned int c,string td)
                           :Card(p,n,mc,cr,cl,desc),Troop(p,n,mc,cr,cl,desc,s,th,hxs,dxs,sdd,r,c),TimeDesc(td){}

TroopSpawner::TroopSpawner(const TroopSpawner& x):Card(x),Troop(x),TimeDesc(x.getTimeDesc()){}

/******************** GETTERS/SETTERS ********************/

   //GETTERS
   string TroopSpawner::getTimeDesc() const{return TimeDesc;}

   //SETTERS
   void TroopSpawner::setTimeDesc(string td){TimeDesc=td;}

/******************** OVERLOADING ********************/

   bool TroopSpawner::operator==(const TroopSpawner & ts) const
   {
       return Troop::operator==(ts) &&
              TimeDesc == ts.TimeDesc;
   }

   bool TroopSpawner::operator!=(const TroopSpawner & ts) const
   {
       return Troop::operator!=(ts) ||
              TimeDesc != ts.TimeDesc;
   }

/******************** METHODS ********************/
   void TroopSpawner::lvlUpgrade(){
       if(Card::isUpgradable())
            Troop::lvlUpgrade();
   }
   void TroopSpawner::lvlDowngrade(){
       if(Card::isDowngradable())
            Troop::lvlDowngrade();
   }
   string TroopSpawner::getType() const{return "Troop Spawner";}

   TroopSpawner* TroopSpawner::clone() const{return new TroopSpawner(*this);}
