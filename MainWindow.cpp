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
    searchbox= new QLineEdit();
    completer= new QCompleter();
    menu =new QMenu("File",menubar);
    popup=new QMessageBox();
    insertWidget=new QWidget();
    filterTypeBox=new QComboBox();
    filterRarityBox=new QComboBox();


    addMenu();
    addLeftLayout();
    addRightLayout();
    setWidgetStyle();


    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow(){
}



void MainWindow::resetlist(){
    if (list->count() != 0) {
        list->reset();
        list->clear();
    }
    for (unsigned int i = 0; i < container.getSize(); ++i)
   {
    //crasha tutttooooo
    //string cardList=container[i]->getName()+" ["+ std::to_string(container[i]->getCardLevel())+"]";
    //list->addItem(new QListWidgetItem(QString::fromStdString(cardList)));
    string c=container[i]->getName();
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
    QHBoxLayout* searchLayout= new QHBoxLayout(this);

    connect(list, &QListWidget::currentRowChanged, [this] {
      if (list->count()>0)
    {
          clearLayout(infolayout);
          viewCardInfo(findListItemInContainer(list->currentRow()));
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
             combineSearchAndFilter(searchbox->text(),filterTypeBox->currentText(), filterRarityBox->currentText() );
              });
   connect(insertButton, &QPushButton::clicked, [this] {
      setStackedWidgetPage(2);
   });
   connect(deleteButton, &QPushButton::clicked, [this] {
       if (list->count() > 0 && list->currentRow() != -1) {
           container.remove(findListItemInContainer(list->currentRow()));
           list->takeItem(list->currentRow());
       }
   });

   filterTypeBox->addItem("All");
   filterTypeBox->addItem("Spell");
   filterTypeBox->addItem("Troop");
   filterTypeBox->addItem("Building");
   filterTypeBox->addItem("Attacking Building");
   filterTypeBox->addItem("Building-Troop Spawner");
   filterTypeBox->addItem("Spell-Troop Spawner");
   filterTypeBox->addItem("Troop Spawner");
   connect(filterTypeBox, &QComboBox::currentTextChanged,[this]{
           if(container.getSize()>0)
          combineSearchAndFilter(searchbox->text(),filterTypeBox->currentText(), filterRarityBox->currentText() );
   });


   filterRarityBox->addItem("All");
   filterRarityBox->addItem("Comune");
   filterRarityBox->addItem("Rara");
   filterRarityBox->addItem("Epica");
   filterRarityBox->addItem("Leggendaria");
   connect(filterRarityBox, &QComboBox::currentTextChanged,[this]{
       if(container.getSize()>0)
           combineSearchAndFilter(searchbox->text(),filterTypeBox->currentText(), filterRarityBox->currentText() );
   });
   /* TEST PER I FILTRI
   DeepPtr<Card> spell= new Spell("Spell1",10,Card::StringToRarity("Comune"),1,"koko is a gorilla!!!!",500,300,3);
   DeepPtr<Card> spell2= new Spell("Spell2",10,Card::StringToRarity("Rara"),1,"koko is a gorilla!!!!",500,300,3);
   DeepPtr<Card> build= new Building("building",10,Card::StringToRarity("Rara"),1,"koko is a gorilla!!!!",500,300);
   DeepPtr<Card> build2= new Building("bulding2",10,Card::StringToRarity("Rara"),1,"koko is a gorilla!!!!",500,300);
   DeepPtr<Card> build3= new Building("bulding3",10,Card::StringToRarity("Leggendaria"),1,"koko is a gorilla!!!!",500,300);
   container.insert(spell);
   container.insert(spell2);
   container.insert(build);
   container.insert(build2);
   container.insert(build3);
   resetlist();
   */


    filterTypeBox->setFixedSize(150,30);
    filterRarityBox->setFixedSize(80,30);
    searchLayout->addWidget(searchbox);
    searchLayout->addWidget(filterTypeBox);
    searchLayout->addWidget(filterRarityBox);
    leftLayout->addLayout(searchLayout);
    leftLayout->addWidget(leftbox);
    leftLayout->addLayout(buttonLayout);
    mainLayout->addLayout(leftLayout);


}
void MainWindow::findNameCard(const QString& str){


    for (int i = 0; i < list->count(); ++i) {
        QListWidgetItem* listItem = list->item(i);
        if (!listItem->text().toUpper().contains(str.toUpper())) {
            list->takeItem(i);
            --i;
        }

    }
}


void MainWindow::addMenu(){

    QAction* save= new QAction(QIcon(":img/add.png"),"Save Set", this);
    QAction* load=new QAction(QIcon(":img/save.png"), "Load Set", this);
    QAction* about=new QAction("About", this);


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
 if(pos!=-1){
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

  }


void MainWindow::addRightLayout(){

    basicInfoWidget();
    infoWidget->setLayout(infolayout);
    stackedWidget->addWidget(infoWidget);
    addInsertWidget();
    rightLayout->addWidget(stackedWidget);
    mainLayout->addLayout(rightLayout);

}

void MainWindow::addInsertWidget()
{
    //Icone
    QPixmap cardIcon= QPixmap(":/img/insertIcon/cardType.png");
    QLabel* cardLabel= new QLabel();
    cardLabel->setPixmap(cardIcon);

    QPixmap nameIcon= QPixmap(":/img/insertIcon/name.png");
    QLabel* nameLabel= new QLabel();
    nameLabel->setPixmap(nameIcon);

    QPixmap manaCostIcon= QPixmap(":/img/insertIcon/manaCost.png");
    QLabel* manaCostLabel= new QLabel();
    manaCostLabel->setPixmap(manaCostIcon);

    QPixmap cardRarityIcon= QPixmap(":/img/insertIcon/rarity.png");
    QLabel* cardRarityLabel= new QLabel();
    cardRarityLabel->setPixmap(cardRarityIcon);

    QPixmap cardLevelIcon= QPixmap(":/img/insertIcon/level.png");
    QLabel* cardLevelLabel= new QLabel();
    cardLevelLabel->setPixmap(cardLevelIcon);

    QPixmap descIcon= QPixmap(":/img/insertIcon/description.png");
    QLabel* descLabel= new QLabel();
    descLabel->setPixmap(descIcon);

    /***************    TROOP ICON    *****************/
    QPixmap shieldTroopIcon= QPixmap(":/img/insertIcon/shield.png");
    QLabel* shieldTroopLabel= new QLabel();
    shieldTroopLabel->setPixmap(shieldTroopIcon);

    QPixmap healthTroopIcon= QPixmap(":/img/insertIcon/health.png");
    QLabel* healthTroopLabel= new QLabel();
    healthTroopLabel->setPixmap(healthTroopIcon);

    QPixmap hitPerSecondTroopIcon= QPixmap(":/img/insertIcon/hitPerSecond.png");
    QLabel* hitPerSecondTroopLabel= new QLabel();
    hitPerSecondTroopLabel->setPixmap(hitPerSecondTroopIcon);

    QPixmap damagePerSecondTroopIcon= QPixmap(":/img/insertIcon/damagePerSecond.png");
    QLabel* damagePerSecondTroopLabel= new QLabel();
    damagePerSecondTroopLabel->setPixmap(damagePerSecondTroopIcon);

    QPixmap spawnDDTroopIcon= QPixmap(":/img/insertIcon/spawnDD.png");
    QLabel* spawnDDTroopLabel= new QLabel();
    spawnDDTroopLabel->setPixmap(spawnDDTroopIcon);

    QPixmap rangeTroopIcon= QPixmap(":/img/insertIcon/range.png");
    QLabel* rangeTroopLabel= new QLabel();
    rangeTroopLabel->setPixmap(rangeTroopIcon);

    QPixmap countTroopIcon= QPixmap(":/img/insertIcon/count.png");
    QLabel* countTroopLabel= new QLabel();
    countTroopLabel->setPixmap(countTroopIcon);

    /***************    SPELL ICON    *****************/
    QPixmap dmgSpellIcon= QPixmap(":/img/insertIcon/dmg.png");
    QLabel* dmgSpellLabel= new QLabel();
    dmgSpellLabel->setPixmap(dmgSpellIcon);

    QPixmap crownTowerDmgSpellIcon= QPixmap(":/img/insertIcon/crownTowerDamage.png");
    QLabel* crownTowerDmgSpellLabel= new QLabel();
    crownTowerDmgSpellLabel->setPixmap(crownTowerDmgSpellIcon);

    QPixmap radiusSpellIcon= QPixmap(":/img/insertIcon/radius.png");
    QLabel* radiusSpellLabel= new QLabel();
    radiusSpellLabel->setPixmap(radiusSpellIcon);

    /***************    BUILDING ICON    *****************/
    QPixmap healthBuildingIcon= QPixmap(":/img/insertIcon/health.png");
    QLabel* healthBuildingLabel= new QLabel();
    healthBuildingLabel->setPixmap(healthBuildingIcon);

    QPixmap lifeTimeBuildingIcon= QPixmap(":/img/insertIcon/lifeTime.png");
    QLabel* lifeTimeBuildingLabel= new QLabel();
    lifeTimeBuildingLabel->setPixmap(lifeTimeBuildingIcon);

    /***************    TROOP-SPAWNER ICON    *****************/
    QPixmap spawnTimeTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
    QLabel* spawnTimeTroopSpawnerLabel= new QLabel();
    spawnTimeTroopSpawnerLabel->setPixmap(spawnTimeTroopSpawnerIcon);

    /***************    SPELL-TROOP-SPAWNER ICON    *****************/
    QPixmap spawnTimeSpellTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
    QLabel* spawnTimeSpellTroopSpawnerLabel= new QLabel();
    spawnTimeSpellTroopSpawnerLabel->setPixmap(spawnTimeSpellTroopSpawnerIcon);
    /***************    BUILDING-TROOP-SPAWNER ICON    *****************/
    QPixmap spawnSpeedBuildingTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
    QLabel* spawnSpeedBuildingTroopSpawnerLabel= new QLabel();
    spawnSpeedBuildingTroopSpawnerLabel->setPixmap(spawnSpeedBuildingTroopSpawnerIcon);
    /***************    ATTACKING-BUILDING ICON    *****************/
    QPixmap hitPerSecondAttackingBuildingIcon= QPixmap(":/img/insertIcon/hitPerSecond.png");
    QLabel* hitPerSecondAttackingBuildingLabel= new QLabel();
    hitPerSecondAttackingBuildingLabel->setPixmap(hitPerSecondAttackingBuildingIcon);

    QPixmap damagePerSecondAttackingBuildingIcon= QPixmap(":/img/insertIcon/damagePerSecond.png");
    QLabel* damagePerSecondAttackingBuildingLabel= new QLabel();
    damagePerSecondAttackingBuildingLabel->setPixmap(damagePerSecondAttackingBuildingIcon);


    QPixmap rangeAttackingBuildingIcon= QPixmap(":/img/insertIcon/range.png");
    QLabel* rangeAttackingBuildingLabel= new QLabel();
    rangeAttackingBuildingLabel->setPixmap(rangeAttackingBuildingIcon);

    /***********************/


    QStringList classList = {"Select card type", "Troop", "Spell", "Building", "Troop spawner", "Spell troop spawner",
                             "Building troop spawner", "Attacking building"};
    QComboBox* comboClassEdit = new QComboBox;
    comboClassEdit->addItems(classList);
    comboClassEdit->insertSeparator(1);

    /*******************    CARD   ********************/
    // Name
    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setMaxLength(20);
    nameEdit->setPlaceholderText("Card name");


    // manaCost
    QLineEdit* manaCostEdit = new QLineEdit();
    QValidator* manaCostValidator = new QIntValidator(1, 10);
    manaCostEdit->setValidator(manaCostValidator);
    manaCostEdit->setPlaceholderText("Mana cost (max:10)");


    // cardRarity
    QStringList cardRarity = {"Select rarity","Common","Rare","Epic","Legendary"};
    QComboBox* comboRarity = new QComboBox;
    comboRarity->addItems(cardRarity);
    comboRarity->insertSeparator(1);

    // cardLevel
    QLineEdit* cardLevelEdit = new QLineEdit();
    QValidator* cardLevelValidator = new QIntValidator(1, 13);
    cardLevelEdit->setValidator(cardLevelValidator);
    manaCostEdit->setPlaceholderText("Level (max:13)");


    // Descrizione
    QTextEdit* descEdit = new QTextEdit();
    descEdit->setPlaceholderText("Description");

    // -----> CardForm <------
    QFormLayout* formLayout= new QFormLayout();
    formLayout->insertRow(0, cardLabel, comboClassEdit);
    formLayout->insertRow(1, nameLabel, nameEdit);
    formLayout->insertRow(2, manaCostLabel,manaCostEdit);
    formLayout->insertRow(3, cardRarityLabel,comboRarity);
    formLayout->insertRow(4, cardLevelLabel,cardLevelEdit);
    formLayout->insertRow(5, descLabel, descEdit);



    /*******************    TROOP   ********************/
    // shield
    QLineEdit* shieldEdit = new QLineEdit();
    QValidator* shieldValidator = new QDoubleValidator(0,99999,6);
    shieldEdit->setValidator(shieldValidator);
    shieldEdit->setPlaceholderText("Shield");

    //troopHealth
    QLineEdit* troopHealthEdit = new QLineEdit();
    QValidator* troopHealthValidator = new QDoubleValidator(0,99999,6);
    troopHealthEdit->setValidator(troopHealthValidator);
    troopHealthEdit->setPlaceholderText("Troop healt");

    //hitxSec
    QLineEdit* hitPerSecondTroopEdit = new QLineEdit();
    QValidator* hitPerSecondTroopValidator = new QDoubleValidator(0,99999,6);
    hitPerSecondTroopEdit->setValidator(hitPerSecondTroopValidator);
    hitPerSecondTroopEdit->setPlaceholderText("Hit (per second)");

    //damagexSec
    QLineEdit* damagePerSecondTroopEdit = new QLineEdit();
    QValidator* damagePerSecondTroopValidator = new QDoubleValidator(0,99999,6);
    damagePerSecondTroopEdit->setValidator(damagePerSecondTroopValidator);
    damagePerSecondTroopEdit->setPlaceholderText("Damage (per second)");

    //spawnDD--->SpawnDeathDamage
    QLineEdit* spawnDDEdit = new QLineEdit();
    QValidator* spawnDDValidator = new QDoubleValidator(0,99999,6);
    spawnDDEdit->setValidator(spawnDDValidator);
    spawnDDEdit->setPlaceholderText("Spawn/Death Damage");

    //range
    QLineEdit* rangeTroopEdit = new QLineEdit();
    QValidator* rangeTroopValidator = new QDoubleValidator(0,99999,6);
    rangeTroopEdit->setValidator(rangeTroopValidator);
    rangeTroopEdit->setPlaceholderText("Troop range");

    //count
    QLineEdit* countEdit = new QLineEdit();
    QValidator* countValidator = new QIntValidator(1, 99999);
    countEdit->setValidator(countValidator);
    countEdit->setPlaceholderText("Count");


    // -----> TroopForm <------
    QFormLayout* troopFormLayout= new QFormLayout();
    troopFormLayout->addRow(shieldTroopLabel, shieldEdit);
    troopFormLayout->addRow(healthTroopLabel, troopHealthEdit);
    troopFormLayout->addRow( hitPerSecondTroopLabel,hitPerSecondTroopEdit);
    troopFormLayout->addRow(damagePerSecondTroopLabel, damagePerSecondTroopEdit);
    troopFormLayout->addRow(spawnDDTroopLabel, spawnDDEdit);
    troopFormLayout->addRow(rangeTroopLabel, rangeTroopEdit);
    troopFormLayout->addRow(countTroopLabel, countEdit);



    /*******************    SPELL   ********************/
    // spellDamage
    QLineEdit* spellDamageEdit = new QLineEdit();
    QValidator* spellDamageValidator = new QDoubleValidator(0,99999,6);
    spellDamageEdit->setValidator(spellDamageValidator);
    spellDamageEdit->setPlaceholderText("Spell damage");


    //crownTowerDamage
    QLineEdit* crownTowerDamageEdit = new QLineEdit();
    QValidator* crownTowerDamageValidator = new QDoubleValidator(0,99999,6);
    crownTowerDamageEdit->setValidator(crownTowerDamageValidator);
    crownTowerDamageEdit->setPlaceholderText("Spell tower damage");

    //radius
    QLineEdit* radiusEdit = new QLineEdit();
    QValidator* radiusValidator = new QDoubleValidator(0,99999,6);
    radiusEdit->setValidator(radiusValidator);
    radiusEdit->setPlaceholderText("Radius");

    // -----> SpellForm <-----
    QFormLayout* spellFormLayout= new QFormLayout();
    spellFormLayout->addRow(dmgSpellLabel, spellDamageEdit);
    spellFormLayout->addRow(crownTowerDmgSpellLabel, crownTowerDamageEdit);
    spellFormLayout->addRow(radiusSpellLabel, radiusEdit);



    /*******************    BUILDING   ********************/
    // buildHealth
    QLineEdit* buildHealthEdit = new QLineEdit();
    QValidator* buildHealthValidator = new QDoubleValidator(0,99999,6);
    buildHealthEdit->setValidator(buildHealthValidator);
    buildHealthEdit->setPlaceholderText("Build health");

    //lifeTime
    QLineEdit* lifeTimeEdit = new QLineEdit();
    QValidator* lifeTimeValidator = new QDoubleValidator(0,99999,6);
    lifeTimeEdit->setValidator(lifeTimeValidator);
    lifeTimeEdit->setPlaceholderText("Life time");


    // -----> BuildingForm <-----
    QFormLayout* buildingFormLayout= new QFormLayout();
    buildingFormLayout->addRow(healthBuildingLabel, buildHealthEdit);
    buildingFormLayout->addRow(lifeTimeBuildingLabel, lifeTimeEdit);



     /*******************    TROOP-SPAWNER  ********************/

    // TimeDesc
    QLineEdit* timeDescEdit = new QLineEdit();
    timeDescEdit->setMaxLength(50);
    timeDescEdit->setPlaceholderText("Time and description of the cause");

    // -----> TroopSpawnerForm <-----
    QFormLayout* troopSpawnerFormLayout= new QFormLayout();
    troopSpawnerFormLayout->addRow(spawnTimeTroopSpawnerLabel, timeDescEdit);



    /*******************    SPELL-TROOP-SPAWNER  ********************/

    // TimeDesc
    QLineEdit* timeSpawnEdit = new QLineEdit();
    timeSpawnEdit->setMaxLength(50);
    timeSpawnEdit->setPlaceholderText("Time and description of the cause");

    // -----> SpellTroopSpawnerForm <-----
    QFormLayout* spellTroopSpawnerFormLayout= new QFormLayout();
    spellTroopSpawnerFormLayout->addRow(spawnTimeSpellTroopSpawnerLabel, timeSpawnEdit);


    /*******************    BUILDING-TROOP-SPAWNER  ********************/

    // SpawnSpeed
    QLineEdit* spawnSpeedEdit = new QLineEdit();
    QValidator* spawnSpeedValidator = new QDoubleValidator(0,99999,6);
    spawnSpeedEdit->setValidator(spawnSpeedValidator);
    spawnSpeedEdit->setPlaceholderText("Spawn speed(in sec)");

    // -----> BuildingTroopSpawnerForm <-----
    QFormLayout* buildingTroopSpawnerFormLayout= new QFormLayout();
    buildingTroopSpawnerFormLayout->addRow(spawnSpeedBuildingTroopSpawnerLabel, spawnSpeedEdit);


    /*******************   ATTACKING BUILDING   ********************/

    // hitPerSecond
    QLineEdit* hitPerSecondAttBuildingEdit = new QLineEdit();
    QValidator* hitPerSecondAttBuildingValidator = new QDoubleValidator(0,99999,6);
    hitPerSecondAttBuildingEdit->setValidator(hitPerSecondAttBuildingValidator);
    hitPerSecondAttBuildingEdit->setPlaceholderText("Hit (per second)");

    // damagePerSecond
    QLineEdit* damagePerSecondAttBuildingEdit = new QLineEdit();
    QValidator* damagePerSecondAttBuildingValidator = new QDoubleValidator(0,99999,6);
    damagePerSecondAttBuildingEdit->setValidator(damagePerSecondAttBuildingValidator);
    damagePerSecondAttBuildingEdit->setPlaceholderText("Damage (per second)");

    // range
    QLineEdit* rangeAttBuildingEdit = new QLineEdit();
    QValidator* rangeAttBuildingValidator = new QDoubleValidator(0,99999,6);
    rangeAttBuildingEdit->setValidator(rangeAttBuildingValidator);
    rangeAttBuildingEdit->setPlaceholderText("Range");

    // -----> AttackingBuildingForm <-----
    QFormLayout* attckingBuildingFormLayout= new QFormLayout();
    attckingBuildingFormLayout->addRow(hitPerSecondAttackingBuildingLabel, hitPerSecondAttBuildingEdit);
    attckingBuildingFormLayout->addRow(damagePerSecondAttackingBuildingLabel, damagePerSecondAttBuildingEdit);
    attckingBuildingFormLayout->addRow(rangeAttackingBuildingLabel, rangeAttBuildingEdit);

    //troopWidget
    QWidget* troopWidget = new QWidget;
    troopWidget->setLayout(troopFormLayout);
    troopWidget->setVisible(false);

    //spellWidget
    QWidget* spellWidget = new QWidget;
    spellWidget->setLayout(spellFormLayout);
    spellWidget->setVisible(false);

    //buildingWidget
    QWidget* buildingWidget = new QWidget;
    buildingWidget->setLayout(buildingFormLayout);
    buildingWidget->setVisible(false);

    //troopSpawnerWidget
    QWidget* troopSpawnerWidget = new QWidget;
    troopSpawnerWidget->setLayout(troopSpawnerFormLayout);
    troopSpawnerWidget->setVisible(false);

    //spellTroopSpawnerWidget
    QWidget* spellTroopSpawnerWidget = new QWidget;
    spellTroopSpawnerWidget->setLayout(spellTroopSpawnerFormLayout);
    spellTroopSpawnerWidget->setVisible(false);

    //buildingTroopSpawnerWidget
    QWidget* buildingTroopSpawnerWidget = new QWidget;
    buildingTroopSpawnerWidget->setLayout(buildingTroopSpawnerFormLayout);
    buildingTroopSpawnerWidget->setVisible(false);

    //attackingBuildingWidget
    QWidget* attackingBuildingWidget = new QWidget;
    attackingBuildingWidget->setLayout(attckingBuildingFormLayout);
    attackingBuildingWidget->setVisible(false);





   /* "Select card type", "Troop", "Spell", "Building", "Troop spawner", "Spell troop spawner",
                                 "Building troop spawner", "Attacking building"};*/

    connect(comboClassEdit, &QComboBox::currentTextChanged, [comboClassEdit, troopWidget,spellWidget,buildingWidget,troopSpawnerWidget,spellTroopSpawnerWidget,
            buildingTroopSpawnerWidget,attackingBuildingWidget] {
        if (comboClassEdit->currentText()=="Select card type") {
            troopWidget->setVisible(false);
            spellWidget->setVisible(false);
            buildingWidget->setVisible(false);
            troopSpawnerWidget->setVisible(false);
            spellTroopSpawnerWidget->setVisible(false);
            buildingTroopSpawnerWidget->setVisible(false);
            attackingBuildingWidget->setVisible(false);

        }
        else if (comboClassEdit->currentText() == "Troop") {
                troopWidget->setVisible(true);

                spellWidget->setVisible(false);
                buildingWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else if (comboClassEdit->currentText() == "Spell") {
                spellWidget->setVisible(true);

                troopWidget->setVisible(false);
                buildingWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else if (comboClassEdit->currentText() == "Building") {
                buildingWidget->setVisible(true);

                troopWidget->setVisible(false);
                spellWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else if (comboClassEdit->currentText() == "Troop spawner") {
                troopWidget->setVisible(true);
                troopSpawnerWidget->setVisible(true);

                spellWidget->setVisible(false);
                buildingWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else if (comboClassEdit->currentText() == "Spell troop spawner") {
                troopWidget->setVisible(true);
                spellWidget->setVisible(true);
                spellTroopSpawnerWidget->setVisible(true);

                buildingWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else if (comboClassEdit->currentText() == "Building troop spawner") {
                buildingWidget->setVisible(true);
                troopWidget->setVisible(true);
                buildingTroopSpawnerWidget->setVisible(true);

                spellWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                attackingBuildingWidget->setVisible(false);
        }
        else{
            // Attacking building
                buildingWidget->setVisible(true);
                attackingBuildingWidget->setVisible(true);

                troopWidget->setVisible(false);
                spellWidget->setVisible(false);
                troopSpawnerWidget->setVisible(false);
                spellTroopSpawnerWidget->setVisible(false);
                buildingTroopSpawnerWidget->setVisible(false);
        }


    });

    QPushButton* confirmInsert = new QPushButton("Confirm");
    QPushButton* cancelInsert = new QPushButton("Cancel");

    connect(cancelInsert, &QPushButton::clicked, [this] {
       setStackedWidgetPage(0);
    });


    QVBoxLayout* insertLayout=new QVBoxLayout();
    insertLayout->addLayout(formLayout);

    QHBoxLayout* cardTypeLatout=new QHBoxLayout();
    cardTypeLatout->addWidget(troopWidget);
    cardTypeLatout->addWidget(spellWidget);
    cardTypeLatout->addWidget(buildingWidget);
    cardTypeLatout->addWidget(troopSpawnerWidget);
    cardTypeLatout->addWidget(spellTroopSpawnerWidget);
    cardTypeLatout->addWidget(buildingTroopSpawnerWidget);
    cardTypeLatout->addWidget(attackingBuildingWidget);
    insertLayout->addLayout(cardTypeLatout);
    insertLayout->addStretch();
    QHBoxLayout* buttonInsertLatout=new QHBoxLayout();
    buttonInsertLatout->addWidget(confirmInsert);
    buttonInsertLatout->addWidget(cancelInsert);
    insertLayout->addLayout(buttonInsertLatout);
    insertWidget->setLayout(insertLayout);
    stackedWidget->addWidget(insertWidget);
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



int MainWindow::findListItemInContainer(int itemPos) const{
    if (itemPos != -1) {
        for (int i = 0; i < container.getSize(); ++i) {
            if (QString::fromStdString(container[i]->getName()) == list->item(itemPos)->text())
            return i;
        }
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

void MainWindow::filterTypeRarity(const QString &type, const QString &rarity){

    if(type=="All"&&rarity=="All") resetlist();
    /*else{
        for(int i=0; i<container.getSize(); ++i)
            if(QString::fromStdString(container[i]->getType())== type)
                list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
    }*/

    if(rarity!= "All"){
        string c;
        list->reset();
        list->clear();
        if(type=="All"){
            for(int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->RarityToString())== rarity)
                    string c=container[i]->getName()+" ["+ std::to_string(container[i]->getCardLevel())+"]";
                    //list->addItem(new QListWidgetItem(QString::fromStdString(cardList)));
                    list->addItem(new QListWidgetItem(QString::fromStdString(c)));
        }
        else{
            for(int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->RarityToString())== rarity&& QString::fromStdString(container[i]->getType())== type)

                    string c=container[i]->getName()+" ["+ std::to_string(container[i]->getCardLevel())+"]";
                                  list->addItem(new QListWidgetItem(QString::fromStdString(c)));
                    //list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
    }

    if(type!= "All"){
        list->reset();
        list->clear();
        if(rarity=="All"){
            for(int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->getType())== type)
                    list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
        else{
            for(int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->RarityToString())== rarity&& QString::fromStdString(container[i]->getType())== type)
                    list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
    }
}

void MainWindow::combineSearchAndFilter(const QString& searchTxt, const QString& filterTypeTxt, const QString& filterRarityTxt){
    list->reset();
    list->clear();
    filterTypeRarity(filterTypeTxt, filterRarityTxt);
    findNameCard(searchTxt);
}
