#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/Card.h"
#include "Template/deepptr.h"
#include "Template/container.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>

#include <QIcon> // Aggiunte
#include <QFileDialog>
#include <QToolBar>
#include <QMessageBox>
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

    // Toolbar
    // QToolBar* toolbar;
    // Menu
    QMenu* menu;
    QMenuBar* menubar;
    // Methods
    void loadFile();
    void saveFile() const;
    void addLeftLayout();
    void addMenu();
    void addRightLayout();
public:
    MainWindow(Controller* c,QWidget *parent = nullptr);
    ~MainWindow();
    void addCardView(string);
};
#endif // MAINWINDOWH
