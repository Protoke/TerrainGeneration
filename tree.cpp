#include <qmath.h>

#include "tree.h"

double Tree::chanceToSpawn(double dirtHeight, double height, double slope,
                           double drain, double wetness, double streamPower,
                           double light) const {
    return dirtHeightResponse(dirtHeight) * heightResponse(height) *
            slopeResponse(slope) * drainAreaResponse(drain) *
            wetnessResponse(wetness) * streamPowerResponse(streamPower) *
            lightResponse(light);
}

Sapin::Sapin() { }
Sapin::~Sapin() { }

double Sapin::dirtHeightResponse(double dirtHeight) const {
    return 1.0;
}

double Sapin::heightResponse(double height) const {
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
    return 1.0;
}

double Sapin::drainAreaResponse(double drain) const {
    return 1.0;
}

double Sapin::wetnessResponse(double wetness) const {
    return 1.0;
}

double Sapin::streamPowerResponse(double streamPower) const {
    return 1.0;
}

double Sapin::lightResponse(double light) const {
    return 1.0;
}

