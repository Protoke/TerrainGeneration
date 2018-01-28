#include "treefield.h"

#include "heightfield.h"
#include "poissontile.h"
#include "tree.h"
#include "mathutilities.h"

TreeField::TreeField() { }

TreeField::TreeField(const Box2 &b, int nx, int ny) :
    Array2(b.bl, b.tr, nx, ny)
{ }

void TreeField::initTrees(const LayerField& lf, const Vec2& origin,
                          const Box2& tileBox, double treeRadius) {
    m_pos.clear();

    HeightField hf = lf.toHeightField();

    ScalarField slope = hf.slope().length();
    ScalarField drainingArea = hf.drainingArea();
    ScalarField streamPower = hf.streamPower();
    ScalarField access = hf.access((hf.tr.x - hf.bl.x) * 2.5);
    ScalarField wetnessIndex = hf.wetnessIndex();

    PoissonTile tile(tileBox.bl, tileBox.tr, treeRadius);
    Sapin sapin;

    Vec2 tilePosition(origin);
    // double boucle de déplacement de la tuile sur x et y
    while(tilePosition.x < hf.tr.x){
        tilePosition.y = origin.y;
        while(tilePosition.y < hf.tr.y){

            // Parcours des positions de la tuile pour essayer de placer les arbres
            for(int i = 0; i < tile.m_pos.size(); ++i){
                Vec2 pos = tile.m_pos[i] + tilePosition;
                if(hf.isInsideDomain(pos.x, pos.y)){
                    // récupération des différents paramètres
                    double dirtValue = lf.m_sand.value(pos.x, pos.y);
                    double heightValue = hf.value(pos.x, pos.y);
                    double slopeValue = slope.value(pos.x, pos.y);
                    double drainValue = drainingArea.value(pos.x, pos.y);
                    double wetnessValue = wetnessIndex.value(pos.x, pos.y);
                    double streamValue = streamPower.value(pos.x, pos.y);
                    double lightValue = access.value(pos.x, pos.y);

                    // tentative de spawn
                    double chanceToSpawn = sapin.chanceToSpawn(dirtValue, heightValue, slopeValue, drainValue,
                                                               wetnessValue, streamValue, lightValue);
                    double proba = randDouble();
                    if(proba <= chanceToSpawn)
                        m_pos.push_back(Vec3(pos, heightValue));
                }
            }

            tilePosition.y += tile.tr.y - tile.bl.y;
        }

        tilePosition.x += tile.tr.x - tile.bl.x;
    }
}

void TreeField::toImage(QImage& image, double resolutionFactor) const {
    image = QImage(nx * resolutionFactor, ny * resolutionFactor,
                   QImage::Format_RGB32);

//    for(int i = 0; i < m_pos.size(); ++i){
//        Vec3 pos = m_pos[i];

//    }


//    for(int i = 0; i < nx; ++i){
//        for(int j = 0; j < ny; ++j){
//            QRgb color;
//            if(useColor){
//                double u = (m_h[index(i,j)] - zmin) / (zmax - zmin);
//                color = qRgb((1.0-u) * 255, 0.0, u * 255);
//            }
//            else{
//                int gray = (m_h[index(i,j)] - zmin) * 255 / (zmax - zmin);
//                color = qRgb(gray, gray, gray);
//            }

//            image.setPixel(i, j, color);
//        }
//    }
}
