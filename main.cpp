#include "app.h"
#include <QtWidgets/QApplication>

#include "analyticheightfield.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[])
{
//	QApplication a(argc, argv);
//	App w;
//	w.show();
//    a.exec();

    QVector<double> offsets = {0.1, 0.2, 0.9, 1.5};
    AnalyticHeightField ahf(&noiseSin, 100, 0.01, offsets, 4);

    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            cout << i << " " << j << " : " << ahf.height(Vec2(i, j)) << endl;
        }
    }


    return 0;
}
