#ifndef LAYERFIELD_H
#define LAYERFIELD_H

#include <QVector>

#include "vec.h"
#include "scalarfield.h"
#include "heightfield.h"

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

    void addSand(const double h);
    void addSand(double h, int i, int j);

    void thermal(const double k, const double erosion_threshold);
    void stabilize(const double percentage_landslide, int nb_iterations);

    ScalarField bedrock() const;
    ScalarField sand() const;

    HeightField toHeightField() const;

    int checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                            double* dumpSlope) const;

    QVector<Vec3> listOfPoints() const;

    int checkStabilizationDirections(const Vec3& p, Vec3* dumpPoints,
                                     double* dumpSlope,
                                     const double stabilizationAngle) const;

    ScalarField m_bedrock;
    ScalarField m_sand;
};

#endif // LAYERFIELD_H
