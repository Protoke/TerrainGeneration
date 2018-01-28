#ifndef TREEFIELD_H
#define TREEFIELD_H

#include <QVector>

#include "array.h"
#include "layerfield.h"

class TreeField : public Array2
{
public:
    TreeField();
    TreeField(const Box2& b, int nx, int ny);

    void initTrees(const LayerField& lf, const Vec2& origin,
                   const Box2& tileBox, double treeRadius);

    void toImage(QImage& image, double resolutionFactor = 1.0) const;

    QVector<Vec3> m_pos;
};

#endif // TREEFIELD_H
