#pragma once

#include "stdafx.h"
#include <vector>
using std::vector;

class AliasFilter {
public:
    AliasFilter();
    AliasFilter(size_t size, vector<vector<int>> elements);
    ~AliasFilter();

    vector<vector<int>> elements;
    size_t size;
    size_t size2;
    int elementsSum;

    COLORREF applyFilter(vector<vector<COLORREF>>& cbuffer, size_t x, size_t y) const;

private:
};