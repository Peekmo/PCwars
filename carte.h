#ifndef CARTE_H
#define CARTE_H
/**
 * \file          carte.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la carte
 */
#include <QGridLayout>
#include "batiment.h"
#include "joueur.h"
#include "general.h"

class Carte : public QGridLayout
{
private:
    std::vector<Case*> *sesCases;
    QString sonNom;
    int saTailleX;
    int saTailleY;
    int nbTours;
    bool enCours;

    Joueur* sonJoueur1;
    Joueur* sonJoueur2;

public:
    /**
      * \brief      Constructeur de la Carte
      * \param  unArgentBatiment Quantite d'argent rapportee par les batiments selon les options de jeu choisies
      */
    Carte(int);

    /**
      * \brief      Destructeur de la Carte
      * \details Lors de la destruction de la carte, toutes les cases qui la composent sont prealablement detruites
      */
    ~Carte();

    /**
      * \brief      Accesseur sur l'attribut sesCases
      * \return Retourne l'ensemble des cases de la carte
      */
	std::vector<Case*>* getCases();

    /**
      * \brief      Methode permettant d'afficher la carte
      */
    void afficher();

    /**
      * \brief      Methode permettant de mettre en place les generaux sur la carte
      * \param general1 General choisi par le joueur 1
      * \param general2 General choisi par le joueur 2
      */
    void setJeu(General*, General*);
};

#endif // CARTE_H
