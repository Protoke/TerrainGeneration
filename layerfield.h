#ifndef LAYERFIELD_H
#define LAYERFIELD_H

#include "scalarfield.h"

class LayerField
{
public:
    void load (const QImage& imageBR,
               const QImage& imageS,
               const Vec2& bl, const Vec2& tr,
               double zMinBR, double zMaxBR,
               double zMinS, double zMaxS);

    void load (const QImage& imageBR,
               const Vec2& bl, const Vec2& tr,
               double zMinBR, double zMaxBR);

    double height(int i, int j) const;

    double height(double i, double j) const;

    void thermal(const double k, const double erosion_threshold);

    void addSand(const double h);

    void addSand(double h, int i, int j);

    void stabilize(const float percentage_landslide);

    ScalarField bedrock();

    ScalarField sand();

private:
    ScalarField m_bedrock;
    ScalarField m_sand;
};

#endif // LAYERFIELD_H
