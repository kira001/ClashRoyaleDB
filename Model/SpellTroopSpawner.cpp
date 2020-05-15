#include "SpellTroopSpawner.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/

SpellTroopSpawner::SpellTroopSpawner(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,unsigned int spellD,unsigned int crownTD,double rad,
                                     unsigned int s,unsigned int th, double hxs, double dxs, unsigned int sdd, double r, unsigned int c,string timeSp):
Card(n,mana,rar,cLevel,desc),
Spell(n,mana,rar,cLevel,desc,spellD,crownTD,rad),
Troop(n,mana,rar,cLevel,desc,s,th,hxs,dxs,sdd,r,c),timeSpawn(timeSp){}



SpellTroopSpawner::SpellTroopSpawner(const SpellTroopSpawner& stp):
                   Spell(stp),Troop(stp),timeSpawn(stp.getTimeSpawn()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
string SpellTroopSpawner::getTimeSpawn() const{return timeSpawn;}

//SETTERS
void SpellTroopSpawner::setTimeSpawn(string timeSp){timeSpawn=timeSp;}


/********************** METHODS *********************/
void SpellTroopSpawner::lvlUpgrade(){
    Spell::lvlUpgrade();
     Card::lvlDowngrade();
    Troop::lvlUpgrade();

}
void SpellTroopSpawner::lvlDowngrade(){
    Spell::lvlDowngrade();
    Card::lvlUpgrade();
    Troop::lvlDowngrade();

}
SpellTroopSpawner* SpellTroopSpawner::clone() const { return new SpellTroopSpawner(*this); }
