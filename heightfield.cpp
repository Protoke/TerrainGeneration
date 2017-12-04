#include "heightfield.h"

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

Vec3 HeightField::normal(double i, double j){
    Vec3 n = Vec3(0.0,0.0,1.0);

    Vec3 o = point(i,j);
    // creation vector for each direction
    Vec3 r = Vec3(point(i+1.0, j) - o);
    Vec3 t = Vec3(point(i, j+1.0) - o);
    Vec3 tl = Vec3(point(i-1.0, j+1.0) - o);
    Vec3 l = Vec3(point(i-1.0, j) - o);
    Vec3 b = Vec3(point(i, j-1.0) - o);
    Vec3 br = Vec3(point(i+1.0, j-1.0) - o);

    if(i < 0.0 || i > nx-1.0 || j < 0.0 || j > ny-1.0) {
        throw std::invalid_argument("normal not in terrain");
    }

    if(i > 0.0 && i < nx-1.0 && j > 0.0 && j < ny-1.0) {
        // case inside terrain
        n = cross(r, t) + cross(t, tl) + cross(tl, l) + cross(l, b) +
            cross(b, br) + cross(br, r);

    }else if(i == 0.0 && j > 0.0 && j < ny-1.0) {
        // case left border
        n = cross(b, br) + cross(br, r) + cross(r, t);

    }else if(i == nx-1.0 && j > 0.0 && j < ny-1.0) {
        // case right border
        n = cross(t, tl) + cross(tl, l) + cross(l, b);

    }else if(i > 0.0 && i < nx-1.0 && j == 0.0) {
        // case bottom border
        n = cross(r,t) + cross(t, tl) + cross(tl, l);

    }else if(i > 0.0 && i < nx-1.0 && j == ny-1.0) {
        // case top border
        n = cross(l, b) + cross(b, br) + cross(br, r);

    }else if(i == 0.0 && j == 0.0) {
        // case bottom left corner
        n = cross(r, t);

    }else if(i == 0.0 && j == ny-1.0) {
        // case top left corner
        n = cross(b, br) + cross(br, r);

    }else if(i == nx-1.0 && j == 0.0) {
        // case bottom right corner
        n = cross(t, tl) + cross(tl, l);

    }else if(i == nx-1.0 && j == ny-1.0) {
        // case top right corner
        n = cross(l, b);
    }

    return normalize(n);
}
