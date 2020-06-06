#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){


    setWindowIcon(QIcon(":/img/icon.png"));
    setFixedSize(980,620);

    mainWidget=new QWidget(this);
    mainLayout=new QHBoxLayout(this);

    leftLayout=new QVBoxLayout(this);
    rightLayout=new QVBoxLayout(this);
    list = new QListWidget();
    list2 = new QListWidget();
    stackedWidget = new QStackedWidget();
    menubar= new QMenuBar();
    searchbox= new QLineEdit();
    completer= new QCompleter();
    menu =new QMenu("File",menubar);
    popup=new QMessageBox();
    insertWidget=new QWidget();

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
   { string c=container[i]->getName()+" ["+ std::to_string(container[i]->getCardLevel())+"]";
    list->addItem(new QListWidgetItem(QString::fromStdString(c)));
    }


}
void MainWindow::infoguide(){
    QMessageBox Box;

    Box.setWindowTitle("Info");
    Box.setText("\n\n Welcome to ClashRoyale v1.0 \n\n Developed by \n KokoGorillaTEAM \n\n");
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
    QPushButton* searchButton = new QPushButton("Search");
    insertButton->setFixedSize(100,50);
    searchButton->setFixedSize(100,50);




    //connect(insertButton, SIGNAL(clicked()),controller,SLOT(addCard()));
      string NameCard="controller->getLastInsert()";
    connect(insertButton, &QPushButton::clicked, [this] {
       setStackedWidgetPage(1);
    });
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(searchButton);
    searchbox->setClearButtonEnabled(true);
    searchbox->addAction(QIcon(":/img/whitesearch.png"), QLineEdit::LeadingPosition);
    searchbox->setPlaceholderText("Search");
    searchbox->setFixedSize(190,30);

    QStringList wordList;
    wordList << "farid" << "koko" << "ian" ; //test Parole da suggerire

    QCompleter *completer = new QCompleter(wordList, searchbox);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    searchbox->setCompleter(completer);

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

    QAction* save= new QAction("Save",menu);
    QAction* load=new QAction("Load",menu);
    QAction* about=new QAction("About");
    QAction* info=new QAction(QIcon(":img/info.png"), "info"); //Da definire

    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);

    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {loadFile();});
    connect(save, &QAction::triggered, [this] { saveFile(); });

    //Aggiungo il menu alla barra
    menubar->addMenu(menu);
    menubar->addAction(about);
    menubar->addAction(info);
    menubar->setFixedHeight(40);
    connect(about, &QAction::triggered, [this] { infoguide(); });
    connect(info, &QAction::triggered, [this] { infoguide(); });

    // Aggiungo la barra al Layout
    setMenuBar(menubar);
}

void MainWindow::addRightLayout(){
    addInfoWidget();
    addInsertWidget();
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




void MainWindow::addCardView(string s){
  //  std::cout<<NameCard;

    list->addItem(new QListWidgetItem(QString::fromStdString(s)));
}

void MainWindow::setWidgetStyle()
{
    mainLayout->setSpacing(6);
    // Imposto le dimensioni
   setMinimumSize(QSize(1200,500));
   setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Imposto il foglio di stile
  QFile file(":/Style/test.css");
  file.open(QFile::ReadOnly);
   QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}

void MainWindow::addInfoWidget()
{/*

    QPushButton* insertButton = new QPushButton("Insert");
    QPushButton* insertButtonn = new QPushButton("load");
    QPushButton* insertButtonnn = new QPushButton("save");


   stackedWidget->addWidget(insertButton);
   stackedWidget->addWidget(insertButtonn);
   stackedWidget->addWidget(insertButtonnn);

   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(stackedWidget);




QPushButton* page1 = new QPushButton("page1");
     connect(page1, &QPushButton::clicked, [this,stackedWidget] {
        stackedWidget->setCurrentIndex(0);
     });
     QPushButton* page2 = new QPushButton("page2");
     connect(page2, &QPushButton::clicked, [this,stackedWidget] {
        stackedWidget->setCurrentIndex(1);
     });
     QPushButton* page3 = new QPushButton("page3");
     connect(page3, &QPushButton::clicked, [this,stackedWidget] {
        stackedWidget->setCurrentIndex(2);
     });

     layout->addWidget(page1);
     layout->addWidget(page2);
     layout->addWidget(page3);*/

    QScrollArea* box2= new QScrollArea();

    box2->setWidget(list2);
    box2->setWidgetResizable(true);
    box2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* editButton = new QPushButton("Edit");


    buttonLayout->addWidget(editButton);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(box2);
    layout->addLayout(buttonLayout);

    QWidget* infoWidget=new QWidget();
    infoWidget->setLayout(layout);
    stackedWidget->addWidget(infoWidget);
}

void MainWindow::addInsertWidget()
{
    QStringList classList = {"Select card type", "Troop", "Spell", "Building", "Troop spawner", "Spell troop spawner",
                             "Building troop spawner", "Attacking building"};
    QComboBox* comboClassEdit = new QComboBox;
    comboClassEdit->addItems(classList);
    comboClassEdit->insertSeparator(1);

    /*******************    CARD   ********************/
    // Name
    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setMaxLength(20);

    // manaCost
    QLineEdit* manaCostEdit = new QLineEdit();
    QValidator* manaCostValidator = new QIntValidator(1, 10);
    manaCostEdit->setValidator(manaCostValidator);

    // cardRarity
    QStringList classRarity = {"Select rarity","Common","Rare","Epic","Legendary"};
    QComboBox* comboRarity = new QComboBox;
    comboRarity->addItems(classRarity);
    comboRarity->insertSeparator(1);

    // cardLevel
    QLineEdit* cardLevelEdit = new QLineEdit();
    QValidator* cardLevelValidator = new QIntValidator(1, 13);
    cardLevelEdit->setValidator(cardLevelValidator);

    // Descrizione
    QTextEdit* descEdit = new QTextEdit();

    // -----> CardForm <------
    QFormLayout* formLayout= new QFormLayout();
    formLayout->insertRow(0, "Card type", comboClassEdit);
    formLayout->insertRow(1, "Name", nameEdit);
    formLayout->insertRow(2, "Mana cost (max:10)",manaCostEdit);
    formLayout->insertRow(3, "Rarity",comboRarity);
    formLayout->insertRow(4, "Level (max:13)",cardLevelEdit);
    formLayout->insertRow(5, "Descrizione", descEdit);



    /*******************    TROOP   ********************/
    // shield
    QLineEdit* shieldEdit = new QLineEdit();
    QValidator* shieldValidator = new QDoubleValidator(0,99999,6);
    shieldEdit->setValidator(shieldValidator);

    //troopHealth
    QLineEdit* troopHealthEdit = new QLineEdit();
    QValidator* troopHealthValidator = new QDoubleValidator(0,99999,6);
    troopHealthEdit->setValidator(troopHealthValidator);

    //hitxSec
    QLineEdit* hitPerSecondTroopEdit = new QLineEdit();
    QValidator* hitPerSecondTroopValidator = new QDoubleValidator(0,99999,6);
    hitPerSecondTroopEdit->setValidator(hitPerSecondTroopValidator);
    hitPerSecondTroopEdit->setPlaceholderText("Hit (per second)");

    //damagexSec
    QLineEdit* damagePerSecondTroopEdit = new QLineEdit();
    QValidator* damagePerSecondTroopValidator = new QDoubleValidator(0,99999,6);
    damagePerSecondTroopEdit->setValidator(damagePerSecondTroopValidator);

    //spawnDD--->SpawnDeathDamage
    QLineEdit* spawnDDEdit = new QLineEdit();
    QValidator* spawnDDValidator = new QDoubleValidator(0,99999,6);
    spawnDDEdit->setValidator(spawnDDValidator);

    //range
    QLineEdit* rangeTroopEdit = new QLineEdit();
    QValidator* rangeTroopValidator = new QDoubleValidator(0,99999,6);
    rangeTroopEdit->setValidator(rangeTroopValidator);

    //count
    QLineEdit* countEdit = new QLineEdit();
    QValidator* countValidator = new QIntValidator(1, 99999);
    countEdit->setValidator(countValidator);

    QPixmap hitPerSecondIcon= QPixmap(":/img/insertIcon/hitPerSecond.png");
    QLabel* hitPerSecondLabel= new QLabel();
    hitPerSecondLabel->setPixmap(hitPerSecondIcon);
    // -----> TroopForm <------
    QFormLayout* troopFormLayout= new QFormLayout();
    troopFormLayout->addRow("Shield", shieldEdit);
    troopFormLayout->addRow("Troop healt", troopHealthEdit);
    troopFormLayout->addRow( hitPerSecondLabel,hitPerSecondTroopEdit);
    troopFormLayout->addRow("Damage (per second)", damagePerSecondTroopEdit);
    troopFormLayout->addRow("Spawn/Death Damage", spawnDDEdit);
    troopFormLayout->addRow("Troop range", rangeTroopEdit);
    troopFormLayout->addRow("Count", countEdit);



    /*******************    SPELL   ********************/
    // spellDamage
    QLineEdit* spellDamageEdit = new QLineEdit();
    QValidator* spellDamageValidator = new QDoubleValidator(0,99999,6);
    spellDamageEdit->setValidator(spellDamageValidator);

    //crownTowerDamage
    QLineEdit* crownTowerDamageEdit = new QLineEdit();
    QValidator* crownTowerDamageValidator = new QDoubleValidator(0,99999,6);
    crownTowerDamageEdit->setValidator(crownTowerDamageValidator);

    //radius
    QLineEdit* radiusEdit = new QLineEdit();
    QValidator* radiusValidator = new QDoubleValidator(0,99999,6);
    radiusEdit->setValidator(radiusValidator);

    // -----> SpellForm <-----
    QFormLayout* spellFormLayout= new QFormLayout();
    spellFormLayout->addRow("Spell damage", spellDamageEdit);
    spellFormLayout->addRow("Tower damage", crownTowerDamageEdit);
    spellFormLayout->addRow("Radius", radiusEdit);



    /*******************    BUILDING   ********************/
    // buildHealth
    QLineEdit* buildHealthEdit = new QLineEdit();
    QValidator* buildHealthValidator = new QDoubleValidator(0,99999,6);
    buildHealthEdit->setValidator(buildHealthValidator);

    //lifeTime
    QLineEdit* lifeTimeEdit = new QLineEdit();
    QValidator* lifeTimeValidator = new QDoubleValidator(0,99999,6);
    lifeTimeEdit->setValidator(lifeTimeValidator);

    // -----> BuildingForm <-----
    QFormLayout* buildingFormLayout= new QFormLayout();
    buildingFormLayout->addRow("Troop health", buildHealthEdit);
    buildingFormLayout->addRow("Life time", lifeTimeEdit);



     /*******************    TROOP-SPAWNER  ********************/

    // TimeDesc
    QLineEdit* timeDescEdit = new QLineEdit();
    timeDescEdit->setMaxLength(50);

    // -----> TroopSpawnerForm <-----
    QFormLayout* troopSpawnerFormLayout= new QFormLayout();
    troopSpawnerFormLayout->addRow("Time and description of the cause", timeDescEdit);



    /*******************    SPELL-TROOP-SPAWNER  ********************/

    // TimeDesc
    QLineEdit* timeSpawnEdit = new QLineEdit();
    timeSpawnEdit->setMaxLength(50);

    // -----> SpellTroopSpawnerForm <-----
    QFormLayout* spellTroopSpawnerFormLayout= new QFormLayout();
    spellTroopSpawnerFormLayout->addRow("Time and description of the cause", timeSpawnEdit);


    /*******************    BUILDING-TROOP-SPAWNER  ********************/

    // SpawnSpeed
    QLineEdit* spawnSpeedEdit = new QLineEdit();
    QValidator* spawnSpeedValidator = new QDoubleValidator(0,99999,6);
    spawnSpeedEdit->setValidator(spawnSpeedValidator);

    // -----> BuildingTroopSpawnerForm <-----
    QFormLayout* buildingTroopSpawnerFormLayout= new QFormLayout();
    buildingTroopSpawnerFormLayout->addRow("Spawn speed(in sec)", spawnSpeedEdit);


    /*******************   ATTACKING BUILDING   ********************/
    /* double hitPerSecond;
    double damagePerSecond;
    double range;*/
    // hitPerSecond
    QLineEdit* hitPerSecondAttBuildingEdit = new QLineEdit();
    QValidator* hitPerSecondAttBuildingValidator = new QDoubleValidator(0,99999,6);
    hitPerSecondAttBuildingEdit->setValidator(hitPerSecondAttBuildingValidator);

    // damagePerSecond
    QLineEdit* damagePerSecondAttBuildingEdit = new QLineEdit();
    QValidator* damagePerSecondAttBuildingValidator = new QDoubleValidator(0,99999,6);
    damagePerSecondAttBuildingEdit->setValidator(damagePerSecondAttBuildingValidator);

    // range
    QLineEdit* rangeAttBuildingEdit = new QLineEdit();
    QValidator* rangeAttBuildingValidator = new QDoubleValidator(0,99999,6);
    rangeAttBuildingEdit->setValidator(rangeAttBuildingValidator);

    // -----> AttackingBuildingForm <-----
    QFormLayout* attckingBuildingFormLayout= new QFormLayout();
    attckingBuildingFormLayout->addRow("Hit (per second)", hitPerSecondAttBuildingEdit);
    attckingBuildingFormLayout->addRow("Damage (per second)", damagePerSecondAttBuildingEdit);
    attckingBuildingFormLayout->addRow("Range", rangeAttBuildingEdit);






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

    insertWidget->setLayout(insertLayout);
    stackedWidget->addWidget(insertWidget);
}

void MainWindow::setStackedWidgetPage(int index)
{
    stackedWidget->setCurrentIndex(index);
}
