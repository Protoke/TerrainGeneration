#pragma once

#include <QVector>

#include "vec.h"

/**
 * @brief Représentation d'une boite alignée sur les axes.
 */
class Box2
{
public:
    /**
     * @brief Constructeur vide.
     */
	Box2();

    /**
     * @brief Contruit une boite à partir des bornes
     * @param bl Point extrémité inférieur gauche
     * @param tr Point extrémité supérieur droit
     */
    Box2(const Vec2& bl, const Vec2& tr);

    /**
     * @brief Constructeur par copie.
     */
    Box2(const Box2& b);

    /**
     * @brief Point extrémité inférieur gauche
     */
    Vec2 bl;

    /**
     * @brief Point extrémité supérieur droit
     */
    Vec2 tr;
};
