#include "layerfield.h"

void LayerField::load(const QImage& imageBR,
                 const QImage& imageS,
                const Vec2& bl, const Vec2& tr,
                double zMinBR, double zMaxBR,
                double zMinS, double zMaxS) {
    m_bedrock = ScalarField();
    m_bedrock.load(imageBR, bl, tr, zMinBR, zMaxBR);
    m_sand = ScalarField();
    double thickness_S = zMaxS - zMinS;
    m_sand.load(imageS, bl, tr, 0, thickness_S);
}

double LayerField::height(int i, int j) {
    double h_bedrock = m_bedrock.value(i,j);
    double h_sand = m_sand.value(i,j);
    return h_bedrock + h_sand;
}

double LayerField::height(double i, double j) {
    double h_bedrock = m_bedrock.value(i,j);
    double h_sand = m_sand.value(i,j);
    return h_bedrock + h_sand;
}

void LayerField::thermal(double k) {
    throw std::logic_error("Not implemented");
    // stress = k * delta_h;
    // h = moyenne des 4 variations de hauteurs
}

void LayerField::addSand(double h) {
    if(h <= 0.0) {
        throw std::invalid_argument("impossible to add a negative or null value of sand");
    }

    for(int i = 0;i < m_sand.nx;i++) {
        for(int j = 0;j < m_sand.ny;j++) {
            m_sand.setValue(i, j, m_sand.value(i, j) + h);
        }
    }
}

void LayerField::stabilize() {
    throw std::logic_error("Not implemented");
}
