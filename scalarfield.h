#pragma once

#include <QVector>
#include <QImage>

#include "vec.h"
#include "array.h"
#include "vecfield.h"

class Vec2Field;

/**
 * @brief Représentation d'une grille de scalaires.
 */
class ScalarField : public Array2 {
public:
    /**
     * @brief Description des types d'interpolation des valeurs.
     */
	enum interpolationType {
		INTERPOL_TRIANGULAR = 0,
		INTERPOL_BILINEAR,
		INTERPOL_BICUBIC
	};

    /**
     * @brief Constructeur vide.
     */
    ScalarField();

    /**
     * @brief Construit un ScalarField nul à partir d'une définition d'une grille.
     * @param b Boite englobante de la grille
     * @param nx Nombre de points de la grille horizontalement
     * @param ny Nombre de points de la grille verticalement
     */
    ScalarField(const Box2& b, int nx, int ny);

    /**
     * @brief Initialise le ScalarField à partir des valeurs d'une image.
     * @param image Image dont les valeurs sont tirées
     * @param bl Point extrémité inférieur gauche
     * @param tr Point extrémité supérieur droit
     * @param zMinBR Valeur minimale
     * @param zMaxBR Valeur maximale
     */
    void load(const QImage& image,
              const Vec2& bl, const Vec2& tr,
              double zMin, double zMax);

    /**
     * @brief Convertit le ScalarField en image.
     * @param image Image stockant les valeurs
     * @param useColor true pour utiliser un dégradé de couleur, false pour utiliser un dégradé de gris (par défaut)
     */
    void toImage(QImage& image, bool useColor = false) const;

    /**
     * @brief Récupère le point 3D de coordonnées (i ,j) sur la grille.
     */
    Vec3 point(int i, int j) const;

    /**
     * @brief Récupère le point 3D de coordonnées réelles (x, y).
     */
    Vec3 point(double x, double y) const;

    /**
     * @brief Convertit le point de coordonnées (i, j) sur la grille en un point de coordonnées réelles.
     */
    Vec2 point2(int i, int j) const;

    /**
     * @brief Retourne la liste des points de la grille (avec leur coordonnée de hauteur) sous forme de liste.
     */
    QVector<Vec3> listOfPoints() const;

    /**
     * @brief Calcule les valeurs minimales et maximales du ScalarField.
     * @return Vec2 comprenant (valeur minimale, valeur maximale)
     */
    Vec2 range() const;

    /**
     * @brief Ajoute un flottant v à tous les points du terrain.
     */
    void add(double v);

    /**
     * @brief Ajoute un flottant v au point de coordonnées (i, j) sur la grille.
     */
    void add(int i, int j, double v);

    /**
     * @brief Initialise le point de coordonnées (i, j) sur la grille à la valeur v.
     */
    void setValue(int i, int j, double v);

    /**
     * @brief Récupère la valeur au point de coordonnées (i, j) de la grille.
     */
    double value(int i, int j) const;

    /**
     * @brief Récupère la valeur au point de coordonnées réelles (x, y) suivant l'interpolation désirée.
     */
    double value(double x, double y,
                  interpolationType interpolation = INTERPOL_TRIANGULAR) const;

    /**
     * @brief Calcule le gradient au point de coordonnées (i, j) sur la grille.
     */
    Vec2 gradient(int i, int j) const;

    /**
     * @brief Calcule le gradient sur toute la grille.
     */
    Vec2Field gradient() const;

    /**
     * @brief Calcule la norme du gradient sur toute la grille.
     */
    ScalarField gradientNorm() const;

    /**
     * @brief Ecrit le contenu de la grille sur la sortie standard.
     */
    void display() const;

protected:
    double triangularInterpol(double x, double y) const;
    double bilinearInterpol(double x, double y) const;
    double bicubicInterpol(double x, double y) const;

    QVector<double> m_h;
};
