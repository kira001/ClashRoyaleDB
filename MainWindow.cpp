#include "MainWindow.h"
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
    insertButton = new QPushButton("Insert");
    deleteButton= new QPushButton("Delete");
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
    Box.setText("\n\n Welcome to ClashRoyale v1.0");
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
          deleteButton->setVisible(true);
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
   deleteButton->setFixedSize(100,50);
   resetSearchFiltersButton->setFixedSize(100,50);
   connect(insertButton, &QPushButton::clicked, [this] {
   clearLayout(insertLayout);
   addInsertWidget();
   insertWidget->setLayout(insertLayout);
   setStackedWidgetPage(2);
   insertButton->setVisible(false);
   deleteButton->setVisible(false);
   });
   connect(deleteButton, &QPushButton::clicked, [this] {
       if (list->count() > 0 && list->currentRow() != -1) {
           container.remove(findListItemInContainer(list->currentRow()));
           list->takeItem(list->currentRow());
       }
       if(list->currentRow() == -1){
           setStackedWidgetPage(0);
       }
   });
   connect(resetSearchFiltersButton, &QPushButton::clicked, [this] {
       resetSearchAndFilter();
   });
   buttonLayout->addWidget(insertButton);
   buttonLayout->addWidget(resetSearchFiltersButton);
   buttonLayout->addWidget(deleteButton);

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
        deleteButton->setVisible(true);});
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
    QPushButton* editButton = new QPushButton("Edit");
    editButton->setFixedSize(100,50);
    buttonLayout->addWidget(editButton);

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
    deleteButton->setVisible(false);
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
  lvUpgrade->setStyleSheet("QPushButton{background-color: rgb(30,30,30); color:white;} QPushButton:hover {background-color: rgb(120,120,120);}");
  lvUpgrade->setFixedSize(100,40);
  lvUpgrade->setIconSize(QSize(30,30));
  //Set icon Downgrade Button
  QPixmap pixmap2(":/img/insertIcon/min.png");
  QIcon ButtonIcon2(pixmap2);
  lvDowngrade->setIcon(ButtonIcon2);
  lvDowngrade->setStyleSheet("QPushButton{background-color: rgb(30,30,30); color:white;} QPushButton:hover {background-color: rgb(120,120,120);}");
  lvDowngrade->setFixedSize(110,40);
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
    formLayout->insertRow(2, manaCostLabel,manaCostEdit);
    formLayout->insertRow(3, cardRarityLabel,comboRarity);
    formLayout->insertRow(4, cardLevelLabel,cardLevelEdit);
    formLayout->insertRow(5, descLabel, descEdit);

    /*******************    TROOP   ********************/
    //shield
    QLineEdit* shieldEdit = new QLineEdit();
    QValidator* shieldValidator = new QDoubleValidator(0,99999,6);
    shieldEdit->setValidator(shieldValidator);
    shieldEdit->setPlaceholderText("Shield");
    //troopHealth
    QLineEdit* troopHealthEdit = new QLineEdit();
    QValidator* troopHealthValidator = new QDoubleValidator(0,99999,6);
    troopHealthEdit->setValidator(troopHealthValidator);
    troopHealthEdit->setPlaceholderText("Troop health");
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
    troopFormLayout->addRow(hitPerSecondTroopLabel,hitPerSecondTroopEdit);
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
    QLineEdit* lifeTimeBuildEdit = new QLineEdit();
    QValidator* lifeTimeValidator = new QDoubleValidator(0,99999,6);
    lifeTimeBuildEdit->setValidator(lifeTimeValidator);
    lifeTimeBuildEdit->setPlaceholderText("Life time (in sec)");


    // -----> BuildingForm <-----
    QFormLayout* buildingFormLayout= new QFormLayout();
    buildingFormLayout->addRow(healthBuildingLabel, buildHealthEdit);
    buildingFormLayout->addRow(lifeTimeBuildingLabel, lifeTimeBuildEdit);

     /*******************    TROOP-SPAWNER  ********************/
    // TimeDesc
    QLineEdit* timeDescEditTroopSpawner = new QLineEdit();
    timeDescEditTroopSpawner->setMaxLength(50);
    timeDescEditTroopSpawner->setPlaceholderText("Time and description of the cause");

    // -----> TroopSpawnerForm <-----
    QFormLayout* troopSpawnerFormLayout= new QFormLayout();
    troopSpawnerFormLayout->addRow(spawnTimeTroopSpawnerLabel, timeDescEditTroopSpawner);

    /*******************    SPELL-TROOP-SPAWNER  ********************/

    // TimeDesc
    QLineEdit* timeSpawnEditSpellTroopSpawner = new QLineEdit();
    timeSpawnEditSpellTroopSpawner->setMaxLength(50);
    timeSpawnEditSpellTroopSpawner->setPlaceholderText("Time and description of the cause");

    // -----> SpellTroopSpawnerForm <-----
    QFormLayout* spellTroopSpawnerFormLayout= new QFormLayout();
    spellTroopSpawnerFormLayout->addRow(spawnTimeSpellTroopSpawnerLabel, timeSpawnEditSpellTroopSpawner);

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
    QWidget* troopWidget = new QWidget();
    troopWidget->setLayout(troopFormLayout);
    troopWidget->setVisible(false);
    //spellWidget
    QWidget* spellWidget = new QWidget();
    spellWidget->setLayout(spellFormLayout);
    spellWidget->setVisible(false);
    //buildingWidget
    QWidget* buildingWidget = new QWidget();
    buildingWidget->setLayout(buildingFormLayout);
    buildingWidget->setVisible(false);
    //troopSpawnerWidget
    QWidget* troopSpawnerWidget = new QWidget();
    troopSpawnerWidget->setLayout(troopSpawnerFormLayout);
    troopSpawnerWidget->setVisible(false);
    //spellTroopSpawnerWidget
    QWidget* spellTroopSpawnerWidget = new QWidget();
    spellTroopSpawnerWidget->setLayout(spellTroopSpawnerFormLayout);
    spellTroopSpawnerWidget->setVisible(false);
    //buildingTroopSpawnerWidget
    QWidget* buildingTroopSpawnerWidget = new QWidget();
    buildingTroopSpawnerWidget->setLayout(buildingTroopSpawnerFormLayout);
    buildingTroopSpawnerWidget->setVisible(false);
    //attackingBuildingWidget
    QWidget* attackingBuildingWidget = new QWidget();
    attackingBuildingWidget->setLayout(attckingBuildingFormLayout);
    attackingBuildingWidget->setVisible(false);

   /* "Select card type", "Troop", "Spell", "Building", "Troop spawner", "Spell troop spawner",
                                 "Building troop spawner", "Attacking building"};*/

    connect(comboClassEdit, &QComboBox::currentTextChanged, [comboClassEdit, troopWidget,spellWidget,buildingWidget,troopSpawnerWidget,spellTroopSpawnerWidget,
            buildingTroopSpawnerWidget,attackingBuildingWidget] {
                QTimer::singleShot(100,[comboClassEdit, troopWidget,spellWidget,buildingWidget,troopSpawnerWidget,spellTroopSpawnerWidget,
                           buildingTroopSpawnerWidget,attackingBuildingWidget]()->void {
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
                               else if (comboClassEdit->currentText() == "Troop Spawner") {
                                       troopWidget->setVisible(true);
                                       troopSpawnerWidget->setVisible(true);
                                       spellWidget->setVisible(false);
                                       buildingWidget->setVisible(false);
                                       spellTroopSpawnerWidget->setVisible(false);
                                       buildingTroopSpawnerWidget->setVisible(false);
                                       attackingBuildingWidget->setVisible(false);
                               }
                               else if (comboClassEdit->currentText() == "Spell-Troop Spawner") {
                                       troopWidget->setVisible(true);
                                       spellWidget->setVisible(true);
                                       spellTroopSpawnerWidget->setVisible(true);

                                       buildingWidget->setVisible(false);
                                       troopSpawnerWidget->setVisible(false);
                                       buildingTroopSpawnerWidget->setVisible(false);
                                       attackingBuildingWidget->setVisible(false);
                               }
                               else if (comboClassEdit->currentText() == "Building-Troop Spawner") {
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
    });

    QPushButton* choseImg = new QPushButton("Add Img");
    QPushButton* deleteImg = new QPushButton("Delete Img");
    QPushButton* confirmInsert = new QPushButton("Confirm");
    QPushButton* cancelInsert = new QPushButton("Cancel");

    QLabel *BoxImg=new QLabel();
    //DeafultImg
    QPixmap imgDefault = QPixmap(":/img/iconCard/default.png");
    BoxImg->setPixmap(imgDefault);


    if(Edit) pathImg=container[cardPos]->getPath();
    //InserImg
    connect(choseImg, &QPushButton::clicked, [this,BoxImg] {
         QString img= QFileDialog::getOpenFileName(this,tr("Choose"),"../ClashRoyaleDB/img/iconCard",tr("images (*.png *.jpg *.jpeg *.gif)"));
         if(img!=""){
             QFileInfo fi(img);
             QString name=fi.fileName();
             string pathImgCard="/img/iconCard/"+name.toStdString();
             pathImg=pathImgCard;

             BoxImg->setPixmap(img);

         }
         else
         {
               pathImg="/img/iconCard/default.png";
         }
     });
    //DeleteImg
    connect(deleteImg, &QPushButton::clicked, [this,BoxImg] {
       pathImg="/img/iconCard/default.png";
       BoxImg->setPixmap(QPixmap(":/img/iconCard/default.png"));
    });


    connect(confirmInsert, &QPushButton::clicked, [this,comboClassEdit,nameEdit,manaCostEdit,comboRarity,cardLevelEdit,descEdit,
            shieldEdit,troopHealthEdit,hitPerSecondTroopEdit,damagePerSecondTroopEdit,spawnDDEdit,rangeTroopEdit,countEdit,
            spellDamageEdit,crownTowerDamageEdit,radiusEdit,
            buildHealthEdit,lifeTimeBuildEdit,
            timeDescEditTroopSpawner,
            timeSpawnEditSpellTroopSpawner,
            spawnSpeedEdit,
            hitPerSecondAttBuildingEdit,damagePerSecondAttBuildingEdit,rangeAttBuildingEdit, Edit, cardPos] {
        try {
            if ((comboClassEdit->currentText()=="Select card type") || nameEdit->text().isEmpty() || manaCostEdit->text().isEmpty() || comboRarity->currentText()=="Select rarity"
                            || cardLevelEdit->text().isEmpty() || descEdit->document()->isEmpty()) {
                        throw MyException("Some field are empty");
                    }
                    else
                    {

                DeepPtr<Card> card;
                         if (comboClassEdit->currentText() == "Troop" ) {
                             if( shieldEdit->text().isEmpty() || troopHealthEdit->text().isEmpty() || hitPerSecondTroopEdit->text().isEmpty() ||
                                     damagePerSecondTroopEdit->text().isEmpty() || spawnDDEdit->text().isEmpty() || rangeTroopEdit->text().isEmpty() || countEdit->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                                   card=new Troop(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                             cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),shieldEdit->text().toDouble(),troopHealthEdit->text().toDouble(),
                                             hitPerSecondTroopEdit->text().toDouble(),damagePerSecondTroopEdit->text().toDouble(),spawnDDEdit->text().toDouble(),rangeTroopEdit->text().toDouble(),countEdit->text().toUInt());
                          }
                          else if (comboClassEdit->currentText() == "Spell") {
                             if(spellDamageEdit->text().isEmpty() || crownTowerDamageEdit->text().isEmpty() || radiusEdit->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                                 card=new Spell(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                                cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),spellDamageEdit->text().toDouble(),crownTowerDamageEdit->text().toDouble(),radiusEdit->text().toDouble());
                              }
                          else if (comboClassEdit->currentText() == "Building") {
                             if( buildHealthEdit->text().isEmpty() || lifeTimeBuildEdit->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                               card=new Building(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                              cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),buildHealthEdit->text().toDouble(),lifeTimeBuildEdit->text().toDouble());
                           }
                          else if (comboClassEdit->currentText() == "Troop Spawner") {
                             if( shieldEdit->text().isEmpty() || troopHealthEdit->text().isEmpty() || hitPerSecondTroopEdit->text().isEmpty() ||
                                     damagePerSecondTroopEdit->text().isEmpty() || spawnDDEdit->text().isEmpty() || rangeTroopEdit->text().isEmpty() || countEdit->text().isEmpty() || timeDescEditTroopSpawner->text().isEmpty() )
                                 throw MyException("Some field are empty");
                             else
                                 card=new TroopSpawner(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                             cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),shieldEdit->text().toDouble(),troopHealthEdit->text().toDouble(),
                                             hitPerSecondTroopEdit->text().toDouble(),damagePerSecondTroopEdit->text().toDouble(),spawnDDEdit->text().toDouble(),rangeTroopEdit->text().toDouble(),countEdit->text().toUInt(),timeDescEditTroopSpawner->text().toStdString());
                                }
                          else if (comboClassEdit->currentText() == "Spell-Troop Spawner") {
                             if( shieldEdit->text().isEmpty() || troopHealthEdit->text().isEmpty() || hitPerSecondTroopEdit->text().isEmpty() || damagePerSecondTroopEdit->text().isEmpty() || spawnDDEdit->text().isEmpty() ||
                                     rangeTroopEdit->text().isEmpty() || countEdit->text().isEmpty() || spellDamageEdit->text().isEmpty() || crownTowerDamageEdit->text().isEmpty() || radiusEdit->text().isEmpty() || timeSpawnEditSpellTroopSpawner->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                               card=new SpellTroopSpawner(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                                          cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),spellDamageEdit->text().toDouble(),crownTowerDamageEdit->text().toDouble(),radiusEdit->text().toDouble(),shieldEdit->text().toDouble(),troopHealthEdit->text().toDouble(),
                                                          hitPerSecondTroopEdit->text().toDouble(),damagePerSecondTroopEdit->text().toDouble(),spawnDDEdit->text().toDouble(),rangeTroopEdit->text().toDouble(),countEdit->text().toUInt(),timeSpawnEditSpellTroopSpawner->text().toStdString());

                                 }
                          else if (comboClassEdit->currentText() == "Building-Troop Spawner") {
                             if( shieldEdit->text().isEmpty() || troopHealthEdit->text().isEmpty() || hitPerSecondTroopEdit->text().isEmpty() || damagePerSecondTroopEdit->text().isEmpty() || spawnDDEdit->text().isEmpty() ||
                                     rangeTroopEdit->text().isEmpty() || countEdit->text().isEmpty() || buildHealthEdit->text().isEmpty() || lifeTimeBuildEdit->text().isEmpty() || spawnSpeedEdit->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                                card=new BuildingTroopSpawner(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                              cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),buildHealthEdit->text().toDouble(),lifeTimeBuildEdit->text().toDouble(),shieldEdit->text().toDouble(),troopHealthEdit->text().toDouble(),
                                                 hitPerSecondTroopEdit->text().toDouble(),damagePerSecondTroopEdit->text().toDouble(),spawnDDEdit->text().toDouble(),rangeTroopEdit->text().toDouble(),countEdit->text().toUInt(),spawnSpeedEdit->text().toDouble());
                           }
                          else if (comboClassEdit->currentText() == "Attacking Building") {
                             if( buildHealthEdit->text().isEmpty() || lifeTimeBuildEdit->text().isEmpty()  || hitPerSecondAttBuildingEdit->text().isEmpty() || damagePerSecondAttBuildingEdit->text().isEmpty() || rangeAttBuildingEdit->text().isEmpty())
                                 throw MyException("Some field are empty");
                             else
                               card=new AttackingBuilding(pathImg,nameEdit->text().toStdString(),manaCostEdit->text().toUInt(),Card::StringToRarity(comboRarity->currentText().toStdString()),
                                              cardLevelEdit->text().toUInt(),descEdit->toPlainText().toStdString(),buildHealthEdit->text().toDouble(),lifeTimeBuildEdit->text().toDouble(),hitPerSecondAttBuildingEdit->text().toDouble(),damagePerSecondAttBuildingEdit->text().toDouble(),rangeAttBuildingEdit->text().toDouble());
                           }
                              if (Edit) container.remove(static_cast<int>(cardPos));

                              if(isCardNameInContainer(card->getName()))
                                  throw  MyException("This name is alredy insert");
                              else
                              container.insert(card);
                              resetlist();
                              resetSearchAndFilter();
                              clearLayout(infolayout);
                              viewCardInfo(list->count()-1);
                              setStackedWidgetPage(1);
                              insertButton->setVisible(true);
                              deleteButton->setVisible(true);


                        }
        } catch (MyException e) {
             QMessageBox msgBox;
             msgBox.setText(QString::fromStdString(e.getMsgException()));
             if(!StyleWhite)
             {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
             else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
             msgBox.exec();

        }
     });

    connect(cancelInsert, &QPushButton::clicked, [this] {
        insertButton->setVisible(true);
        deleteButton->setVisible(true);
        if(list->count() < 1) setStackedWidgetPage(0);
        else setStackedWidgetPage(1);

    });

    // Set texts when edit
    if(Edit){

        /************ Card attributes ************/
        comboClassEdit->setCurrentText(QString::fromStdString(container[cardPos]->getType()));
        nameEdit->setText(QString::fromStdString(container[cardPos]->getName()));
        manaCostEdit->setText(QString::number(container[cardPos]->getManaCost()));
        comboRarity->setCurrentText(QString::fromStdString(container[cardPos]->RarityToString()));
        cardLevelEdit->setText(QString::number(container[cardPos]->getCardLevel()));
        descEdit->setText(QString::fromStdString(container[cardPos]->getDescription()));
        string dir=QFileInfo(".").absolutePath().toStdString() + "/ClashRoyaleDB";
        QPixmap cardImg= QPixmap(QString::fromStdString(dir+container[cardPos]->getPath()));
        BoxImg->setPixmap(cardImg);

        /************ Other attributes ************/

        QString typeCard= QString::fromStdString(container[cardPos]->getType());

        if (typeCard == "Spell" || typeCard == "Spell-Troop Spawner"){
            Spell* spellCard= dynamic_cast<Spell*> (container[cardPos].operator ->());
            spellDamageEdit->setText(QString::number(std::floor(spellCard->getSpellDamage())));
            crownTowerDamageEdit->setText(QString::number(std::floor(spellCard->getCrownTowerDamage())));
            radiusEdit->setText(QString::number(spellCard->getRadius()));
        }

        if (typeCard == "Troop" || typeCard == "Building-Troop Spawner" || typeCard == "Spell-Troop Spawner" || typeCard == "Troop Spawner") {
            Troop* troopCard= dynamic_cast<Troop*> (container[cardPos].operator ->());
            shieldEdit->setText(QString::number(std::floor(troopCard->getShield())));
            troopHealthEdit->setText(QString::number(std::floor(troopCard->getTroopHealth())));
            hitPerSecondTroopEdit->setText(QString::number(troopCard->getHitxSec()));
            damagePerSecondTroopEdit->setText(QString::number(std::floor(troopCard->getDamagexSec())));
            spawnDDEdit->setText(QString::number(std::floor(troopCard->getSpawnDD())));
            rangeTroopEdit->setText(QString::number(troopCard->getRange()));
            countEdit->setText(QString::number(troopCard->getCount()));
        }

        if (typeCard == "Building" || typeCard == "Building-Troop Spawner" || typeCard == "Attacking Building") {
            Building* buildingCard= dynamic_cast<Building*> (container[cardPos].operator ->());
            buildHealthEdit->setText(QString::number(std::floor(buildingCard->getBuildHealth())));
            lifeTimeBuildEdit->setText(QString::number(buildingCard->getLifeTime()));
        }

        if (typeCard == "Building-Troop Spawner"){
           BuildingTroopSpawner* buildingTroopSpawnerCard= dynamic_cast<BuildingTroopSpawner*> (container[cardPos].operator ->());
           spawnSpeedEdit->setText(QString::number(buildingTroopSpawnerCard->getSpawnSpeed()));
        }

        if (typeCard == "Spell-Troop Spawner"){
           SpellTroopSpawner* spellTroopSpawnerCard= dynamic_cast<SpellTroopSpawner*> (container[cardPos].operator ->());
           timeSpawnEditSpellTroopSpawner->setText(QString::fromStdString(spellTroopSpawnerCard->getTimeSpawn()));
        }

        if (typeCard == "Attacking Building") {
            AttackingBuilding* attackingBuildingCard= dynamic_cast<AttackingBuilding*> (container[cardPos].operator ->());
            hitPerSecondAttBuildingEdit->setText(QString::number(attackingBuildingCard->getHitPerSecond()));
            damagePerSecondAttBuildingEdit->setText(QString::number(attackingBuildingCard->getDamagePerSecond()));
            rangeAttBuildingEdit->setText(QString::number(attackingBuildingCard->getRange()));
        }

        if (typeCard == "Troop Spawner"){
           TroopSpawner* troopSpawnerCard= dynamic_cast<TroopSpawner*> (container[cardPos].operator ->());
           timeDescEditTroopSpawner->setText(QString::fromStdString(troopSpawnerCard->getTimeDesc()));
        }
    }

    // Set size Button And BoxImg
    BoxImg->setFixedSize(190,190);
    BoxImg->setScaledContents(true);
    choseImg->setFixedSize(90,40);
    deleteImg->setFixedSize(90,40);

    //Set size Button Conferm AND Cancel insert
    confirmInsert->setFixedSize(100,50);
    cancelInsert->setFixedSize(100,50);

    // Set icon Button
    //Delete Button
    QPixmap pixmap1(":/img/x.png");
    QIcon ButtonIcon1(pixmap1);
    deleteImg->setIcon(ButtonIcon1);
    // Insert Button
    QPixmap pixmap2(":/img/add.png");
    QIcon ButtonIcon2(pixmap2);
    choseImg->setIcon(ButtonIcon2);

    // ButtonLayout
    QHBoxLayout* buttonImgBoxLayout = new QHBoxLayout();
    buttonImgBoxLayout->addWidget(choseImg);
    buttonImgBoxLayout->addWidget(deleteImg);

    // ImgBoxLayout
    QVBoxLayout* imgBoxLayout = new QVBoxLayout();
    imgBoxLayout->addWidget(BoxImg);
    imgBoxLayout->addLayout(buttonImgBoxLayout);
    imgBoxLayout->setSpacing(2);
    // BoxLayout
    QHBoxLayout* basicCard= new QHBoxLayout();
    basicCard->addLayout(imgBoxLayout);
    basicCard->addLayout(formLayout);
    insertLayout->addLayout(basicCard);

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
    buttonInsertLatout->setMargin(10);
    insertLayout->addLayout(buttonInsertLatout);

}

void MainWindow::setStackedWidgetPage(int index)
{
    stackedWidget->setCurrentIndex(index);
}

/************ Methods for Style Windows ************/

void MainWindow::setWidgetStyle()
{
   mainLayout->setSpacing(6);
   //SetSiz
   setFixedHeight(620);
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   //setStule
   QFile file(":/Style/dark.css");
   file.open(QFile::ReadOnly);
   QString styleSheet = QLatin1String(file.readAll());
   setStyleSheet(styleSheet);
}

void MainWindow::setWidgetStyleWhite(){

   mainLayout->setSpacing(6);
   //setSize
   setFixedHeight(620);
   setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   //set Style
   QFile file(":/Style/white.css");
   file.open(QFile::ReadOnly);
   QString styleSheet = QLatin1String(file.readAll());
   setStyleSheet(styleSheet);
}


/************ Methods for Search & Filters ************/
void MainWindow::findNameCard(const QString& str){
    for (int i = 0; i < list->count(); ++i) {
        QListWidgetItem* listItem = list->item(i);
        if (!listItem->text().toUpper().contains(str.toUpper())) {
            list->takeItem(i);
            --i;
        }
    }
}


int MainWindow::findListItemInContainer(int itemPos) const{
    if (itemPos != -1) {

        for (unsigned int i = 0; i < container.getSize(); ++i) {
            if (QString::fromStdString(container[i]->getName()) == list->item(itemPos)->text())
            return static_cast<int>(i);
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

void MainWindow::filterTypeRarity(const QString &type, const QString &rarity){

    if(type=="All types"&&rarity=="All rarities") resetlist();
    if(rarity!= "All rarities"){
        list->reset();
        list->clear();
        if(type=="All types"){
            for(unsigned int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->RarityToString())== rarity)
                    list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
        else{
            for(unsigned int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->RarityToString())== rarity&& QString::fromStdString(container[i]->getType())== type)
                    list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
    }

    if(type!= "All types"){
        list->reset();
        list->clear();
        if(rarity=="All rarities"){
            for(unsigned int i=0; i<container.getSize(); ++i)
                if(QString::fromStdString(container[i]->getType())== type)
                    list->addItem(new QListWidgetItem(QString::fromStdString(container[i]->getName())));
        }
        else{
            for(unsigned int i=0; i<container.getSize(); ++i)
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

void MainWindow::resetSearchAndFilter(){
    filterRarityBox->setCurrentText("All rarities");
    filterTypeBox->setCurrentText("All types");
    searchbox->clear();
}

bool MainWindow::isCardNameInContainer(std::string cardName) const
{
    for (unsigned int i = 0; i < container.getSize(); ++i) {
        if (container[i]->getName() == cardName)
            return true;
    }
    return false;
}

/************ Methods for Input/Output Files ************/
//Write Json
QJsonObject MainWindow::writeJson(Card *card) const{
    QJsonObject cardJson;
    cardJson["Icon NameFile"] = QString::fromStdString(card->getPath());
    cardJson["Card Name"] = QString::fromStdString(card->getName());
    cardJson["Mana Cost"] = static_cast<int>(card->getManaCost());
    cardJson["Rarity"] = QString::fromStdString(card->RarityToString());
    cardJson["Level"] = static_cast<int>(card->getCardLevel());
    cardJson["Description"] = QString::fromStdString(card->getDescription());

    if(card->getType()== "Building" || card->getType()=="Attacking Building" || card->getType()=="Building-Troop Spawner"){
        Building* buildingCard= dynamic_cast<Building*>(card);
        cardJson["Type"] = QString::fromStdString(buildingCard->getType());
        cardJson["Build Health"] = buildingCard->getBuildHealth();
        cardJson["Life Time"] = buildingCard->getLifeTime();
    }

    if(card->getType()== "Troop" || card->getType()=="Troop Spawner" || card->getType()=="Building-Troop Spawner" || card->getType()=="Spell-Troop Spawner"){
        Troop* troopCard= dynamic_cast<Troop*>(card);
        cardJson["Type"] = QString::fromStdString(troopCard->getType());
        cardJson["Shield"] = troopCard->getShield();
        cardJson["Troop Health"] = troopCard->getTroopHealth();
        cardJson["Hit per Second"] = troopCard->getHitxSec();
        cardJson["Damage per Second"] = troopCard->getDamagexSec();
        cardJson["Spawn Death Damage"] = troopCard->getSpawnDD();
        cardJson["Range"] = troopCard->getRange();
        cardJson["Count"] = static_cast<int>(troopCard->getCount());
    }

    if(card->getType()=="Spell" || card->getType()=="Spell-Troop Spawner"){
        Spell* spellCard= dynamic_cast<Spell*>(card);
        cardJson["Type"] = QString::fromStdString(spellCard->getType());
        cardJson["Damage"] = spellCard->getSpellDamage();
        cardJson["Crown Tower Damage"] = spellCard->getCrownTowerDamage();
        cardJson["Radius"] = spellCard->getRadius();
    }

    if(card->getType()=="Troop Spawner"){
        TroopSpawner* troopSpawnerCard= dynamic_cast<TroopSpawner*>(card);
        cardJson["Type"] = QString::fromStdString(troopSpawnerCard->getType());
        cardJson["Time and Description"] =QString::fromStdString(troopSpawnerCard->getTimeDesc());
    }

    if(card->getType()=="Attacking Building"){
        AttackingBuilding* attackingBuildingCard= dynamic_cast<AttackingBuilding*>(card);
        cardJson["Type"] = QString::fromStdString(attackingBuildingCard->getType());
        cardJson["Hit per Second"] = attackingBuildingCard->getHitPerSecond();
        cardJson["Damage per Second"] = attackingBuildingCard->getDamagePerSecond();
        cardJson["Range"] = attackingBuildingCard->getRange();
    }

    if(card->getType()=="Building-Troop Spawner"){
        BuildingTroopSpawner* buildingTroopSpawnerCard= dynamic_cast<BuildingTroopSpawner*>(card);
        cardJson["Type"] = QString::fromStdString(buildingTroopSpawnerCard->getType());
        cardJson["Spawn Speed"] = buildingTroopSpawnerCard->getSpawnSpeed();
    }

    if(card->getType()=="Spell-Troop Spawner"){
        SpellTroopSpawner* spellTroopSpawnerCard= dynamic_cast<SpellTroopSpawner*>(card);
        cardJson["Type"] = QString::fromStdString(spellTroopSpawnerCard->getType());
        cardJson["Time Spawn"] = QString::fromStdString(spellTroopSpawnerCard->getTimeSpawn());
    }

    return cardJson;

}
//Read Json
void MainWindow::readJson(Card *card, const QJsonObject &obj){
    if (obj.contains("Icon NameFile") && obj["Icon NameFile"].isString())
        card->setPath(obj["Icon NameFile"].toString().toStdString());
    if (obj.contains("Card Name") && obj["Card Name"].isString())
        card->setName(obj["Card Name"].toString().toStdString());
    if (obj.contains("Mana Cost") && obj["Mana Cost"].isDouble())
        card->setManaCost(static_cast<unsigned int>(obj["Mana Cost"].toInt()));
        card->setCardRarity(Card::StringToRarity(obj["Rarity"].toString().toStdString()));
       if (obj.contains("Level") && obj["Level"].isDouble())
        card->setCardLevel(static_cast<unsigned int>(obj["Level"].toInt()));
    if (obj.contains("Description") && obj["Description"].isString())
        card->setDescription(obj["Description"].toString().toStdString());
    if(card->getType()== "Building" || card->getType()=="Attacking Building" || card->getType()=="Building-Troop Spawner"){
        Building* buildingCard= dynamic_cast<Building*>(card);
        if (obj.contains("Build Health") && obj["Build Health"].isDouble())
            buildingCard->setBuildHealth(obj["Build Health"].toDouble());
        if (obj.contains("Life Time") && obj["Life Time"].isDouble())
            buildingCard->setLifeTime(obj["Life Time"].toDouble());
    }

    if(card->getType()== "Troop" || card->getType()=="Troop Spawner" || card->getType()=="Building-Troop Spawner" || card->getType()=="Spell-Troop Spawner"){
        Troop* troopCard= dynamic_cast<Troop*>(card);
        if (obj.contains("Shield") && obj["Shield"].isDouble())
            troopCard->setShield(obj["Shield"].toDouble());
        if (obj.contains("Troop Health") && obj["Troop Health"].isDouble())
            troopCard->setTroopHealth(obj["Troop Health"].toDouble());
        if (obj.contains("Hit per Second") && obj["Hit per Second"].isDouble())
            troopCard->setHitxSec(obj["Hit per Second"].toDouble());
        if (obj.contains("Damage per Second") && obj["Damage per Second"].isDouble())
            troopCard->setDamagexSec(obj["Damage per Second"].toDouble());
        if (obj.contains("Spawn Death Damage") && obj["Spawn Death Damage"].isDouble())
            troopCard->setSpawnDD(obj["Spawn Death Damage"].toDouble());
        if (obj.contains("Range") && obj["Range"].isDouble())
            troopCard->setRange(obj["Range"].toDouble());
        if (obj.contains("Count") && obj["Count"].isDouble())
            troopCard->setCount(static_cast<unsigned int>(obj["Count"].toInt()));
    }

    if(card->getType()=="Spell" || card->getType()=="Spell-Troop Spawner"){
        Spell* spellCard= dynamic_cast<Spell*>(card);
        if (obj.contains("Damage") && obj["Damage"].isDouble())
            spellCard->setSpellDamage(obj["Damage"].toDouble());
        if (obj.contains("Crown Tower Damage") && obj["Crown Tower Damage"].isDouble())
            spellCard->setCrownTowerDamage(obj["Crown Tower Damage"].toDouble());
        if (obj.contains("Radius") && obj["Radius"].isDouble())
            spellCard->setRadius(obj["Radius"].toDouble());
    }

    if(card->getType()=="Troop Spawner"){
        TroopSpawner* troopSpawnerCard= dynamic_cast<TroopSpawner*>(card);
        if (obj.contains("Time and Description") && obj["Time and Description"].isString())
            troopSpawnerCard->setTimeDesc(obj["Time and Description"].toString().toStdString());
    }

    if(card->getType()=="Attacking Building"){
        AttackingBuilding* attackingBuildingCard= dynamic_cast<AttackingBuilding*>(card);
        if (obj.contains("Hit per Second") && obj["Hit per Second"].isDouble())
            attackingBuildingCard->setHitPerSecond(obj["Hit per Second"].toDouble());
        if (obj.contains("Damage per Second") && obj["Damage per Second"].isDouble())
            attackingBuildingCard->setDamagePerSecond(obj["Damage per Second"].toDouble());
        if (obj.contains("Range") && obj["Range"].isDouble())
            attackingBuildingCard->setRange(obj["Range"].toDouble());
    }

    if(card->getType()=="Building-Troop Spawner"){
        BuildingTroopSpawner* buildingTroopSpawnerCard= dynamic_cast<BuildingTroopSpawner*>(card);
        if (obj.contains("Spawn Speed") && obj["Spawn Speed"].isDouble())
            buildingTroopSpawnerCard->setSpawnSpeed(obj["Spawn Speed"].toDouble());
    }

    if(card->getType()=="Spell-Troop Spawner"){
        SpellTroopSpawner* spellTroopSpawnerCard= dynamic_cast<SpellTroopSpawner*>(card);
        if (obj.contains("Time Spawn") && obj["Time Spawn"].isString())
            spellTroopSpawnerCard->setTimeSpawn(obj["Time Spawn"].toString().toStdString());
    }

}
//Load File
void MainWindow::loadFile(){
    QString fileName = QFileDialog::getOpenFileName(this->menu, tr("Open File"), "../ClashRoyaleDB/Load&Save", tr("JSON files (*.json)"));
        if (!fileName.isEmpty()) {
            if (!fileName.endsWith(".json")) {
                QMessageBox msgBox;
                msgBox.setText("Invalid format. Please select a .json file.");
                if(!StyleWhite)
                {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
                else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
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
                    if(!StyleWhite)
                    {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
                    else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
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
                                            else if (type == "Building-Troop Spawner") card = new BuildingTroopSpawner();
                                            else if (type == "Spell-Troop Spawner") card = new SpellTroopSpawner();
                                            else if (type == "Attacking Building") card = new AttackingBuilding();
                                            else if (type == "Troop Spawner") card = new TroopSpawner();
                                            readJson(card.operator ->(),obj);
                                            container.insert(card);
                                        }
                               }
                    clearLayout(infolayout);
                    resetlist();
                      }
              }

        }
}
//Save File
void MainWindow::saveFile() const{
     if (container.getSize() != 0) {
        QString fileName = QFileDialog::getSaveFileName(this->menu, tr("Save File"), "../ClashRoyaleDB/Load&Save", tr("JSON files (*.json)"));
        if (!fileName.endsWith(".json"))
            fileName.append(".json");
        QJsonArray arrayJson;
       //ciclo il container e faccio il push sull Json
        for (unsigned int i = 0; i < container.getSize(); ++i)
        arrayJson.push_back(QJsonValue(writeJson(container[i].operator ->())));
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
        if(!StyleWhite)
        {msgBox.setStyleSheet("background-color: rgb(30,30,30); color: rgb(225,225,225);");}
        else{msgBox.setStyleSheet("background-color: rgb(220,220,220);");}
        msgBox.exec();
    }
}
