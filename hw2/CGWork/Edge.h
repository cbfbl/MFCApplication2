#pragma once

#include "Vec4.h"

class Edge {
public:
    Edge();
    Edge(Vec4 start, Vec4 end, double rgb[3]);
    ~Edge();

    Vec4 start;
    Vec4 end;
    int red;
    int green;
    int blue;

private:
};