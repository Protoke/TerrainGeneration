#include "treefield.h"

#include <QColor>

#include "heightfield.h"
#include "poissontile.h"
#include "mathutilities.h"

TreeField::TreeField() { }

TreeField::TreeField(const LayerField &lf)
{
    initSapinDensity(lf);
}

void TreeField::initSapinDensity(const LayerField &lf) {
    Sapin sapin;
    m_sapinDensity = initTreeDensity(lf, &sapin);
}

QVector<Vec2> TreeField::spawnTrees(const Vec2& origin, const Box2& tileBox,
                                    double treeRadius) {
    randSeed();
    QVector<Vec2> posSapin;
    PoissonTile tile(tileBox.bl, tileBox.tr, treeRadius);

    Vec2 tilePosition(origin);
    // double boucle de déplacement de la tuile sur x et y
    while(tilePosition.x < m_sapinDensity.tr.x){
        tilePosition.y = origin.y;
        while(tilePosition.y < m_sapinDensity.tr.y){
            // Parcours des positions de la tuile pour essayer de placer les arbres
            for(int i = 0; i < tile.m_pos.size(); ++i){
                Vec2 pos = tile.m_pos[i] + tilePosition;
                if(m_sapinDensity.isInsideDomain(pos.x, pos.y)){
                    // tentative de spawn
                    double chanceToSpawn = m_sapinDensity.value(pos.x, pos.y);
                    double proba = randDouble();
                    if(proba <= chanceToSpawn)
                        posSapin.push_back(pos);
                }
            }

            tilePosition.y += tile.tr.y - tile.bl.y;
        }

        tilePosition.x += tile.tr.x - tile.bl.x;
    }

    return posSapin;
}

void TreeField::toImage(QImage& image, const QVector<Vec2>& posTree,
                        double resolutionFactor) const {
    double nxRescaled = (double)m_sapinDensity.nx * resolutionFactor;
    double nyRescaled = (double)m_sapinDensity.ny * resolutionFactor;

    image = QImage(nxRescaled, nyRescaled, QImage::Format_RGB32);
    image.fill(QColor(0, 0, 0));

    double xScale = nxRescaled / (m_sapinDensity.tr.x - m_sapinDensity.bl.x);
    double yScale = nyRescaled / (m_sapinDensity.tr.y - m_sapinDensity.bl.y);

    QRgb color = qRgb(255, 255, 255);

    for(int i = 0; i < posTree.size(); ++i){
        Vec2 pos = posTree[i];
        pos.x *= xScale;
        pos.y *= yScale;

        image.setPixel(pos.x, nyRescaled - 1 - pos.y, color);
    }
}

ScalarField TreeField::initTreeDensity(const LayerField& lf, Tree* t){
    ScalarField sf(Box2(lf.bedrock().bl, lf.bedrock().tr),
                   lf.bedrock().nx, lf.bedrock().ny);

    HeightField hf = lf.toHeightField();
    ScalarField slope = hf.slope().length();
    ScalarField streamPower = hf.streamPower();
    ScalarField access = hf.access((hf.tr.x - hf.bl.x) * 2.5);
    ScalarField wetnessIndex = hf.wetnessIndex();

    for(int i = 0; i < sf.nx; ++i)
    for(int j = 0; j < sf.ny; ++j){
        // récupération des différents paramètres
        double dirtValue = lf.sand().value((int)i, (int)j);
        double heightValue = hf.value((int)i, (int)j);
        double slopeValue = slope.value((int)i, (int)j);
        double wetnessValue = wetnessIndex.value((int)i, (int)j);
        double streamValue = streamPower.value((int)i, (int)j);
        double lightValue = access.value((int)i, (int)j);

        double density = t->chanceToSpawn(dirtValue, heightValue, slopeValue,
                                         wetnessValue, streamValue, lightValue);
        sf.setValue(i, j, density);
    }

    return sf;
}
