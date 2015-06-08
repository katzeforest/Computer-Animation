#include "graphicsscene.h"

GraphicsScene::GraphicsScene(GraphWidget* graphWiget) :
    graph(graphWiget)
{
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	// On right mouse click
	if (mouseEvent->button() == Qt::RightButton)
	{
        // LOOK - Add code here for the following
        // If Interpolation point has selection then check its position and
        // then delete the point
        // Else if curve point has selection, then create a new node and
        // add an interpolation point

		QPointF mousePos = mouseEvent->scenePos();
		int index = 0;

		if (InterpPointHasSelection(mousePos, index))
		{
			this->graph->DeleteInterpPoint(index);
		    this->graph->spline->Interpolate();
			this->graph->spline->Paint();
		}
		else if (CurvePointHasSelection(mousePos, index))
		{
			Node * newIntepPoint = new Node(this->graph, InterpPoints);
			newIntepPoint->setPos(this->graph->spline->curvePoints.at(index)->pos());
			int newIndex = index/int(1/STEP) + 1;
			this->graph->AddInterpPoint(newIntepPoint, newIndex);
			this->graph->spline->Interpolate();
			this->graph->spline->Paint();
		}
	}
	else if (!this->hasSelection(mouseEvent->scenePos()))
    {
        Node * newNode = new Node(this->graph, InterpPoints);
        newNode->setPos(mouseEvent->scenePos());

        this->graph->AddInterpPoints(newNode);
        this->graph->spline->Interpolate();
        this->graph->spline->Paint();
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

bool GraphicsScene::hasSelection(QPointF mousePos)
{

    for (int i = 0; i < this->graph->spline->interpPoints.size(); ++i) {
        QPointF temp = this->graph->spline->interpPoints.at(i)->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 400)
        {
            return true;
        }
    }

    for (int i = 0; i < this->graph->spline->controlPoints.size(); ++i) {
        QPointF temp = this->graph->spline->controlPoints.at(i)->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 400)
        {
            return true;
        }
    }
    if (this->graph->spline->startPoint != NULL)
    {
        QPointF temp = this->graph->spline->startPoint->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 400)
        {
            return true;
        }
    }
    if (this->graph->spline->endPoint != NULL)
    {
        QPointF temp = this->graph->spline->endPoint->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 400)
        {
            return true;
        }
    }

    return false;
}

// LOOK
// Is the mouse pointer near a curve point
bool GraphicsScene::CurvePointHasSelection(QPointF mousePos, int &index)
{

    for (index = 0; index < this->graph->spline->curvePoints.size(); ++index)
	{
        QPointF temp = this->graph->spline->curvePoints.at(index)->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 100)
        {
            return true;
        }
    }
	return false;
}

// LOOK
// Is the mouse pointer near a interp point
bool GraphicsScene::InterpPointHasSelection(QPointF mousePos, int &index)
{
    for (index = 0; index < this->graph->spline->interpPoints.size(); ++index)
	{
        QPointF temp = this->graph->spline->interpPoints.at(index)->pos() - mousePos;
        if (temp.x()*temp.x() + temp.y()*temp.y() < 200)
        {
            return true;
        }
    }
	return false;
}