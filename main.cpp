#include <iostream>
#include <math.h>
#include "Model/Card.h"
#include "Model/Spell.h"
#include "Model/SpellTroopSpawner.h"
int main(){

 Spell s("Koko",10,Card::StringToRarity("Comune"),1,"koko is a gorilla!!!!",500,300,3);

for(int i=0;i<13;i++){
    std::cout<<"INFO CARTA UP----------------------\n";
    std::cout<<s.getCardLevel()<<"\n";
    std::cout<<floor(s.getSpellDamage())<<"\n";
    std::cout<<s.getCrownTowerDamage()<<"\n";
     s.lvlUpgrade();
}
for(int i=0;i<13;i++){
    std::cout<<"INFO CARTA DOWN----------------------\n";
    std::cout<<s.getCardLevel()<<"\n";
    std::cout<<floor(s.getSpellDamage())<<"\n";
    std::cout<<s.getCrownTowerDamage()<<"\n";
     s.lvlDowngrade();
}
 /* std::cout<<s.getName()<<"\n";
  std::cout<<s.getManaCost()<<"\n";
  std::cout<<s.RarityToString()<<"\n";
  std::cout<<s.getCardLevel()<<"\n";
  std::cout<<s.getMaxLevel()<<"\n";
  std::cout<<s.getDescription()<<"\n";
  std::cout<<s.getSpellDamage()<<"\n";
  std::cout<<s.getCrownTowerDamage()<<"\n";
  std::cout<<s.getRadius()<<"\n";


  std::cout<<"\nAumento di livello\n";
  std::cout<<s.getName()<<"\n";
  std::cout<<s.getManaCost()<<"\n";
  std::cout<<s.RarityToString()<<"\n";
  std::cout<<s.getCardLevel()<<"\n";
  std::cout<<s.getMaxLevel()<<"\n";
  std::cout<<s.getDescription()<<"\n";
  std::cout<<s.getSpellDamage()<<"\n";
  std::cout<<s.getCrownTowerDamage()<<"\n";
  std::cout<<s.getRadius()<<"\n";

  s.lvlDowngrade();
  std::cout<<"\nDowngrade di livello\n";
  std::cout<<s.getName()<<"\n";
  std::cout<<s.getManaCost()<<"\n";
  std::cout<<s.RarityToString()<<"\n";
  std::cout<<s.getCardLevel()<<"\n";
  std::cout<<s.getMaxLevel()<<"\n";
  std::cout<<s.getDescription()<<"\n";
  std::cout<<s.getSpellDamage()<<"\n";
  std::cout<<s.getCrownTowerDamage()<<"\n";
  std::cout<<s.getRadius()<<"\n";*/

   /*SpellTroopSpawner stp("Koko",10,Card::StringToRarity("Comune"),1,"koko is a gorilla!!!!",
                         500,300,3,20,700,1.5,89,20,5,2,"Every 7 Seconds");

   for(int i=0;i<13;i++){
       std::cout<<"INFO CARTA UP----------------------\n";
       std::cout<<"Name "<<stp.getName()<<"\n";
       std::cout<<"cLevel "<<stp.getCardLevel()<<"\n";
       std::cout<<"spellDamage "<<floor(stp.getSpellDamage())<<"\n";
       std::cout<<"Crown TDm "<<floor(stp.getCrownTowerDamage())<<"\n";
       std::cout<<"Shield "<<floor(stp.getShield())<<"\n";
       std::cout<<"Health "<<stp.getTroopHealth()<<"\n";
       std::cout<<"HitxSec "<<stp.getHitxSec()<<"\n";
       std::cout<<"DamagexSec "<<floor(stp.getDamagexSec())<<"\n";
       std::cout<<"SpawnDD "<<floor(stp.getSpawnDD())<<"\n";
       std::cout<<"Range "<<stp.DimRange()<<"\n";
       std::cout<<"Damage "<<stp.damage()<<"\n";

        stp.lvlUpgrade();
   }
   for(int i=0;i<13;i++){
       std::cout<<"INFO CARTA DOWN----------------------\n";
       std::cout<<"Name "<<stp.getName()<<"\n";
       std::cout<<"cLevel "<<stp.getCardLevel()<<"\n";
       std::cout<<"spellDamage "<<floor(stp.getSpellDamage())<<"\n";
       std::cout<<"Crown TDm "<<floor(stp.getCrownTowerDamage())<<"\n";
       std::cout<<"Shield "<<floor(stp.getShield())<<"\n";
       std::cout<<"Health "<<floor(stp.getTroopHealth())<<"\n";
       std::cout<<"HitxSec "<<floor(stp.getHitxSec())<<"\n";
       std::cout<<"DamagexSec "<<floor(stp.getDamagexSec())<<"\n";
       std::cout<<"SpawnDD "<<floor(stp.getSpawnDD())<<"\n";
       std::cout<<"Range "<<stp.DimRange()<<"\n";
       std::cout<<"Damage "<<stp.damage()<<"\n";

        stp.lvlDowngrade();
   }*/
   /*

       std::cout<<"INFO CARTA UP----------------------\n";
       std::cout<<stp.getName()<<"\n";

       std::cout<<stp.getCardLevel()<<"\n";
       std::cout<<floor(stp.getSpellDamage())<<"\n";
       std::cout<<stp.getCrownTowerDamage()<<"\n";
       std::cout<<stp.getDamagexSec()<<"\n";
       std::cout<<stp.getTimeSpawn()<<"\n";

       stp.lvlUpgrade();

       std::cout<<stp.getCardLevel()<<"\n";
       std::cout<<floor(stp.getSpellDamage())<<"\n";
       std::cout<<stp.getCrownTowerDamage()<<"\n";
       std::cout<<floor(stp.getDamagexSec())<<"\n";
       std::cout<<stp.getTimeSpawn()<<"\n";
       stp.lvlDowngrade();

       std::cout<<stp.getCardLevel()<<"\n";
       std::cout<<floor(stp.getSpellDamage())<<"\n";
       std::cout<<stp.getCrownTowerDamage()<<"\n";
       std::cout<<floor(stp.getDamagexSec())<<"\n";
       std::cout<<stp.getTimeSpawn()<<"\n";
*/

}
