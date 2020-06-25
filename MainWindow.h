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
#include <QStackedWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QCompleter>
#include <QLabel>
#include <QImage>
#include<QTextEdit>
//stacked W
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Container<DeepPtr<Card>> container;
    QWidget* mainWidget;
    QWidget* infoWidget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* infolayout;
    QVBoxLayout* rightLayout;
    QListWidget* list;
    QWidget* insertWidget;
    QVBoxLayout* insertLayout;


    QListWidget* list2;
    QStackedWidget *stackedWidget;

    QLineEdit* searchbox; //Search
    QCompleter* completer; //SuggestionWordsFromSearch
    QMessageBox* popup;
    QComboBox* filterTypeBox;
    QComboBox* filterRarityBox;
    // Menu
    QMenu* menu;
    QMenu* menu2;
    QMenuBar* menubar;
    // Methods
    void setToolBar();
    void loadFile();
    void saveFile() const;
    void addLeftLayout();
    void addMenu();
    void addRightLayout();
    void setWidgetStyle();
    void setWidgetStyleWhite();
    void basicInfoWidget();
    void viewCardInfo(int);
    void addInsertWidget();
    void setStackedWidgetPage(int);
    void findNameCard(const QString& std);
    void resetlist(); // "Ripristina lista originale" utile per filtrare o per il search
    void infoguide();
    int findListItemInContainer(int itemPos) const;
    void showInfoCard(int);
    void clearLayout(QLayout*);
    void filterTypeRarity(const QString& type, const QString &rarity);
    void combineSearchAndFilter(const QString& searchTxt, const QString& filterTypeTxt, const QString& filterRarityTxt);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addCardView(string);
};
#endif // MAINWINDOWH
