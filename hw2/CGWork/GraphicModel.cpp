#include "GraphicModel.h"

GraphicModel::GraphicModel()
{
    wireframeColor = RGB(0, 0, 0);
    useCustomWireframeColor = false;
    thetaX = 0;
    thetaY = 0;
    thetaZ = 0;
    scaleX = 0.14;
    scaleY = 0.14;
    scaleZ = 0.14;
    translateX = 0;
    translateY = 0;
    translateZ = 0;
}

GraphicModel::GraphicModel(CString& name, vector<GraphicObject> graphicObjects)
{
    wireframeColor = RGB(0, 0, 0);
    useCustomWireframeColor = false;
    this->name = name;
    objects = graphicObjects;
    thetaX = 0;
    thetaY = 0;
    thetaZ = 0;
    scaleX = 0.14;
    scaleY = 0.14;
    scaleZ = 0.14;
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    transparency = 0;
}

GraphicModel::~GraphicModel()
{
}

void GraphicModel::addCurrentKeyFrame()
{
    animationKeyFrames.push_back(tuple<double, double, double, double, double, double, double, double, double>(
                thetaX, thetaY, thetaZ, scaleX, scaleY, scaleZ, translateX, translateY, translateZ));
}