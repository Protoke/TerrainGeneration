#include <qmath.h>

#include "tree.h"

ScalarField Tree::dirtHeightMapResponse(const ScalarField& dirtHeight) const {
    ScalarField sf(Box2(dirtHeight.bl, dirtHeight.tr), dirtHeight.nx, dirtHeight.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, dirtHeightResponse(dirtHeight.value(i, j)));
    }

    return sf;
}

ScalarField Tree::heightMapResponse(const ScalarField& height) const {
    ScalarField sf(Box2(height.bl, height.tr), height.nx, height.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, heightResponse(height.value(i, j)));
    }

    return sf;
}

ScalarField Tree::slopeMapResponse(const ScalarField& slope) const {
    ScalarField sf(Box2(slope.bl, slope.tr), slope.nx, slope.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, slopeResponse(slope.value(i, j)));
    }

    return sf;
}

ScalarField Tree::wetnessMapResponse(const ScalarField& wetness) const {
    ScalarField sf(Box2(wetness.bl, wetness.tr), wetness.nx, wetness.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, wetnessResponse(wetness.value(i, j)));
    }

    return sf;
}

ScalarField Tree::streamPowerMapResponse(const ScalarField& streamPower) const {
    ScalarField sf(Box2(streamPower.bl, streamPower.tr), streamPower.nx, streamPower.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, streamPowerResponse(streamPower.value(i, j)));
    }

    return sf;
}

ScalarField Tree::lightMapResponse(const ScalarField& light) const {
    ScalarField sf(Box2(light.bl, light.tr), light.nx, light.ny);

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        sf.setValue(i, j, lightResponse(light.value(i, j)));
    }

    return sf;
}

double Tree::chanceToSpawn(double dirtHeight, double height, double slope,
                           double wetness, double streamPower,
                           double light) const {
    double val = qMin(dirtHeightResponse(dirtHeight), heightResponse(height));
    val = qMin(val, slopeResponse(slope));
    val = qMin(val, wetnessResponse(wetness));
    val = qMin(val, streamPowerResponse(streamPower));
    val = qMin(val, lightResponse(light));
    return  val;
}

Sapin::Sapin() { }
Sapin::~Sapin() { }

double Sapin::dirtHeightResponse(double dirtHeight) const {
    if(dirtHeight > 1.0)
        return 1.0;
    return 0.0;
}

double Sapin::heightResponse(double height) const {
    // coeff pour changer la hauteur de spawn des sapins
    // utile pour la démo, pas pour du réaliste
    height += 100.0;
    height *= 10.0;

    if(height >= 0 && height < 500)
        return 0.0004 * height;
    if(height >= 500 && height < 1500)
        return qCos((height - 500.0) * M_PI / 1000.0 + M_PI)
               * 0.8 / 2.0 + 0.6;
    if(height >= 1500 && height < 2000)
        return 1.0;
    if(height >= 2000 && height < 3000)
        return qCos((height - 2000.0) * M_PI / 1000.0)
               / 2.0 + 0.5;
    return 0.0;
}

double Sapin::slopeResponse(double slope) const {
    if(abs(slope) >= qTan(80.0 * M_PI / 180.0))
        return 0.0;
    return 1.0;
}

double Sapin::wetnessResponse(double wetness) const {
    double b = 3;
    double c = 2;
    return qExp(-(wetness - b) * (wetness - b) / (2 * c * c));
}

double Sapin::streamPowerResponse(double streamPower) const {
    if(streamPower >= 0 && streamPower < 200)
        return (qCos(streamPower * M_PI / 200.0) + 1.0) / 2.0;
    if(streamPower >= 200)
        return 0.0;
    return 1.0;
}

double Sapin::lightResponse(double light) const {
    if(light >= 0 && light < 0.5)
        return (qCos(light * M_PI / 0.5 + M_PI) + 1.0) / 2.0;
    if(light >= 0.5)
        return 1.0;
    return 0.0;
}

