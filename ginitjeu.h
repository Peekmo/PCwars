#ifndef GINITJEU_H
#define GINITJEU_H
/**
 * \file          ginitjeu.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre d'initialisation du jeu
 */
#include <QWidget>
#include <vector>
#include <QLineEdit>
#include "options.h"
#include "general.h"

class gInitJeu : public QWidget
{
private:
    std::vector<Menu*>* sonInitJeu;
    std::vector<General*>* sesGeneraux;

public:
    /**
      * \brief      Constructeur de la fenêtre d'initialisation du jeu
      * \param parent
      */
    gInitJeu(QWidget*);

    /**
      * \brief       Methode de choix du general
      * \details Cette methode permet au joueur de changer de general
      * \param modification Le general change si ce paramètre a pour valeur "true"
      */
    void setGeneral(bool);

    /**
      * \brief      Accesseur sur l'attribut sonInitJeu
      * \return Retourne la valeur de l'attribut sonInitJeu
      */
    std::vector<Menu*>* getInitJeu();

    /**
      * \brief      Accesseur sur l'attribut sesGeneraux
      * \return Retourne la valeur de l'attribut sesGeneraux
      */
    std::vector<General*>* getGeneraux();
};

#endif // GINITJEU_H
