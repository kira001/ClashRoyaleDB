MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    setWindowIcon(QIcon(":/img/insertIcon/icon.png"));
    QWidget::setWindowTitle ("ClashRoyaleWiki");

    mainWidget=new QWidget(this);
    mainLayout=new QHBoxLayout;
    stackedWidget = new QStackedWidget;
@@ -53,7 +53,7 @@ void MainWindow::resetlist(){
void MainWindow::infoguide() const{
    QMessageBox Box;
    Box.setWindowTitle("About");
    Box.setText("\n\n Welcome to ClashRoyaleWiki v1.0");
    Box.setText("\n\n Welcome to ClashRoyale Wiki v1.0");
    Box.setInformativeText("\n Developed by \n KokoGorillaTEAM \n");
    QPixmap logo = QPixmap(":/img/insertIcon/infobox.png");
    logo = logo.scaledToWidth(150);
@@ -634,7 +634,7 @@ void MainWindow::viewCardInfo(int pos)
  cardLabel->setFixedSize(190,190);
  cardLabel->setScaledContents(true);
  //Set Layout
  buttonLayout->setMargin(12);
  buttonLayout->setMargin(10);
  imgAndButton->addWidget(cardLabel);
  buttonUpAndDown->addWidget(lvDowngrade);
  buttonUpAndDown->addWidget(lvUpgrade);
@@ -1307,7 +1307,7 @@ void MainWindow::addInsertWidget(bool Edit, unsigned int cardPos)
    QHBoxLayout* buttonInsertLatout=new QHBoxLayout();
    buttonInsertLatout->addWidget(confirmInsert);
    buttonInsertLatout->addWidget(cancelInsert);
    buttonInsertLatout->setMargin(12);
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
    setStackedWidgetPage(0);
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
     if (obj.contains("Rarity") && Card::StringToRarity(obj["Rarity"].toString().toStdString()))
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
