#include "GraphicObject.h"

GraphicObject::GraphicObject() {}

GraphicObject::GraphicObject(double rgb[3], double transparency)
    : red(rgb[0] * 255)
    , green(rgb[1] * 255)
    , blue(rgb[2] * 255)
    , transparency(transparency)
{
}

GraphicObject::~GraphicObject()
{
}



