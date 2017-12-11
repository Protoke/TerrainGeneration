#ifndef ANALYTICHEIGHTFIELD_H
#define ANALYTICHEIGHTFIELD_H

#include <QVector>

#include "vec.h"
#include "qmath.h"

inline double noiseSin(double x, double y){
    return 1 - (qSin(x / 6.28) + 1.0) / 2.0 + (sin(y / 6.28) + 1.0) / 2.0;
}

class AnalyticHeightField
{
public:
    AnalyticHeightField();
    AnalyticHeightField(double (*noiseFunction)(double,double), double A, double T,
                        QVector<double> offsets, int levels);

    double height(const Vec2& v) const;

private:
    double (*m_noiseFunction)(double,double);
    double m_A, m_T;
    QVector<double> m_offsets;
    int m_levels;
};

#endif // ANALYTICHEIGHTFIELD_H
