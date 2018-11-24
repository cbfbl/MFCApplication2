#include "GraphicObject.h"

GraphicObject::GraphicObject() {}

GraphicObject::GraphicObject(double rgb[3])
    : red(rgb[0] * 255)
    , green(rgb[1] * 255)
    , blue(rgb[2] * 255)
{
}

GraphicObject::~GraphicObject()
{
}



