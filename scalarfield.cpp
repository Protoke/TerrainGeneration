#include "scalarfield.h"

#include <stdexcept> 

void ScalarField::load(const QImage& image, Point2 bl, Point2 tr, double zMin, double zMax) {
	throw std::logic_error("Not implemented");
}

Point3 ScalarField::operator() (int i, int j) {
	return Point3(
		bl.x + (tr.x - bl.x) * i / (nx - 1),
		bl.y + (tr.y - bl.y) * j / (ny - 1),
		height[index(i, j)]
	);
}

Point3 ScalarField::operator() (double x, double y, interpolationType interpolation) {
	
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

int ScalarField::index(int i, int j) {
	return i*ny + j;
}
