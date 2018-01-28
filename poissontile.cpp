#include "poissontile.h"

#include "mathutilities.h"

PoissonTile::PoissonTile() { }

PoissonTile::PoissonTile(const Vec2& bl, const Vec2& tr, double radius) :
    Box2(bl, tr)
{
    populate(radius);
}

void PoissonTile::populate(double radius){
    randSeed();
    m_pos.clear();

    /* Des tests avec différentes valeurs ont étés réalisés pour trouver
     * cette "relation". Elle permet d'avoir un bon remplissage de la tuile
     * sans trop forcer sur la boucle.
     */
    int failuresBeforeGivingUp = (tr.x - bl.x) * (tr.y - bl.y) / radius;

    int nbFailures = 0;
    while(nbFailures < failuresBeforeGivingUp){
        Vec2 pos = randVec2(bl.x, bl.y, tr.x, tr.y);

        if(isPosValid(pos, radius))
            m_pos.push_back(pos);
        else
            nbFailures++;
    }

}

bool PoissonTile::isPosValid(const Vec2& pos, double radius) const{
    Vec2 xOffset = Vec2(tr.x - bl.x, 0.0);
    Vec2 yOffset = Vec2(0.0, tr.y - bl.y);

    for(int i = 0; i < m_pos.size(); ++i){
        Vec2 center = m_pos[i];

        /* On teste sur les disques déja présents dans la tuile, mais aussi
         * dans les tuiles "voisines". Elles correspondent à la tuile
         * translatée dans les 4 (le mieux serait 8) directions voisines.
         * Cela évite que les débordement des cerlces sur les tuiles
         * "voisines" n'entraînent des collisions.
         */
        if(intersectCircles(pos, radius, center, radius) ||
           intersectCircles(pos, radius, center - xOffset, radius) ||
           intersectCircles(pos, radius, center + xOffset, radius) ||
           intersectCircles(pos, radius, center - yOffset, radius) ||
           intersectCircles(pos, radius, center + yOffset, radius))
            return false;
    }
    return true;
}
