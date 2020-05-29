#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    setWindowIcon(QIcon(":/img/icon.png"));
    setFixedSize(980, 620);

    mainWidget=new QWidget(this);
    mainLayout=new QHBoxLayout(this);
    leftLayout=new QVBoxLayout(this);
    rightLayout=new QVBoxLayout(this);
    list = new QListWidget();
    list2 = new QListWidget();
    menubar= new QMenuBar();
    menu =new QMenu("File",menubar); //inizializzo l'oggetto
    addMenu();
    addLeftLayout();
    addRightLayout();
    //setWidgetStyle();
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);





}
MainWindow::~MainWindow(){
}
void MainWindow::addLeftLayout(){
    QScrollArea* box= new QScrollArea();

    box->setWidget(list);
    box->setWidgetResizable(true);
    box->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* insertButton = new QPushButton("Insert");
    QPushButton* searchButton = new QPushButton("Search");

    //connect(insertButton, SIGNAL(clicked()),controller,SLOT(addCard()));
      string NameCard="controller->getLastInsert()";
    connect(insertButton, &QPushButton::clicked, [this] {
        addCardView(container[0]->getName());
    });
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(searchButton);


    leftLayout->addWidget(box);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);


}

void MainWindow::addMenu(){
    //Creare la barra dei menu , poi il menu, poi le azioni
    //QMenuBar* menubar= new QMenuBar(this);
    //QMenu *menu =new QMenu("File",menubar);
    QAction* save= new QAction("Save",menu);
    QAction* load=new QAction("Load",menu);


    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);

    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {loadFile();});
    connect(save, &QAction::triggered, [this] { saveFile(); });

    //Aggiungo il menu alla barra
    menubar->addMenu(menu);

    // Aggiungo la barra al Layout
    setMenuBar(menubar);
}

void MainWindow::addRightLayout(){

    QScrollArea* box2= new QScrollArea();

    box2->setWidget(list2);
    box2->setWidgetResizable(true);
    box2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* editButton = new QPushButton("Edit");


    buttonLayout->addWidget(editButton);

    rightLayout->addWidget(box2);
    rightLayout->addLayout(buttonLayout);

    mainLayout->addLayout(rightLayout);
}

void MainWindow::loadFile(){
    QString fileName = QFileDialog::getOpenFileName(this->menu, tr("Open container"), "../ClashRoyale", tr("JSON files (*.json)"));
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
                                            string cardList=container[0]->getName()+" ["+ std::to_string(container[0]->getCardLevel())+"]";
                                            list->addItem(new QListWidgetItem(QString::fromStdString(cardList)));

                                        }
                               }

                      }
              }

        }
}

void MainWindow::saveFile() const{
     if (container.getSize() != 0) {
        QString fileName = QFileDialog::getSaveFileName(this->menu, tr("Save container"), "../ClashRoyale/Load&Save", tr("JSON files (*.json)"));
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
    mainLayout->setSpacing(0);

    // Imposto le dimensioni
    setMinimumSize(QSize(500,500));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Imposto il foglio di stile
    QFile file(":/Style/test.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}
