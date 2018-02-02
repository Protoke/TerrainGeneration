#ifndef ANALYTICSCALARFIELD_H
#define ANALYTICSCALARFIELD_H

#include <QVector>

#include "vec.h"
#include "qmath.h"
#include "noise.h"

/**
 * @brief Représentation d'un terrain analytique, généré par une somme de fonction de bruit
 */
class AnalyticScalarField
{
public:
    /**
     * @brief Constructeur vide.
     */
    AnalyticScalarField();

    /**
     * @brief Crée un AnalyticScalarField à partir de la définition d'une somme de bruit.
     * @param noise Classe représentant la fonction de bruit
     * @param a Amplitude du bruit initiale.
     * @param t Période du bruit initiale.
     * @param off Vecteur d'offsets permettant de décaler l'origine du bruit  chaque niveau. Doit avoir la même taille que le nombre de niveaux.
     * @param lvl Nombre de niveau de bruit
     */
    AnalyticScalarField(const Noise* noise, double a, double t,
                        QVector<double>& off, int lvl);

    /**
     * @brief Fonction de récupération de la valeur de l'AnalyticScalarField aux coordonnées v.
     */
    double value(const Vec2& v) const;

private:
    const Noise* noise;
    double m_A, m_T;
    QVector<double> m_offsets;
    int m_levels;
};

#endif // ANALYTICSCALARFIELD_H
