#ifndef CARD_H
#define CARD_H

#include <iostream>

#include <string>


#include <QString> //In questa classe non viene usato 
#include <QJsonArray> ////In questa classe non viene usato 
#include <QJsonDocument>
#include <QJsonObject>

using std::string;
class Card
{
public:
    enum rarity{common,rare,epic,legendary};
private:
    string path;
    string name;
    unsigned int manaCost;
    rarity cardRarity;
    unsigned int cardLevel;
    string description;
    const unsigned int MaxLevel=13;

    void controlRarityLevel(unsigned int cLevel) const;
public:
    // CONSTRUCTORS/DESTRUCTORS
    Card()=default;
    Card(string, string, unsigned int, rarity, unsigned int,string);
    Card(const Card&);
    virtual ~Card() = default;

    // SETTERS
    void setPath(string p);
    void setName(string n);
    void setManaCost(unsigned int mana);
    void setCardRarity(rarity rar);
    void setCardLevel(unsigned int cLevel);
    void setDescription(string desc);
    // GETTERs
    string getPath() const;
    string getName() const;
    unsigned int getManaCost() const;
    rarity getCardRarity() const;
    unsigned int getCardLevel() const;
    string getDescription() const;
    unsigned int getMaxLevel() const;


    // CONVERSION ENUM<--->STRING
    string RarityToString() const;
    static rarity StringToRarity(std::string);

    // METHODS
    virtual void lvlUpgrade();
    virtual void lvlDowngrade();
    bool isUpgradable() const;
    bool isDowngradable() const;
    virtual string getType() const = 0; // Controllo il tipo -> Troop,Spell,Building ecc

    virtual Card* clone() const = 0;
    virtual QJsonObject writeJson() const;
    virtual void readJson(const QJsonObject& obj);

};

#endif // CARD_H
