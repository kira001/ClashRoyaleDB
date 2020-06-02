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
    menubar= new QMenuBar();
    searchbox= new QLineEdit();
    completer= new QCompleter();
    menu =new QMenu("File",menubar);
    toolbar = new QToolBar();
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
    Box.setStyleSheet("background-color: rgb(18,18,18); color: rgb(255, 255, 255)");
    Box.exec();
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
    searchbox->setClearButtonEnabled(true);
    searchbox->addAction(QIcon(":/img/whitesearch2.icns"), QLineEdit::LeadingPosition);
    searchbox->setPlaceholderText("Search");


    QStringList wordList;
    wordList << "farid" << "koko" << "ian" ; //test Parole da suggerire

    QCompleter *completer = new QCompleter(wordList, searchbox);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    searchbox->setCompleter(completer);

    connect(searchbox, &QLineEdit::textChanged, [this] {
         if (container.getSize() > 0)
             findNameCard(searchbox->text());
     });

    leftLayout->addWidget(box);
    leftLayout->addWidget(searchbox);
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
    QAction* info=new QAction(QIcon(":/img/info.png"), "info");

    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);

    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {loadFile();});
    connect(save, &QAction::triggered, [this] { saveFile(); });

    //Aggiungo il menu alla barra
    menubar->addMenu(menu);
    menubar->addAction(info);

    connect(info, &QAction::triggered, [this] { infoguide(); });

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

    //test immagine destra
    QPixmap testlogo = QPixmap(":/img/koko.png");
    testlogo = testlogo.scaledToWidth(150);
    QLabel* logoLabel = new QLabel;
    logoLabel->setPixmap(testlogo);

    buttonLayout->addWidget(editButton);
    rightLayout->addWidget(logoLabel);
    rightLayout->addWidget(box2);
    rightLayout->addLayout(buttonLayout);

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
