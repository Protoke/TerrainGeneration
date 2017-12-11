#include "scalarfield.h"

#include <stdexcept> 

ScalarField::ScalarField() { }

ScalarField::ScalarField(const Box2& b, int nx, int ny) :
    Array2(b.bl, b.tr, nx, ny)
{
    m_h.resize((nx) * (ny));
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_h[index(i,j)] = 0.0;
        }
    }
}

void ScalarField::load(const QImage& image,
                       const Vec2& bl, const Vec2& tr,
                       double zMin, double zMax)
{
    this->bl = bl;
    this->tr = tr;
    nx = image.width();
    ny = image.height();
    m_h.resize((nx) * (ny));

    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_h[index(i,j)] = (float)qRed(image.pixel(i, j)) * (zMax - zMin) / 255.0
                    + zMin;
        }
    }
}

Vec3 ScalarField::point(int i, int j) {
    return Vec3(bl.x + (tr.x-bl.x) * i / (nx - 1),
                bl.y + (tr.y-bl.y) * j / (ny - 1),
                value(i, j));
}

Vec3 ScalarField::point(double x, double y) {
    return Vec3(x, y, value(x, y));
}

Vec2 ScalarField::point2(int i, int j){
    Vec3 p = point(i, j);
    return Vec2(p.x, p.y);
}

double ScalarField::value(int i, int j){
    return m_h[index(i,j)];
}

void ScalarField::setValue(int i, int j, int v) {
    m_h[index(i,j)] = v;
}

double ScalarField::value(double x, double y,
                           interpolationType interpolation)
{
    switch(interpolation){
    case INTERPOL_TRIANGULAR : return triangularInterpol(x, y); break;
    case INTERPOL_BILINEAR : return bilinearInterpol(x, y); break;
    case INTERPOL_BICUBIC : return bicubicInterpol(x, y); break;
    default : throw std::invalid_argument("Bad interpolation");
    }
}

double ScalarField::triangularInterpol(double x, double y) {
    // Local coordinates
    Vec2 pLocal = localCoordinates(x, y);

    // Cell coordinates
    Vec2 cell = Vec2(int(pLocal.x * nx), int(pLocal.y * ny));
    int cellX = (int) cell.x;
    int cellY = (int) cell.y;

    // In-cell coordinates
    Vec2 pCell = Vec2(pLocal.x - cell.x * (tr.x - bl.x) / nx,
                          pLocal.y - cell.y * (tr.y - bl.y) / ny);

    if (pLocal.x + pLocal.y < 1.0) {
        return (1 - pCell.x - pCell.y) * value(cellX, cellY)
               + pCell.x * value(cellX+1, cellY)
               + pCell.y * value(cellX, cellY+1);
    }
    //else
    return (pCell.x + pCell.y - 1) * value(cellX+1, cellY+1)
           + (1 - pCell.x) * value(cellX+1, cellY)
           + (1 - pCell.y) * value(cellX, cellY+1);
}

double ScalarField::bilinearInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
    return 0.0;
}

double ScalarField::bicubicInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
    return 0.0;
}

