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

	void load(const QImage& image, Point2 bl, Point2 tr, double zMin, double zMax);

	Point3 operator() (int i, int j);
	Point3 operator() (double x, double y, interpolationType interpolation = INTERPOL_TRIANGULAR);

private:
	int index(int i, int j);

	Point3 triangularInterpol(double x, double y);
	Point3 bilinearInterpol(double x, double y);
	Point3 bicubicInterpol(double x, double y);

	QVector<float> height;
	int nx, ny;
	Point2 bl, tr;
};
