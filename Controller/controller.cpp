#include "controller.h"


Controller::Controller(Container<DeepPtr<Card>> m, QObject* parent)
        : QObject(parent), view(nullptr), model(m) {}

void Controller::setView(MainWindow* v) { view = v; }

string Controller::getLastInsert() const
{
    return model[model.getSize()]->getName();
}

void Controller::addCard()
{
    SpellTroopSpawner* stp=new SpellTroopSpawner("Koko",10,Card::StringToRarity("Comune"),1,"koko is a gorilla!!!!",
                             500,300,3,20,700,1.5,89,20,5,2,"Every 7 Seconds");
    model.insert(stp);
    std::cout<<model[model.getSize()]->getName();
  //  view->addCardView();
}


