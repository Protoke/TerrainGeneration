#include "app.h"
#include <QtWidgets/QApplication>

#include <QImage>

#include "analyticscalarfield.h"
#include "heightfield.h"
#include "mesh.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    App w;
//    w.show();
//    a.exec();

//    QVector<double> offsets = {1, 10, 100, 1000};
//    AnalyticScalarField asf(new SimplexNoise(), 1, 0.1, offsets, 10);
//    HeightField hf(asf, Box2(Vec2(0, 0), Vec2(20, 20)), 1000, 1000);
//    Mesh m = hf.createMesh();
//    m.saveOBJ("../terrainNoise.obj");
//    QImage image;
//    hf.toImage(image);
//    image.save("../terrainNoise.jpg");

//    for(int i = 0; i < 10; ++i){
//        for(int j = 0; j < 10; ++j){
//            cout << i << " " << j << " : " << ahf.height(Vec2(i, j)) << endl;
//        }
//    }

    QImage i("../TerrainGeneration/Resources/circuit.png");
//    QImage i("../TerrainGeneration/Resources/test3.png");
    HeightField hf;
    hf.load(i, Vec2(0, 0), Vec2(100, 100), 0, 100);
    Mesh m = hf.createMesh();
    m.saveOBJ("../terrain.obj");
    QImage image;
    hf.toImage(image);
    image.save("../terrain.jpg");
    ScalarField drainingArea = hf.drainingArea();
    drainingArea.toImage(image);
    image.save("../drain.jpg");
    ScalarField slope = hf.slope();
    slope.toImage(image);
    image.save("../slope.jpg");

    return 0;
}
