#include "AliasFilter.h"

AliasFilter::AliasFilter() {}

AliasFilter::AliasFilter(size_t size, vector<vector<int>> elements) 
    : size(size)
    , size2(size / 2)
    , elements(elements)
{
    elementsSum = 0;
    for (vector<int> row : elements) {
        for (int e : row) {
            elementsSum += e;
        }
    }
}
AliasFilter::~AliasFilter() {}

COLORREF AliasFilter::applyFilter(vector<vector<COLORREF>>& cbuffer, size_t x, size_t y) const
{
    // The filter center is at the center of the filter matrix.

    int pixelR = 0;
    int pixelG = 0;
    int pixelB = 0;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            int e = elements[i][j];
            COLORREF color = cbuffer[x + i - size2][y + j - size2];
            int colorR = GetRValue(color);
            int colorG = GetGValue(color);
            int colorB = GetBValue(color);
            pixelR += colorR * e;
            pixelG += colorG * e;
            pixelB += colorB * e;
        }
    }
    pixelR /= elementsSum;
    pixelG /= elementsSum;
    pixelB /= elementsSum;

    pixelR = max(min(pixelR, 255), 0);
    pixelG = max(min(pixelG, 255), 0);
    pixelB = max(min(pixelB, 255), 0);

    return RGB(pixelR, pixelG, pixelB);
}