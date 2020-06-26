#include "Card.h"
#include "myexception.h"
/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Card::Card(string p,string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc):
           path(p),name(n),manaCost(mana),cardRarity(rar),cardLevel(cLevel),description(desc)
           {
            Card::setMaxLevel(rar);
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
void Card::setCardRarity(Card::rarity rar){ cardRarity=rar;  Card::setMaxLevel(rar); }
void Card::setCardLevel(unsigned int cLevel){ cardLevel=cLevel; }
void Card::setDescription(string desc){ description=desc; }
void Card::setMaxLevel(Card::rarity rar){
    switch (rar)
       {
         case Card::rarity::common: MaxLevel=13; break;
         case Card::rarity::rare: MaxLevel=11;break;
         case Card::rarity::epic: MaxLevel=8;break;
         case Card::rarity::legendary: MaxLevel=5;break;
       }
}



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
    if(sRar=="Rare") return Card::rarity::rare;
    if(sRar=="Epic") return Card::rarity::epic;
    return Card::rarity::legendary;
}

/************************ METHODS **************************/
void Card::lvlUpgrade(){
    if(cardLevel<MaxLevel){
        cardLevel++;
    }
    else{
        // qui potremmo mettere una exception al posto del cout ovviamente
        std::cout<<"Livello massimo raggiunto";
    }
}
void Card::lvlDowngrade(){
    if(cardLevel>1){
        cardLevel--;
    }
    else{
        // qui potremmo mettere una exception al posto del cout ovviamente
        std::cout<<"Livello minimo raggiunto";
    }
}

void Card::controlRarityLevel(rarity rar,unsigned int cLevel) const{
    switch (rar)
       {
         case Card::rarity::common:{
            if(cLevel>13){
                throw MyException("Max level is 13 for a common");
            }
            break;
         }
         case Card::rarity::rare:{
                if(cLevel>11){
                    throw MyException("Max level is 11 for a rare");
                }
                break;
         }
         case Card::rarity::epic:{
            if(cLevel>8){
                throw MyException("Max level is 8 for a epic");
            }
            break;
         }
         case Card::rarity::legendary: {
            if(cLevel>5){
                throw MyException("Max level is 5 for a legendary");
            }
            break;
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
    setMaxLevel(StringToRarity(obj["Rarity"].toString().toStdString()));
if (obj.contains("Level") && obj["Level"].isDouble())
    setCardLevel(static_cast<unsigned int>(obj["Level"].toInt()));
if (obj.contains("Description") && obj["Description"].isString())
    setDescription(obj["Description"].toString().toStdString());

}
