#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "MainWindow.h"
#include "Model/Card.h"
#include "Template/container.h"
#include "Template/deepptr.h"
#include "Model/SpellTroopSpawner.h"
class Controller : public QObject {
    Q_OBJECT

private:
   MainWindow* view;
   Container<DeepPtr<Card>> model;
public slots:

   void addCard();
public:
   explicit Controller(Container<DeepPtr<Card>> card, QObject *parent = nullptr);
   void setView(MainWindow* v);
   string getLastInsert()const;
};

#endif  // CONTROLLER_H
