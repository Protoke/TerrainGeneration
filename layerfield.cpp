#include "layerfield.h"
#include <math.h>

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

    // TODO : gerer les cases en bordures pour l'erosion

    // pour chaque case de la grille sauf les bords
    for(int i = 1;i < m_bedrock.nx - 1;i++) {
        for(int j = 1; j < m_bedrock.ny - 1;j++) {

            // stress = k * delta_h;
            // delta_h = moyenne des 4 variations de hauteurs
            // en verifiant que le voisin n'est pas plus grand
            // (on prend le max entre 0 et la difference de hauteur avec le voisin)
            double delta_h = ( max(m_bedrock.value(i,j) - height(i, j+1), 0.0) +
                               max(m_bedrock.value(i,j) - height(i, j-1), 0.0) +
                               max(m_bedrock.value(i,j) - height(i+1 , j), 0.0) +
                               max(m_bedrock.value(i,j) - height(i-1, j), 0.0 ) )
                              / 4.0 ;
            // on verifie que la moyennes des differences de hauteurs est superieure > seuil
            if(delta_h > erosion_threshold) {
                // quantite de bedrock a transformer en sable
                double stress = k * (delta_h - erosion_threshold);
                m_bedrock.setValue(i, j, m_bedrock.value(i,j) - stress);
                addSand(i, j, stress);
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
    if(h <= 0.0) {
        throw std::invalid_argument("impossible to add a negative or null value of sand");
    }
    if(i >= 0 && i < m_sand.nx && j >= 0 && j < m_sand.ny) {
        throw std::invalid_argument("invalid cell coordinates");
    }
    m_sand.setValue(i, j, m_sand.value(i, j) + h);
}

void LayerField::stabilize(const float percentage_landslide) {
    // TODO : CONTINUE

    float stabilization_angle = tan(45.0);

    // parcours du terrain
    for(int i = 0;i < m_sand.nx;i++) {
        for(int j = 0;j < m_sand.ny;j++) {

            int nb_landslides = 0;
            QVector<Vec2> landslides_destinations;
            float delta = m_sand.cellSize().x; // largeur d'une case
            // pour chaque voisin en 8-connexite
            Vec2* neighbours = m_sand.neighbours8(i, j);
            for(int k = 0;k < 8;k++) {
                // stabilite = abs( h voisin - h actuel) / delta
                Vec2 n = neighbours[k];
                float stabilization = abs(height(i, j) - height(n.x, n.y));
                if(k <= 3) {
                    // division par delta
                    stabilization /= delta;
                }else {
                    // division par 2 * racine(delta)
                    stabilization /= 2.0f * sqrt(delta);
                }
                // landslide or not ?
                if(stabilization > stabilization_angle) {
                    nb_landslides++;
                    landslides_destinations.push_back(n);
                }
            }
            // do landslides
            // compute percentage of sand who falls
            float landslide_quantity = percentage_landslide * m_sand.value(i, j) / 100.0f;
            // delete sand of the current vertex
            addSand(i, j, - landslide_quantity);
            // add sand on the neighbours
            for(Vec2 v : landslides_destinations) {
                addSand(landslide_quantity / (float)nb_landslides);
            }
        }
    }
}
