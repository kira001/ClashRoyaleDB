#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){


    setWindowIcon(QIcon(":/img/icon.png"));
    setFixedSize(980,620);

    mainWidget=new QWidget(this);
    infoWidget=new QWidget;
    mainLayout=new QHBoxLayout(this);

    leftLayout=new QVBoxLayout(this);
    rightLayout=new QVBoxLayout(this);
    infolayout=new QVBoxLayout;
    list = new QListWidget();
    list2 = new QListWidget();
    stackedWidget = new QStackedWidget();
    menubar= new QMenuBar();
    toolbar = new QToolBar();
    searchbox= new QLineEdit();
    completer= new QCompleter();
    menu =new QMenu("File",menubar);
    popup=new QMessageBox();


    addMenu();
    addLeftLayout();
    addRightLayout();
    setWidgetStyle();


    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow(){
}
void MainWindow::setToolBar(){
    toolbar->setMovable(false);
    QAction* save= new QAction(QIcon(":img/save.png"),QString("Save Set"));
    QAction* load=new QAction(QIcon(":img/add.png"),QString("Laad Set"));
    QAction* info=new QAction(QIcon(":img/question (1).png"),QString("About"));
    //QAction* DarkWhite=new QAction(QIcon(":img/info.png"), toolbar); //Da definire

    //Aggiungo le azioni al menu
    toolbar->addAction(load);
    toolbar->addAction(save);
    toolbar->addAction(info);
    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {loadFile();});
    connect(save, &QAction::triggered, [this] {saveFile(); });
    connect(info, &QAction::triggered, [this] {infoguide(); });
   // Aggiungo la barra al Layout
  toolbar->setFixedHeight(70);
  toolbar->addSeparator();

}





void MainWindow::resetlist(){
    if (list->count() != 0) {
        list->reset();
        list->clear();
    }
    for (unsigned int i = 0; i < container.getSize(); ++i)
   { string c=container[i]->getName()+" ["+ std::to_string(container[i]->getCardLevel())+"]";
    list->addItem(new QListWidgetItem(QString::fromStdString(c)));
    }


}
void MainWindow::infoguide(){
    QMessageBox Box;
    Box.setWindowTitle("About");
    Box.setText("\n\n Welcome to ClashRoyale v1.0");
    Box.setInformativeText("\n Developed by \n KokoGorillaTEAM \n");
    QPixmap logo = QPixmap(":/img/infobox.png");
    logo = logo.scaledToWidth(150);
    Box.setIconPixmap(logo);
    Box.setStyleSheet("background-color: rgb(30,30,30); color: rgb(246,163,5);");
    Box.exec();
}

void MainWindow::addLeftLayout(){

    QScrollArea* leftbox= new QScrollArea();
    leftbox->setWidget(list);
    leftbox->setWidgetResizable(true);
    leftbox->setFixedSize(450,400);
    leftbox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* insertButton = new QPushButton("Insert");
    QPushButton* deleteButton= new QPushButton("Delete");
    insertButton->setFixedSize(100,50);
    deleteButton->setFixedSize(100,50);


    //string NameCard="controller->getLastInsert()";

   //connect(insertButton, &QPushButton::clicked, [this] {

   //});
   // connect(deleteButton, &QPushButton::clicked, [this] {

   // });




    connect(list, &QListWidget::currentRowChanged, [this] {
      if (list->count()>0)
    {
          clearLayout(infolayout);
          viewCardInfo(list->currentRow());
          setStackedWidgetPage(1);
      }
    });



    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(deleteButton);
    searchbox->setClearButtonEnabled(true);
    searchbox->addAction(QIcon(":/img/whitesearch.png"), QLineEdit::LeadingPosition);
    searchbox->setPlaceholderText("Search");
    searchbox->setFixedSize(190,30);

   connect(searchbox, &QLineEdit::textChanged, [this] {
         if (container.getSize() > 0)
             findNameCard(searchbox->text());
              });

    leftLayout->addWidget(searchbox);
    leftLayout->addWidget(leftbox);
    leftLayout->addLayout(buttonLayout);
    mainLayout->addLayout(leftLayout);


}
void MainWindow::findNameCard(const QString& str){

    resetlist();
    for (int i = 0; i < list->count(); ++i) {
        QListWidgetItem* listItem = list->item(i);
        if (!listItem->text().toUpper().contains(str.toUpper())) {
            list->takeItem(i);
            --i;
        }

    }
}


void MainWindow::addMenu(){

    QAction* save= new QAction(QIcon(":img/add.png"),"Save Set");
    QAction* load=new QAction(QIcon(":img/save.png"), "Load Set");
    QAction* about=new QAction("About");


    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);


    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {loadFile();});
    connect(save, &QAction::triggered, [this] {saveFile(); });

    //Aggiungo il menu alla barra
    menubar->addMenu(menu);
    menubar->addAction(about);

    //seletore DarkMode



    connect(about, &QAction::triggered, [this] {infoguide(); });


    // Aggiungo la barra al Layout
    setMenuBar(menubar);
}




void MainWindow::viewCardInfo(int pos)
{

    QFrame*infoBox = new QFrame;
    infoBox->setFrameShape(QFrame::HLine);
    infoBox->setFrameShadow(QFrame::Sunken);

    //Picture+infocardBasic
    QHBoxLayout* layoutInfoTop=new QHBoxLayout(this);
    QVBoxLayout* layoutInfoBasic=new QVBoxLayout();
    QFormLayout* formLayout1 = new QFormLayout;
    unsigned int fixPos= static_cast<unsigned int>(pos);

    string cardNameLevel=container[fixPos]->getName()+" ["+ std::to_string(container[fixPos]->getCardLevel())+"]";
    QLabel* NameCard=new QLabel(QString::fromStdString(cardNameLevel));
    formLayout1->addRow("Type: ", new QLabel(QString::fromStdString(container[fixPos]->getType())));
    formLayout1->addRow("Rarity: ", new QLabel(QString::fromStdString(container[fixPos]->RarityToString())));
    formLayout1->addRow("Description: ", new QLabel(QString::fromStdString(container[fixPos]->getDescription())));


    QPixmap logo = QPixmap(":/img/testcard.png");
    logo = logo.scaledToWidth(150);
    QLabel* cardLabel=new QLabel();
    cardLabel->setPixmap(logo);

    cardLabel->setFixedSize(150,150);
    //Button Edit
    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* editButton = new QPushButton("Edit");
    editButton->setFixedSize(100,50);
    buttonLayout->addWidget(editButton);



   //info Card Base
  QFormLayout* formLayout = new QFormLayout;
  formLayout->setHorizontalSpacing(20);
  formLayout->addRow("Name Card: ", new QLabel(QString::fromStdString(container[fixPos]->getName())));
  formLayout->addRow("Level: ", new QLabel(QString::number(container[fixPos]->getCardLevel())));
  formLayout->addRow("Mana Cost: ", new QLabel(QString::number(container[fixPos]->getManaCost())));
  formLayout->addRow("Type: ", new QLabel(QString::fromStdString(container[fixPos]->getType())));
  formLayout->addRow("Rarity: ", new QLabel(QString::fromStdString(container[fixPos]->RarityToString())));
  formLayout->addRow("Description: ", new QLabel(QString::fromStdString(container[fixPos]->getDescription())));
  if(container[fixPos]->getType()=="Bulding")
  {
      Building* building = dynamic_cast<Building*>(container[fixPos].operator->());
      formLayout->addRow("Health: ", new QLabel(QString::number(building->getBuildHealth())));
      formLayout->addRow("Life Time: ", new QLabel(QString::number(building->getLifeTime())));

  }
  else if(container[fixPos]->getType()=="Spell")
  {
    Spell* spell = dynamic_cast<Spell*>(container[fixPos].operator->());
    formLayout->addRow("Damage: ", new QLabel(QString::number(spell->getSpellDamage())));
    formLayout->addRow("Crown Tower Damage: ", new QLabel(QString::number(spell->getCrownTowerDamage())));
    formLayout->addRow("Radius: ", new QLabel(QString::number(spell->getRadius())));
  }
  else if(container[fixPos]->getType()=="Troop"){
      Troop* troop = dynamic_cast<Troop*>(container[fixPos].operator->());
          formLayout->addRow("Shield: ", new QLabel(QString::number(troop->getShield())));
          formLayout->addRow("Health: ", new QLabel(QString::number(troop->getTroopHealth())));
          formLayout->addRow("Hit Per Second: ", new QLabel(QString::number(troop->getHitxSec())));
          formLayout->addRow("Damage Per Second: ", new QLabel(QString::number(troop->getDamagexSec())));
          formLayout->addRow("Spawn Death Damage: ", new QLabel(QString::number(troop->getSpawnDD())));
          formLayout->addRow("Range: ", new QLabel(QString::number(troop->getRange())));
          formLayout->addRow("Count: ", new QLabel(QString::number(troop->getCount())));
      }
  else if(container[fixPos]->getType()=="Attacking Building"){
      AttackingBuilding* attackingBuilding = dynamic_cast<AttackingBuilding*>(container[fixPos].operator->());
      formLayout->addRow("Health: ", new QLabel(QString::number(attackingBuilding->getBuildHealth())));
      formLayout->addRow("Life Time: ", new QLabel(QString::number(attackingBuilding->getLifeTime())));
      formLayout->addRow("Hit Per Second: ", new QLabel(QString::number(attackingBuilding->getHitPerSecond())));
      formLayout->addRow("Damage Per Second: ", new QLabel(QString::number(attackingBuilding->getDamagePerSecond())));
      formLayout->addRow("Range: ", new QLabel(QString::number(attackingBuilding->getRange())));
    }
  else if(container[fixPos]->getType()=="Building-Troop Spawner"){
      BuildingTroopSpawner* buildingTroopSpawner = dynamic_cast<BuildingTroopSpawner*>(container[fixPos].operator->());
      formLayout->addRow("Building Health: ", new QLabel(QString::number(buildingTroopSpawner->getBuildHealth())));
      formLayout->addRow("Troop Health: ", new QLabel(QString::number(buildingTroopSpawner->getTroopHealth())));
      formLayout->addRow("Life Time: ", new QLabel(QString::number(buildingTroopSpawner->getLifeTime())));
      formLayout->addRow("Spawn Speed: ", new QLabel(QString::number(buildingTroopSpawner->getSpawnSpeed())));
      formLayout->addRow("Shield: ", new QLabel(QString::number(buildingTroopSpawner->getShield())));
      formLayout->addRow("Hit Per Second: ", new QLabel(QString::number(buildingTroopSpawner->getHitxSec())));
      formLayout->addRow("Damage Per Second: ", new QLabel(QString::number(buildingTroopSpawner->getDamagexSec())));
      formLayout->addRow("Spawn Death Damage: ", new QLabel(QString::number(buildingTroopSpawner->getSpawnDD())));
      formLayout->addRow("Range: ", new QLabel(QString::number(buildingTroopSpawner->getRange())));
      formLayout->addRow("Count: ", new QLabel(QString::number(buildingTroopSpawner->getCount())));
            }
  else if(container[fixPos]->getType()=="Spell-Troop Spawner"){
       SpellTroopSpawner* spellTroopSpawner = dynamic_cast<SpellTroopSpawner*>(container[fixPos].operator->());

       formLayout->addRow("Damage: ", new QLabel(QString::number(spellTroopSpawner->getSpellDamage())));
       formLayout->addRow("Crown Tower Damage: ", new QLabel(QString::number(spellTroopSpawner->getCrownTowerDamage())));
       formLayout->addRow("Radius: ", new QLabel(QString::number(spellTroopSpawner->getRadius())));
       formLayout->addRow("Shield: ", new QLabel(QString::number(spellTroopSpawner->getShield())));
       formLayout->addRow("Health: ", new QLabel(QString::number(spellTroopSpawner->getTroopHealth())));
       formLayout->addRow("Hit Per Second: ", new QLabel(QString::number(spellTroopSpawner->getHitxSec())));
       formLayout->addRow("Damage Per Second: ", new QLabel(QString::number(spellTroopSpawner->getDamagexSec())));
       formLayout->addRow("Spawn Death Damage: ", new QLabel(QString::number(spellTroopSpawner->getSpawnDD())));
       formLayout->addRow("Range: ", new QLabel(QString::number(spellTroopSpawner->getRange())));
       formLayout->addRow("Count: ", new QLabel(QString::number(spellTroopSpawner->getCount())));
       formLayout->addRow("Time Spawn: ", new QLabel(QString::number(spellTroopSpawner->getCount())));

      }
  else if(container[fixPos]->getType()=="TroopSpawner"){
    TroopSpawner* troopSpawner = dynamic_cast<TroopSpawner*>(container[fixPos].operator->());
    formLayout->addRow("Shield: ", new QLabel(QString::number(troopSpawner->getShield())));
    formLayout->addRow("Health: ", new QLabel(QString::number(troopSpawner->getTroopHealth())));
    formLayout->addRow("Hit Per Second: ", new QLabel(QString::number(troopSpawner->getHitxSec())));
    formLayout->addRow("Damage Per Second: ", new QLabel(QString::number(troopSpawner->getDamagexSec())));
    formLayout->addRow("Spawn Death Damage: ", new QLabel(QString::number(troopSpawner->getSpawnDD())));
    formLayout->addRow("Range: ", new QLabel(QString::number(troopSpawner->getRange())));
    formLayout->addRow("Count: ", new QLabel(QString::number(troopSpawner->getCount())));
    formLayout->addRow("Time and Description: ", new QLabel(QString::fromStdString(troopSpawner->getTimeDesc())));
      }
  layoutInfoBasic->addWidget(NameCard);
  layoutInfoBasic->addLayout(formLayout1);
  layoutInfoTop->addWidget(cardLabel);
  layoutInfoTop->addLayout(layoutInfoBasic);
  infoBox->setLayout(layoutInfoTop);
  infolayout->addLayout(layoutInfoTop);
  infolayout->addWidget(infoBox);
  infolayout->addLayout(layoutInfoTop);
  infolayout->addLayout(formLayout);
  infolayout->addLayout(buttonLayout);
  //infolayout->addStretch();


  }


void MainWindow::addRightLayout(){


    basicInfoWidget();
    infoWidget->setLayout(infolayout);
    stackedWidget->addWidget(infoWidget);
    //addInsertWidget();
    rightLayout->addWidget(stackedWidget);
    mainLayout->addLayout(rightLayout);

}

void MainWindow::loadFile(){
    QString fileName = QFileDialog::getOpenFileName(this->menu, tr("Open File"), ".../Load&Save", tr("JSON files (*.json)"));
        if (!fileName.isEmpty()) {
            if (!fileName.endsWith(".json")) {
                QMessageBox msgBox;
                msgBox.setText("Invalid format. Please select a .json file.");
                msgBox.exec();
            }
            else {
                QFile loadFile(fileName);
                loadFile.open(QIODevice::ReadOnly);
                QByteArray dataArray = loadFile.readAll();
                loadFile.close();
                QJsonDocument docJson = QJsonDocument::fromJson(dataArray);
                QJsonArray arrayJson = docJson.array();
                if (arrayJson.isEmpty()) {
                    QMessageBox msgBox;
                    msgBox.setText("The file is empty.");
                    msgBox.exec();
                }
                else {
                    if (container.getSize() != 0)
                                       container.clear();
                                       unsigned int count=0;//test stampa su list
                    foreach (const QJsonValue& value, arrayJson) {
                                        QJsonObject obj = value.toObject();if (obj.contains("Type") && obj["Type"].isString()) {
                                            QString type = obj["Type"].toString();
                                            DeepPtr<Card> card;
                                            if (type == "Spell") card = new Spell(); //Switch case ??
                                            else if (type == "Troop") card = new Troop();
                                            else if (type == "Building") card = new Building();
                                            else if (type == "Building Troop Spawner") card = new BuildingTroopSpawner();
                                            else if (type == "Spell-Troop Spawner") card = new SpellTroopSpawner();
                                            else if (type == "Attacking Building") card = new AttackingBuilding();
                                            else if (type == "TroopSpawner") card = new TroopSpawner();
                                            card->readJson(obj);
                                            container.insert(card);
                                            string cardList=container[count]->getName()+" ["+ std::to_string(container[count]->getCardLevel())+"]";
                                            list->addItem(new QListWidgetItem(QString::fromStdString(cardList)));
                                            count++;
                                                                                  }
                               }
                    clearLayout(infolayout);
                    resetlist();
                      }
              }

        }
}

void MainWindow::saveFile() const{
     if (container.getSize() != 0) {
        QString fileName = QFileDialog::getSaveFileName(this->menu, tr("Save File"), ".../Load&Save", tr("JSON files (*.json)"));
        if (!fileName.endsWith(".json"))
            fileName.append(".json");
        QJsonArray arrayJson;
       //ciclo il container e faccio il push sull Json
        for (unsigned int i = 0; i < container.getSize(); ++i)
        arrayJson.push_back(QJsonValue(container[i]->writeJson()));
        QJsonDocument docJson(arrayJson);
        QString docString = docJson.toJson();
        QFile saveFile(fileName);
        saveFile.open(QIODevice::WriteOnly);
        saveFile.write(docString.toUtf8());
        saveFile.close();
     }
    else {
        QMessageBox msgBox;
        msgBox.setText("The container is empty.");
        msgBox.exec();
    }
}




void MainWindow::setWidgetStyle()
{
    mainLayout->setSpacing(6);
    // Imposto le dimensioni
   setMaximumSize(QSize(1200,800));
   //setMinimumSize(QSize(800,500));
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //Imposto il foglio di stile
  QFile file(":/Style/test.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}



void MainWindow::basicInfoWidget() //Pagina Iniziale
{
    QPixmap logo = QPixmap(":/img/background.png");
    logo = logo.scaledToWidth(450);
    QLabel* logoLabel = new QLabel;
    logoLabel->setPixmap(logo);
    logoLabel->setStyleSheet("margin-bottom: 2em");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(logoLabel);
    QWidget* basicInfo=new QWidget();
    basicInfo->setLayout(layout);
    stackedWidget->addWidget(basicInfo);

}

// MainWindow::CardView(string s){
  //  std::cout<<NameCard;

    //list->addItem(new QListWidgetItem(QString::fromStdString(s)));
//}


int MainWindow::searchItem(int row)
{

    QListWidgetItem* listItem = list->item(row);
    string charName = listItem->text().toStdString();
    unsigned int cont=container.getSize();
    while(cont){
       if (container[cont]->getName() == charName)
         {return static_cast<int>(cont);}
     }

     return -1;
}




void MainWindow::clearLayout(QLayout* layout){
    while(layout->count() > 0){
        QLayoutItem* item = layout->takeAt(0);
        if(QWidget* widget = item->widget()){
            widget->deleteLater();
        }
        else if (QLayout* innerLayout = item->layout()) {
            clearLayout(innerLayout);
        }
        delete item;
    }
}


void MainWindow::setStackedWidgetPage(int index)
{
    stackedWidget->setCurrentIndex(index);
}
