#ifndef TREE_H
#define TREE_H

#include "scalarfield.h"

/**
 * @brief Classe abstraite représentant un arbre quelconque.
 */
class Tree
{
public:
    /**
     * @brief Réponse de l'arbre entre 0 et 1 à l'épaisseur de terre.
     */
    virtual double dirtHeightResponse(double dirtHeight) const = 0;
    ScalarField dirtHeightMapResponse(const ScalarField& dirtHeight) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la hauteur.
     */
    virtual double heightResponse(double height) const = 0;
    ScalarField heightMapResponse(const ScalarField& height) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la pente.
     */
    virtual double slopeResponse(double slope) const = 0;
    ScalarField slopeMapResponse(const ScalarField& slope) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 au taux d'humidité.
     */
    virtual double wetnessResponse(double wetness) const = 0;
    ScalarField wetnessMapResponse(const ScalarField& wetness) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 au stream power.
     */
    virtual double streamPowerResponse(double streamPower) const = 0;
    ScalarField streamPowerMapResponse(const ScalarField& streamPower) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la lumière.
     */
    virtual double lightResponse(double light) const = 0;
    ScalarField lightMapResponse(const ScalarField& light) const;

    /**
     * @brief Calcule la densité de probabilité d'un arbre en fonction des paramètres du terrain.
     */
    double chanceToSpawn(double dirtHeight, double height, double slope,
                         double wetness, double streamPower,
                         double light) const;
};

/**
 * @brief Représentation d'un sapin.
 */
class Sapin : public Tree
{
public:
    /**
     * @brief Contructeur vide.
     */
    Sapin();
    ~Sapin();

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à l'épaisseur de terre.
     */
    virtual double dirtHeightResponse(double dirtHeight) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la hauteur.
     */
    virtual double heightResponse(double height) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la pente.
     */
    virtual double slopeResponse(double slope) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 au taux d'humidité.
     */
    virtual double wetnessResponse(double wetness) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 au stream power.
     */
    virtual double streamPowerResponse(double streamPower) const;

    /**
     * @brief Réponse de l'arbre entre 0 et 1 à la lumière.
     */
    virtual double lightResponse(double light) const;
};

#endif // TREE_H
