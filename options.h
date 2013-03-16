#ifndef OPTIONS_H
#define OPTIONS_H
/**
 * \file          options.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres des options
 */
#include "menu.h"

class Options : public Menu
{
private:
    QLabel *sesFleches;

public:
    /**
      * \brief      Constructeur des options
      * \details Tous les parametres servent a la creation d'un nouveau menu (de la classe parent Menu)
      */
    Options(bool, int, QString, QWidget*);

    /**
      * \brief      Modificateur de la valeur de l'attribut saSelection (de la classe parent Menu)
      * \param  uneSelection Nouvelle valeur de l'attrbitu saSelection
      */
    void setSelection(bool);
};

#endif // OPTIONS_H
