#include "heightfield.h"

#include <iostream>

HeightField::HeightField() { }

HeightField::HeightField(const Box2& b, int nx, int ny) :
    ScalarField(b, nx, ny)
{ }

HeightField::HeightField(const AnalyticScalarField& a, const Box2& b,
                              int nx, int ny) :
    HeightField(b, nx, ny)
{
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_h[index(i,j)] = a.value(point2(i,j));
        }
    }
}

bool HeightField::inside(const Vec3 &p){
    return p.z < value(p.x, p.y);
}

Vec3 HeightField::normal(int i, int j){
    Vec3 n = Vec3(0.0, 0.0, 1.0);
    Vec3 o = point(i,j);
    // creation vector for each direction
    Vec3 r = Vec3(point(i+1, j) - o);
    Vec3 t = Vec3(point(i, j+1) - o);
    Vec3 tl = Vec3(point(i-1, j+1) - o);
    Vec3 l = Vec3(point(i-1, j) - o);
    Vec3 b = Vec3(point(i, j-1) - o);
    Vec3 br = Vec3(point(i+1, j-1) - o);

    if(i < 0 || i > nx-1 || j < 0 || j > ny-1) {
        throw std::invalid_argument("normal not in terrain");
    }

    if(i > 0 && i < nx-1 && j > 0 && j < ny-1) {
        // case inside terrain
        n = cross(r, t) + cross(t, tl) + cross(tl, l) + cross(l, b) +
            cross(b, br) + cross(br, r);

    }else if(i == 0 && j > 0 && j < ny-1) {
        // case left border
        n = cross(b, br) + cross(br, r) + cross(r, t);

    }else if(i == nx-1 && j > 0 && j < ny-1) {
        // case right border
        n = cross(t, tl) + cross(tl, l) + cross(l, b);

    }else if(i > 0 && i < nx-1 && j == 0) {
        // case bottom border
        n = cross(r,t) + cross(t, tl) + cross(tl, l);

    }else if(i > 0 && i < nx-1 && j == ny-1) {
        // case top border
        n = cross(l, b) + cross(b, br) + cross(br, r);

    }else if(i == 0 && j == 0) {
        // case bottom left corner
        n = cross(r, t);

    }else if(i == 0 && j == ny-1) {
        // case top left corner
        n = cross(b, br) + cross(br, r);

    }else if(i == nx-1 && j == 0) {
        // case bottom right corner
        n = cross(t, tl) + cross(tl, l);

    }else if(i == nx-1 && j == ny-1) {
        // case top right corner
        n = cross(l, b);
    }

    return normalize(n);
}

Vec3 HeightField::normal(double x, double y){
    Vec3 n = Vec3(0.0, 0.0, 1.0);

    // normal interpolation

    // Local coordinates
    Vec2 pLocal = localCoordinates(x, y);

    // Cell coordinates
    Vec2 cell = Vec2(int(pLocal.x * nx), int(pLocal.y * ny));
    int cellX = (int) cell.x;
    int cellY = (int) cell.y;

    // In-cell coordinates
    Vec2 pCell = Vec2(pLocal.x - cell.x * (tr.x - bl.x) / nx,
                          pLocal.y - cell.y * (tr.y - bl.y) / ny);

    // in first triangle
    if (pLocal.x + pLocal.y < 1.0) {
        n = (1 - pCell.x - pCell.y) * normal(cellX, cellY)
               + pCell.x * normal(cellX+1, cellY)
               + pCell.y * normal(cellX, cellY+1);
    }
    // else in second triangle
    n = (pCell.x + pCell.y - 1) * normal(cellX+1, cellY+1)
           + (1 - pCell.x) * normal(cellX+1, cellY)
           + (1 - pCell.y) * normal(cellX, cellY+1);

    return normalize(n);
}

ScalarField HeightField::drainingArea(){
    // Init de la lsite des points dans l'ordre du plus bas au plus haut
    QVector<Vec3> points = listOfPoints();
    std::sort(points.begin(), points.end());

    // Init du SF résultat à 1 partout
    ScalarField sf(Box2(bl, tr), nx, ny);
    sf.add(1.0);

    // Traitement des points par ordre de hauteur décroissante
    for(int i = points.size() - 1; i >= 0; --i){
        Vec3 point = points[i];

//        std::cout << "to dispatch : " << point << " ; ";

        Vec3 q[8];
        double h[8];
        double s[8];
        int n = checkFlowDirections(point, q, h, s);
        if(n == 0)
            continue;

        // Calcul de la somme des différences de pente
        // On peut le changer avec la hauteur
        double totalSlope = 0.0;
        for(int k = 0; k < n; ++k){
            totalSlope += s[k];
        }

        // Dispatch sur les voisins avec une fraction dépendant de la pente
        // (ou hauteur)
        double toDispatch = sf.value(int(point.x), int(point.y));
        double maxSlope = 0;
        int maxPoint;
        for(int k = 0; k < n; ++k){
//            sf.add(q[k].x, q[k].y, toDispatch * s[k] / totalSlope);
            if(s[k] > maxSlope){
                maxSlope = s[k];
                maxPoint = k;
            }
        }

//        std::cout << "Point " << q[maxPoint] << " : ";
//        std::cout << "OldValue : " <<
//                     sf.value(int(q[maxPoint].x),
//                              int(q[maxPoint].y)) << "; ";
//        sf.add(int(q[maxPoint].x), int(q[maxPoint].y), toDispatch);
//        std::cout << "NewValue : " <<
//                     sf.value(int(q[maxPoint].x),
//                              int(q[maxPoint].y)) << std::endl;
    }

    return sf;
}

int HeightField::checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                                     double* dumpHeight, double* dumpSlope)
{
    int n = 0;
    Vec2 a = Vec2(p);

    for(int i = 0; i < 8; ++i){
        Vec2 b = a + next[i];
        if(!isInsideDomain(int(b.x), int(b.y)))
            continue;

        Vec3 q(b.x, b.y, value(int(b.x), int(b.y)));
        double diff = q.z - p.z;
        if(diff < 0.0){
            dumpPoints[n] = q;
            dumpHeight[n] = diff;
            dumpSlope[n] = diff / length[i];
            n++;
        }
    }

    return n;
}

Mesh HeightField::createMesh(int stepi, int stepj){
    Mesh m;

    // stockage des points min et max du terrain
    Vec2 zMinMax = range();
    // min
    Vec3 p = point(0,0);
    p.z = zMinMax.x;
    m.setMin(p);
    // max
    p = point(nx-1, ny-1);
    p.z = zMinMax.y;
    m.setMax(p);

    for(int i = 0; i < nx; i+=stepi){
        for(int j = 0; j < ny; j+=stepj){
            m.addVertex(point(i,j));
        }
    }

    int nyReduced = int(ny/stepj);

    for(int i = 0; i < nx-stepi; i+=stepi){
        for(int j = 0; j < ny-stepj; j+=stepj){
            Face fbl, ftr;
            int iReduced = i/stepi;
            int jReduced = j/stepj;

            fbl.v[0] = iReduced * nyReduced + jReduced;
            fbl.v[1] = (iReduced+1) * nyReduced + jReduced;
            fbl.v[2] = iReduced * nyReduced + (jReduced+1);
            ftr.v[0] = (iReduced+1) * nyReduced + jReduced;
            ftr.v[1] = (iReduced+1) * nyReduced + (jReduced+1);
            ftr.v[2] = iReduced * nyReduced + (jReduced+1);

            m.addFace(fbl);
            m.addFace(ftr);
        }
    }

    return m;
}
