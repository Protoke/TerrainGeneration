#ifndef ANALYTICSCALARFIELD_H
#define ANALYTICSCALARFIELD_H

#include <QVector>

#include "vec.h"
#include "qmath.h"
#include "noise.h"

//inline double noiseSin(double x, double y){
//    return 1 - (qSin(x / 6.28) + 1.0) / 2.0 + (sin(y / 6.28) + 1.0) / 2.0;
//}

class AnalyticScalarField
{
public:
    AnalyticScalarField();
    AnalyticScalarField(const Noise* noise, double a, double f,
                        QVector<double>& off, int lvl);

    double value(const Vec2& v) const;

private:
    const Noise* noise;
    double m_A, m_F;
    QVector<double> m_offsets;
    int m_levels;
};

#endif // ANALYTICSCALARFIELD_H
