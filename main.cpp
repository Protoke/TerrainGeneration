#include "app.h"
#include <QtWidgets/QApplication>

#include <QImage>
#include <QTime>
#include <iostream>

#include "analyticscalarfield.h"
#include "heightfield.h"
#include "mesh.h"
#include "iostream"
#include "poissontile.h"
#include "layerfield.h"
#include "treefield.h"

using namespace std;

void demo(){
    QTime timer;
    int ms;
    QImage display;

    /* Terrain depuis heightmap */
    cout << "Loading terrain from height map." << endl;
    timer.start();
    QImage i("../TerrainGeneration/Resources/circuit.png");
    HeightField hfImage;
    hfImage.load(i, Vec2(0, 0), Vec2(100, 100), 0, 50);
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds." << endl;
    cout << "Generating OBJ." << endl;
    timer.start();
    Mesh m = hfImage.createMesh();
    m.saveOBJ("../terrainHeightMap.obj");
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds" << endl;
    hfImage.toImage(display, true);
    display.save("../terrainHeightMap.jpg");

    /* Terrain random */
    cout << "Generating terrain with noise." << endl;
    timer.start();
    QVector<double> offsets = {1, 42, 157, 427, 893, 1523, 4242, 6666, 9999, 12345};
    AnalyticScalarField asf(new SimplexNoise(), 150, 750, offsets, 10);
    HeightField hf(asf, Box2(Vec2(0, 0), Vec2(1000, 1000)), 500, 500);
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds." << endl;
    hf.toImage(display, true);
    display.save("../terrainRandom.jpg");
    cout << "Generating OBJ." << endl;
    timer.start();
    m = hf.createMesh();
    m.saveOBJ("../terrainRandom.obj");
    ms= timer.elapsed();
    cout << "Done in " << ms << " milliseconds" << endl;

    /* Erosion / Stabilisation */
    cout << "Eroding and stabilising terrain." << endl;
    timer.start();
    LayerField lf(hf);
    lf.addSand(5.0);
    for(int i = 0; i < 10; i++){
        lf.thermal(0.5, 0.0);
        lf.stabilize(0.3, 10);
    }
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds." << endl;
    cout << "Generating OBJ." << endl;
    timer.start();
    hf = lf.toHeightField();
    m = hf.createMesh();
    m.saveOBJ("../terrainErroded.obj");
    timer.elapsed();
    hf.toImage(display, true);
    display.save("../terrainErroded.jpg");
    cout << "Done in " << ms << " milliseconds." << endl;

    /* Descripteurs de terrain */
    cout << "Extracting data from terrain." << endl;
    timer.start();
    ScalarField slope = hf.slope().length();
    ms = timer.elapsed();
    slope.toImage(display, true);
    display.save("../slope.jpg");
    cout << "Slope computed in " << ms << " milliseconds." << endl;
    timer.start();
    ScalarField drainingArea = hf.drainingArea();
    ms = timer.elapsed();
    drainingArea.toImage(display, true);
    display.save("../drain.jpg");
    cout << "Drain area computed in " << ms << " milliseconds." << endl;
    timer.start();
    ScalarField streamPower = hf.streamPower();
    ms = timer.elapsed();
    streamPower.toImage(display, true);
    display.save("../streamPower.jpg");
    cout << "Stream power computed in " << ms << " milliseconds." << endl;
    timer.start();
    ScalarField wetnessIndex = hf.wetnessIndex();
    ms = timer.elapsed();
    wetnessIndex.toImage(display, true);
    display.save("../wetnessIndex.jpg");
    cout << "Wetness index computed in " << ms << " milliseconds." << endl;
    timer.start();
    ScalarField access = hf.access(250);
    ms = timer.elapsed();
    access.toImage(display, true);
    display.save("../access.jpg");
    cout << "Access computed in " << ms << " milliseconds." << endl;

    /* Végétation */
    cout << "Computing tree density." << endl;
    timer.start();
    TreeField tf(lf);
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds" << endl;
    tf.m_sapinDensity.toImage(display, true);
    display.save("../treeDensity.jpg");
    cout << "Computing tree positions." << endl;
    timer.start();
    QVector<Vec2> trees = tf.spawnTrees(Vec2(-5, -5), Box2(Vec2(0, 0), Vec2(15, 15)), 3);
    ms = timer.elapsed();
    cout << "Done in " << ms << " milliseconds" << endl;
    tf.toImage(display, trees, 1);
    display.save("../trees.jpg");

    Sapin sapin;
    ScalarField sfDisplay;
    sfDisplay = sapin.dirtHeightMapResponse(lf.sand());
    sfDisplay.toImage(display, true);
    display.save("../dirtHeightResponse.jpg");
    sfDisplay = sapin.heightMapResponse(hf);
    sfDisplay.toImage(display, true);
    display.save("../heightResponse.jpg");
    sfDisplay = sapin.slopeMapResponse(slope);
    sfDisplay.toImage(display, true);
    display.save("../slopeResponse.jpg");
    sfDisplay = sapin.wetnessMapResponse(wetnessIndex);
    sfDisplay.toImage(display, true);
    display.save("../wetnessResponse.jpg");
    sfDisplay = sapin.streamPowerMapResponse(streamPower);
    sfDisplay.toImage(display, true);
    display.save("../streamPowerResponse.jpg");
    sfDisplay = sapin.lightMapResponse(access);
    sfDisplay.toImage(display, true);
    display.save("../lightResponse.jpg");
}

void testTree() {
    QImage terrain("../TerrainGeneration/Resources/test.png");
    LayerField lf;
    lf.load(terrain, Vec2(0, 0), Vec2(100, 100), 0, 3000);

    QImage tree;
    TreeField tf(lf);
    tf.m_sapinDensity.toImage(tree);
    tree.save("../treeDensity.jpg");

    Vec2 origin(0, 0);
    Box2 tileBox(Vec2(0, 0), Vec2(50, 50));
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
//    testPoisson();
//    testLayerField();
//    testTree();
    demo();

    return 0;
}
