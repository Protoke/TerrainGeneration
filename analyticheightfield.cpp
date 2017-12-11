#include "analyticheightfield.h"

AnalyticHeightField::AnalyticHeightField() { }

AnalyticHeightField::AnalyticHeightField(double (*noiseFunction)(double,double),
                                         double A, double T,
                                         QVector<double> offsets, int levels) :
    m_A(A), m_T(T), m_levels(levels)
{
    m_noiseFunction = noiseFunction;
    m_offsets = offsets;
}

double AnalyticHeightField::height(const Vec2 &v) const{
    double height = 0;

    double pow2 = 1;

    for(int i = 0; i < m_levels; ++i){
        height += m_noiseFunction(v.x/(m_T/pow2) + m_offsets[i], v.y/(m_T/pow2) + m_offsets[i]) * (m_A/pow2);
        pow2 *= 2;
    }

    return height;
}

