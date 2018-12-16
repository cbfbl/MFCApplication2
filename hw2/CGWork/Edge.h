#pragma once

#include "Vec4.h"

class Edge {
public:
    Edge();
    Edge(Vec4 start, Vec4 end);
    ~Edge();

    Vec4 start;
    Vec4 end;

    BOOL operator<(const Edge& rhs) const;  // In terms of minimum Y coordinate.
    BOOL operator==(const Edge& rhs) const;
    int ymin() const;
    int ymax() const;

private:
};