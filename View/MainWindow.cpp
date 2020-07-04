t#include "View/MainWindow.h"
#include "Model/myexception.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    setWindowIcon(QIcon(":/img/insertIcon/icon.png"));

    mainWidget=new QWidget(this);
    mainLayout=new QHBoxLayout;
    stackedWidget = new QStackedWidget;
    infoWidget=new QWidget;
    list = new QListWidget;
    insertWidget=new QWidget;
    leftLayout=new QVBoxLayout;
    rightLayout=new QVBoxLayout;
    infolayout=new QVBoxLayout;
    insertLayout=new QVBoxLayout;
    menubar= new QMenuBar;
    menu =new QMenu("File",menubar);
    menu2 =new QMenu("Themes",menubar);
    searchbox= new QLineEdit;
    completer= new QCompleter;
    filterTypeBox=new QComboBox;
    filterRarityBox=new QComboBox;
    insertButton = new QPushButton("Insert Card");
    deleteAllButton= new QPushButton("Delete All");
    pathImg="/img/iconCard/default.png";
    StyleWhite=false;
    addMenu();
    addLeftLayout();
    addRightLayout();
    setWidgetStyle();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow(){}

/************ Reset List ************/
void MainWindow::resetlist(){
    if (list->count() != 0) {
        list->reset();
        list->clear();
    }
    for (unsigned int i = 0; i < container.getSize(); i++)
   {
      list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
    }
}

/************ Message box About ************/
void MainWindow::infoguide() const{
    QMessageBox Box;
    Box.setWindowTitle("About");
    Box.setText("\n\n Welcome to ClashRoyale Wiki v1.0");
    Box.setInformativeText("\n Developed by \n KokoGorillaTEAM \n");
    QPixmap logo = QPixmap(":/img/insertIcon/infobox.png");
    logo = logo.scaledToWidth(150);
    Box.setIconPixmap(logo);
    if(!StyleWhite){
    Box.setStyleSheet("background-color: rgb(30,30,30); color: rgb(246,163,5);");}
    else{
    Box.setStyleSheet("background-color: rgb(225,225,225); color: rgb(246,163,5);");
    }
    Box.exec();
}
/************ Set Layout ************/
void MainWindow::addLeftLayout(){

   //set scrollArea & set Layout
    QScrollArea* leftbox= new QScrollArea;
    leftbox->setWidget(list);
    leftbox->setWidgetResizable(true);
    leftbox->setFixedSize(450,400);
    leftbox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    QHBoxLayout* searchLayout= new QHBoxLayout;
    //list
    connect(list, &QListWidget::currentRowChanged, [this] {
      if (list->count()>0)
    {
          clearLayout(infolayout);
          viewCardInfo(findListItemInContainer(list->currentRow()));
          setStackedWidgetPage(1);
          insertButton->setVisible(true);
          deleteAllButton->setVisible(true);
      }
    });
   //searchbox
    searchbox->setClearButtonEnabled(true);
    searchbox->addAction(QIcon(":/img/insertIcon/whitesearch.png"), QLineEdit::LeadingPosition);
    searchbox->setPlaceholderText("Search");
   connect(searchbox, &QLineEdit::textChanged, [this] {
         if (container.getSize() > 0)
             combineSearchAndFilter(searchbox->text(),filterTypeBox->currentText(), filterRarityBox->currentText() );
              });
   //insert&delete&resetSearchFilters Button
   QPushButton* resetSearchFiltersButton= new QPushButton("Reset Filters");
   insertButton->setFixedSize(100,50);
   deleteAllButton->setFixedSize(100,50);
   resetSearchFiltersButton->setFixedSize(100,50);
   connect(insertButton, &QPushButton::clicked, [this] {
   clearLayout(insertLayout);
   addInsertWidget();
   insertWidget->setLayout(insertLayout);
   setStackedWidgetPage(2);
   insertButton->setVisible(false);
   deleteAllButton->setVisible(false);
   });
   connect(deleteAllButton, &QPushButton::clicked, [this] {
       if (list->count() > 0) {
           container.clear();
           list->clear();
           setStackedWidgetPage(0);
       }
   });
   connect(resetSearchFiltersButton, &QPushButton::clicked, [this] {
       resetSearchAndFilter();
   });
   buttonLayout->addWidget(insertButton);
   buttonLayout->addWidget(resetSearchFiltersButton);
   buttonLayout->addWidget(deleteAllButton);

   //Filters
   filterTypeBox->addItem("All types");
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
   filterRarityBox->addItem("All rarities");
   filterRarityBox->addItem("Common");
   filterRarityBox->addItem("Rare");
   filterRarityBox->addItem("Epic");
   filterRarityBox->addItem("Legendary");
   connect(filterRarityBox, &QComboBox::currentTextChanged,[this]{
       if(container.getSize()>0)
           combineSearchAndFilter(searchbox->text(),filterTypeBox->currentText(), filterRarityBox->currentText() );
   });
    searchbox->setFixedSize(190,30);
    filterTypeBox->setFixedSize(150,30);
    filterRarityBox->setFixedSize(20,30);
    searchLayout->addWidget(searchbox);
    searchLayout->addWidget(filterTypeBox);
    searchLayout->addWidget(filterRarityBox);
    leftLayout->addLayout(searchLayout);
    leftLayout->addWidget(leftbox);
    leftLayout->addLayout(buttonLayout);
    mainLayout->addLayout(leftLayout);

}

void MainWindow::addMenu(){
    QAction* save= new QAction(QIcon(":img/insertIcon/add.png"),"Save Set", this);
    QAction* load=new QAction(QIcon(":img/insertIcon/save.png"), "Load Set", this);
    QAction* about=new QAction("About", this);
    QAction* white=new QAction("Light", this);
    QAction* dark=new QAction("Dark", this);
    //Add action
    menu->addAction(save);
    menu->addAction(load);
    menu2->addAction(white);
    menu2->addAction(dark);
    connect(load, &QAction::triggered, [this] {
        loadFile();
        resetSearchAndFilter();
        setStackedWidgetPage(0);
        insertButton->setVisible(true);
        deleteAllButton->setVisible(true);});
    connect(save, &QAction::triggered, [this] {saveFile();});
    connect(dark, &QAction::triggered, [this] {
        StyleWhite=false;
        setWidgetStyle();});
    connect(white, &QAction::triggered, [this] {
        StyleWhite=true;
                setWidgetStyleWhite();});
    //Add menubar
    menubar->addMenu(menu);
    menubar->addMenu(menu2);
    menubar->addAction(about);
    connect(about, &QAction::triggered, [this] {infoguide();});
    // set menubar
    setMenuBar(menubar);
}

void MainWindow::addRightLayout()
{
    basicInfoWidget();
    infoWidget->setLayout(infolayout);
    stackedWidget->addWidget(infoWidget);
    stackedWidget->addWidget(insertWidget);
    rightLayout->addWidget(stackedWidget);
    mainLayout->addLayout(rightLayout);
}

/************ Page of StackedWidget ************/
//First Page
void MainWindow::basicInfoWidget()
{
    QPixmap logo = QPixmap(":/img/insertIcon/background.png");
    logo = logo.scaledToWidth(450);
    QLabel* logoLabel = new QLabel();
    logoLabel->setPixmap(logo);
    logoLabel->setStyleSheet("margin-bottom: 2em");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(logoLabel);
    QWidget* basicInfo=new QWidget();
    basicInfo->setLayout(layout);
    stackedWidget->addWidget(basicInfo);

}
//View CardInfo page
void MainWindow::viewCardInfo(int pos)
{
 if(pos!=-1 && pos>=0){
     unsigned int fixPos= static_cast<unsigned int>(pos);

     /***************    SET ICON    *****************/
     QPixmap cardIcon= QPixmap(":/img/insertIcon/cardType.png");
     QLabel* cardLabel0= new QLabel();
     cardLabel0->setPixmap(cardIcon);

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

     /***************    ICON    *****************/
     QPixmap shieldIcon= QPixmap(":/img/insertIcon/shield.png");
     QLabel* shieldLabel= new QLabel();
     shieldLabel->setPixmap(shieldIcon);

     QPixmap healthIcon= QPixmap(":/img/insertIcon/health.png");
     QLabel* healthLabel= new QLabel();
     healthLabel->setPixmap(healthIcon);

     QPixmap hitPerSecondIcon= QPixmap(":/img/insertIcon/hitPerSecond.png");
     QLabel* hitPerSecondLabel= new QLabel();
     hitPerSecondLabel->setPixmap(hitPerSecondIcon);

     QPixmap damageIcon= QPixmap(":/img/insertIcon/dmg.png");
     QLabel* damageLabel= new QLabel();
     damageLabel->setPixmap(damageIcon);

     QPixmap damagePerSecondIcon= QPixmap(":/img/insertIcon/damagePerSecond.png");
     QLabel* damagePerSecondLabel= new QLabel();
     damagePerSecondLabel->setPixmap(damagePerSecondIcon);

     QPixmap spawnDDIcon= QPixmap(":/img/insertIcon/spawnDD.png");
     QLabel* spawnDDLabel= new QLabel();
     spawnDDLabel->setPixmap(spawnDDIcon);

     QPixmap rangeIcon= QPixmap(":/img/insertIcon/range.png");
     QLabel* rangeLabel= new QLabel();
     rangeLabel->setPixmap(rangeIcon);

     QPixmap radiusIcon= QPixmap(":/img/insertIcon/radius.png");
     QLabel* radiusLabel= new QLabel();
     radiusLabel->setPixmap(radiusIcon);

     QPixmap countIcon= QPixmap(":/img/insertIcon/count.png");
     QLabel* countLabel= new QLabel();
     countLabel->setPixmap(countIcon);

     QPixmap crownTowerDmgIcon= QPixmap(":/img/insertIcon/crownTowerDamage.png");
     QLabel* crownTowerDmgLabel= new QLabel();
     crownTowerDmgLabel->setPixmap(crownTowerDmgIcon);

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

     /***************    TROOP-SPAWNER ICON    *****************/
     QPixmap spawnTimeTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
     QLabel* spawnTimeTroopSpawnerLabel= new QLabel();
     spawnTimeTroopSpawnerLabel->setPixmap(spawnTimeTroopSpawnerIcon);

     /***************    SPELL-TROOP-SPAWNER ICON    *****************/
     QPixmap spawnTimeSpellTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
     QLabel* spawnTimeSpellTroopSpawnerLabel= new QLabel();
     spawnTimeSpellTroopSpawnerLabel->setPixmap(spawnTimeSpellTroopSpawnerIcon);

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

     /***************    BUILDING ICON    *****************/
     QPixmap healthBuildingIcon= QPixmap(":/img/insertIcon/health.png");
     QLabel* healthBuildingLabel= new QLabel();
     healthBuildingLabel->setPixmap(healthBuildingIcon);

     QPixmap lifeTimeBuildingIcon= QPixmap(":/img/insertIcon/lifeTime.png");
     QLabel* lifeTimeBuildingLabel= new QLabel();
     lifeTimeBuildingLabel->setPixmap(lifeTimeBuildingIcon);

     /***************    TROOP-SPAWNER ICON    *****************/
     QPixmap spawnTimeIcon= QPixmap(":/img/insertIcon/lifeTime.png");
     QLabel* spawnTimeLabel= new QLabel();
     spawnTimeLabel->setPixmap(spawnTimeIcon);

     /***************    BUILDING-TROOP-SPAWNER ICON    *****************/
     QPixmap spawnSpeedBuildingTroopSpawnerIcon= QPixmap(":/img/insertIcon/lifeTime.png");
     QLabel* spawnSpeedBuildingTroopSpawnerLabel= new QLabel();
     spawnSpeedBuildingTroopSpawnerLabel->setPixmap(spawnSpeedBuildingTroopSpawnerIcon);

    //Layout
    QHBoxLayout* layoutInfoTop=new QHBoxLayout();
    QFormLayout* formLayout0 = new QFormLayout();
    QVBoxLayout* imgAndButton=new QVBoxLayout();
    QHBoxLayout* buttonUpAndDown=new QHBoxLayout();
    QHBoxLayout* Multiform=new QHBoxLayout();
    QHBoxLayout* buttonLayout=new QHBoxLayout();

    //Button Edit
    QPushButton* editButton = new QPushButton("Edit Card");
    editButton->setFixedSize(100,50);
    buttonLayout->addWidget(editButton);

    //Button Delete
    QPushButton* deleteButton = new QPushButton("Delete Card");
    deleteButton->setFixedSize(100,50);
    buttonLayout->addWidget(deleteButton);

    //Label Text
    string cardNameLevel= container[fixPos]->getName() + " [" + "Level: "+ std::to_string(container[fixPos]->getCardLevel())+"]";
    QLabel* nameCard=new QLabel(QString::fromStdString(cardNameLevel));
    QLabel* typeCard=new QLabel("Type: "+ QString::fromStdString(container[fixPos]->getType()));
    QLabel* rarityCard=new QLabel("Rarity: "+ QString::fromStdString(container[fixPos]->RarityToString()));
    QLabel* manaCostCard=new QLabel("Mana Cost: "+ QString::number(container[fixPos]->getManaCost()));
    QTextEdit* desc=new QTextEdit(QString::fromStdString(container[fixPos]->getDescription()));
    desc->setReadOnly(true);
    desc->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    desc->setFixedHeight(100);

    //Form BasicInfo
    formLayout0->addRow(nameLabel,nameCard);
    formLayout0->addRow(cardLabel0,typeCard);
    formLayout0->addRow(cardRarityLabel,rarityCard);
    formLayout0->addRow(manaCostLabel,manaCostCard);
    formLayout0->addRow(descLabel,desc);

    //Action EditButton
    connect(editButton, &QPushButton::clicked, [this, fixPos] {
    clearLayout(insertLayout);
    addInsertWidget(true,fixPos);
    insertWidget->setLayout(insertLayout);
    setStackedWidgetPage(2);
    insertButton->setVisible(false);
    deleteAllButton->setVisible(false);
    });
    //Action deleteButton
    connect(deleteButton, &QPushButton::clicked, [this] {
        if (list->count() > 0 && list->currentRow() != -1) {
            container.remove(findListItemInContainer(list->currentRow()));
            list->takeItem(list->currentRow());
        }
        if(list->currentRow() == -1){
            setStackedWidgetPage(0);
        }
    });
   //layout info Card
  QFormLayout* formLayout1 = new QFormLayout();
  QFormLayout* formLayout2 = new QFormLayout();
  QFormLayout* formLayout3 = new QFormLayout();
    pathImg=QFileInfo(".").absolutePath().toStdString() + "/ClashRoyaleDB";
  if(container[fixPos]->getType()=="Building")
  {
      Building* building = dynamic_cast<Building*>(container[fixPos].operator->());
      pathImg= pathImg+building->getPath();

      QLabel* healthBuilding=new QLabel("Health: "+ QString::number(std::floor(building->getBuildHealth())));
      QLabel* lifetimeBuilding=new QLabel("Life Time: "+ QString::number(building->getLifeTime()));

      formLayout1->addRow(healthLabel,healthBuilding);
      formLayout1->addRow(lifeTimeBuildingLabel,lifetimeBuilding);

      Multiform->addLayout(formLayout1);

  }
  else if(container[fixPos]->getType()=="Spell")
  {
    Spell* spell = dynamic_cast<Spell*>(container[fixPos].operator->());
    pathImg=pathImg+ spell->getPath();

    QLabel* damageSpell=new QLabel("Damage: "+ QString::number(std::floor(spell->getSpellDamage())));
    QLabel* crownTowerDamage=new QLabel("Crown Tower Damage: "+ QString::number(std::floor(spell->getCrownTowerDamage())));
    QLabel* radius=new QLabel("Radius: "+ QString::number(spell->getRadius()));

    formLayout1->addRow(dmgSpellLabel,damageSpell);
    formLayout1->addRow(crownTowerDmgSpellLabel,crownTowerDamage);
    formLayout1->addRow(radiusSpellLabel,radius);

    Multiform->addLayout(formLayout1);

  }
  else if(container[fixPos]->getType()=="Troop"){
      Troop* troop = dynamic_cast<Troop*>(container[fixPos].operator->());
       pathImg= pathImg+troop->getPath();

      QLabel* shieldTroop=new QLabel("Shield: "+ QString::number(std::floor(troop->getShield())));
      QLabel* healthTroop=new QLabel("Health: "+ QString::number(std::floor(troop->getTroopHealth())));
      QLabel* hitxsecTroop=new QLabel("Hit (per second): "+ QString::number(troop->getHitxSec()));
      QLabel* damagexsecTroop=new QLabel("Damage (per second): "+ QString::number(std::floor(troop->getDamagexSec())));
      QLabel* sddTroop=new QLabel("Spawn/Death Damage: "+ QString::number(std::floor(troop->getSpawnDD())));
      QLabel* rangeTroop=new QLabel("Range("+QString::fromStdString(troop->dimRange())+"): "+ QString::number(troop->getRange()));
      QLabel* countTroop=new QLabel("Count: "+ QString::number(troop->getCount()));
      QLabel* damageTroop=new QLabel("Damage: "+ QString::number(std::floor(troop->damage())));

      formLayout1->addRow(shieldLabel,shieldTroop);
      formLayout1->addRow(healthLabel,healthTroop);
      formLayout1->addRow(hitPerSecondLabel,hitxsecTroop);
      formLayout1->addRow(damagePerSecondLabel,damagexsecTroop);
      formLayout1->addRow(damageLabel,damageTroop);
      formLayout1->addRow(spawnDDLabel,sddTroop);
      formLayout2->addRow(rangeLabel,rangeTroop);
      formLayout2->addRow(countLabel,countTroop);

      Multiform->addLayout(formLayout1);
      Multiform->addLayout(formLayout2);

  }
  else if(container[fixPos]->getType()=="Attacking Building"){
      AttackingBuilding* attackingBuilding = dynamic_cast<AttackingBuilding*>(container[fixPos].operator->());
      pathImg=pathImg+ attackingBuilding->getPath();

      QLabel* healthAttBuilding=new QLabel("Health: "+ QString::number(std::floor(attackingBuilding->getBuildHealth())));
      QLabel* lifetimeAttBuilding=new QLabel("Life Time: "+ QString::number(attackingBuilding->getLifeTime()));
      QLabel* hitxsecAttBuilding=new QLabel("Hit (per second): "+ QString::number(attackingBuilding->getHitPerSecond()));
      QLabel* damagexsecAttBuilding=new QLabel("Damage (per second): "+ QString::number(std::floor(attackingBuilding->getDamagePerSecond())));
      QLabel* rangeAttBuilding=new QLabel("Range("+QString::fromStdString(attackingBuilding->dimRange())+"): "+ QString::number(attackingBuilding->getRange()));
      QLabel* damageAttBuilding=new QLabel("Damage: "+ QString::number(std::floor(attackingBuilding->damage())));

      formLayout1->addRow(healthBuildingLabel,healthAttBuilding);
      formLayout1->addRow(lifeTimeBuildingLabel,lifetimeAttBuilding);
      formLayout1->addRow(hitPerSecondAttackingBuildingLabel,hitxsecAttBuilding);
      formLayout1->addRow(damagePerSecondAttackingBuildingLabel,damagexsecAttBuilding);
      formLayout1->addRow(damageLabel,damageAttBuilding);
      formLayout1->addRow(rangeAttackingBuildingLabel,rangeAttBuilding);

      Multiform->addLayout(formLayout1);

  }
  else if(container[fixPos]->getType()=="Building-Troop Spawner"){
      BuildingTroopSpawner* buildingTroopSpawner = dynamic_cast<BuildingTroopSpawner*>(container[fixPos].operator->());
      pathImg= pathImg+buildingTroopSpawner->getPath();

      QLabel* health1BuildingTroop=new QLabel("Building Health: "+ QString::number(std::floor(buildingTroopSpawner->getBuildHealth())));
      QLabel* health2BuildingTroop=new QLabel("Troop Health: "+ QString::number(std::floor(buildingTroopSpawner->getTroopHealth())));
      QLabel* lifetimeBuildingTroop=new QLabel("Life Time: "+ QString::number(buildingTroopSpawner->getLifeTime()));
      QLabel* spawnsecondBuildingTroop=new QLabel("Spawn Speed: "+ QString::number(buildingTroopSpawner->getSpawnSpeed()));
      QLabel* shieldBuildingTroop=new QLabel("Shield: "+ QString::number(std::floor(buildingTroopSpawner->getShield())));
      QLabel* hitxsecBuildingTroop=new QLabel("hit (per second): "+ QString::number(buildingTroopSpawner->getHitxSec()));
      QLabel* damagexsecBuildingTroop=new QLabel("Damage (per second): "+ QString::number(std::floor(buildingTroopSpawner->getDamagexSec())));
      QLabel* sddBuildingTroop=new QLabel("Spawn/Death Damage: "+ QString::number(std::floor(buildingTroopSpawner->getSpawnDD())));
      QLabel* rangeBuildingTroop=new QLabel("Range("+QString::fromStdString(buildingTroopSpawner->dimRange())+"): "+ QString::number(buildingTroopSpawner->getRange()));
      QLabel* countBuildingTroop=new QLabel("Count: "+ QString::number(buildingTroopSpawner->getCount()));
      QLabel* damageBuildingTroop=new QLabel("Damage: "+ QString::number(std::floor(buildingTroopSpawner->damage())));

      formLayout1->addRow(shieldLabel,shieldBuildingTroop);
      formLayout1->addRow (healthLabel,health2BuildingTroop);
      formLayout1->addRow(hitPerSecondLabel,hitxsecBuildingTroop);
      formLayout1->addRow(damagePerSecondLabel,damagexsecBuildingTroop);
      formLayout1->addRow(damageLabel,damageBuildingTroop);
      formLayout1->addRow(spawnDDLabel,sddBuildingTroop);
      formLayout2->addRow(rangeLabel,rangeBuildingTroop);
      formLayout2->addRow(countLabel,countBuildingTroop);
      formLayout2->addRow(healthBuildingLabel,health1BuildingTroop);
      formLayout2->addRow(lifeTimeBuildingLabel,lifetimeBuildingTroop);
      formLayout2->addRow(spawnSpeedBuildingTroopSpawnerLabel,spawnsecondBuildingTroop);

      Multiform->addLayout(formLayout1);
      Multiform->addLayout(formLayout2);

  }
  else if(container[fixPos]->getType()=="Spell-Troop Spawner"){
       SpellTroopSpawner* spellTroopSpawner = dynamic_cast<SpellTroopSpawner*>(container[fixPos].operator->());
       pathImg=pathImg+spellTroopSpawner->getPath();

        QLabel* shieldSpellTroop=new QLabel("Shield: "+ QString::number(std::floor(spellTroopSpawner->getShield())));
        QLabel* healthSpellTroop=new QLabel("Health: "+ QString::number(std::floor(spellTroopSpawner->getTroopHealth())));
        QLabel* hitxsecSpellTroop=new QLabel("Hit (per second): "+ QString::number(spellTroopSpawner->getHitxSec()));
        QLabel* damagexsecSpellTroop=new QLabel("Damage (per second): "+ QString::number(std::floor(spellTroopSpawner->getDamagexSec())));
        QLabel* sddSpellTroop=new QLabel("Spawn Death Damage: "+ QString::number(std::floor(spellTroopSpawner->getSpawnDD())));
        QLabel* rangeSpellTroop=new QLabel("Range("+QString::fromStdString(spellTroopSpawner->dimRange())+"): "+ QString::number(spellTroopSpawner->getRange()));
        QLabel* countSpellTroop=new QLabel("Count: "+ QString::number(spellTroopSpawner->getCount()));
        QLabel* damageSpellTroop=new QLabel("Spell Damage: "+ QString::number(std::floor(spellTroopSpawner->getSpellDamage())));
        QLabel* crowntowerdamageSpellTroop=new QLabel("Crown Tower Damage: "+ QString::number(std::floor(spellTroopSpawner->getCrownTowerDamage())));
        QLabel* radiusSpellTroop=new QLabel("Radius: "+ QString::number(spellTroopSpawner->getRadius()));
        QLabel* tsSpellTroop=new QLabel("Time Spawn: "+ QString::fromStdString(spellTroopSpawner->getTimeSpawn()));
        QLabel* damageTSpellTroop=new QLabel("Troop Damage: "+ QString::number(std::floor(spellTroopSpawner->damage())));

        formLayout1->addRow(shieldLabel,shieldSpellTroop);
        formLayout1->addRow(healthLabel,healthSpellTroop);
        formLayout1->addRow(hitPerSecondLabel,hitxsecSpellTroop);
        formLayout1->addRow(damagePerSecondLabel,damagexsecSpellTroop);
        formLayout1->addRow(damageLabel,damageTSpellTroop);
        formLayout1->addRow(spawnDDLabel,sddSpellTroop);
        formLayout2->addRow(rangeLabel,rangeSpellTroop);
        formLayout2->addRow(countLabel,countSpellTroop);
        formLayout2->addRow(dmgSpellLabel,damageSpellTroop);
        formLayout2->addRow(crownTowerDmgSpellLabel,crowntowerdamageSpellTroop);
        formLayout2->addRow(radiusSpellLabel,radiusSpellTroop);
        formLayout3->addRow(spawnTimeLabel,tsSpellTroop);

        Multiform->addLayout(formLayout1);
        Multiform->addLayout(formLayout2);
        Multiform->addLayout(formLayout3);
      }
  else if(container[fixPos]->getType()=="Troop Spawner"){
    TroopSpawner* troopSpawner = dynamic_cast<TroopSpawner*>(container[fixPos].operator->());
     pathImg=pathImg+troopSpawner->getPath();

     QLabel* shieldTroopSpawner=new QLabel("Shield: "+ QString::number(std::floor(troopSpawner->getShield())));
     QLabel* healthTroopSpawner=new QLabel("Health: "+ QString::number(std::floor(troopSpawner->getTroopHealth())));
     QLabel* hitxsecTroopSpawner=new QLabel("Hit (per second): "+ QString::number(troopSpawner->getHitxSec()));
     QLabel* damagexsecTroopSpawner=new QLabel("Damage (per second): "+ QString::number(std::floor(troopSpawner->getDamagexSec())));
     QLabel* sddTroopSpawner=new QLabel("Spawn Death Damage: "+ QString::number(std::floor(troopSpawner->getSpawnDD())));
     QLabel* rangeTroopSpawner=new QLabel("Range("+QString::fromStdString(troopSpawner->dimRange())+"): "+ QString::number(troopSpawner->getRange()));
     QLabel* countTroopSpawner=new QLabel("Count: "+ QString::number(troopSpawner->getCount()));
     QLabel* timedescTroopSpawner=new QLabel("Time and Description: "+ QString::fromStdString(troopSpawner->getTimeDesc()));
     QLabel* damageTroopSpawner=new QLabel("Damage: "+ QString::number(std::floor(troopSpawner->damage())));

     formLayout1->addRow(shieldLabel,shieldTroopSpawner);
     formLayout1->addRow(healthLabel,healthTroopSpawner);
     formLayout1->addRow(hitPerSecondLabel,hitxsecTroopSpawner);
     formLayout1->addRow(damagePerSecondLabel,damagexsecTroopSpawner);
     formLayout1->addRow(damageLabel,damageTroopSpawner);
     formLayout1->addRow(spawnDDLabel,sddTroopSpawner);
     formLayout2->addRow(rangeLabel,rangeTroopSpawner);
     formLayout2->addRow(countLabel,countTroopSpawner);
     formLayout2->addRow(spawnTimeTroopSpawnerLabel,timedescTroopSpawner);

     Multiform->addLayout(formLayout1);
     Multiform->addLayout(formLayout2);
  }

  // Button Upgrade stats
  QPushButton* lvUpgrade = new QPushButton("Upgrade");
  connect(lvUpgrade, &QPushButton::clicked, [this,fixPos] {
      try {
          container[fixPos]->lvlUpgrade();
          clearLayout(infolayout);
          viewCardInfo(static_cast<int>(fixPos));
      } catch (MyException e) {
          QMessageBox msgBox;
          msgBox.setText(QString::fromStdString(e.getMsgException()));
          if(!StyleWhite)
          {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
          else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
          msgBox.exec();
      }
  });

  // Button Upgrade stats
  QPushButton* lvDowngrade = new QPushButton("Downgrade");
  connect(lvDowngrade, &QPushButton::clicked, [this,fixPos] {
      try {
          container[fixPos]->lvlDowngrade();
          clearLayout(infolayout);
          viewCardInfo(static_cast<int>(fixPos));

      } catch (MyException e) {
          QMessageBox msgBox;
          msgBox.setText(QString::fromStdString(e.getMsgException()));
          if(!StyleWhite)
          {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
          else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
          msgBox.exec();
      }

  } );

  //Set icon Upgrade Button
  QPixmap pixmap1(":/img/insertIcon/add.png");
  QIcon ButtonIcon1(pixmap1);
  lvUpgrade->setIcon(ButtonIcon1);
  lvUpgrade->setStyleSheet("QPushButton{background-color: rgb(30,30,30); color:white; font:9pt;} QPushButton:hover {background-color: rgb(120,120,120);}");
  lvUpgrade->setFixedSize(100,40);
  lvUpgrade->setIconSize(QSize(30,30));
  //Set icon Downgrade Button
  QPixmap pixmap2(":/img/insertIcon/min.png");
  QIcon ButtonIcon2(pixmap2);
  lvDowngrade->setIcon(ButtonIcon2);
  lvDowngrade->setStyleSheet("QPushButton{background-color: rgb(30,30,30); color:white; font:9pt;} QPushButton:hover {background-color: rgb(120,120,120);}");
  lvDowngrade->setFixedSize(100,40);
  lvDowngrade->setIconSize(QSize(30,30));
  //Set Img Card
  QString s=QString::fromStdString(pathImg);
  pathImg="/img/iconCard/default.png"; //Reset PathImg
  QPixmap cardimg =QPixmap(s);
  QLabel* cardLabel=new QLabel();
  cardLabel->setPixmap(cardimg);
  cardLabel->setFixedSize(190,190);
  cardLabel->setScaledContents(true);
  //Set Layout
  buttonLayout->setMargin(10);
  imgAndButton->addWidget(cardLabel);
  buttonUpAndDown->addWidget(lvDowngrade);
  buttonUpAndDown->addWidget(lvUpgrade);
  imgAndButton->addLayout(buttonUpAndDown);
  layoutInfoTop->addLayout(imgAndButton);
  layoutInfoTop->addLayout(formLayout0);
  infolayout->addLayout(layoutInfoTop);
  infolayout->addLayout(Multiform);
  infolayout->addLayout(buttonLayout);

}}

//Insert And Edit Page
void MainWindow::addInsertWidget(bool Edit, unsigned int cardPos)
{
    /***************    SET ICON    *****************/
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

    QStringList classList = {"Select card type", "Troop", "Spell", "Building", "Troop Spawner", "Spell-Troop Spawner",
                             "Building-Troop Spawner", "Attacking Building"};
    QComboBox* comboClassEdit = new QComboBox;
    comboClassEdit->addItems(classList);
    comboClassEdit->insertSeparator(1);

    /*******************    CARD   ********************/
    //Name
    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setMaxLength(80);
    nameEdit->setPlaceholderText("Card name");
    //manaCost
    QLineEdit* manaCostEdit = new QLineEdit();
    QValidator* manaCostValidator = new QIntValidator(1, 10);
    manaCostEdit->setValidator(manaCostValidator);
    manaCostEdit->setPlaceholderText("Mana cost (max:10)");
    //cardRarity
    QStringList cardRarity = {"Select rarity","Common","Rare","Epic","Legendary"};
    QComboBox* comboRarity = new QComboBox;
    comboRarity->addItems(cardRarity);
    comboRarity->insertSeparator(1);
    //cardLevel
    QLineEdit* cardLevelEdit = new QLineEdit();
    QValidator* cardLevel1Validator = new QIntValidator(1, 99);
    cardLevelEdit->setValidator(cardLevel1Validator);
    cardLevelEdit->setPlaceholderText("Level (max:13)");
    //Description
    QTextEdit* descEdit = new QTextEdit();
    descEdit->setPlaceholderText("Description");
    descEdit->setFixedHeight(70);
    // -----> CardForm <------
    QFormLayout* formLayout= new QFormLayout();
    formLayout->insertRow(0, cardLabel, comboClassEdit);
    formLayout->insertRow(1, nameLabel, nameEdit);
    formLayout->insertRow(2, manaCostLabel
