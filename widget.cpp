#include "widget.h"



Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
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
void Widget::addLeftLayout()
{
    QScrollArea* box= new QScrollArea();

    box->setWidget(list);
    box->setWidgetResizable(true);
    box->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
    QPushButton* insertButton = new QPushButton("Insert");
    QPushButton* mButton = new QPushButton("cerca");

    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(mButton);


    leftLayout->addWidget(box);
    leftLayout->addLayout(buttonLayout);

    mainLayout->addLayout(leftLayout);

}

void Widget::addMenu()
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

void Widget::addRightLayout()
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

Widget::~Widget()
{
}

