#ifndef TREEFIELD_H
#define TREEFIELD_H

#include <QVector>

#include "tree.h"
#include "scalarfield.h"
#include "layerfield.h"

/**
 * @brief Classe servant à stocker les densités de probabilité des différents arbre ainsi que de générer les positions des arbres.
 */
class TreeField
{
public:
    /**
     * @brief Constructeur vide.
     */
    TreeField();

    /**
     * @brief Construit le TreeField et génère les probabilité de densité à partir d'un LayerField.
     */
    TreeField(const LayerField& lf);

    /**
     * @brief Génère les probabilité de densité à partir d'un LayerField.
     */
    void initSapinDensity(const LayerField& lf);

    /**
     * @brief Génère les positions des arbres avec une tuile de poisson.
     * @param origin Position de la tuile à l'origine
     * @param tileBox Boite décrivant la borne min et la borne max de la tuile
     * @param treeRadius Rayon des arbres
     * @return Liste des centre des arbres générés
     */
    QVector<Vec2> spawnTrees(const Vec2& origin, const Box2& tileBox,
                             double treeRadius);

    /**
     * @brief Convertit une lsite de position de centres d'arbres en image.
     * @param image Image dans laquelle dessiner les position des arbres
     * @param posTree Liste des positions des arbres
     * @param resolutionFactor Facteur de résolution de l'image.
     * Par défaut, la résolution de l'image correspond à la résolution du terrain ayant servir à générer les probabilités de densité.
     * Avec un facteur > 1.0, la résolution de l'image augmente, et les positions des arbres sur l'image sont plus précises.
     */
    void toImage(QImage& image, const QVector<Vec2>& posTree,
                        double resolutionFactor = 1.0) const;

    /**
     * @brief Probabilité de densité pour les sapins.
     */
    ScalarField m_sapinDensity;

protected:
    ScalarField initTreeDensity(const LayerField& lf, Tree* t);
};

#endif // TREEFIELD_H
