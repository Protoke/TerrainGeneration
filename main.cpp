#include "app.h"
#include <QtWidgets/QApplication>

#include <QImage>
#include <iostream>

#include "analyticscalarfield.h"
#include "heightfield.h"
#include "mesh.h"
#include "iostream"
#include "poissontile.h"
#include "layerfield.h"
#include "treefield.h"

using namespace std;

void testTree() {
//    QImage terrain("../TerrainGeneration/Resources/test.png");
    LayerField lf;
    lf.load(terrain, Vec2(0, 0), Vec2(100, 100), 0, 3000);

    QImage tree;
    TreeField tf(lf);
    tf.m_sapinDensity.toImage(tree);
    tree.save("../treeDensity.jpg");

    Vec2 origin(0, 0);
    Box2 tileBox(Vec2(0, 0), Vec2(10, 10));
    QVector<Vec2> sapins = tf.spawnTrees(origin, tileBox, 2.0);
    tf.toImage(tree, sapins, 20.0);
    tree.save("../treePositions.jpg");
}

void testLayerField(){
    // TEST LAYERFIELD
    QImage imageBR("../TerrainGeneration/Resources/test3.png");
    LayerField lf;
    lf.load(imageBR, Vec2(0,0), Vec2(100,100), 0, 100);

    cout << "BEDROCK BASE" << endl;
    lf.bedrock().display();
    cout << endl;

    lf.thermal(1.0, 0.0);

    cout << "BEDROCK AFTER THERMAL" << endl;
    lf.bedrock().display();
    cout << endl;

    cout << "SAND AFTER THERMAL" << endl;
    lf.sand().display();
    cout << endl;

    QImage terrainAfterThermal;
    lf.toHeightField().toImage(terrainAfterThermal);
    terrainAfterThermal.save("../terrainAfterThermal.jpg");

    lf.stabilize(0.5, 1);

    cout << "SAND AFTER STABILIZE" << endl;
    lf.sand().display();

    QImage terrainAfterStabilize;
    lf.toHeightField().toImage(terrainAfterStabilize);
    terrainAfterStabilize.save("../terrainAfterStabilize1.jpg");

    lf.stabilize(0.5, 1);

    lf.toHeightField().toImage(terrainAfterStabilize);
    terrainAfterStabilize.save("../terrainAfterStabilize2.jpg");

    lf.stabilize(0.5, 1);

    lf.toHeightField().toImage(terrainAfterStabilize);
    terrainAfterStabilize.save("../terrainAfterStabilize3.jpg");
}

void testPoisson(){
    PoissonTile pt(Vec2(0, 0), Vec2(20, 20), 2);
    cout << "Nb points : " << pt.m_pos.size() << endl;
    for(int i = 0; i < pt.m_pos.size(); ++i){
        cout << "Point : " << pt.m_pos[i] << endl;
    }
}

void testInterpolationHauteur(){
    // Terrain depuis heightmap
//    QImage i("../TerrainGeneration/Resources/circuit.png");
    QImage i("../TerrainGeneration/Resources/test3.png");
    HeightField hf;
    hf.load(i, Vec2(0, 0), Vec2(100, 100), 0, 100);

    ScalarField height(Box2(hf.bl, hf.tr), hf.nx, hf.ny);
    for(int i = 0; i < height.nx; ++i)
    for(int j = 0; j < height.ny; ++j){
        Vec2 pos((double)i * (height.tr.x - height.bl.x) / (height.nx-1),
                 (double)j * (height.tr.y - height.bl.y) / (height.ny-1));
        height.setValue(i, j, hf.value(pos.x, pos.y));
    }
    QImage image;
    height.toImage(image);

    image.save("../heightIterpolation.jpg");
    std::cout << "----- Original -----" << std::endl;
    hf.display();
    std::cout << "----- Interpol -----" << std::endl;
    height.display();
}

void testIndicateursTerrain(){
    // Terrain random
    QVector<double> offsets = {1, 10, 100, 1000};
    AnalyticScalarField asf(new SimplexNoise(), 1, 0.1, offsets, 10);
    HeightField hf(asf, Box2(Vec2(0, 0), Vec2(50, 50)), 200, 200);

    // Terrain depuis heightmap
//    QImage i("../TerrainGeneration/Resources/circuit.png");
//    QImage i("../TerrainGeneration/Resources/test3.png");
//    HeightField hf;
//    hf.load(i, Vec2(0, 0), Vec2(100, 100), 0, 100);

    Mesh m = hf.createMesh();
    m.saveOBJ("../terrain.obj");
    QImage image;
    hf.toImage(image);
    image.save("../terrain.jpg");
    ScalarField drainingArea = hf.drainingArea();
    drainingArea.toImage(image, true);
    image.save("../drain.jpg");
    ScalarField slope = hf.slope().length();
    slope.toImage(image, true);
    image.save("../slope.jpg");
    ScalarField streamPower = hf.streamPower();
    streamPower.toImage(image, true);
    image.save("../streamPower.jpg");
    ScalarField wetnessIndex = hf.wetnessIndex();
    wetnessIndex.toImage(image, true);
    image.save("../wetnessIndex.jpg");
    ScalarField access = hf.access(250);
    access.toImage(image, true);
    image.save("../access.jpg");
}

void testInterface(int argc, char *argv[]){
        QApplication a(argc, argv);
        App w;
        w.show();
        a.exec();
}

int main(int argc, char *argv[])
{
//    testInterface(argc, argv);
//    testIndicateursTerrain();
//    testInterpolationHauteur();
<<<<<<< HEAD
//    testPoisson();
//    testLayerField();
    testTree();
=======
//  testPoisson();
    testLayerField();
>>>>>>> 0a039e9eb11b37f2be0915e5cbd731a99a44109d

    return 0;
}
