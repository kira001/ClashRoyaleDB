#include "MainWindow.h"
#include "Controller/controller.h"


MainWindow::MainWindow(Controller* c,QWidget *parent)
    : QMainWindow(parent),controller(c)
{
    mainWidget=new QWidget(this);
    mainLayout=new QHBoxLayout(this);
    leftLayout=new QVBoxLayout(this);
    rightLayout=new QVBoxLayout(this);
    list = new QListWidget();
    list2 = new QListWidget();
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
    QPushButton* mButton = new QPushButton("cerca");

    //connect(insertButton, SIGNAL(clicked()),controller,SLOT(addCard()));
      string NameCard="controller->getLastInsert()";
    connect(insertButton, &QPushButton::clicked, [this,NameCard ] {
        addCardView(NameCard);
    });
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(mButton);


    leftLayout->addWidget(box);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);

}

void MainWindow::addMenu()
{
    //Creare la barra dei menu , poi il menu, poi le azioni
    QMenuBar* menubar= new QMenuBar(this);
    QMenu *menu =new QMenu("File",menubar);
    QAction* save= new QAction("Save",menu);
    QAction* load=new QAction("Load",menu);


    //Aggiungo le azioni al menu
    menu->addAction(save);
    menu->addAction(load);

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
    QPushButton* modificaButton = new QPushButton("Modifica");


    buttonLayout->addWidget(modificaButton);

    rightLayout->addWidget(box2);
    rightLayout->addLayout(buttonLayout);

    mainLayout->addLayout(rightLayout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addCardView(string s)
{


  //  std::cout<<NameCard;
    list->addItem(new QListWidgetItem(QString::fromStdString(s)));



}

