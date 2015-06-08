#ifndef ENUMS_H
#define ENUMS_H

enum Style
{
    BezierBernstein,
    BezierDeCasteljau,
    BezierMatrix,
    BSpline,
    HermiteClamped,
    HermiteNatural
};

enum NodeType
{
    InterpPoints,
    PseudoPoints,
    ControlPoints,
    CurvePoints
};

#endif // ENUMS_H
