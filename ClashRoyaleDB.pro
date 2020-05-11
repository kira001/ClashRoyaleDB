#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------


TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Model/AttackingBuilding.cpp \
    Model/Building.cpp \
    Model/BuildingTroopSpawner.cpp \
    Model/Card.cpp \
    Model/Spell.cpp \
    Model/SpellTroopSpawner.cpp \
    Model/Troop.cpp \
    Model/TroopSpawner.cpp \
    main.cpp

HEADERS += \
     Model/Building.h \
     Model/AttackingBuilding.h \
     Model/BuildingTroopSpawner.h \
     Model/Card.h \
     Model/Spell.h \
     Model/SpellTroopSpawner.h \
     Model/Troop.h \
     Model/TroopSpawner.h \
     Template/container.h \
     Template/deepptr.h


