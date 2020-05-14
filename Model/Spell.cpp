#include "Spell.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Spell::Spell():Card(){}
Spell::Spell(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,unsigned int spellD,unsigned int crownTD,double rad):
          Card(n,mana,rar,cLevel,desc),spellDamage(spellD),crownTowerDamage(crownTD),radius(rad){}


Spell::Spell(const Spell& s):Card(s),spellDamage(s.getSpellDamage()),crownTowerDamage(s.getCrownTowerDamage()),radius(getRadius()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
unsigned int Spell::getSpellDamage() const{return spellDamage;}
unsigned int Spell::getCrownTowerDamage() const{return crownTowerDamage;}
double Spell::getRadius() const{return radius;}

//SETTERS
void Spell::setSpellDamage(unsigned int spellD){spellDamage=spellD;}
void Spell::setCrownTowerDamage(unsigned int crownTD){crownTowerDamage=crownTD;}
void Spell::setRadius(double rad){radius=rad;}



/********************** METHODS *********************/
void Spell::lvlUpgrade(){
    Card::lvlUpgrade();
    spellDamage*= static_cast<unsigned int>( (100+3*Card::getCardLevel())/100);
    crownTowerDamage*=static_cast<unsigned int>( (100+2*Card::getCardLevel())/100);

}
void Spell::lvlDowngrade(){
    if(Card::getCardLevel()>1){
    spellDamage*= static_cast<unsigned int>(100/(100+3*Card::getCardLevel()));
    crownTowerDamage*=static_cast<unsigned int>( 100/(100+2*Card::getCardLevel()));
    Card::lvlDowngrade();
    }
}
Spell* Spell::clone() const { return new Spell(*this); }
