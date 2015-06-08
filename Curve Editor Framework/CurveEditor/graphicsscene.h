#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QtGui/QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QDebug>

#include "graphwidget.h"
#include "node.h"
#include "graphwidget.h"

class GraphWidget;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(GraphWidget* graphWiget);

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent);

private:
    bool hasSelection(QPointF mousePos);
	bool CurvePointHasSelection(QPointF mousePos, int &index);
    bool InterpPointHasSelection(QPointF mousePos, int &index);
	GraphWidget *graph;
};

#endif // GRAPHICSSCENE_H
