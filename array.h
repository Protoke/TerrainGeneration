#ifndef ARRAY2_H
#define ARRAY2_H

#include "box.h"

/**
 * @brief Représentation d'une grille régulière orthogonale.
 */
class Array2 : public Box2
{
public:
    /**
     * @brief Constructeur vide.
     */
    Array2();

    /**
     * @brief Crée une grille à partir de deux points bornes et d'un nombre de point horizontal et vertical.
     * @param bl Point extrémité inférieur gauche
     * @param tr Point extrémité supérieur droit
     * @param nx Nombre de points sur la grille horizontalement
     * @param ny Nombre de points sur la grille verticalement
     */
    Array2(const Vec2& bl, const Vec2& tr, int nx, int ny);

    /**
     * @brief Constructeur par copie
     */
    Array2(const Array2& a);

    /**
     * @brief Calcule les coordonnées 1D d'un point en fonction de coordonnées 2D d'un point de la grille.
     * @param i Coordonnée horizontale
     * @param j Coordonnée verticale
     * @return index du point (i,j) pour un tableau 1D contenant tous les points de la grille dans l'ordre j croissant, puis i croissant
     */
    int index(int i, int j) const;

    /**
     * @brief Calcule les coordonnées interne à la cellule à partir d'un point réel.
     * @param x Coordonnée réelle horizontale
     * @param y Coordonnée réelle verticale
     * @return Coordonnées (u, v) normalisées entre 0 et 1.
     */
    Vec2 localCoordinates(double x, double y) const;

    /**
     * @brief Calcule la taille d'une cellule de la grille.
     * @return Vec2 contenant (taille horizontale , taille verticale).
     */
    Vec2 cellSize() const;

    /**
     * @brief Vérifie que le point (i, j) correspond bien à un point de la grille.
     * @param i Coordonnée horizontale
     * @param j Coordonnée verticale
     * @return true si les coordonnées décrivent un point de la grille, false sinon.
     */
    bool isInsideDomain(int i, int j) const;

    /**
     * @brief Vérifie que le point (x, y) réel est bien inclut dans la grille (bornes inférieures et supérieures comprises).
     * @param i Coordonnée réelle horizontale
     * @param j Coordonnée réelle verticale
     * @return true si les coordonnées représentent un point inclut dans grille, false sinon.
     */
    bool isInsideDomain(double x, double y) const;

    /**
     * @brief Nombre de points horizontalement.
     */
    int nx;
    /**
     * @brief Nombre de points verticalement.
     */
    int ny;

    /**
     * @brief Tableau décrivant les différences entre un point central et chacun des 8 points voisins.
     * Utilisé pour boucler sur les voisins d'un point avec la formule voisin[i] = centre + next[i].
     */
    static const Vec2 next[8];
    /**
     * @brief Tableau décrivant la distance entre un point central et chacun des 8 points voisins.
     */
    static const double length[8];
};

#endif // ARRAY2_H
