#include "analyticscalarfield.h"

AnalyticScalarField::AnalyticScalarField() { }

AnalyticScalarField::AnalyticScalarField(const Noise* noise, double a, double t,
                                         QVector<double>& off, int lvl) :
    noise(noise), m_A(a), m_T(t), m_offsets(off), m_levels(lvl)
{}

double AnalyticScalarField::value(const Vec2& v) const
{
    double height = 0.0;
    double pow2 = 1.0;

    for(int i = 0; i < m_levels; ++i){
        Vec2 vi(v.x/(m_T/pow2) + m_offsets[i] * 0.61,
                v.y/(m_T/pow2) + m_offsets[i] * 1.79);
        double value = noise->value(vi) * (m_A/pow2);
        height += value;
        pow2 *= 2.0;
    }

    // Gestion de la mer, tout ce qui est en dessous est sous la surface
    // de l'eau. Les fonds marins ne sont donc pas modélisés
//    if(height < -0.3)
//        height = -0.3;

    return height;
}

