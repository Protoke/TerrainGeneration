#include "scalarfield.h"

#include <stdexcept> 
#include <QRgb>
#include <QColor>

ScalarField::ScalarField() { }

ScalarField::ScalarField(const Box2& b, int nx, int ny) :
    Array2(b.bl, b.tr, nx, ny)
{
    m_h.resize((nx) * (ny));
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_h[index(i,j)] = 0.0;
        }
    }
}

void ScalarField::load(const QImage& image,
                       const Vec2& bl, const Vec2& tr,
                       double zMin, double zMax)
{
    this->bl = bl;
    this->tr = tr;
    nx = image.width();
    ny = image.height();
    m_h.resize((nx) * (ny));

    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_h[index(i,j)] = (float)qRed(image.pixel(i, ny - 1 -j)) * (zMax - zMin) / 255.0
                    + zMin;
        }
    }
}

void ScalarField::toImage(QImage& image, bool useColor) const {
    Vec2 zMinMax = range();
    double zmin = zMinMax.x;
    double zmax = zMinMax.y;

    image = QImage(nx, ny, QImage::Format_RGB32);
    image.fill(QColor(0, 0, 0));

    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            QRgb color;
            if(useColor){
                double u = 2 * (m_h[index(i,j)] - zmin) / (zmax - zmin);
                double down = min(1.0, 2.0 - u);
                double up = min(1.0, u);
                color = qRgb(down * 255, up * 255, 0.0);
            }
            else{
                int gray = (m_h[index(i,j)] - zmin) * 255 / (zmax - zmin);
                color = qRgb(gray, gray, gray);
            }

            image.setPixel(i, ny - 1 - j, color);
        }
    }
}

Vec3 ScalarField::point(int i, int j) const {
    return Vec3(bl.x + (tr.x-bl.x) * i / (nx - 1),
                bl.y + (tr.y-bl.y) * j / (ny - 1),
                value(i, j));
}

Vec3 ScalarField::point(double x, double y) const {
    return Vec3(x, y, value(x, y));
}

Vec2 ScalarField::point2(int i, int j) const {
    Vec3 p = point(i, j);
    return Vec2(p.x, p.y);
}

QVector<Vec3> ScalarField::listOfPoints() const {
    QVector<Vec3> points(nx * ny);

    for(int i = 0; i < nx-1; ++i){
        for(int j = 0; j < ny-1; ++j){
            points[index(i, j)] = Vec3(i, j, value(i, j));
        }
    }

    return points;
}

Vec2 ScalarField::range() const {
    float zmin = m_h[0], zmax = m_h[0];
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            float value = m_h[index(i,j)];
            if(zmax < value)
                zmax = value;
            if(zmin > value)
                zmin = value;
        }
    }

    return Vec2(zmin, zmax);
}

void ScalarField::add(double v){
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            add(i, j, v);
        }
    }
}

void ScalarField::add(int i, int j, double v){
    m_h[index(i,j)] += v;
}

void ScalarField::setValue(int i, int j, double v) {
    m_h[index(i,j)] = v;
}

double ScalarField::value(int i, int j) const {
    return m_h[index(i,j)];
}

double ScalarField::value(double x, double y,
                           interpolationType interpolation) const
{
    switch(interpolation){
    case INTERPOL_TRIANGULAR : return triangularInterpol(x, y);
    case INTERPOL_BILINEAR : return bilinearInterpol(x, y);
    case INTERPOL_BICUBIC : return bicubicInterpol(x, y);
    default : throw std::invalid_argument("Bad interpolation");
    }
}

double ScalarField::triangularInterpol(double x, double y) const {
    double ncx = nx - 1;
    double ncy = ny - 1;

    // Local coordinates
    Vec2 pLocal = localCoordinates(x, y);

    // Cell coordinates
    int cellX = pLocal.x * ncx;
    int cellY = pLocal.y * ncy;
    if(cellX == ncx)
        cellX -= 1;
    if(cellY == ncy)
        cellY -= 1;

    // In-cell coordinates
    Vec2 pCell = Vec2(pLocal.x * ncx - (double)cellX,
                      pLocal.y * ncy - (double)cellY);

    if (pCell.x + pCell.y < 1.0) {
        return (1.0 - pCell.x - pCell.y) * value(cellX, cellY)
               + pCell.x * value(cellX+1, cellY)
               + pCell.y * value(cellX, cellY+1);
    }
    //else
    return (pCell.x + pCell.y - 1.0) * value(cellX+1, cellY+1)
           + (1.0 - pCell.x) * value(cellX, cellY+1)
           + (1.0 - pCell.y) * value(cellX+1, cellY);
}

double ScalarField::bilinearInterpol(double x, double y) const {
    double ncx = nx - 1;
    double ncy = ny - 1;

    // Local coordinates
    Vec2 pLocal = localCoordinates(x, y);

    // Cell coordinates
    int cellX = pLocal.x * ncx;
    int cellY = pLocal.y * ncy;
    if(cellX == ncx)
        cellX -= 1;
    if(cellY == ncy)
        cellY -= 1;

    // In-cell coordinates
    Vec2 pCell = Vec2(pLocal.x * ncx - (double)cellX,
                      pLocal.y * ncy - (double)cellY);

    return (1.0 - pCell.x) * (1-0 * pCell.y) * value(cellX, cellY) +
            pCell.x * (1.0 - pCell.y) * value(cellX + 1, cellY) +
            (1.0 - pCell.x) * pCell.y * value(cellX, cellY + 1) +
            pCell.x * pCell.y * value(cellX + 1, cellY + 1);
}

double ScalarField::bicubicInterpol(double x, double y) const {
	throw std::logic_error("Not implemented");
    return 0.0;
}

Vec2 ScalarField::gradient(int i, int j) const {
    Vec3 p = Vec3(i, j, value(i, j));
    Vec2 grad;

    // Parcours de tous les voisins
    for(int i = 0; i < 8; ++i){

        Vec2 b = Vec2(p) + next[i];

        // Vérification de non débordement avant de récupérer le voisin
        if(!isInsideDomain(int(b.x), int(b.y)))
            continue;

        // Calcul de la pente
        Vec3 q(b.x, b.y, value(int(b.x), int(b.y)));
        double diff = q.z - p.z;
        grad = grad + normalize(next[i]) * diff / length[i];
    }

    return grad;
}

Vec2Field ScalarField::gradient() const {
    Vec2Field vf(Box2(bl, tr), nx, ny);

    for(int i = 0; i < nx; ++i)
    for(int j = 0; j < ny; ++j){
        Vec2 grad = gradient(i, j);
        vf.setValue(i, j, grad);
    }

    return vf;
}

ScalarField ScalarField::gradientNorm() const {
    ScalarField sf(Box2(bl, tr), nx, ny);

    Vec2Field vf;
    vf = gradient();

    for(int i = 0; i < nx; ++i)
    for(int j = 0; j < ny; ++j){
        Vec2 grad = vf.value(i, j);
        sf.setValue(i, j, grad.length());
    }

    return sf;
}

void ScalarField::display() const {
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            std::cout << value(i, j) << " ";
        }
        std::cout << endl;
    }
}
