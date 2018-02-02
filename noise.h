#ifndef NOISE_H
#define NOISE_H

#include "vec.h"

/**
 * @brief Classe abstraite de représentation de fonction de bruit 2D.
 */
class Noise
{
public:
    /**
     * @brief Retourne la valeur du bruit pour le point p.
     */
    virtual double value(const Vec2& p) const = 0;
};

/**
 * @brief Représentation d'une fonction de bruit simplex.
 */
class SimplexNoise : public Noise
{
public:
    /**
     * @brief Retourne la valeur du bruit pour le point p.
     */
    virtual double value(const Vec2& p) const;

protected:
    static const int grad2[8][2];
    static const int perm[512];

    double dot(const int* g, const double& x, const double& y) const;
};

#endif // NOISE_H
