#pragma once

#include "Vec4.h"
#include "Edge.h"
#include <vector>
using std::vector;

class GraphicPolygon {
public:
    GraphicPolygon();
    ~GraphicPolygon();

    vector<Edge> edges;
    Vec4 center;
    Vec4 normal;

private:
};