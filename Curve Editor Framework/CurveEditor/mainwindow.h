#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QComboBox>
#include "graphwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionTool_Bar_triggered(bool checked);

    void on_actionStatus_bar_triggered(bool checked);

    void on_actionClear_Scene_triggered();

    void on_actionMethod_Choose_ComboBox_Changed(int index);

    void on_actionShow_Control_Points_triggered(bool checked);

	void on_actionShow_Curve_Points_triggered(bool checked);

private:
    Ui::MainWindow *ui;

    GraphWidget *graphwidget;
    QComboBox *methodChooseComboBox;
};

#endif // MAINWINDOW_H
