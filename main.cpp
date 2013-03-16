#include <QApplication>
#include "fenetre.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Fenetre *maFenetre = new Fenetre();
    maFenetre->show();

    return app.exec();
}
