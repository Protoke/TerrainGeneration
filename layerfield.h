#ifndef LAYERFIELD_H
#define LAYERFIELD_H

#include <QVector>

#include "vec.h"
#include "scalarfield.h"
#include "heightfield.h"

/**
 * @brief Représentation d'un terrain multi-couches (bedrock et sand/dirt).
 */
class LayerField
{
public:
    /**
     * @brief Constructeur vide.
     */
    LayerField();

    /**
     * @brief Construit un terrain multi-couches à partir d'une carte de hauteur.
     * Seule la couche bedrock est remplie à partir de ces informations, la couche sand est nulle.
     * @param Carte de hauteur pour construire la couche bedrock.
     */
    LayerField(const HeightField& hf);

    /**
     * @brief Initialise les couches bedrock et sand à partir d'images de cartes de hauteur et d'une boite englobante du terrain.
     * @param imageBR Image représentant la carte de hauteur de la couche bedrock
     * @param imageS Image représentant la carte de hauteur de la couche sand
     * @param bl Point extrémité inférieur gauche
     * @param tr Point extrémité supérieur droit
     * @param zMinBR Hauteur minimale de la couche bedrock
     * @param zMaxBR Hauteur maximale de la couche bedrock
     * @param zMinS Hauteur minimale de la couche sand
     * @param zMaxS Hauteur maximale de la couche sand
     */
    void load (const QImage& imageBR,
               const QImage& imageS,
               const Vec2& bl, const Vec2& tr,
               double zMinBR, double zMaxBR,
               double zMinS, double zMaxS);

    /**
     * @brief Initialise la couche bedrock à partir d'images de cartes de hauteur et d'une boite englobante du terrain. La couche sand est nulle.
     * @param imageBR Image représentant la carte de hauteur de la couche bedrock
     * @param bl Point extrémité inférieur gauche
     * @param tr Point extrémité supérieur droit
     * @param zMinBR Hauteur minimale de la couche bedrock
     * @param zMaxBR Hauteur maximale de la couche bedrock
     */
    void load (const QImage& imageBR,
               const Vec2& bl, const Vec2& tr,
               double zMinBR, double zMaxBR);

    /**
     * @brief Calcule la hauteur totale au point de la grille (i, j).
     * @param i Coordonnée horizontale
     * @param j Coordonnée verticale
     * @return Hauteur de la couche bedrock + hauteur de la couche sand au point (i, j)
     */
    double height(int i, int j) const;

    /**
     * @brief Calcule la hauteur totale au point réel (x, y).
     * @param x Coordonnée horizontale
     * @param y Coordonnée verticale
     * @return Hauteur de la couche bedrock + hauteur de la couche sand au point (x, y)
     */
    double height(double x, double y) const;

    /**
     * @brief Ajoute une hauteur h de sable (à la couche sand) sur tout le terrain.
     */
    void addSand(double h);

    /**
     * @brief Ajoute une hauteur h de sable (à la couche sand) au point sur la grille de coordonnée (i, j).
     */
    void addSand(double h, int i, int j);

    /**
     * @brief Calcule une érosion thermique sur tout le terrain.
     * @param k Pourcentage (entre 0 et 1) de bedrock soumissible à l'érosion qui est converti en sable
     * @param erosion_threshold Seuil minimal de différence de hauteur pour qu'il y ait érosion
     */
    void thermal(double k, double erosion_threshold);

    /**
     * @brief Procède à la stabilisation du sable sur le terrain.
     * @param percentage_landslide Pourcentage (entre 0 et 1) de sable qui va glisser pendant une itération
     * @param nb_iterations Nombre d'itérations totale à effectuer
     */
    void stabilize(double percentage_landslide, int nb_iterations);

    /**
     * @brief Getter.
     */
    ScalarField bedrock() const;

    /**
     * @brief Getter.
     */
    ScalarField sand() const;

    /**
     * @brief Génère un HeightField à partir du terrain multi-couches.
     */
    HeightField toHeightField() const;

    /**
     * @brief Calcule le potentiel flux sur chaque voisin du point p.
     * On ne retourne que les informations des voisins plus bas que p. De ce fait, si p a 4 voisins plus bas, les 4 première cases des tableaux résultats seront remplies.
     * @param p Point sur lequel on veut effectuer les calculs
     * @param dumpPoints Paramètre de sortie. Tableau de 8 éléments contenant les coordonnées des voisins.
     * @param dumpSlope Paramètre de sortie. Tableau de 8 éléments contenant la pente entre le point central et les voisins.
     * @return Nombre de voisins plus bas que p.
     */
    int checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                            double* dumpSlope) const;

    /**
     * @brief Retourne la liste des points de la grille (avec leur coordonnée de hauteur) sous forme de liste.
     */
    QVector<Vec3> listOfPoints() const;

    /**
     * @brief Calcule le potentiel flux sur chaque voisin du point p.
     * On ne retourne que les informations des voisins plus bas que p et créant une pente d'un angle supérieur à stabilizationAngle.
     * @param p Point sur lequel on veut effectuer les calculs
     * @param dumpPoints Paramètre de sortie. Tableau de 8 éléments contenant les coordonnées des voisins.
     * @param dumpSlope Paramètre de sortie. Tableau de 8 éléments contenant la pente entre le point central et les voisins.
     * @param stabilizationAngle
     * @return Nombre de voisins plus bas que p.
     */
    int checkStabilizationDirections(const Vec3& p, Vec3* dumpPoints,
                                     double* dumpSlope,
                                     double stabilizationAngle) const;

protected:
    ScalarField m_bedrock;
    ScalarField m_sand;
};

#endif // LAYERFIELD_H
