#include "mainwindow.h"
#include "ui_mainwindow.h"

// debug
#include <QDebug>
// /debug

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphwidget = new GraphWidget(this);

    setCentralWidget(graphwidget);

    methodChooseComboBox = new QComboBox(this);
    methodChooseComboBox->setGeometry(380, 30, 150, 18);
    methodChooseComboBox->addItem("Bezier Bernstein");
    methodChooseComboBox->addItem("Bezier de Casteljau");
    methodChooseComboBox->addItem("Bezier Matrix");
    methodChooseComboBox->addItem("BSpline");
    methodChooseComboBox->addItem("Hermite Spline (clamped)");
    methodChooseComboBox->addItem("Hermite Spline (natural)");

    connect(methodChooseComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_actionMethod_Choose_ComboBox_Changed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog;
    aboutDialog.setModal(true);
    aboutDialog.exec();
}

void MainWindow::on_actionTool_Bar_triggered(bool checked)
{
    if (checked)
    {
        ui->toolBar->show();
        methodChooseComboBox->show();
    }
    else
    {
        ui->toolBar->hide();
        methodChooseComboBox->hide();
    }
}

void MainWindow::on_actionStatus_bar_triggered(bool checked)
{
    if (checked)
        ui->statusBar->show();
    else
        ui->statusBar->hide();
}

void MainWindow::on_actionClear_Scene_triggered()
{
    //graphwidget->scene()->clear();
    graphwidget->spline->Clear();
}

void MainWindow::on_actionMethod_Choose_ComboBox_Changed(int index)
{
    //qDebug() << "index = " << index;
    switch(index)
    {
    case 0:
        graphwidget->spline->showPseudoPoints = true;
        graphwidget->spline->style = BezierBernstein;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    case 1:
        graphwidget->spline->showPseudoPoints = true;
        graphwidget->spline->style = BezierDeCasteljau;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    case 2:
        graphwidget->spline->showPseudoPoints = true;
        graphwidget->spline->style = BezierMatrix;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    case 3:
        graphwidget->spline->showPseudoPoints = false;
        graphwidget->spline->style = BSpline;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    case 4:
        graphwidget->spline->showPseudoPoints = true;
        graphwidget->spline->style = HermiteClamped;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    case 5:
        graphwidget->spline->showPseudoPoints = false;
        graphwidget->spline->style = HermiteNatural;
        graphwidget->spline->Interpolate();
        graphwidget->spline->Paint();
        break;
    default:
        break;
    }
    graphwidget->repaint();
}

void MainWindow::on_actionShow_Control_Points_triggered(bool checked)
{
    graphwidget->spline->showControlPoints = checked;
    graphwidget->spline->Interpolate();
    graphwidget->spline->Paint();
}

void MainWindow::on_actionShow_Curve_Points_triggered(bool checked)
{
    graphwidget->spline->showCurvePoints = checked;
    graphwidget->spline->Interpolate();
    graphwidget->spline->Paint();
}
