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
    m_height.resize((m_nx - 1) * (m_ny - 1));

    for(int i = 0; i < m_nx; ++i){
        for(int j = 0; j < m_ny; ++j){
            m_height[index(i,j)] = (float)qRed(image.pixel(i, j)) * (zMax - zMin)
                    + zMin;
        }
    }
}

double ScalarField::height(int i, int j){
    return m_height[index(i,j)];
}

double ScalarField::height(double x, double y,
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
    // Local coordonates
    Vec2 pLocal = Vec2((x + m_bl.x) / (m_tr.x - m_bl.x),
                           (y - m_bl.y) / (m_tr.y - m_bl.y));

    // Cell coordonates
    Vec2 cell = Vec2(int(pLocal.x * m_nx), int(pLocal.y * m_ny));

    // In-cell coordonnates
    Vec2 pCell = Vec2(pLocal.x - cell.x * (m_tr.x - m_bl.x) / m_nx,
                          pLocal.y - cell.y * (m_tr.y - m_bl.y) / m_ny);

    if (pLocal.x + pLocal.y < 1.0) {
        return (1 - pCell.x - pCell.y) * height(cell.x,cell.y)
               + pCell.x * height(cell.x+1,cell.y)
               + pCell.y * height(cell.x,cell.y+1);
    }
    //else
    return (pCell.x + pCell.y - 1) * height(cell.x+1,cell.y+1)
           + (1 - pCell.x) * height(cell.x+1,cell.y)
           + (1 - pCell.y) * height(cell.x,cell.y+1);
}

double ScalarField::bilinearInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
    return 0.0;
}

double ScalarField::bicubicInterpol(double x, double y) {
	throw std::logic_error("Not implemented");
    return 0.0;
}

