#include "scalarfield.h"

#include <stdexcept> 

void ScalarField::load(const QImage& image,
                       const Vec2& bl, const Vec2& tr,
                       double zMin, double zMax)
{
    this->m_bl = bl;
    this->m_tr = tr;
    m_nx = image.width();
    m_ny = image.height();
    m_h.resize((m_nx - 1) * (m_ny - 1));

    for(int i = 0; i < m_nx; ++i){
        for(int j = 0; j < m_ny; ++j){
            m_h[index(i,j)] = (float)qRed(image.pixel(i, j)) * (zMax - zMin)
                    + zMin;
        }
    }
}

Vec3 ScalarField::point(int x, int y) {
    return Vec3(x, y, value(x, y));
}

Vec3 ScalarField::point(double x, double y) {
    return Vec3(x, y, value(x, y));
}

double ScalarField::value(int i, int j){
    return m_h[index(i,j)];
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
    Vec2 pLocal = Vec2((x + m_bl.x) / (m_tr.x - m_bl.x),
                           (y - m_bl.y) / (m_tr.y - m_bl.y));

    // Cell coordinates
    Vec2 cell = Vec2(int(pLocal.x * m_nx), int(pLocal.y * m_ny));
    int cellX = (int) cell.x;
    int cellY = (int) cell.y;

    // In-cell coordinates
    Vec2 pCell = Vec2(pLocal.x - cell.x * (m_tr.x - m_bl.x) / m_nx,
                          pLocal.y - cell.y * (m_tr.y - m_bl.y) / m_ny);

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

