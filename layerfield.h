#ifndef LAYERFIELD_H
#define LAYERFIELD_H

#include "scalarfield.h"

class LayerField
{
public:
    LayerField();

    void load (const QImage& imageBR,
               const QImage& imageS,
               const Vec2& bl, const Vec2& tr,
               double zMinBR, double zMaxBR,
               double zMinS, double zMaxS);

    double height(int i, int j);

    double height(double i, double j);

    void thermal(const double stress);

    void addSand(const double h);

    void stabilize();

private:
    ScalarField m_bedrock;
    ScalarField m_sand;
};

#endif // LAYERFIELD_H
