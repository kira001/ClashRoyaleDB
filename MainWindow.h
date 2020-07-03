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
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QStackedWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QCompleter>
#include <QLabel>
#include <QImage>
#include <QTextEdit>
#include <QTimer>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Container<DeepPtr<Card>> container;
    QWidget* mainWidget;
    QWidget* infoWidget;
    QWidget* insertWidget;
    QListWidget* list;
    QStackedWidget *stackedWidget;
    //Layout
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftLayout;
    QVBoxLayout* infolayout;
    QVBoxLayout* rightLayout;
    QVBoxLayout* insertLayout;
    // Search & Filter
    QLineEdit* searchbox;
    QCompleter* completer;
    QComboBox* filterTypeBox;
    QComboBox* filterRarityBox;
    //Buttons Delete & Insert
    QPushButton* insertButton;
    QPushButton* deleteAllButton;
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
    void addInsertWidget(bool Edit=false, unsigned int cardPos=0);
    void setStackedWidgetPage(int);
    void findNameCard(const QString& std);
    void resetlist();
    void infoguide() const;
    int findListItemInContainer(int itemPos) const;
    void clearLayout(QLayout*);
    void filterTypeRarity(const QString& type, const QString &rarity);
    void combineSearchAndFilter(const QString& searchTxt, const QString& filterTypeTxt, const QString& filterRarityTxt);
    void resetSearchAndFilter();
    bool isCardNameInContainer(string cardName) const;
    QJsonObject writeJson(Card* card) const;
    void readJson(Card* card, const QJsonObject& obj);
    //String for path IMG
    string pathImg;
    bool StyleWhite;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOWH
