#include "heightfield.h"

#include <iostream>

const Vec3 HeightField::ray[9]= {
    Vec3(0.0, 0.0, 0.5),
    Vec3(0.0, 1.0, 0.5),
    Vec3(0.0, -1.0, 0.5),
    Vec3(1.0, 0.0, 0.5),
    Vec3(-1.0, 0.0, 0.5),
    Vec3(1.0, 1.0, 0.5),
    Vec3(1.0, -1.0, 0.5),
    Vec3(-1.0, 1.0, 0.5),
    Vec3(-1.0, -1.0, 0.5)
};

double lambda;

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

bool HeightField::inside(const Vec3 &p) const {
    return p.z < value(p.x, p.y);
}

Vec3 HeightField::normal(int i, int j) const {
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

Vec3 HeightField::normal(double x, double y) const {
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

bool HeightField::intersect(Ray& r, double& t, double range) const{
    double d = 0.0;
    Vec3 p = r(d);

    while(isInsideDomain(p.x, p.y) && d < range){
        if(p.z <= value(p.x, p.y)){
            t = d;
            return true;
        }

        double step = (p.z - r.origin.z) / lambda;

        d += max(step, 0.1);
        p = r(d);
    }

    return false;
}

ScalarField HeightField::drainingArea() const {
    // Init de la lsite des points dans l'ordre du plus bas au plus haut
    QVector<Vec3> points = listOfPoints();
    std::sort(points.begin(), points.end());

    // Init du SF résultat à 1 partout
    ScalarField sf(Box2(bl, tr), nx, ny);
    sf.add(1.0);

    // Traitement des points par ordre de hauteur décroissante
    for(int i = points.size() - 1; i >= 0; --i){
        Vec3 point = points[i];

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

        double toDispatch = sf.value(int(point.x), int(point.y));

        // Dispatch sur les voisins avec une fraction dépendant de la pente
        // (ou hauteur)
//        for(int k = 0; k < n; ++k){
//            sf.add(q[k].x, q[k].y, toDispatch * s[k] / totalSlope);
//        }

        // Dispatch sur le voisin de plus grande pente (ou hauteur)
        double maxSlope = 0;
        int maxPoint;
        for(int k = 0; k < n; ++k){
            if(s[k] <= maxSlope){
                maxSlope = s[k];
                maxPoint = k;
            }
        }
        sf.add(int(q[maxPoint].x), int(q[maxPoint].y), toDispatch);
    }

    return sf;
}

Vec2Field HeightField::slope() const {
    return gradient();
}

ScalarField HeightField::streamPower() const {
    ScalarField A = drainingArea();
    ScalarField s = slope().length();

    ScalarField sf(Box2(bl, tr), nx, ny);

    for(int i = 0; i < nx; ++i)
    for(int j = 0; j < ny; ++j){
        sf.setValue(i, j, qSqrt(A.value(i, j)) * qFabs(s.value(i, j)));
    }

    return sf;
}

double HeightField::access(Vec2 _p, double range) const {
    Vec3 p = point(_p.x, _p.y);
    p.z += 0.1; // décalage pour éviter l'auto-intersection

    int n = 9; // nb de rayons

    int value = 0;
    for(int i = 0; i < n; i++){
        Ray r(p, ray[i]);
        double t;
        if(!intersect(r, t, range))
            value++;
    }

//    std::cout << "Point " << p << " done." << std::endl;

    return (double)value / (double)n;
}

ScalarField HeightField::access(double range) const {
    ScalarField sf(Box2(bl, tr), nx, ny);

    double stepX = (tr.x - bl.x) / (nx-1);
    double stepY = (tr.y - bl.y) / (ny-1);

    lambda = gradientNorm().range().y; // max de la dérivée

    for(int i = 0; i < nx; ++i)
    for(int j = 0; j < ny; ++j){
        Vec2 pos((double)i * stepX,
                 (double)j * stepY);
        sf.setValue(i, j, access(pos, range));
    }

    return sf;
}

ScalarField HeightField::wetnessIndex() const {
    ScalarField A = drainingArea();
    ScalarField s = slope().length();

    ScalarField sf(Box2(bl, tr), nx, ny);

    for(int i = 0; i < nx; ++i)
    for(int j = 0; j < ny; ++j){
        sf.setValue(i, j, qLn(A.value(i, j) / (1.0 + qFabs(s.value(i, j)))));
    }

    return sf;
}

int HeightField::checkFlowDirections(const Vec3& p, Vec3* dumpPoints,
                                     double* dumpHeight, double* dumpSlope) const
{
    int n = 0;
    Vec2 a = Vec2(p);

    // Parcours de tous les voisins
    for(int i = 0; i < 8; ++i){
        Vec2 b = a + next[i];

        // Vérification de non débordement avant de récupérer le voisin
        if(!isInsideDomain(int(b.x), int(b.y)))
            continue;

        Vec3 q(b.x, b.y, value(int(b.x), int(b.y)));
        double diff = q.z - p.z;

        // Vérification d'une pente descendante
        if(diff < 0.0){
            dumpPoints[n] = q;
            dumpHeight[n] = diff;
            dumpSlope[n] = diff / length[i];
            n++;
        }
    }

    return n;
}

Mesh HeightField::createMesh(int stepi, int stepj) const {
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
