#include "options.h"

Options::Options(bool uneSelection, int unY, QString unNewTexte, QWidget *parent): Menu(uneSelection, unY, unNewTexte, parent)
{
    // Définition des images pour les flèches des côtés
    sesFleches = new QLabel(parent);
    sesFleches->setGeometry(125, sonY, 450, 40);
    sesFleches->setAlignment(Qt::AlignCenter);

    if (saSelection == true)
        sesFleches->setPixmap(QPixmap("images/fleches-true.png"));
    else
        sesFleches->setPixmap(QPixmap("images/fleches-false.png"));
}

void Options::setSelection(bool uneSelection)
{
    Menu::setSelection(uneSelection);

    if (saSelection == true)
        sesFleches->setPixmap(QPixmap("images/fleches-true.png"));
    else
        sesFleches->setPixmap(QPixmap("images/fleches-false.png"));
}
