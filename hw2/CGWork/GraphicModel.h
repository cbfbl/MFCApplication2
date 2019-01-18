#pragma once

#include <vector>
#include <tuple>
using std::vector;
using std::tuple;
#include "GraphicObject.h"

class GraphicModel {
public:
    GraphicModel();
    GraphicModel(CString& name, vector<GraphicObject> graphicObjects);
    ~GraphicModel();

    void addCurrentKeyFrame();

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
    vector<tuple<double, double, double, double, double, double, double, double, double>> animationKeyFrames; // list of <thetaX, thetaY, thetaZ, scaleX, scaleY, scaleZ, translateX, translateY, translateZ> tuples.
    double transparency;

private:
};