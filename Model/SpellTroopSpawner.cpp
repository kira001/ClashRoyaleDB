#include "SpellTroopSpawner.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
SpellTroopSpawner::SpellTroopSpawner():Spell(),Troop(){}
SpellTroopSpawner::SpellTroopSpawner(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,unsigned int spellD,unsigned int crownTD,double rad,
                                     unsigned int s,unsigned int th, double hxs, double dxs, unsigned int sdd, double r, unsigned int c,string timeSp):
Spell(n,mana,rar,cLevel,desc,spellD,crownTD,rad),
Troop(n,mana,rar,cLevel,desc,s,th,hxs,dxs,sdd,r,c),timeSpawn(timeSp){}



SpellTroopSpawner::SpellTroopSpawner(const SpellTroopSpawner& stp):
                   Spell(stp),Troop(stp),timeSpawn(stp.getTimeSpawn()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
string SpellTroopSpawner::getTimeSpawn() const{return timeSpawn;}

//SETTERS
void SpellTroopSpawner::setTimeSpawn(string timeSp){timeSpawn=timeSp;}
