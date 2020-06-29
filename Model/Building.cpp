#include "Building.h"
#include "myexception.h"
double Building::getBuildHealth() const{
    return buildHealth;
}

void Building::setBuildHealth(double bHealth){
    buildHealth = bHealth;
}

double Building::getLifeTime() const{
    return lifeTime;
}

void Building::setLifeTime(double lTime){
    lifeTime = lTime;
}
string Building::getType() const{return "Building";}
void Building::lvlUpgrade(){
    if(Card::isUpgradable()){
        Card::lvlUpgrade();
        upgradeStats();
    }

}

void Building::lvlDowngrade(){
    if(Card::isDowngradable()){
        downgradeStats();
        Card::lvlDowngrade();
    }
}

Building* Building::clone() const{
    return new Building(*this);
}


void Building::upgradeStats(){
    buildHealth= (buildHealth*(100+7*Card::getCardLevel()))/100;
}

void Building::downgradeStats(){
    buildHealth= (buildHealth*100/(100+7*Card::getCardLevel()));
}


QJsonObject Building::writeJson() const
{
    QJsonObject bJson=Card::writeJson();
    bJson["Type"] = QString::fromStdString(getType());
    bJson["Build Health"] = getBuildHealth();
    bJson["Life Time"] = getLifeTime();
    return bJson;

}

void Building::readJson(const QJsonObject &obj)
{    Card::readJson(obj);

    if (obj.contains("Build Health") && obj["Build Health"].isDouble())
        setBuildHealth(obj["Build Health"].toDouble());
    if (obj.contains("Life Time") && obj["Life Time"].isDouble())
        setLifeTime(obj["Life Time"].toDouble());
}



Building::Building(std::string p, std::string n, unsigned int mana, Card::rarity rar, unsigned int cLevel, std::string desc, double bHealth, double lTime):
    Card(p,n,mana,rar,cLevel,desc), buildHealth(bHealth), lifeTime(lTime){}

Building::Building(const Building &b): Card(b), buildHealth(b.getBuildHealth()), lifeTime(b.getLifeTime()){}
