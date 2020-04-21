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
    void setMaxLevel(rarity rar);
    // GETTERs
    string getName() const;
    unsigned int getManaCost() const;
    rarity getCardRarity() const;
    unsigned int getCardLevel() const;
    string getDescription() const;
    unsigned int getMaxLevel() const;
    // CONVESION ENUM<--->STRING
    string RarityToString() const;
    static rarity StringToRarity(std::string);


};
#endif // CARD_H
