#pragma once

#include <vector>
using std::vector;
#include "Edge.h"
#include "GraphicPolygon.h"

class GraphicObject {
public:
    GraphicObject();
    GraphicObject(double rgb[3]);
    ~GraphicObject();

    vector<Edge> boundingBox;
    vector<GraphicPolygon> polygons;
    int red;
    int green;
    int blue;

private:

};