#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>

#include "Model/Card.h"
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QListWidget* list;
    QListWidget* list2;
    Controller* controller;

    void addLeftLayout();
    void addMenu();
    void addRightLayout();
public:
    MainWindow(Controller* c,QWidget *parent = nullptr);
    ~MainWindow();
    void addCardView(string);
};
#endif // MAINWINDOWH
