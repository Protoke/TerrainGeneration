#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QString>

#include "vec.h"
#include "face.h"

/**
 * @brief Représentation d'un maillage.
 */
class Mesh
{
public:
    /**
     * @brief Initialise le mesh à partir d'un fichier OBJ.
     * @param filename Chemin du fichier OBJ
     * @return true si le chargement est un succès, false sinon
     */
    bool loadOBJ(const QString& filename);

    /**
     * @brief Sauvegarde le mesh dans un fichier OBJ.
     * @param filename Chemin du fichier OBJ
     * @return true si la sauvegarde est un succès, false sinon
     */
    bool saveOBJ(const QString& filename) const;

    /**
     * @brief Retourne l'id du sommet de coordonnées p.
     */
    int getId(const Vec3& p) const;

    /**
     * @brief Retourne l'id de la face f.
     */
    int getId(const Face& f) const;

    /**
     * @brief Retourne les coordonnées du sommet associé à id.
     */
    Vec3 vertex(int id) const;

    /**
     * @brief Retourne les coordonnées du sommet numéro idInFace dans la face idFace.
     */
    Vec3 vertex(int idFace, int idInFace) const;

    /**
     * @brief Retourne la face associé à id.
     */
    Face face(int id) const;

    /**
     * @brief Retourne le nombre de sommets.
     */
    int nbVertices() const;

    /**
     * @brief Retourne le nombre de faces.
     */
    int nbFaces() const;

    /**
     * @brief Ajoute le sommet v au maillage.
     */
    void addVertex(const Vec3& v);

    /**
     * @brief Ajoute la face f au maillage.
     */
    void addFace(const Face& f);

    /**
     * @brief Initialise la borne max du maillage.
     */
    void setMax(Vec3 vertex);

    /**
     * @brief Initialise la borne min du maillage.
     */
    void setMin(Vec3 vertex);

    /**
     * @brief Affiche le maillage avec OpenGL.
     */
    void draw() const;

private:
    QVector<Face> m_faces;
    QVector<Vec3> m_vertices;
    Vec3 m_vMin;
    Vec3 m_vMax;
};

#endif // MESH_H
