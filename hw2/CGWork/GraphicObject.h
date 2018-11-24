#pragma once

#include <vector>
using std::vector;
#include "Edge.h"

class GraphicObject {
public:
    GraphicObject();
    GraphicObject(double rgb[3]);
    ~GraphicObject();

    vector<Edge> boundingBox;
    vector<Edge> edges;
    int red;
    int green;
    int blue;

private:

};