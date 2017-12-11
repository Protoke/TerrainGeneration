#include "app.h"
#include <QtWidgets/QApplication>

#include <QImage>

#include "analyticheightfield.h"
#include "heightfield.h"
#include "mesh.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[])
{
//	QApplication a(argc, argv);
//	App w;
//	w.show();
//    a.exec();

    QVector<double> offsets = {0.1, 0.2, 0.9, 1.5};
    AnalyticHeightField ahf(&noiseSin, 10, 0.1, offsets, 4);
    HeightField hf(ahf, Box2(Vec2(-100, -100), Vec2(100, 100)), 2000, 2000);
    Mesh m = hf.createMesh();
    m.saveOBJ("../terrain.obj");
    QImage image;
    hf.toImage(image);
    image.save("../terrain.jpg");

//    for(int i = 0; i < 10; ++i){
//        for(int j = 0; j < 10; ++j){
//            cout << i << " " << j << " : " << ahf.height(Vec2(i, j)) << endl;
//        }
//    }

//    QImage i("../TerrainGeneration/Resources/circuit.png");
//    HeightField hf;
//    hf.load(i, Vec2(0, 0), Vec2(100, 100), 0, 1000);
//    Mesh m = hf.createMesh(8,8);
//    m.saveOBJ("../terrain.obj");

    return 0;
}
