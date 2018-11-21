#include "Edge.h"

Edge::Edge() {}

Edge::Edge(Vec4 start, Vec4 end, double rgb[3])
    : start(start)
    , end(end)
    , red(rgb[0]*255)
    , green(rgb[1]*255)
    , blue(rgb[2]*255)
{
    
}

Edge::~Edge()
{
}
