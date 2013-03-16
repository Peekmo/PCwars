#include "gmenu.h"

GMenu::GMenu(QWidget *parent)
{
    // Définition du fond
    QLabel *sonFondAffiche = new QLabel(this);
    sonFondAffiche->setPixmap(QPixmap("images/titre.jpg"));
    sonFondAffiche->setGeometry(0,0,700,500);

    // On crée les menus
    sonMenu = new std::vector<Menu*>();

    this->setParent(parent);

    sonMenu->push_back(new Menu(true, 150, "Jouer", this));
    sonMenu->push_back(new Menu(false, 250, "Options", this));
    sonMenu->push_back(new Menu(false, 350, "Quitter", this));

    std::vector<Menu*>::iterator it;

    // On place les menus
    for (it = sonMenu->begin(); it != sonMenu->end(); it++)
    {
        (*it)->setGeometry(200,(*it)->getY(), 300, 40);
    }
}

std::vector<Menu*>* GMenu::getMenu()
{
    return sonMenu;
}

