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
              const Point2& m_bl, const Point2& m_tr,
              double zMin, double zMax);

    double height(int i, int j);
    double height(double x, double y,
                  interpolationType interpolation = INTERPOL_TRIANGULAR);

private:
	int index(int i, int j);

    double triangularInterpol(double x, double y);
    double bilinearInterpol(double x, double y);
    double bicubicInterpol(double x, double y);

    QVector<float> m_height;
    int m_nx, m_ny;
    Point2 m_bl, m_tr;
};
