/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Sep 27 14:46:57 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "aboutdialog.h"
#include "graphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClear_Scene;
    QAction *actionTool_Bar;
    QAction *actionStatus_bar;
    QAction *actionAbout;
    QAction *actionShow_Control_Points;
    QAction *actionShow_Curve_Points;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuScene;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1078, 512);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionClear_Scene = new QAction(MainWindow);
        actionClear_Scene->setObjectName(QString::fromUtf8("actionClear_Scene"));
        actionTool_Bar = new QAction(MainWindow);
        actionTool_Bar->setObjectName(QString::fromUtf8("actionTool_Bar"));
        actionTool_Bar->setCheckable(true);
        actionTool_Bar->setChecked(true);
        actionStatus_bar = new QAction(MainWindow);
        actionStatus_bar->setObjectName(QString::fromUtf8("actionStatus_bar"));
        actionStatus_bar->setCheckable(true);
        actionStatus_bar->setChecked(true);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionShow_Control_Points = new QAction(MainWindow);
        actionShow_Control_Points->setObjectName(QString::fromUtf8("actionShow_Control_Points"));
        actionShow_Control_Points->setCheckable(true);
        actionShow_Control_Points->setChecked(false);
        actionShow_Curve_Points = new QAction(MainWindow);
        actionShow_Curve_Points->setObjectName(QString::fromUtf8("actionShow_Curve_Points"));
        actionShow_Curve_Points->setCheckable(true);
        actionShow_Curve_Points->setChecked(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(5, 1, 1071, 441));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1078, 21));
        menuScene = new QMenu(menuBar);
        menuScene->setObjectName(QString::fromUtf8("menuScene"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuScene->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuScene->addAction(actionClear_Scene);
        menuView->addAction(actionTool_Bar);
        menuView->addAction(actionStatus_bar);
        menuHelp->addAction(actionAbout);
        toolBar->addAction(actionClear_Scene);
        toolBar->addSeparator();
        toolBar->addAction(actionShow_Control_Points);
        toolBar->addSeparator();
		toolBar->addAction(actionShow_Curve_Points);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Curve Editor", 0, QApplication::UnicodeUTF8));
        actionClear_Scene->setText(QApplication::translate("MainWindow", "Clear Scene", 0, QApplication::UnicodeUTF8));
        actionTool_Bar->setText(QApplication::translate("MainWindow", "Tool Bar", 0, QApplication::UnicodeUTF8));
        actionStatus_bar->setText(QApplication::translate("MainWindow", "Status bar", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About Curve Editor...", 0, QApplication::UnicodeUTF8));
        actionShow_Control_Points->setText(QApplication::translate("MainWindow", "Show Control Points", 0, QApplication::UnicodeUTF8));
        actionShow_Curve_Points->setText(QApplication::translate("MainWindow", "Show Curve Points", 0, QApplication::UnicodeUTF8));
        menuScene->setTitle(QApplication::translate("MainWindow", "Scene", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
