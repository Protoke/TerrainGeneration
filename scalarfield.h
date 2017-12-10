#pragma once

#include <QVector>
#include <QImage>

#include "vec.h"
#include "array.h"

class ScalarField : public Array2 {
public:
	enum interpolationType {
		INTERPOL_TRIANGULAR = 0,
		INTERPOL_BILINEAR,
		INTERPOL_BICUBIC
	};

    void load(const QImage& image,
              const Vec2& bl, const Vec2& tr,
              double zMin, double zMax);

    Vec3 point(int i, int j);

    Vec3 point(double x, double y);

    double value(int i, int j);

    double value(double x, double y,
                  interpolationType interpolation = INTERPOL_TRIANGULAR);

    void setValue(int x, int y, int v);

private:
    double triangularInterpol(double x, double y);
    double bilinearInterpol(double x, double y);
    double bicubicInterpol(double x, double y);

    QVector<double> m_h;
};
