#include <QTime>

#include "mathutilities.h"

int integer(double v){
    if(v < 0)
        return (int)v - 1;
    return (int)v;
}

void randSeed(){
    qsrand(QTime::currentTime().msec());
}

double randDouble(double min, double max){
    double random = ((double) qrand()) / (double) RAND_MAX;
    return min + random * (max - min);
}

bool intersectCircles(const Vec2 &ca, double ra, const Vec2 &cb, double rb){
    double dist = (cb - ca).length();
    return dist < ra + rb;
}
