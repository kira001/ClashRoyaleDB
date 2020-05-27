#include "Card.h"

/******************** CONSTRUCTORS/DESTRUCTORS  ********************/
Card::Card(string n, unsigned int mana, rarity rar, unsigned int cLevel,string desc):
           name(n),manaCost(mana),cardRarity(rar),cardLevel(cLevel),description(desc)
           {Card::setMaxLevel(rar);}

Card::Card(const Card& c):
           name(c.getName()),manaCost(c.getManaCost()),cardRarity(c.getCardRarity()),cardLevel(c.getCardLevel()),description(c.getDescription()){}

/******************** GETTERS/SETTERS ********************/

//GETTERS
string Card::getName() const{ return name; }
unsigned int Card::getManaCost() const { return manaCost; }
Card::rarity Card::getCardRarity() const { return cardRarity; }
unsigned int Card::getCardLevel() const { return cardLevel; }
string Card::getDescription() const{ return description; }
unsigned int Card::getMaxLevel() const{ return MaxLevel; }

//SETTERS
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
         case Card::rarity::common:return "Comune";
         case Card::rarity::rare:return "Rara";
         case Card::rarity::epic:return "Epica";
         case Card::rarity::legendary:return "Leggendaria";
       }
}

Card::rarity Card::StringToRarity(string sRar){
    if(sRar=="Comune") return Card::rarity::common;
    if(sRar=="Rara") return Card::rarity::rare;
    if(sRar=="Epica") return Card::rarity::epic;
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

QJsonObject Card::serializeJson() const
{
    QJsonObject cardJson;
    cardJson["Card Name"] = QString::fromStdString(getName());
    cardJson["Mana Cost"] = static_cast<int>(getManaCost()); //conversione unsigned int -> int
    cardJson["Rarity"] = QString::fromStdString(RarityToString());
    //cardJson["level"] = static_cast<int>(getCardLevel()); //Non lo usiamo perchè usiamo i tasti + e -
    cardJson["Type"] = QString::fromStdString(getType());
    cardJson["Description"] = QString::fromStdString(getDescription());
    return cardJson;

}

void Card::deserializeJson(const QJsonObject& obj)
{
if (obj.contains("Card Name") && obj["Card Name"].isString())
    setName(obj["Card Name"].toString().toStdString());
if (obj.contains("Mana Cost") && obj["Mana Cost"].isDouble())
    setManaCost(static_cast<unsigned int>(obj["Mana Cost"].toInt())); //conversione
if (obj.contains("Rarity") && obj["Rarity"].isString())
    setCardRarity(StringToRarity(obj["Rarity"].toString().toStdString()));
    setMaxLevel(StringToRarity(obj["Rarity"].toString().toStdString()));
//if (obj.contains("level") && obj["level"].isDouble()) // non settiamo il livello
  //  setLevel(obj["level"].toInt());
if (obj.contains("Dscription") && obj["Description"].isString())
    setDescription(obj["Description"].toString().toStdString());

}



