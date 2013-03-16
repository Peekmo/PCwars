#ifndef BATIMENT_H
#define BATIMENT_H
/**
 * \file          batiment.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres des batiments
 */
#include "case.h"

class Batiment : public Case
{
private:
    TypeBatiment sonTypeBatiment;
    int sesPointsCapture;
    int sonArgentBatiments;
    int sonJoueur;

	QLabel *sonJoueurAffichage;

    // Attribut pour savoir a quel joueur appartient un batiment lors de l'initialisation
    static int joueurActuel;

public:
    /**
      * \brief      Constructeur du Batiment
      * \param  unePosX Position du batiment en abcisse sur la carte
      * \param  unePosY Position du batiment en ordonnee sur la carte
      * \param  unTypeBatiment Type du batiment (qg, base, ville, port)
      * \param  unArgent Quantite d'argent qu'offre le batiment, selon les options de jeu choisies
      */
    Batiment(int, int, TypeBatiment, int);

    /**
      * \brief      Accesseur sur l'attribut sonJoueur
      * \return Retourne la valeur de l'attribut sonJoueur
      */
    int getJoueur();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonJoueur
      * \details    Il y a deux joueurs, les valeurs possibles seront donc 1 ou 2
      * \param  unJoueur Nouvelle valeur de l'attribut sonJoueur
      */
    void setJoueur(int);

    /**
      * \brief      Accesseur sur l'attribut sesPointsCapture
      * \return Retourne la valeur de l'attribut sesPointsCapture
      */
    int getPointsCapture();

    /**
      * \brief      Modificateur de la valeur de l'attribut sesPointsCapture
      * \param newPts Nouvelle valeur de l'attribut sesPointsCapture
      */
    void setPointsCapture(int);

    /**
      * \brief      Accesseur sur l'attribut sonUnite
      * \return Retourne la valeur de l'attribut sonUnite
      */
    Unite* getUnite();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonUnite
      * \param  uneUnite Nouvelle valeur de l'attribut sonUnite
      */
    void setUnite(Unite *);

    /**
      * \brief        Accesseur sur l'attribut sonVisuel (de la classe parent Case)
      * \return Retourne la valeur de l'attribut sonVisuel
      */
    char getVisuel();

};

#endif // BATIMENT_H
