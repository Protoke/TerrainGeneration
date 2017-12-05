#include "layerfield.h"

LayerField::LayerField()
{

}

void LayerField::load(const QImage& imageBR,
                 const QImage& imageS,
                const Vec2& bl, const Vec2& tr,
                double zMinBR, double zMaxBR,
                double zMinS, double zMaxS) {
    m_bedrock = ScalarField();
    m_bedrock.load(imageBR, bl, tr, zMinBR, zMaxBR);
    m_sand = ScalarField();
    m_sand.load(imageS, bl, tr, zMinS, zMaxS);
}

double LayerField::height(int i, int j) {
    throw std::logic_error("Not implemented");
    return 0.0;
}

double LayerField::height(double i, double j) {
    throw std::logic_error("Not implemented");
    return 0.0;
}

void LayerField::thermal(double stress) {
    throw std::logic_error("Not implemented");
}

void LayerField::addSand(double h) {
    throw std::logic_error("Not implemented");
}

void LayerField::stabilize() {
    throw std::logic_error("Not implemented");
}
