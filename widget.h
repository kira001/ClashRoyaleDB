#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>
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

    void addLeftLayout();
    void addMenu();
    void addRightLayout();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
