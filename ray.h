#ifndef RAY_H
#define RAY_H

#include "vec.h"

/**
 * @brief Représentation d'un rayon.
 */
class Ray
{
public:
    /**
     * @brief Constructeur vide.
     */
    Ray();

    /**
     * @brief Construit un rayon.
     * @param origin Origine du rayon
     * @param direction Direction du rayon
     */
    Ray(Vec3 origin, Vec3 direction);

    /**
     * @brief Calcule les coordonnées du point d'abscisse d sur le rayon.
     */
    Vec3 operator()(double d) const;

    /**
     * @brief Origine du rayon.
     */
    Vec3 origin;

    /**
     * @brief Direction du rayon.
     */
    Vec3 direction;
};

#endif // RAY_H
