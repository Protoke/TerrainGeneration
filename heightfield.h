#ifndef HEIGHTFILED_H
#define HEIGHTFILED_H

#include "scalarfield.h"
#include "analyticscalarfield.h"
#include "vec.h"
#include "mesh.h"
#include "ray.h"

/**
 * @brief Classe représentant une carte de hauteur.
 */
class HeightField : public ScalarField
{
public:
    /**
     * @brief Constructeur vide.
     */
    HeightField();

    /**
     * @brief Construit un HeightField plat (hauteur 0) à partir d'une définition d'une grille.
     * @param b Boite englobante de la grille
     * @param nx Nombre de points de la grille horizontalement
     * @param ny Nombre de points de la grille verticalement
     */
    HeightField(const Box2& b, int nx, int ny);

    /**
     * @brief Construit un HeightField à partir des valeurs d'un AnalyticScalarField et d'une grille.
     * @param a Terrain analytique sur lequel prendre les valeurs
     * @param b Boite englobante de la grille
     * @param nx Nombre de points de la grille horizontalement
     * @param ny Nombre de points de la grille verticalement
     */
    HeightField(const AnalyticScalarField& a, const Box2& b, int nx, int ny);

    /**
     * @brief Test d'intersection entre un point et le terrain (si le point est sous le sol).
     * @param p Coordonnées réelles du point à tester
     * @return true si le point est sous le sol (p.z <= terrain.z), false sinon.
     */
    bool inside(const Vec3& p) const;

    /**
     * @brief Calcule la normale au terrain pour le point sur la grille (i, j)
     * @param i Coordonnée horizontale
     * @param j Coordonnée verticale
     * @return Vecteur représentant la normale au terrain
     */
    Vec3 normal(int i, int j) const;

    /**
     * @brief Calcule la normale au terrain pour le point sur la grille (i, j)
     * @param i Coordonnée horizontale
     * @param j Coordonnée verticale
     * @return Vecteur représentant la normale au terrain
     */
    Vec3 normal(double x, double y) const;

    /**
     * @brief Calcule l'intersection d'un rayon avec le terrain.
     * @param r Rayon dont on veut calculer l'intersection
     * @param t Paramètre de sortie. Distance à laquelle l'intersection a été trouvée
     * @param range Distance maximale sur le rayon à tester
     * @return true si le rayon a intersecté le terrain (t est alors initialisé), false sinon.
     */
    bool intersect(Ray& r, double& t, double range) const;

    /**
     * @brief Calcule l'aire de drainage sur tout le terrain.
     */
    ScalarField drainingArea() const;

    /**
     * @brief Calcule le vecteur de la pente sur tout le terrain.
     */
    Vec2Field slope() const;

    /**
     * @brief Calcule le stream power sur tout le terrain.
     */
    ScalarField streamPower() const;

    /**
     * @brief Calcule l'accessibilité au point p.
     * @param _p Point sur lequel on veut calculer l'accessibilité
     * @param range Distance maximale à laquelle on veut calculer l'accessibilité
     */
    double access(Vec2 _p, double range) const;

    /**
     * @brief Calcule l'accessibilité sur tout le terrain.
     * @param range Distance maximale à laquelle on veut calculer l'accessibilité
     */
    ScalarField access(double range) const;

    /**
     * @brief Calcule le wetness index sur tout le terrain.
     */
    ScalarField wetnessIndex() const;

    /**
     * @brief Calcule le potentiel flux sur chaque voisin du point p.
     * On ne retourne que les informations des voisins plus bas que p. De ce fait, si p a 4 voisins plus bas, les 4 première cases des tableaux résultats seront remplies.
     * @param p Point sur lequel on veut effectuer les calculs
     * @param dumpPoints Paramètre de sortie. Tableau de 8 éléments contenant les coordonnées des voisins.
     * @param dumpHeight Paramètre de sortie. Tableau de 8 éléments contenant la différence de hauteur entre le point central et les voisins.
     * @param dumpSlope Paramètre de sortie. Tableau de 8 éléments contenant la pente entre le point central et les voisins.
     * @return Nombre de voisins plus bas que p.
     */
    int checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                            double* dumpHeight, double* dumpSlope) const;

    /**
     * @brief Crée un maillage du terrain.
     * @param stepi Pas entre chaque sommet sur l'axe horizontal
     * @param stepj Pas entre chaque sommet sur l'axe vertical
     * @return Maillage décrivant le terrain.
     */
    Mesh createMesh(int stepi = 1, int stepj = 1) const;

    // TODO faire des rayons aléatoire
    /**
     * @brief Liste de 9 rayons utilisés pour le calcul de l'accessibilité.
     */
    static const Vec3 ray[9];
};

#endif // HEIGHTFILED_H
