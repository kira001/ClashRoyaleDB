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
    QVBoxLayout* mainLayout;
    QHBoxLayout* dataLayout;
    QVBoxLayout* infoItemLayout;
    QListWidget* list;

    void addInfoLayout();
    void addMenu();
    void addButton();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
