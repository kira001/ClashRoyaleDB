#include "Card.h"
#include "myexception.h"
/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Card::Card(string p,string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc):
           path(p),name(n),manaCost(mana),cardRarity(rar),cardLevel(cLevel),description(desc)
           {
            controlRarityLevel(rar,cLevel);
           }

Card::Card(const Card& c):
           path(c.getPath()),name(c.getName()),manaCost(c.getManaCost()),cardRarity(c.getCardRarity()),cardLevel(c.getCardLevel()),description(c.getDescription()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
string Card::getPath() const{ return path; }
string Card::getName() const{ return name; }
unsigned int Card::getManaCost() const { return manaCost; }
Card::rarity Card::getCardRarity() const { return cardRarity; }
unsigned int Card::getCardLevel() const { return cardLevel; }
string Card::getDescription() const{ return description; }
unsigned int Card::getMaxLevel() const{ return MaxLevel; }

//SETTERS
void Card::setPath(string p){ path=p; }
void Card::setName(string n){ name=n; }
void Card::setManaCost(unsigned int mana){ manaCost=mana; }
void Card::setCardRarity(Card::rarity rar){ cardRarity=rar;}
void Card::setCardLevel(unsigned int cLevel){ cardLevel=cLevel; }
void Card::setDescription(string desc){ description=desc; }

/******************** CONVERSION ENUM<--->STRING ********************/
string Card::RarityToString() const{
    switch (cardRarity)
       {
         case Card::rarity::common:return "Common";
         case Card::rarity::rare:return "Rare";
         case Card::rarity::epic:return "Epic";
         case Card::rarity::legendary:return "Legendary";
       }
}

Card::rarity Card::StringToRarity(string sRar){

    if(sRar=="Common") return Card::rarity::common;
    else if(sRar=="Rare") return Card::rarity::rare;
    else if(sRar=="Epic") return Card::rarity::epic;
    else return Card::rarity::legendary;
}

/************************ METHODS **************************/
void Card::lvlUpgrade(){
        cardLevel++;
}
void Card::lvlDowngrade(){
    cardLevel--;
}

bool Card::isUpgradable() const
{
    return cardLevel<MaxLevel? true: throw MyException("Maximum level reached");
}

bool Card::isDowngradable() const
{
    switch (cardRarity)
       {
         case Card::rarity::common: return cardLevel>1? true: throw MyException("Minimum level reached for common");
         case Card::rarity::rare:  return cardLevel>3? true: throw MyException("Minimum level reached for rare");
         case Card::rarity::epic:  return cardLevel>6? true: throw MyException("Minimum level reached for epic");
         case Card::rarity::legendary:  return cardLevel>9? true: throw MyException("Minimum level reached for legendary");
       }

}

void Card::controlRarityLevel(rarity cardRar, unsigned int cLevel) const{
    if(cLevel>13)
    {
        throw MyException("Max level is 13");
    }
    else
    {
        switch (cardRar)
           {
             case Card::rarity::common:  cardLevel>0? true: throw MyException("Minimum level for common is 1");break;
             case Card::rarity::rare:   cardLevel>2? true: throw MyException("Minimum level for rare is 3");break;
             case Card::rarity::epic:   cardLevel>5? true: throw MyException("Minimum level for epic is 6");break;
             case Card::rarity::legendary:   cardLevel>8? true: throw MyException("Minimum level for legendary is 9");break;
           }
    }
}
QJsonObject Card::writeJson() const
{
    QJsonObject cardJson;
    cardJson["Icon NameFile"] = QString::fromStdString(getPath());
    cardJson["Card Name"] = QString::fromStdString(getName());
    cardJson["Mana Cost"] = static_cast<int>(getManaCost()); //conversione unsigned int -> int
    cardJson["Rarity"] = QString::fromStdString(RarityToString());
    cardJson["Level"] = static_cast<int>(getCardLevel());
    cardJson["Description"] = QString::fromStdString(getDescription());
    return cardJson;

}

void Card::readJson(const QJsonObject& obj)
{
if (obj.contains("Icon NameFile") && obj["Icon NameFile"].isString())
        setPath(obj["Icon NameFile"].toString().toStdString());
if (obj.contains("Card Name") && obj["Card Name"].isString())
    setName(obj["Card Name"].toString().toStdString());
if (obj.contains("Mana Cost") && obj["Mana Cost"].isDouble())
    setManaCost(static_cast<unsigned int>(obj["Mana Cost"].toInt())); //conversione
if (obj.contains("Rarity") && obj["Rarity"].isString())
    setCardRarity(StringToRarity(obj["Rarity"].toString().toStdString()));
  //  setMaxLevel(StringToRarity(obj["Rarity"].toString().toStdString()));
if (obj.contains("Level") && obj["Level"].isDouble())
    setCardLevel(static_cast<unsigned int>(obj["Level"].toInt()));
if (obj.contains("Description") && obj["Description"].isString())
    setDescription(obj["Description"].toString().toStdString());

}
