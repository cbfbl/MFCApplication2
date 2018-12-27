#pragma once

#include <vector>
#include <map>
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
    std::map<std::pair<vector<int>, vector<int>>, std::pair<int, int>> edgePolygons;
    int red;
    int green;
    int blue;

private:

};