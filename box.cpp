#include "box.h"

Box2::Box2() { }

Box2::Box2(Point2 bl, Point2 tr) : bl(bl), tr(tr) { }

Box2::Box2(const Box2& b) : bl(b.bl), tr(b.tr) { }
