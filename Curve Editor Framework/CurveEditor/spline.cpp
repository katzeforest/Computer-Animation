#include "spline.h"

const int Division = 20;

Spline::Spline(GraphWidget *graphWidget)
:graph(graphWidget)
{
	deleteNodes(interpPoints);
	deleteNodes(controlPoints);
	deleteNodes(curvePoints);
    
	deleteEdges(pseudoEdges);
	deleteEdges(curveEdges);
	deleteEdges(controlEdges);
    
	startPoint = NULL;
	endPoint = NULL;
	totalPoints = 0;
	style = BezierBernstein;
	showControlPoints = false;
	showCurvePoints = false; // LOOK
	showPseudoPoints = true;
}

void Spline::SetVisible(QList<Node *> nodes, bool visible)
{
	foreach(Node * i, nodes)
	{
		i->setVisible(visible);
		i->setEnabled(visible);
	}
}
void Spline::SetVisible(QList<Edge *> edges, bool visible)
{
	foreach(Edge * i, edges)
	{
		i->setVisible(visible);
		i->setEnabled(visible);
	}
}
void Spline::SetVisible(bool visible)
{
	if (this->startPoint && this->endPoint)
	{
		this->startPoint->setVisible(visible);
		this->startPoint->setEnabled(visible);
		this->endPoint->setVisible(visible);
		this->endPoint->setEnabled(visible);
		if (!visible)
		{
			this->graph->scene()->removeItem(startPoint);
			this->graph->scene()->removeItem(endPoint);
		}
		else
		{
			this->graph->scene()->addItem(startPoint);
			this->graph->scene()->addItem(endPoint);
		}
	}
}

void Spline::Clear()
{
	deleteNodes(interpPoints);
	deleteNodes(controlPoints);
	deleteNodes(curvePoints);
    
	deleteEdges(pseudoEdges);
	deleteEdges(curveEdges);
	deleteEdges(controlEdges);
    
	if (startPoint)
	{
		this->graph->scene()->removeItem(startPoint);
		delete startPoint;
		startPoint = NULL;
	}
	if (endPoint)
	{
		this->graph->scene()->removeItem(endPoint);
		delete endPoint;
		endPoint = NULL;
	}
    
	totalPoints = 0;
}

void Spline::PaintPseudeLines()
{
	if (startPoint && endPoint)
	{
		Interpolate();
		deleteEdges(pseudoEdges);
		calcPseudoEdges();
		Paint();
	}
}

void Spline::deleteNodes(QList<Node *> &nodes)
{
	foreach(Node * i, nodes)
	{
		delete i;
	}
	nodes.clear();
}

void Spline::deleteEdges(QList<Edge *> &edges)
{
	foreach(Edge * i, edges)
	{
		delete i;
	}
	edges.clear();
}

void Spline::Paint()
{
	deleteEdges(curveEdges);
	deleteEdges(pseudoEdges);
	deleteEdges(controlEdges);
    
	// Curve Points & Edges
    // LOOK
	if(showCurvePoints)
	{
		foreach(Node * i, curvePoints)
		{
			this->graph->scene()->addItem(i);
		}
	}
	calcCurveEdges();
    
	// Control Points & Edges
	if (showControlPoints)
	{
		foreach(Node * i, controlPoints)
		{
			this->graph->scene()->addItem(i);
		}
		calcControlEdges();
	}
    
	if (showPseudoPoints)
	{
		calcPseudoEdges();
		this->SetVisible(true);
	}
	else
	{
		this->SetVisible(false);
	}
    
	this->graph->repaint(-1000, -1000, 2000, 2000);
}

void Spline::AddPoint(Node *newNode)
{
	interpPoints.append(newNode);
	graph->scene()->addItem(newNode);
	totalPoints++;
    
	CalcStartPoint();
	CalcEndPoint();
}

// LOOK (Adding intermediate control points)
void Spline::AddPoint(Node *newNode, int& index)
{
	interpPoints.insert(index, newNode);
	graph->scene()->addItem(newNode);
	totalPoints++;
    
	CalcStartPoint();
	CalcEndPoint();
}

// LOOK (Adding intermediate control points)
void Spline::DeletePoint(int& index)
{
	// Remove Node
	if (index >= 0 && index < interpPoints.size())
	{
		graph->scene()->removeItem(interpPoints[index]);
		interpPoints.removeAt(index);
		--totalPoints;
	}

	// Remove the start and end points if points less than 2
	if (totalPoints<=2)
	{
		if (startPoint)
		{
			ClearStartPoint();
		}
		if (endPoint)
		{
			ClearEndPoint();
		}
	}
	else
	{
		// Calculate the first and last points if those get deleted
		if (index == 0)
		{
			ClearStartPoint();
			CalcStartPoint();
		}
		if(index==totalPoints)
		{
			ClearEndPoint();
			CalcEndPoint();
		}
	}
    
	// Recalculate start and end points if those are the only points
	if(totalPoints==2)
	{
		ClearStartPoint();
		ClearEndPoint();
		CalcStartPoint();
		CalcEndPoint();
	}
}

void Spline::ClearStartPoint()
{
	this->graph->scene()->removeItem(startPoint);
	delete startPoint;
	startPoint = NULL;
}

void Spline::ClearEndPoint()
{
	this->graph->scene()->removeItem(endPoint);
	delete endPoint;
	endPoint = NULL;
}

void Spline::CalcStartPoint()
{
	if (totalPoints == 2 || (totalPoints>2 && !startPoint))
	{
		Node* p1 = interpPoints[0];
		Node* p2 = interpPoints[1];
        
		QPointF line12 = p1->pos() - p2->pos();
		double length12 = sqrt(line12.x()*line12.x() + line12.y()*line12.y());
        
		startPoint = new Node(this->graph, PseudoPoints);
		startPoint->setPos(p1->pos() + line12 / length12 * 50);
		graph->scene()->addItem(startPoint);
	}
}

void Spline::CalcEndPoint()
{
	if (totalPoints < 2)
		return;
	if (!endPoint)
	{
		endPoint = new Node(this->graph, PseudoPoints);
		graph->scene()->addItem(endPoint);
	}
    
	Node* pN = interpPoints[totalPoints - 1];
	Node* pNm1 = interpPoints[totalPoints - 2];
    
	QPointF lineNNm1 = pN->pos() - pNm1->pos();
	double lengthNNm1 = sqrt(lineNNm1.x()*lineNNm1.x() + lineNNm1.y()*lineNNm1.y());
    
	endPoint->setPos(pN->pos() + lineNNm1 / lengthNNm1 * 50);
}

void Spline::calcCurveEdges()
{
	deleteEdges(curveEdges);
	for (int i = 0; i < curvePoints.size() - 1; i++)
	{
		Edge * tmp = new Edge(curvePoints[i]->pos(), curvePoints[i+1]->pos());
		curveEdges.append(tmp);
		graph->scene()->addItem(tmp);
	}
}

void Spline::calcControlEdges()
{
	deleteEdges(controlEdges);
    
	switch(style)
	{
        case BezierBernstein:
        case BezierDeCasteljau:
        case BezierMatrix:
            if (this->controlPoints.size() == 2*(totalPoints-1))
            {
                for (int i = 0; i < this->totalPoints - 1; i ++)
                {
                    Node * n1 = interpPoints[i];
                    Node * n2 = interpPoints[i+1];
                    Node * c1 = controlPoints[2*i];
                    Node * c2 = controlPoints[2*i+1];
                    Edge * e1 = new Edge(n1->pos(), c1->pos(), 1);
                    Edge * e2 = new Edge(c1->pos(), c2->pos(), 1);
                    Edge * e3 = new Edge(c2->pos(), n2->pos(), 1);
                    controlEdges.append(e1);
                    controlEdges.append(e2);
                    controlEdges.append(e3);
                    graph->scene()->addItem(e1);
                    graph->scene()->addItem(e2);
                    graph->scene()->addItem(e3);
                }
            }
            break;
        case BSpline:
            for (int i = 0; i < this->controlPoints.size() - 1; i++)
            {
                Node * c1 = controlPoints[i];
                Node * c2 = controlPoints[i+1];
                
                Edge * e1 = new Edge(c1->pos(), c2->pos(), 1);
                controlEdges.append(e1);
                graph->scene()->addItem(e1);
            }
            break;
        case HermiteClamped:
        case HermiteNatural:
            if (this->controlPoints.size() == totalPoints)
            {
                for (int i = 0; i < this->totalPoints; i++)
                {
                    Node * c1 = interpPoints[i];
                    Node * c2 = controlPoints[i];
                    
                    c2->setPosition(c1->getPosition() + c2->getPosition());
                    
                    Edge * e1 = new Edge(c1->pos(), c2->pos(), 1);
                    controlEdges.append(e1);
                    graph->scene()->addItem(e1);
                }
            }
            break;
	}
}

void Spline::calcPseudoEdges()
{
	if (totalPoints >= 2)
	{
		deleteEdges(pseudoEdges);
		// start
		Edge * start = new Edge(startPoint->pos(), ((Node *)interpPoints.first())->pos(), 2);
		pseudoEdges.append(start);
		graph->scene()->addItem(start);
		// end
		Edge * end = new Edge(endPoint->pos(), ((Node *)interpPoints.last())->pos(), 2);
		pseudoEdges.append(end);
		graph->scene()->addItem(end);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start your code here.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Spline::Interpolate()
{
	//Clear the old curve points
	deleteNodes(curvePoints);
	//Calculate control points.
	CalcControlPoints();
	//Depending on the selected style, interpolate the curve.
	switch(style){
        case BezierBernstein:		InterpBernstein();       break;
        case BezierDeCasteljau:		InterpCasteljau();      break;
        case BezierMatrix:          InterpMatrix();         break;
        case BSpline:               InterpBSpline();        break;
        case HermiteClamped:        InterpHermiteClamped(); break;
        case HermiteNatural:        InterpHermiteNatural(); break;
	}
}



//////////////////////////////////////////////////////////////////////////
// Calculate the control points
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// controlPoints- type: QList<Node *>
//				  discription: stores all the control points for curve interpolation and display.
//                             For Bezier curve, between very pair of consecutive interpolation points,
//                             there should be two control points. These four points determins the curve interpolation.
//                             For B-Spline, there should be totalPoints + 2 control points calculated from Ac = p.
//
// Hint: To implement Hermite and B-Spline, you need to write functions to create the A matrix as in the handouts.
//       Then you solve a linear system Ac = p, where p is the interpolation points vector and c are the control points.
//       We have provided you with a data structure to store and solve the linear system.
//       Below is an example code, read the understand it.
//
//	matrix<float> A(3,3);
//  matrix<float> c(3,1);
//  matrix<float> p(3,1);
//  A(0,0) = 1.0; A(0,1) = 0.0; A(0,2) = 0.0;
//  A(1,0) = 0.0; A(1,1) = 1.0; A(1,2) = 0.0;
//  A(2,0) = 0.0; A(2,1) = 0.0; A(2,2) = 1.0;
//  p(0,0) = 1.0; p(1,0) = 2.0; p(2,0) = 3.0;
//  c = A.Solve(p);
//
//  The result in c is c(0,0) = 1.0; c(1,0) = 2.0; c(3,0) = 3.0, which satisfies Ac = p.
// Hint2: To get the position which is a vec3 in the class Node*, we need to use the method Node::getPosition().
// Example:
// vec3 startPointPos = startPoint->getPosition();
//
// Hint3: To new a Node*, add it into the List, and set the position of it, you need to do like this:
// Example:
// Node* ctrl = new Node(graph, ControlPoints);
// ctrl->setPosition(/*some vec3*/);
// controlPoints.append(ctrl);
void Spline::CalcControlPoints()                                                                                               //*****************
{
	// Clear previous controlPoints
	deleteNodes(controlPoints);
	// Based on style use appropriate ways to compute control points
	switch(style)
	{
        case BezierBernstein:
        case BezierDeCasteljau:
        case BezierMatrix:

		//ADD CODE
           {
				QList <Node*> interpPointsCorrected(interpPoints);

				interpPointsCorrected.prepend(startPoint);
				interpPointsCorrected.append(endPoint);

				for (int i = 0; i <= interpPointsCorrected.size() - 4; ++i)
				{
					vec3 b1 = interpPointsCorrected[i+1]->getPosition() + (interpPointsCorrected[i+2]->getPosition() - interpPointsCorrected[i]->getPosition())/6; // for the points inbetween 
					vec3 b2 = interpPointsCorrected[i+2]->getPosition() - (interpPointsCorrected[i+3]->getPosition() - interpPointsCorrected[i+1]->getPosition())/6;

					Node* newControlPoint = new Node(graph, ControlPoints);
					newControlPoint->setPosition(b1);
					controlPoints.append(newControlPoint);

					newControlPoint = new Node(graph, ControlPoints);
					newControlPoint->setPosition(b2);
					controlPoints.append(newControlPoint);
				}

				if (controlPoints.size() >= 2)
				{
					controlPoints.first()->setPosition(interpPoints.first()->getPosition()*2 - startPoint->getPosition());
					controlPoints.last()->setPosition(interpPoints.last()->getPosition()*2 - endPoint->getPosition());
				}	
			}
            break;
        case BSpline:
            // make sure there are at least 2 totalPoints.
            // ADD YOUR CODE HERE
			{
				if (totalPoints < 2)
					return;

	            matrix<float> A(totalPoints+2, totalPoints+2);
                matrix<float> C(totalPoints+2, 3);
                matrix<float> d(totalPoints+2, 3);

				int totalControlPoints = totalPoints+2;

				//Make matrix A

			    for(int i = 0; i < totalControlPoints; i++)
				{
					for(int j = 0; j <totalControlPoints; j++)
					{
						if(i == 0)
						{
							if(j == 0 || j ==2 )
								A(i,j) = 0.25;
							else if(j == 1)
								A(i,j) = -0.5;
							else
								A(i,j) = 0;
						}
						else if(i == totalControlPoints - 1)
						{
							if(j == totalControlPoints - 1 || j == totalControlPoints - 3)
								A(i,j) = 0.25;
							else if(j == totalControlPoints - 2)
								A(i,j) = -0.5;
							else
								A(i,j) = 0;
						}
						else
						{
							if( j == i-1 || j == i+1)
								A(i,j) = 0.167;
							else if(j == i)
								A(i,j) = 0.667;
							else
								A(i,j) =0;
						}					
						
					}
				}

					
				
				d(0,0) = 0; d(0,1) = 0; d(0,2) = 0;
				for(int i = 1; i <= totalPoints; i++)
				{
					vec3 v = interpPoints[i-1]->getPosition();
					d(i,0)= v[0]; d(i,1)= v[1]; d(i,2)= v[2];
				}
				 
				d(totalControlPoints-1,0) = 0; d(totalControlPoints-1,1) = 0; d(totalControlPoints-1,2) = 0;

				//Get C
				C = A.Solve(d);

				for (int i = 0; i < totalControlPoints ; ++i)
				{
					Node * newControlPoint = new Node(graph, ControlPoints);
					newControlPoint->setPosition(vec3(C(i,0), C(i,1), C(i,2)));
					controlPoints.append(newControlPoint);
				}
			}
            break;
            // In the case for Hermite, you want to implement both "clamped" and "natural" versions.
        case HermiteClamped:
            // make sure there are at least 2 totalPoints.
            // ADD YOUR CODE HERE
			{
				if (totalPoints < 2)
					return;
				
	            matrix<float> A(totalPoints, totalPoints);
                matrix<float> C(totalPoints, 3);
                matrix<float> d(totalPoints, 3);

				//Make matrix A
				A(0,0) = A(totalPoints-1, totalPoints-1) = 1;
			    for(int i = 1; i < totalPoints; i++)
					A(0,i) = 0;
			    for(int i = 1; i < totalPoints - 1; i++)
				{
					for(int j = 0; j < totalPoints; j++)
					{
						if(j == i-1 || j == i+1)
							A(i,j)= 1;
						else if(j == i)
							A(i,j)= 4;
						else
							A(i,j)= 0;
					}
				}
				for(int i = 0; i < totalPoints-1; i++)
					A(totalPoints-1,i) = 0;

				//Get d
				vec3 startPos = startPoint->getPosition() - interpPoints[0]->getPosition();
				d(0,0) = startPos[0]; d(0,1) = startPos[1]; d(0,2) = startPos[2];
				for(int i = 2; i < totalPoints; i++)
				{
					vec3 v = (interpPoints[i]->getPosition() - interpPoints[i-2]->getPosition())*3;
					d(i-1,0)= v[0]; d(i-1,1)= v[1]; d(i-1,2)= v[2];
				}
				vec3 endPos = endPoint->getPosition() - interpPoints[totalPoints-1]->getPosition();
				d(totalPoints-1,0) = endPos[0]; d(totalPoints-1,1) = endPos[1]; d(totalPoints-1,2) = endPos[2];

				//Get C
				C = A.Solve(d);

				for (int i = 0; i < totalPoints ; ++i)
				{
					Node * newControlPoint = new Node(graph, ControlPoints);
					newControlPoint->setPosition(vec3(C(i,0), C(i,1), C(i,2)));
					controlPoints.append(newControlPoint);
				}
			}
            break;
        case HermiteNatural:
            // make sure there are at least 2 totalPoints.
            // ADD YOUR CODE HERE
			{

				if (totalPoints < 2)
					return;

	            matrix<float> A(totalPoints, totalPoints);
                matrix<float> C(totalPoints, 3);
                matrix<float> d(totalPoints, 3);

				//Make matrix A
				A(0,0) = A(totalPoints-1, totalPoints-1) = 2;
				A(0,1) = A(totalPoints-1, totalPoints-2) = 1;
			    for(int i = 2; i < totalPoints; i++)
					A(0,i) = 0; // here it maake the 0, 1 0 again?
			    for(int i = 1; i < totalPoints - 1; i++)
				{
					for(int j = 0; j < totalPoints; j++)
					{
						if(j == i-1 || j == i+1)
							A(i,j)= 1;
						else if(j == i)
							A(i,j)= 4;
						else
							A(i,j)= 0;
					}
				}
				for(int i = 0; i < totalPoints-2; i++)
					A(totalPoints-1,i) = 0;

				//Get d
				vec3 startPos = (interpPoints[1]->getPosition() - interpPoints[0]->getPosition())*3;
				d(0,0) = startPos[0]; d(0,1) = startPos[1]; d(0,2) = startPos[2];
				for(int i = 2; i < totalPoints; i++)
				{
					vec3 v = (interpPoints[i]->getPosition() - interpPoints[i-2]->getPosition()) * 3;
					d(i-1,0)= v[0]; d(i-1,1)= v[1]; d(i-1,2)= v[2];
				}
				vec3 endPos = (interpPoints[totalPoints-1]->getPosition() - interpPoints[totalPoints-2]->getPosition())*3;
				d(totalPoints-1,0) = endPos[0]; d(totalPoints-1,1) = endPos[1]; d(totalPoints-1,2) = endPos[2];

				//Get C
				C = A.Solve(d);

				for (int i = 0; i < totalPoints ; ++i)
				{
					Node * newControlPoint = new Node(graph, ControlPoints);
					newControlPoint->setPosition(vec3(C(i,0), C(i,1), C(i,2)));
					controlPoints.append(newControlPoint);
				}
			}

           break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Cubic Berstein Bezier Spline
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points
//
// Hint: To get the position which is a vec3 in the class Node*, we need to use the method Node::getPosition().
// Example:
// vec3 b = interpPoints[i]->getPosition();
//
// Hint2: To new a Node*, add it into the List, and set the position of it, you need to do like this:
// Example:
// Node* newNode = new Node(graph, CurvePoints);
// newNode->setPosition(/*some vec3*/);
// curvePoints.append(newNode);
void Spline::InterpBernstein()                                                                                      //*****************
{
	// ADD YOUR CODE HERE
	int m = interpPoints.size();
	if (m < 2)
		return;

	QList<vec3> workingPoints;

	for (int i=0; i < interpPoints.size() - 1; ++i)
	{
		workingPoints.append(interpPoints[i]->getPosition());
		workingPoints.append(controlPoints[i*2]->getPosition());
		workingPoints.append(controlPoints[i*2+1]->getPosition());
	}
	workingPoints.append(interpPoints.last()->getPosition());

	// each iteration uses 4 points (2 control points and 2 interpolation points)
	for (int i = 0; i <= workingPoints.size()-4; i+=3)
	{      
		vec3 b0 = workingPoints[i];
		vec3 b1 = workingPoints[i+1];
		vec3 b2 = workingPoints[i+2];
		vec3 b3 = workingPoints[i+3];

		for (float t = 0; t <1; t += STEP)
		{  
			float u = (1.0 - t);
	
			vec3 Bernsteintemp = b0 * u*u*u + b1 * 3*t*u*u + b2 * 3*t*t*u + b3 * t*t*t  ;

			Node * newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(Bernsteintemp);
			curvePoints.append(newCurvePoint);
		}
	}

	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(workingPoints.last());
	curvePoints.append(newCurvePoint);
}

//////////////////////////////////////////////////////////////////////////
// Cubic de Casteljau Bezier Spline
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points
//
// Hint: To get the position which is a vec3 in the class Node*, we need to use the method Node::getPosition().
// Example:
// vec3 b = interpPoints[i]->getPosition();
//
// Hint2: To new a Node*, add it into the List, and set the position of it, you need to do like this:
// Example:
// Node* newNode = new Node(graph, CurvePoints);
// newNode->setPosition(/*some vec3*/);
// curvePoints.append(newNode);
void Spline::InterpCasteljau()                                                                                    //*****************
{
	// ADD YOU CODE HERE	
	
	int m = interpPoints.size();
	if (m < 2)
		return;

	QList<vec3> workingPoints;

	for (int i=0; i < interpPoints.size() - 1; ++i)
	{
		workingPoints.append(interpPoints[i]->getPosition());
		workingPoints.append(controlPoints[i*2]->getPosition());
		workingPoints.append(controlPoints[i*2+1]->getPosition());
	}
	workingPoints.append(interpPoints.last()->getPosition());

	// each iteration uses 4 points (2 control points and 2 interpolation points)
	for (int i = 0; i <= workingPoints.size()-4; i+=3)
	{
		unsigned int n = 4;

		for (float t = 0; t < 1; t += STEP)
		{
			QList<vec3> Q;

			for (unsigned int v=i; v < i+n; ++v)
				Q.append(workingPoints[v]);

			for (unsigned int k = 1; k < n; ++k)
			{
				for (unsigned int i = 0; i < (n - k); ++i)
					Q[i] = (1-t)*Q[i] + t*Q[i+1];
			}
			Node * newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(Q[0]);
			curvePoints.append(newCurvePoint);
		}
	}
	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(workingPoints.last());
	curvePoints.append(newCurvePoint);
}

//////////////////////////////////////////////////////////////////////////
// Interpolation Matrix Bezier Spline
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points
//
// Hint: To get the position which is a vec3 in the class Node*, we need to use the method Node::getPosition().
// Example:
// vec3 b = interpPoints[i]->getPosition();
//
// Hint2: To new a Node*, add it into the List, and set the position of it, you need to do like this:
// Example:
// Node* newNode = new Node(graph, CurvePoints);
// newNode->setPosition(/*some vec3*/);
// curvePoints.append(newNode);
// Hint3: If you have any problem in vec3 vec4 mat4 operations, see the SvzAlgebra.h and svzalgebra.cpp to find some specific method out.
// For Example:
// vec3 operator * (const mat4& a, const vec3& v); has been defined in SvzAlgebra.h
// That means you can do operations like this:
// vec3 A;
// mat4 M;
// vec3 B = M*A;
// (It automatically transfer the A and B vectors to homogeneous vectors)
void Spline::InterpMatrix()                                                                                                 //*****************
{
	 
	// ADD YOUR CODE HERE.
	int m = interpPoints.size();
	if (m < 2)
		return;

	matrix<float> M(4,4);
    matrix<float> T(4,1);
    matrix<float> G(3,4);

	M(0,0)= 1; M(0,1)= -3; M(0,2)= 3;  M(0,3)= -1;
	M(1,0)= 0; M(1,1)= 3;  M(1,2)= -6; M(1,3)= 3;
	M(2,0)= 0; M(2,1)= 0;  M(2,2)= 3;  M(2,3)= -3;
	M(3,0)= 0; M(3,1)= 0;  M(3,2)= 0;  M(3,3)= 1;

	QList<vec3> workingPoints;

	for (int i=0; i < interpPoints.size() - 1; ++i)
	{
		workingPoints.append(interpPoints[i]->getPosition());
		workingPoints.append(controlPoints[i*2]->getPosition());
		workingPoints.append(controlPoints[i*2+1]->getPosition());
	}
	workingPoints.append(interpPoints.last()->getPosition());

	for (int i = 0; i <= workingPoints.size()-4; i+=3)
	{      
		vec3 b0 = workingPoints[i];
		vec3 b1 = workingPoints[i+1];
		vec3 b2 = workingPoints[i+2];
		vec3 b3 = workingPoints[i+3];   

		G(0,0) = b0[0]; G(0,1) = b1[0]; G(0,2) = b2[0];  G(0,3) = b3[0];
        G(1,0) = b0[1]; G(1,1) = b1[1];  G(1,2) = b2[1]; G(1,3) = b3[1];
        G(2,0) = b0[2]; G(2,1) = b1[2];  G(2,2) = b2[2];  G(2,3) = b3[2];
	   
		for (float t = 0; t < 1.0; t += STEP)
		{  
	
			T(0,0) = 1.0; T(1,0) = t; T(2,0) = t*t; T(3,0) = t*t*t;

		    matrix<float> Matrixtemp = G*M*T;
			vec3 pos(Matrixtemp(0,0), Matrixtemp(1,0), 0);
			Node* newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(pos);
			curvePoints.append(newCurvePoint);
		}   
	}
	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(workingPoints.last());
	curvePoints.append(newCurvePoint);
}

//////////////////////////////////////////////////////////////////////////
// BSpline curve
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points
void Spline::InterpBSpline()                                                                                        //*****************
{
	// ADD YOUR CODE HERE
		if (totalPoints < 2)
		return;

	matrix<float> M(4,4);
    matrix<float> T(1,4);
    matrix<float> G(4,3);

	M(0,0)= -1.0/6; M(0,1)= 3.0/6;  M(0,2)= -3.0/6; M(0,3)= 1.0/6;
	M(1,0)= 3.0/6; M(1,1)= -6.0/6;  M(1,2)= 3.0/6;  M(1,3)= 0;
	M(2,0)= -3.0/6; M(2,1)= 0;  M(2,2)= 3.0/6;  M(2,3)= 0;
	M(3,0)= 1.0/6;  M(3,1)= 4.0/6;  M(3,2)= 1.0/6;  M(3,3)= 0;

	for (int i = 0; i < controlPoints.size()-3; i++)
	{      
		vec3 b0 = controlPoints[i]->getPosition();
		vec3 b1 = controlPoints[i+1]->getPosition();
		vec3 b2 = controlPoints[i+2]->getPosition();
		vec3 b3 = controlPoints[i+3]->getPosition();   

		G(0,0) = b0[0]; G(0,1) = b0[1];  G(0,2) = b0[2]; 
        G(1,0) = b1[0]; G(1,1) = b1[1];  G(1,2) = b1[2]; 
		G(2,0) = b2[0]; G(2,1) = b2[1];  G(2,2) = b2[2]; 
		G(3,0) = b3[0]; G(3,1) = b3[1];  G(3,2) = b3[2];


	   
		for (float t = 0; t < 1.0; t += STEP)
		{  
	
			T(0,0) = t*t*t; T(0,1) = t*t; T(0,2) = t; T(0,3) = 1;

		    matrix<float> Matrixtemp = T*M*G;
			vec3 pos(Matrixtemp(0,0), Matrixtemp(0,1), 0);
			Node* newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(pos);
			curvePoints.append(newCurvePoint);
		}
	}
	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(interpPoints.last()->getPosition());
	curvePoints.append(newCurvePoint);

}

//////////////////////////////////////////////////////////////////////////
// Hermite Curve ('Clamped' condition)
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points
void Spline::InterpHermiteClamped()                                                                                      //*****************
{
	// ADD YOUR CODE HERE

	if (totalPoints < 2)
		return;

	matrix<float> M(4,4);
    matrix<float> T(4,1);
    matrix<float> G(3,4);

	M(0,0)= 1; M(0,1)= 0;  M(0,2)= -3; M(0,3)= 2;
	M(1,0)= 0; M(1,1)= 0;  M(1,2)= 3;  M(1,3)= -2;
	M(2,0)= 0; M(2,1)= 1;  M(2,2)= -2; M(2,3)= 1;
	M(3,0)= 0; M(3,1)= 0;  M(3,2)= -1; M(3,3)= 1;

	for (int i = 0; i < totalPoints-1; i++)
	{      
		vec3 b0 = interpPoints[i]->getPosition();
		vec3 b1 = interpPoints[i+1]->getPosition();
		vec3 b2 = controlPoints[i]->getPosition();
		vec3 b3 = controlPoints[i+1]->getPosition();   

		G(0,0) = b0[0]; G(0,1) = b1[0];  G(0,2) = b2[0]; G(0,3) = b3[0];
        G(1,0) = b0[1]; G(1,1) = b1[1];  G(1,2) = b2[1]; G(1,3) = b3[1];
        G(2,0) = b0[2]; G(2,1) = b1[2];  G(2,2) = b2[2]; G(2,3) = b3[2];
	   
		for (float t = 0; t < 1.0; t += STEP)
		{  
	
			T(0,0) = 1.0; T(1,0) = t; T(2,0) = t*t; T(3,0) = t*t*t;

		    matrix<float> Matrixtemp = G*M*T;
			vec3 pos(Matrixtemp(0,0), Matrixtemp(1,0), 0);
			Node* newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(pos);
			curvePoints.append(newCurvePoint);
		}
	}
	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(interpPoints.last()->getPosition());
	curvePoints.append(newCurvePoint);
}

//////////////////////////////////////////////////////////////////////////
// Hermite Curve ('Natural' condition)
//////////////////////////////////////////////////////////////////////////
// This function utilizes the following member variables
// interpPoints	- type: QList<Node *>
//				  discription: stores all the interpolation points
// controlPoints- type: QList<Node *>
//				  discription: stores the control points that helps to determine the curve.
//                             Between very pair of consecutive interpolation points,there should be two control points.
//                             These four points determins the curve interpolation.
// startPoint	- type: Node*
//				  discription: stores the tangent to the first interpolation point
// endPoint		- type: Node*
//				  discription: stores the tangent to the second interpolation point
// totalPoints	- type: int
//				  discription: total number of interpolation points
// This function modifies the following member variables
// curvePoints	- type: QList<Node *>
//				  discription: stores all the points that form the curve, including all interpolation points 
// Hint: It is exactly the same like the method above.
void Spline::InterpHermiteNatural()                                                                                      //*****************
{
	// ADD YOUR CODE HERE.
	if (totalPoints < 2)
		return;

	matrix<float> M(4,4);
    matrix<float> T(4,1);
    matrix<float> G(3,4);

	M(0,0)= 1; M(0,1)= 0;  M(0,2)= -3; M(0,3)= 2;
	M(1,0)= 0; M(1,1)= 0;  M(1,2)= 3;  M(1,3)= -2;
	M(2,0)= 0; M(2,1)= 1;  M(2,2)= -2; M(2,3)= 1;
	M(3,0)= 0; M(3,1)= 0;  M(3,2)= -1; M(3,3)= 1;

	for (int i = 0; i < totalPoints-1; i++)
	{      
		vec3 b0 = interpPoints[i]->getPosition();
		vec3 b1 = interpPoints[i+1]->getPosition();
		vec3 b2 = controlPoints[i]->getPosition();
		vec3 b3 = controlPoints[i+1]->getPosition();   

		G(0,0) = b0[0]; G(0,1) = b1[0];  G(0,2) = b2[0]; G(0,3) = b3[0];
        G(1,0) = b0[1]; G(1,1) = b1[1];  G(1,2) = b2[1]; G(1,3) = b3[1];
        G(2,0) = b0[2]; G(2,1) = b1[2];  G(2,2) = b2[2]; G(2,3) = b3[2];
	   
		for (float t = 0; t < 1.0; t += STEP)
		{  
	
			T(0,0) = 1.0; T(1,0) = t; T(2,0) = t*t; T(3,0) = t*t*t;

		    matrix<float> Matrixtemp = G*M*T;
			vec3 pos(Matrixtemp(0,0), Matrixtemp(1,0), 0);
			Node* newCurvePoint = new Node(graph, CurvePoints);
			newCurvePoint->setPosition(pos);
			curvePoints.append(newCurvePoint);
		}
	}
	// Add last point
	Node * newCurvePoint = new Node(graph, CurvePoints);
	newCurvePoint->setPosition(interpPoints.last()->getPosition());
	curvePoints.append(newCurvePoint);
}
