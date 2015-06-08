#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include <QtGui/QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include "graphicsscene.h"
#include "spline.h"
#include "enums.h"

class Node;
class Spline;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    void AddInterpPoints(Node * newNode);
	void AddInterpPoint(Node * newNode, int& index);
	void DeleteInterpPoint(int& index);

    Spline *spline;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void scaleView(qreal scaleFactor);

private:
};

#endif // GRAPHWIDGET_H
