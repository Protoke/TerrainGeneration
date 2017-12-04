#pragma once

#include <QVector>
#include <QImage>

#include "vec.h"

class ScalarField {
public:
	enum interpolationType {
		INTERPOL_TRIANGULAR = 0,
		INTERPOL_BILINEAR,
		INTERPOL_BICUBIC
	};

    void load(const QImage& image,
              const Vec2& m_bl, const Vec2& m_tr,
              double zMin, double zMax);

    double value(double x, double y,
                  interpolationType interpolation = INTERPOL_TRIANGULAR);

private:
    double triangularInterpol(double x, double y);
    double bilinearInterpol(double x, double y);
    double bicubicInterpol(double x, double y);

    QVector<double> m_h;
    int m_nx, m_ny;
    Vec2 m_bl, m_tr;
};
