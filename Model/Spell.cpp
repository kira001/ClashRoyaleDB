#include "Spell.h"
#include "myexception.h"
/******************** CONSTRUCTORS/DESTRUCTORS  ********************/

Spell::Spell(string p,string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc,double spellD,double crownTD,double rad):
          Card(p,n,mana,rar,cLevel,desc),spellDamage(spellD),crownTowerDamage(crownTD),radius(rad){}


Spell::Spell(const Spell& s):Card(s),spellDamage(s.getSpellDamage()),crownTowerDamage(s.getCrownTowerDamage()),radius(s.getRadius()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
double Spell::getSpellDamage() const{return spellDamage;}
double Spell::getCrownTowerDamage() const{return crownTowerDamage;}
double Spell::getRadius() const{return radius;}

//SETTERS
void Spell::setSpellDamage(double spellD){spellDamage=spellD;}
void Spell::setCrownTowerDamage(double crownTD){crownTowerDamage=crownTD;}
void Spell::setRadius(double rad){radius=rad;}

/********************** OVERLOADING *********************/

bool Spell::operator==(const Spell & s) const
{
    return Card::operator==(s) &&
           spellDamage == s.spellDamage &&
           crownTowerDamage == s.crownTowerDamage &&
           radius == s.radius;
}

bool Spell::operator!=(const Spell & s) const
{
    return Card::operator!=(s) ||
           spellDamage != s.spellDamage ||
           crownTowerDamage != s.crownTowerDamage ||
           radius != s.radius;
}



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
    if(Card::isUpgradable()){
        Card::lvlUpgrade();
        upgradeStats();
    }
}
void Spell::lvlDowngrade(){
    if(Card::isDowngradable()){
        downgradeStats();
        Card::lvlDowngrade();
    }
}

QJsonObject Spell::writeJson() const
{
    QJsonObject SJson=Card::writeJson();
    SJson["Type"] = QString::fromStdString(getType());
    SJson["Damage"] = getSpellDamage();
    SJson["Crown Tower Damage"] = getCrownTowerDamage();
    SJson["Radius"] = getRadius();
    
    return SJson;
}
void Spell::readJson(const QJsonObject &obj)
{
    Card::readJson(obj);
    if (obj.contains("Damage") && obj["Damage"].isDouble())
        setSpellDamage(obj["Damage"].toDouble());
    if (obj.contains("Crown Tower Damage") && obj["Crown Tower Damage"].isDouble())
        setCrownTowerDamage(obj["Crown Tower Damage"].toDouble());
    if (obj.contains("Radius") && obj["Radius"].isDouble())
        setRadius(obj["Radius"].toDouble());

}
string Spell::getType() const {return "Spell";}
Spell* Spell::clone() const { return new Spell(*this); }
