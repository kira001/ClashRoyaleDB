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
    string name;
    unsigned int manaCost;
    rarity cardRarity;
    unsigned int cardLevel;
    string description;
    unsigned int MaxLevel;

     void setMaxLevel(rarity rar);
    void controlRarityLevel(rarity rar ,unsigned int cLevel) const;
public:
    // CONSTRUCTORS/DESTRUCTORS
    Card()=default;
    Card(string, unsigned int, rarity, unsigned int,string);
    Card(const Card&);
    virtual ~Card() = default;

    // SETTERS
    void setName(string n);
    void setManaCost(unsigned int mana);
    void setCardRarity(rarity rar);
    void setCardLevel(unsigned int cLevel);
    void setDescription(string desc);

    // GETTERs
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

    virtual string getType() const = 0; // Controllo il tipo -> Troop,Spell,Building ecc

    virtual Card* clone() const = 0;
    virtual QJsonObject writeJson() const;
    virtual void readJson(const QJsonObject& obj);

/*
     aggiungere le variabili con solo :
        -string timeSpawn;
        - unsigned int maxSpawned;
     di conseguenza aggiornare i cotruttori e metodi
     Distruttori
     Operatori
     Clone
     Gestore dei Json
    */
};

//unsigned int Card::MaxLevel=13;
#endif // CARD_H
