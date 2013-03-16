#ifndef GMENU_H
#define GMENU_H
/**
 * \file          gmenu.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre du menu principal
 */
#include <QWidget>
#include <vector>
#include <QLineEdit>
#include "menu.h"

class GMenu : public QWidget
{
private:
    std::vector<Menu*> *sonMenu;
public:
    /**
      * \brief      Constructeur de la fenêtre du menu principal
      * \details Il s'agit du menu contenant les boutons "Jouer", "Options", "Quitter"
      * \param parent
      */
    GMenu(QWidget*);

    /**
      * \brief      Accesseur sur l'attribut sonMenu
      * \return Retourne la valeur de l'attribut sonMenu
      */
    std::vector<Menu*>* getMenu();
};

#endif // GMENU_H
