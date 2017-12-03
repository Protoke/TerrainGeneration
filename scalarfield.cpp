#include "scalarfield.h"

#include <stdexcept> 

void ScalarField::load(const QImage& image,
                       const Point2& bl, const Point2& tr,
                       double zMin, double zMax)
    : bl(bl), tr(tr)
{
	throw std::logic_error("Not implemented");

    nx = image.width();
    ny = image.height();
    height.resize((nx - 1) * (ny - 1));

    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            height[index(i,j)] = (float)qRed(image.pixel(i, j)) * (zMax - zMin)
                    + zMin;
        }
    }
}

Point3 ScalarField::operator() (int i, int j) {
	return Point3(
		bl.x + (tr.x - bl.x) * i / (nx - 1),
		bl.y + (tr.y - bl.y) * j / (ny - 1),
		height[index(i, j)]
	);
}

Point3 ScalarField::operator() (double x, double y,
                                interpolationType interpolation)
{
    switch(interpolation){
    case INTERPOL_TRIANGULAR : triangularInterpol(x, y); break;
    case INTERPOL_BILINEAR : bilinearInterpol(x, y); break;
    case INTERPOL_BICUBIC : bicubicInterpol(x, y); break;
    default : throw std::invalid_argument("Bad interpolation");
    }
}

int ScalarField::index(int i, int j) {
    return i*ny + j;
}

Point3 triangularInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
	return Point3();
}

Point3 bilinearInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
	return Point3();
}

Point3 bicubicInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
	return Point3();
}

