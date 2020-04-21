#ifndef SPELL_H
#define SPELL_H

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
    // costruttori
    Card();
    Card(string, unsigned int, rarity, unsigned int,string);
    Card(const Card&);

    // SET method
    void setName(string n);
    void setManaCost(unsigned int mana);
    void setCardRarity(rarity rar);
    void setCardLevel(unsigned int cLevel);
    void setDescription(string desc);
    void setMaxLevel(rarity rar);

    //GET method
    string getName() const;
    unsigned int getManaCost() const;
    rarity getCardRarity() const;
    unsigned int getCardLevel() const;
    string getDescription() const;
    unsigned int getMaxLevel() const;

    // Conversione enum<--->string
    string RarityToString() const;
    static rarity StringToRarity(std::string);


};
#endif // SPELL_H
