#ifndef POISSONTILE_H
#define POISSONTILE_H

#include "box.h"
#include "vec.h"

/**
 * @brief Représentation d'une tuile remplie de disques de Poisson.
 */
class PoissonTile : public Box2
{
public:
    /**
     * @brief Constructeur vide.
     */
    PoissonTile();

    /**
     * @brief Crée une tuile de centre de disques de Poisson.
     * @param bl Point englobant minimum (inférieur gauche)
     * @param tr Point englobant maximum (supérieur droit)
     * @param radius Rayon des disques de poisson
     */
    PoissonTile(const Vec2& bl, const Vec2& tr, double radius);

    /**
     * @brief Remplit la tuile avec des disques de Poisson. Supprime les disques
     * précédemment générés.
     * @param radius Rayon des disques de poisson
     */
    void populate(double radius);

    /**
     * @brief Vérifie la validité de la position dans la tuile, en prenant en compte
     * le débordement de certains disques hors de la tuile.
     * @param pos Centre d'un disque à tester
     * @param radius Rayon des disques de poisson
     * @return Vrai si la position n'intersecte aucun disques déja présents, faux sinon.
     */
    bool isPosValid(const Vec2& pos, double radius) const;

    /**
     * @brief Liste des positions des centre des disques des la tuile.
     */
    QVector<Vec2> m_pos;
};

#endif // POISSONTILE_H
