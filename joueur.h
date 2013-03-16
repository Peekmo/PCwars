#ifndef JOUEUR_H
#define JOUEUR_H
/**
 * \file          joueur.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres du joueur
 */
#include <QString>

class Joueur
{
private:
	int sonId;
    QString sonNom;
    int sonArgent;

public:
    /**
      * \brief      Constructeur du joueur
      * \param  unId Le numero du joueur (1 ou 2)
      * \param  unNom Nom du joueur
      * \param  unArgent Argent de depart du joueur (defini selon l'attribut sonArgentDepart de la fenetre des options)
      */
    Joueur(int, QString, int);

    /**
      * \brief      Accesseur sur l'attribut sonNom
      * \return Retourne la valeur de l'attribut sonNom
      */
    QString getNom();

    /**
      * \brief      Accesseur sur l'attribut sonArgent
      * \return Retourne la valeur de l'attribut sonArgent
      */
    int getArgent();

    /**
      * \brief      Accesseur sur l'attribut sonId
      * \return Retourne la valeur de l'attribut sonId
      */
	int getId();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonArgent
      * \param  unArgent Nouvelle valeur de l'attribut sonArgent
      */
	void setArgent(int);
};


#endif // JOUEUR_H
