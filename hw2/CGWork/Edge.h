#pragma once

#include "Vec4.h"

class Edge {
public:
    Edge();
    Edge(Vec4 start, Vec4 end);
    ~Edge();

    Vec4 start;
    Vec4 end;

private:
};