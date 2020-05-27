#include "Spell.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/

Spell::Spell(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,double spellD,double crownTD,double rad):
          Card(n,mana,rar,cLevel,desc),spellDamage(spellD),crownTowerDamage(crownTD),radius(rad){}


Spell::Spell(const Spell& s):Card(s),spellDamage(s.getSpellDamage()),crownTowerDamage(s.getCrownTowerDamage()),radius(getRadius()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
double Spell::getSpellDamage() const{return spellDamage;}
double Spell::getCrownTowerDamage() const{return crownTowerDamage;}
double Spell::getRadius() const{return radius;}

//SETTERS
void Spell::setSpellDamage(double spellD){spellDamage=spellD;}
void Spell::setCrownTowerDamage(double crownTD){crownTowerDamage=crownTD;}
void Spell::setRadius(double rad){radius=rad;}



/********************** METHODS *********************/
void Spell::upgradeStats(){
    spellDamage= (spellDamage*(100+3*Card::getCardLevel()))/100;
    crownTowerDamage=(crownTowerDamage*(100+2*Card::getCardLevel()))/100;
}
void Spell::downgradeStats(){
    spellDamage= (spellDamage*100/(100+3*Card::getCardLevel()));
    crownTowerDamage=(crownTowerDamage*100/(100+2*Card::getCardLevel()));
}
void Spell::lvlUpgrade(){
    if(Card::getCardLevel()<Card::getMaxLevel()){
        Card::lvlUpgrade();
        upgradeStats();
    }
}
void Spell::lvlDowngrade(){
    if(Card::getCardLevel()>1){
        downgradeStats();
        Card::lvlDowngrade();
    }
}
QJsonObject Spell::writeJson() const
{}
void Spell::readJson(const QJsonObject &obj)
{}
string Spell::getType() const {return "Spell";}
Spell* Spell::clone() const { return new Spell(*this); }
