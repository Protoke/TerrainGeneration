#include <math.h>

#include "layerfield.h"
#include "poissontile.h"
#include "tree.h"

void LayerField::load(const QImage& imageBR,
                 const QImage& imageS,
                const Vec2& bl, const Vec2& tr,
                double zMinBR, double zMaxBR,
                double zMinS, double zMaxS) {
    m_bedrock = ScalarField();
    m_bedrock.load(imageBR, bl, tr, zMinBR, zMaxBR);
    m_sand = ScalarField();
    double thickness_S = zMaxS - zMinS;
    m_sand.load(imageS, bl, tr, 0, thickness_S);
}

void LayerField::load (const QImage& imageBR,
                       const Vec2& bl, const Vec2& tr,
                       double zMinBR, double zMaxBR) {
    m_bedrock = ScalarField();
    m_bedrock.load(imageBR, bl, tr, zMinBR, zMaxBR);
    m_sand = ScalarField(Box2(bl, tr), imageBR.width(), imageBR.height());
}

double LayerField::height(int i, int j) const {
    double h_bedrock = m_bedrock.value(i,j);
    double h_sand = m_sand.value(i,j);
    return h_bedrock + h_sand;
}

double LayerField::height(double i, double j) const {
    double h_bedrock = m_bedrock.value(i,j);
    double h_sand = m_sand.value(i,j);
    return h_bedrock + h_sand;
}

void LayerField::thermal(double k, double erosion_threshold) {
    if(k <= 0.0 || erosion_threshold < 0.0) {
        throw std::invalid_argument("bad value for coefficient k or erosion_threshold in thermal function");
    }

    // calcul de delta_h pour chaque case de la grille sauf les bords
    for(int i = 0;i < m_bedrock.nx;i++) {
        for(int j = 0; j < m_bedrock.ny;j++) {

            // stress = k * delta_h;
            // delta_h = moyenne des 4 variations de hauteurs
            // en verifiant que le voisin n'est pas plus grand
            // (on prend le max entre 0 et la difference de hauteur avec le voisin)
            double value = m_bedrock.value(i,j);
            int nb_neighbours = 0;
            double delta_h = 0.0;

            for(int n = 0;n <= 6;n+=2) {
                Vec2 v = Vec2(i, j) + m_bedrock.next[n];
                // Verification de non debordement avant de recuperer le voisin
                if(!m_bedrock.isInsideDomain(int(v.x), int(v.y)))
                    continue;
                delta_h += max( value - height(int(v.x), int(v.y)), 0.0 );
                nb_neighbours++;
            }
            delta_h /= nb_neighbours;

            // on verifie que la moyennes des differences de hauteurs est superieure au seuil
            if(delta_h > erosion_threshold) {
                // quantite de bedrock a transformer en sable
                double stress = k * (delta_h - erosion_threshold);
                m_bedrock.setValue(i, j, m_bedrock.value(i,j) - stress);
                addSand(stress, i, j);
            }
       }
    }
}

void LayerField::addSand(double h) {
    if(h <= 0.0) {
        throw std::invalid_argument("impossible to add a negative or null value of sand");
    }

    for(int i = 0;i < m_sand.nx;i++) {
        for(int j = 0;j < m_sand.ny;j++) {
            m_sand.setValue(i, j, m_sand.value(i, j) + h);
        }
    }
}

void LayerField::addSand(double h, int i, int j) {
   if(i < 0 || i >= m_sand.nx || j < 0 || j >= m_sand.ny) {
        throw std::invalid_argument("invalid cell coordinates");
    }
    m_sand.setValue(i, j, std::max(0.0, m_sand.value(i, j) + h));
}

/**
 * @brief LayerField::stabilize
 * @param percentage_landslide in [0.0, 1.0]
 * @param nb_iterations
 */
void LayerField::stabilize(double percentage_landslide, int nb_iterations) {
    // TODO : CONTINUE
    // liste de points dans l'ordre de hauteur decroissante
    // utilisation de checkFlowDirection

    double stabilization_angle = tan(45.0);

    for(int count = 0;count < nb_iterations;count++) {
        // Init de la liste des points dans l'ordre du plus bas au plus haut
        QVector<Vec3> points = listOfPoints();
        std::sort(points.begin(), points.end());

        // parcours du terrain
        for(int i = points.size() - 1;i >= 0; i--) {
            Vec3 point = points[i];
            Vec3 n_positions[8];    // positions des voisins
            double n_slope[8];      // pente des voisins
            int n = checkStabilizationDirections(point, n_positions, n_slope,
                                                 stabilization_angle);

            // Calcul de la somme des differences de pente
            double totalSlope = 0.0;
            for(int k = 0; k < n; ++k){
                totalSlope += n_slope[k];
            }

            double landscape_quantity = percentage_landslide *
                                        m_sand.value(point.x, point.y);

            // Enleve la quantite de sable du point
            // et dispatche sur les voisins avec une fraction dependante de la pente
            for(int k = 0; k < n; ++k){
                addSand(-landscape_quantity, point.x, point.y);
                addSand(landscape_quantity * n_slope[k] / totalSlope,
                        n_positions[k].x, n_positions[k].y);
            }
        }
    }
}

ScalarField LayerField::bedrock() const {
    return m_bedrock;
}

ScalarField LayerField::sand() const {
    return m_sand;
}

HeightField LayerField::toHeightField() const {
    HeightField hf(Box2(m_bedrock.bl, m_bedrock.tr), m_bedrock.nx, m_bedrock.ny);

    for(int i = 0; i < m_bedrock.nx; ++i)
    for(int j = 0; j < m_bedrock.ny; ++j){
        hf.setValue(i, j, height(i, j));
    }

    return hf;
}

int LayerField::checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                                    double* dumpSlope) const
{
    int n = 0; // nombre de voisins plus bas que p
    Vec2 a = Vec2(p);

    // Parcours de tous les voisins
    for(int i = 0; i < 8; ++i){
        Vec2 b = a + m_sand.next[i];

        // Vérification de non débordement avant de récupérer le voisin
        if(!m_sand.isInsideDomain(int(b.x), int(b.y)))
            continue;

        Vec3 q(b.x, b.y, height(int(b.x), int(b.y)));
        double diff = q.z - p.z;

        // Vérification d'une pente descendante
        if(diff < 0.0){
            dumpPoints[n] = q; // position du voisin
            dumpSlope[n] = diff / m_sand.length[i]; // difference de hauteur du voisin
            n++;
        }
    }

    return n;
}

QVector<Vec3> LayerField::listOfPoints() const {
    QVector<Vec3> points(m_bedrock.nx * m_bedrock.ny);

    for(int i = 0; i < m_bedrock.nx; ++i){
        for(int j = 0; j < m_bedrock.ny; ++j){
            points[m_bedrock.index(i, j)] = Vec3(i, j, height(i, j));
        }
    }

    return points;
}

int LayerField::checkStabilizationDirections(const Vec3& p, Vec3* dumpPoints,
                                             double* dumpSlope,
                                             const double stabilizationAngle) const {

    Vec3 n_positions[8];    // positions des voisins
    double n_slope[8];      // pente des voisins
    // recuperation du nb de voisins plus bas que p avec position et pente
    int n = checkFlowDirections(p, n_positions, n_slope);

    // Parcours de tous les voisins plus bas que p
    int newN = 0;
    for(int i = 0; i < n; ++i){

        // Verification de la stabilite
        if(-n_slope[i] > stabilizationAngle){
            dumpPoints[newN] = n_positions[i]; // position du voisin
            dumpSlope[newN] = n_slope[i];
            newN++;
        }
    }

    return newN;

}
