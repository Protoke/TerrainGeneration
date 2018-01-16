#pragma once

#include <QVector>
#include <QImage>

#include "vec.h"
#include "array.h"
#include "vecfield.h"

class ScalarField : public Array2 {
public:
	enum interpolationType {
		INTERPOL_TRIANGULAR = 0,
		INTERPOL_BILINEAR,
		INTERPOL_BICUBIC
	};

    ScalarField();
    ScalarField(const Box2& b, int nx, int ny);

    void load(const QImage& image,
              const Vec2& bl, const Vec2& tr,
              double zMin, double zMax);
    void toImage(QImage& image) const;

    Vec3 point(int i, int j) const;
    Vec3 point(double x, double y) const;
    Vec2 point2(int i, int j) const;
    QVector<Vec3> listOfPoints() const;

    Vec2 range() const;

    void add(double v);
    void add(int i, int j, double v);

    void setValue(int x, int y, int v);
    double value(int i, int j) const;
    double value(double x, double y,
                  interpolationType interpolation = INTERPOL_TRIANGULAR) const;

    Vec2 gradient(int i, int j) const;
    Vec2Field gradient() const;
    ScalarField gradientNorm() const;

    void display() const;

protected:
    double triangularInterpol(double x, double y) const;
    double bilinearInterpol(double x, double y) const;
    double bicubicInterpol(double x, double y) const;

    QVector<double> m_h;
};
