#pragma once

#include <vector>
using std::vector;
#include "GraphicObject.h"

class GraphicModel {
public:
    GraphicModel();
    GraphicModel(CString& name, vector<GraphicObject> graphicObjects);
    ~GraphicModel();

    CString name;
    vector<GraphicObject> objects;
    COLORREF wireframeColor;
    bool useCustomWireframeColor;
    double thetaX;
    double thetaY;
    double thetaZ;
    double scaleX;
    double scaleY;
    double scaleZ;
    double translateX;
    double translateY;
    double translateZ;

private:
};