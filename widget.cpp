#include "widget.h"



Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget=new QWidget(this);
    mainLayout=new QVBoxLayout(this);
    dataLayout=new QHBoxLayout(this);
    infoItemLayout= new QVBoxLayout(this);
    list = new QListWidget(this);

    addInfoLayout();
    addMenu();
    addButton();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}
void Widget::addInfoLayout()
{
    QScrollArea* box= new QScrollArea();

    box->setWidget(list);
    box->setWidgetResizable(true);
    box->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QScrollArea* box2= new QScrollArea();

        box->setWidget(list);
        box->setWidgetResizable(true);
        box->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    dataLayout->addWidget(box);
    dataLayout->addWidget(box2);
    mainLayout->addLayout(dataLayout);

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

void Widget::addButton()
{
    QHBoxLayout* buttonLayout=new QHBoxLayout(this);
     QPushButton* insertButton = new QPushButton("Insert");
      QPushButton* mButton = new QPushButton("aasvasv");
      QPushButton* moButton = new QPushButton("modifica");
     buttonLayout->addWidget(insertButton);
     buttonLayout->addWidget(mButton);
     buttonLayout->addWidget(moButton);
     mainLayout->addLayout(buttonLayout);
}

Widget::~Widget()
{
}

