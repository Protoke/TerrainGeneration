#ifndef TREEFIELD_H
#define TREEFIELD_H

#include <QVector>

#include "tree.h"
#include "scalarfield.h"
#include "layerfield.h"

class TreeField
{
public:
    TreeField();
    TreeField(const LayerField& lf);

    void initSapinDensity(const LayerField& lf);

    QVector<Vec2> spawnTrees(const Vec2& origin, const Box2& tileBox,
                             double treeRadius);

    void toImage(QImage& image, const QVector<Vec2>& posTree,
                        double resolutionFactor = 1.0) const;

    ScalarField m_sapinDensity;

protected:
    ScalarField initTreeDensity(const LayerField& lf, Tree* t);
};

#endif // TREEFIELD_H
