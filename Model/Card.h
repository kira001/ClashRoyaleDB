#ifndef CARD_H
#define CARD_H

#include <string>
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
public:
    // CONSTRUCTORS/DESTRUCTORS
    Card();
    Card(string, unsigned int, rarity, unsigned int,string);
    Card(const Card&);

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

    /*
     Metodo virtuale puro lvlUpgrade stats
     Metodo virtuale puro lvlDowngrade stats

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
#endif // CARD_H
