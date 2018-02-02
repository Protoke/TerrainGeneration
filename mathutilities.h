#ifndef MATHUTILITIES_H
#define MATHUTILITIES_H

#include "vec.h"

/* Cast */
/**
 * @brief Cast un flottant en entier en prenant en compte le décalage dans les négatifs.
 */
int integer(double v);

/* Random */
/**
 * @brief Initialise le seed du générateur de nombres aléatoire. A utiliser avant randDouble().
 */
void randSeed();

/**
 * @brief Génère un double aléatoire entre min et max.
 */
double randDouble(double min = 0.0, double max = 1.0);

/* Geometry */
/**
 * @brief Retourne true si le cercle de centre ca et de rayon ra intersecte le cercle de centre cb et de rayon rb.
 */
bool intersectCircles(const Vec2& ca, double ra, const Vec2& cb, double rb);

#endif // MATHUTILITIES_H
