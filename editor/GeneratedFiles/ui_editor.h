/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editorClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *editorClass)
    {
        if (editorClass->objectName().isEmpty())
            editorClass->setObjectName(QStringLiteral("editorClass"));
        editorClass->resize(986, 642);
        centralWidget = new QWidget(editorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        editorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(editorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 986, 21));
        editorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(editorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        editorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(editorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        editorClass->setStatusBar(statusBar);

        retranslateUi(editorClass);

        QMetaObject::connectSlotsByName(editorClass);
    } // setupUi

    void retranslateUi(QMainWindow *editorClass)
    {
        editorClass->setWindowTitle(QApplication::translate("editorClass", "editor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editorClass: public Ui_editorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
