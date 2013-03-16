#ifndef FENETRE_H
#define FENETRE_H
/**
 * \file          fenetre.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre
 */
#include <QWidget>
#include <QKeyEvent>
#include <QApplication>
#include "gmenu.h"
#include "goptions.h"
#include "ginitjeu.h"
#include "gjeu.h"
#include "gchargement.h"

class Fenetre : public QWidget
{
    Q_OBJECT

private:
    GMenu* menuPrincipal;
    GOptions* optionsPrincipales;
    gInitJeu* initJeu;
    GChargement* chargement;
    GJeu* jeu;

    /**
      * \brief      Methode permettant de fermer la fenêtre en cours
      * \details La fenêtre en cours doit être fermee pour pouvoir en afficher une autre (pour la navigation entre les menus)
      */
    void fermerFenetre();

private slots:
    /**
      * \brief      Slot d'affichage des options de jeu
      * \details Affiche le menu des options
      */
    void afficherOptions();

    /**
      * \brief      Slot d'affichage du menu principal
      * \details Affiche le menu principal du jeu
      */
    void afficherMenu();

    /**
      * \brief      Slot d'affichage de l'initialisation du jeu
      * \details Affiche le menu de choix des noms de joueurs et du general
      */
    void afficherInit();

    /**
      * \brief      Slot d'affichage du jeu
      * \details La taille de la fenêtre est fixee a 900x600 px
      */
    void afficherJeu();

    /**
      * \brief      Slot d'affichage du chargement (fictif)
      * \details Un timer simule le chargement
      */
    void afficherChargement();

    /**
      * \brief      Slot de fin de jeu
      * \details Quand la partie est terminee, la fenêtre est redimensionnee a l'origine, et tous les menus sont recrees
      */
	void finJeu();

signals:
    /**
      * \brief      Signal de fermeture de la fenêtre
      * \details Connecte au slot close()
      */
    void fermetureFenetre();

    /**
      * \brief      Signal de retour au menu principal
      * \details Connecte au slot afficherMenu()
      */
    void retourMenu();

    /**
      * \brief      Signal d'entree dans le menu des options
      * \details Connecte au slot afficherOptions()
      */
    void envoieOptions();

    /**
      * \brief      Signal d'entree dans le menu d'initialisation du jeu
      * \details Connecte au slot afficherInit()
      */
    void envoieInit();

    /**
      * \brief      Signal d'entree sur l'ecran de chargement
      * \details Connecte au slot afficherChargement()
      */
    void envoieChargement();

    /**
      * \brief      Signal d'entree sur l'ecran de jeu
      * \details Connecte au slot afficherJeu()
      */
    void envoieJeu();

    /**
      * \brief      Signal de fin du jeu
      * \details Connecte au slot finJeu()
      */
	void envoieFin();

public:
    /**
      * \brief      Constructeur de la Fenêtre
      * \details La fenêtre a pour titre "PcWars", et a une taille fixe de 700x500 px
      */
    Fenetre();

    /**
      * \brief      Methode gerant les entrees clavier
      * \details Cette methode gère les deplacements dans les menus, sur la carte du jeu, ainsi que les actions pendant le jeu
      * \param anEvent Evènement (appui sur une touche du clavier)
      */
    void keyPressEvent(QKeyEvent *);

};

#endif // FENETRE_H
