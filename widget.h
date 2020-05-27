#ifndef WIDGET_H
#define WIDGET_H

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
class Widget : public QMainWindow
{
    Q_OBJECT
private:
    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QListWidget* list;
    QListWidget* list2;

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
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
