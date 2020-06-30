#include "SpellTroopSpawner.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/

SpellTroopSpawner::SpellTroopSpawner(string p, string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,double spellD,double crownTD,double rad,
                                     double s,double th, double hxs, double dxs, double sdd, double r, unsigned int c,string timeSp):
Card(p,n,mana,rar,cLevel,desc),
Spell(p,n,mana,rar,cLevel,desc,spellD,crownTD,rad),
Troop(p,n,mana,rar,cLevel,desc,s,th,hxs,dxs,sdd,r,c),timeSpawn(timeSp){}



SpellTroopSpawner::SpellTroopSpawner(const SpellTroopSpawner& stp):
                   Card(stp),Spell(stp),Troop(stp),timeSpawn(stp.getTimeSpawn()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
string SpellTroopSpawner::getTimeSpawn() const{return timeSpawn;}

//SETTERS
void SpellTroopSpawner::setTimeSpawn(string timeSp){timeSpawn=timeSp;}

bool SpellTroopSpawner::operator==(const SpellTroopSpawner & sts) const
{
    return Spell::operator==(sts) &&
           Troop::operator==(sts) &&
           timeSpawn == sts.timeSpawn;
}

bool SpellTroopSpawner::operator!=(const SpellTroopSpawner & sts) const
{
    return Spell::operator!=(sts) ||
           Troop::operator!=(sts) ||
           timeSpawn != sts.timeSpawn;
}


/********************** METHODS *********************/
void SpellTroopSpawner::lvlUpgrade(){
    if(Card::isUpgradable()){
        Card::lvlUpgrade();
        Spell::upgradeStats();
        Troop::upgradeStats();
    }
}
void SpellTroopSpawner::lvlDowngrade(){
    if(Card::isDowngradable()){
       Spell::downgradeStats();
       Troop::downgradeStats();
       Card::lvlDowngrade();
    }
}
string SpellTroopSpawner::getType() const{return "Spell-Troop Spawner";}

SpellTroopSpawner* SpellTroopSpawner::clone() const { return new SpellTroopSpawner(*this); }
