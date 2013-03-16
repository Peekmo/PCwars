#ifndef GOPTIONS_H
#define GOPTIONS_H
/**
 * \file          goptions.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre des options
 */
#include <QWidget>
#include <vector>
#include "options.h"

class GOptions : public QWidget
{
private:
    std::vector<Menu*>* sesOptions;
    int sonArgentBatiments;
    int sonNombreTours;
    int sonNombreUnites;
    int sonArgentDepart;

public:
    /**
      * \brief      Constructeur de la fenêtre des options
      * \details Il s'agit de la fenêtre permettant de choisir :
      * \details - La quantite d'argent reçue par les batiments
      * \details - Le nombre de tours maximal
      * \details - Le nombre d'unites maximal
      * \details - La quantite d'argent au depart
      * \details - Ainsi qu'un bouton de retour au menu principal
      * \param  parent
      */
    GOptions(QWidget*);

    /**
      * \brief      Accesseur sur l'attribut sesOptions
      * \return Retourne la valeur de l'attribut sesOptions
      */
    std::vector<Menu*>* getOptions();

    /**
      * \brief      Modificateur de la valeur de l'attribut sesOptions
      * \details Cette methode change les options affichees dans le menu lorsqu'il y a eu modification
      * \param  modification Valeur indiquant ou non s'il y a eu modification sur le menu
      */
    void setOptions(bool);

    /**
      * \brief      Accesseur sur l'attribut sonArgentBatiment
      * \return Retourne la valeur de l'attribut sonArgentBatiment
      */
    int getArgentBatiments();

    /**
      * \brief      Accesseur sur l'attribut sonNombreTours
      * \return Retourne la valeur de l'attribut sonNombreTours
      */
    int getNbTours();

    /**
      * \brief      Accesseur sur l'attribut sonNombreUnites
      * \return Retourne la valeur de l'attribut sonNombreUnites
      */
    int getNbUnites();

    /**
      * \brief      Accesseur sur l'attribut sonArgentDepart
      * \return Retourne la valeur de l'attribut sonArgentDepart
      */
    int getArgentDepart();
};

#endif // GOPTIONS_H
