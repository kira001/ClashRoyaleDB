#include "MainWindow.h"
#include "Controller/controller.h"

Widget::Widget(QWidget *parent) : QMainWindow(parent)
{

MainWindow::MainWindow(Controller* c,QWidget *parent)
    : QMainWindow(parent),controller(c)
{
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
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);



}
void MainWindow::addLeftLayout()
{
    QScrollArea* box= new QScrollArea();

    box->setWidget(list);
    box->setWidgetResizable(true);
    box->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* insertButton = new QPushButton("Insert");
    QPushButton* searchButton = new QPushButton("Search");

    //connect(insertButton, SIGNAL(clicked()),controller,SLOT(addCard()));
      string NameCard="controller->getLastInsert()";
    connect(insertButton, &QPushButton::clicked, [this,NameCard ] {
        addCardView(NameCard);
    });
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(searchButton);


    leftLayout->addWidget(box);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);

}

void MainWindow::addMenu()
{
    //Creare la barra dei menu , poi il menu, poi le azioni
    //QMenuBar* menubar= new QMenuBar(this);
    //QMenu *menu =new QMenu("File",menubar);
    QAction* save= new QAction("Save",menu);
    QAction* load=new QAction("Load",menu);


    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);

    //test della funzione loadFile e saveFile
    connect(load, &QAction::triggered, [this] {
            loadFile();
       });
    connect(save, &QAction::triggered, [this] { saveFile(); });

    //Aggiungo il menu alla barra
    menubar->addMenu(menu);

    // Aggiungo la barra al Layout
    setMenuBar(menubar);
}

void MainWindow::addRightLayout()
{

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
                } //else if Caso dove trovo stessi nomi di tipo es Troop -> creo un nuovo oggeto
    }}


}

void MainWindow::saveFile() const{

    // if (container.getSize() != 0) {
        QString fileName = QFileDialog::getSaveFileName(this->menu, tr("Save container"), "../ClashRoyale", tr("JSON files (*.json)"));
        if (!fileName.endsWith(".json"))
            fileName.append(".json");
        QJsonArray arrayJson;
       //ciclo il container e faccio il push sull Json
       // for (unsigned int i = 0; i < container.getSize(); ++i)
       //     arrayJson.push_back(QJsonValue(container[i]->serialize()));
        QJsonDocument docJson(arrayJson);
        QString docString = docJson.toJson();
        QFile saveFile(fileName);
        saveFile.open(QIODevice::WriteOnly);
        saveFile.write(docString.toUtf8());
        saveFile.close();
   // }
   // else {
   //     QMessageBox msgBox;
   //     msgBox.setText("The container is empty.");
   //     msgBox.exec();
   // }

}


Widget::~Widget()
{
}

void MainWindow::addCardView(string s)
{


  //  std::cout<<NameCard;
    list->addItem(new QListWidgetItem(QString::fromStdString(s)));



}
