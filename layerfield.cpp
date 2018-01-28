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
 */
void LayerField::stabilize(const float percentage_landslide) {
    // TODO : CONTINUE
    // liste de points dans l'ordre de hauteur decroissante
    // utilisation de checkFlowDirection

    float stabilization_angle = tan(45.0);

    // parcours du terrain
    for(int i = 0;i < m_sand.nx;i++) {
        for(int j = 0;j < m_sand.ny;j++) {

            int nb_landslides = 0;
            QVector<Vec2> landslides_destinations;
            // pour chaque voisin en 8-connexite
            Vec2 current = Vec2(i, j);
            for(int k = 0;k < 8;k++){
                // stabilite = abs( h voisin - h actuel) / delta
                // recuperation voisin
                Vec2 n = current + m_sand.next[k];
                // verification de non debordement
                if(!m_sand.isInsideDomain((int)n.x, (int)n.y))
                    continue;

                // calcul de stabilite
                float stabilization = abs(height(i, j) - height(n.x, n.y));
                // divise par delta ou 2*sqrt(delta) selon la position du voisin
                stabilization /= m_sand.length[k];

                // landslide or not ?
                if(stabilization > stabilization_angle) {
                    nb_landslides++;
                    landslides_destinations.push_back(n);
                }
            }

            // do landslides
            if(landslides_destinations.size() > 0) {
                // compute percentage of sand who falls
                float landslide_quantity = percentage_landslide * m_sand.value(i, j);
                // delete sand of the current vertex
                addSand(- landslide_quantity, i, j);
                // add sand on the neighbours
                for(Vec2 v : landslides_destinations) {
                    addSand(landslide_quantity / (float)nb_landslides, v.x, v.y);
                }
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
    int n = 0;
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
            dumpPoints[n] = q;
            dumpSlope[n] = diff / m_sand.length[i];
            n++;
        }
    }

    return n;
}
