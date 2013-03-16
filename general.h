#ifndef GENERAL_H
#define GENERAL_H
/**
 * \file          general.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres du general
 */
#include <QString>
#include "unite.h"

class General : public Unite
{
private:
    int sonId;
    int saFurie;
	bool saFurieActivee;

public:
    /**
     * \brief       Constructeur du General
     * \param    unNom Nom du general permettant de l'identifier
     * \param    unJoueur Identifiant du joueur a qui appartient le general
     */
    General(QString, int);

    /**
     * \brief       Modificateur de la valeur de l'attribut saFurie
     * \details    Augmente ou remet a zero la furie du general
     * \param    uneFurie Nouvelle valeur de l'attribut saFurie
     */
	void setFurie(int);

    /**
     * \brief       Accesseur sur l'attribut saFurie
     * \return Retourne la valeur de l'attribut saFurie
     */
	int getFurie();

    /**
     * \brief       Methode permettant de savoir si le general est en Furie ou pas
     * \details Le general est en furie si son attribut saFurie est vaut 10
     * \return Retourne la valeur de l'attribut saFurie
     */
	bool getIsFurie();

    /**
     * \brief       Modificateur de la valeur de l'attribut saFurieActivee
     * \param    uneFurieActivee Nouvelle valeur de l'attribut saFurieActivee
     */
	void setFurieActivee(bool);

    /**
     * \brief       Accesseur sur l'attribut saFurieActivee
     * \return Retourne la valeur de l'attribut saFurieActivee
     */
	bool getFurieActivee();
};

#endif // GENERAL_H
