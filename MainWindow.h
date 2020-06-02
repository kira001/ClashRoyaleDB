#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/Card.h"
#include "Model/Troop.h"
#include "Model/TroopSpawner.h"
#include "Model/Spell.h"
#include "Model/Building.h"
#include "Model/BuildingTroopSpawner.h"
#include "Model/AttackingBuilding.h"
#include "Model/SpellTroopSpawner.h"
#include "Template/deepptr.h"
#include "Template/container.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QPixmap>
#include <QIcon> // Aggiunte
#include <QFileDialog>
#include <QToolBar>
#include <QMessageBox>
#include <QLineEdit>
#include <QCompleter>
#include <QLabel>

//stacked W
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Container<DeepPtr<Card>> container;
    QWidget* mainWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;
    QListWidget* list;
    QListWidget* list2;
    QLineEdit* searchbox; //Search
    QCompleter* completer; //SuggestionWordsFromSearch


    // Toolbar
    QToolBar* toolbar;
    // Menu
    QMenu* menu;
    QMenuBar* menubar;
    // Methods
    void loadFile();
    void saveFile() const;
    void addLeftLayout();
    void addMenu();
    void addRightLayout();
    void setWidgetStyle();
    void findNameCard(const QString& std);
    void resetlist(); // "Ripristina lista originale" utile per filtrare o per il search
    void infoguide();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addCardView(string);
};
#endif // MAINWINDOWH
