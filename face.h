#ifndef FACE_H
#define FACE_H

/**
 * @brief Représentation d'une face d'un maillage. Ici la face est triangulaire.
 */
class Face
{
public:
    /**
     * @brief Constructeur vide.
     */
    Face();

    /**
     * @brief Construit une face à parir de l'indice des ses 3 sommets.
     */
    Face(int v0, int v1, int v2);

    /**
     * @brief Liste des indices des 3 sommets.
     */
    int v[3];
};

/**
 * @brief Opérateur de comparaison d'égalité.
 */
bool operator== (const Face& f1, const Face& f2);

#endif // FACE_H
