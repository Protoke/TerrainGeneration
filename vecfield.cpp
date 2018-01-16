#include "vecfield.h"

VecField::VecField() { }

VecField::VecField(const Box2 &b, int nx, int ny) :
    Array2(b.bl, b.tr, nx, ny)
{ }

Vec2Field::Vec2Field() { }

Vec2Field::Vec2Field(const Box2 &b, int nx, int ny) :
    VecField(b, nx, ny)
{
    m_v.resize((nx) * (ny));
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            m_v[index(i,j)] = Vec2();
        }
    }
}

void Vec2Field::setValue(int i, int j, const Vec2& v) {
    m_v[index(i,j)] = v;
}

Vec2 Vec2Field::value(int i, int j) const {
    return m_v[index(i,j)];
}

void Vec2Field::display() const {
    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            std::cout << value(i, j) << " ";
        }
        std::cout << endl;
    }
}

ScalarField Vec2Field::length() const {
    ScalarField sf(Box2(bl, tr), nx, ny);

    for(int i = 0; i < nx; ++i){
        for(int j = 0; j < ny; ++j){
            sf.setValue(i, j, value(i, j).length());
        }
    }

    return sf;
}
