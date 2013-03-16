#ifndef GJEU_H
#define GJEU_H
/**
 * \file          gjeu.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre de jeu
 */
#include <QWidget>
#include <QtGui>
#include <QDebug>
#include "carte.h"
#include "goptions.h"
#include "general.h"

class GJeu : public QWidget
{
	Q_OBJECT

private:
    Carte *saCarte;

    GOptions* sesOptions;

    // Variables et objets necessaires pour l'affichage et animation du menu du haut
	QLabel *sonMenuHaut;
	QTimer *sonTimerMenuHaut;
	bool sonMenuAffiche;
	int sonMenuPosition;
	QLabel *montrerMenu;

    // Options generales du jeu
    int sonNbTours;
	int joueurActuel;
	int etapeTour;

    // Affichages lies aux tour de jeu
	QLabel *tourJoueur;
	int affichageJoueurX;
	QTimer *affichageJoueur;
	bool sonJoueurAffiche;

    // Affichages lies au curseur
	QLabel *sonCurseur;
	Unite *ancienneUnite;

    // Affichage des infos des unites
	QLabel *sonMenuBas;

	// Menu de recrutement
	QLabel *sonRecrutement;
	QTimer *affichageRecrutement;
	bool montrerRecrutement;

    // Affichage des degats infliges
	QLabel *sesDegatsJoueur1;
	QLabel *sesDegatsJoueur2;
	Unite *attaquante;
	Unite *defendante;
	QTimer *affichageDegats;

    // Capture de batiment
	QLabel *afficherCapturer;
	QTimer *affichageCapturer;

    // Affichage transport d'unite rate
	QLabel *afficherTransportRate;
	QTimer *affichageTransportRate;

	// Affichage fin de jeu
	QLabel *saFinJeu;
	QTimer *affichageFinJeu;

	// Soin
	QTimer *affichageSoin;

	// Affichage de la furie
	QLabel *saFurieJ1;
	QLabel *saFurieJ2;
	QLabel *infoFurie;
	QTimer *affichageFurie;

	// Joueurs
    Joueur* sonJoueur1;
    Joueur* sonJoueur2;
	General* sonGeneralJ1;
	General* sonGeneralJ2;

public slots:
    /**
      * \brief      Slot de changement d'image
      * \details Affiche le menu contextuel pendant le jeu
      */
	void changerImage();

    /**
      * \brief      Slot d'affichage du joueur
      * \details Affiche le nom du joueur devant jouer au debut du tour
      */
	void afficherJoueur();

    /**
      * \brief      Slot d'affichage du panneau de recrutement
      * \details Afficher le panneau de recrutement des unites
      */
	void afficherRecrutement();

    /**
      * \brief      Slot d'effacement des degats
      * \details Reinitialise l'affichage après un combat
      */
	void effacerDegats();

    /**
      * \brief      Slot d'effacement des captures
      * \details Reinitialise les points de capture et l'affichage a la fin d'une capture
      */
	void effacerCapture();

    /**
      * \brief      Slot de fin du jeu
      * \details Affiche la fin de la partie
      */
	void fin();

    /**
      * \brief      Slot de fin d'affichage du message de destruction de l'unite lors de l'annulation d'un transport
      * \details Pour des raisons obscures, l'annulation d'un transport provoque la destruction de l'unite transportee.
      */
	void finAffichageTransportRate();

    /**
      * \brief      Slot de masquage du soin
      * \details Masque l'affichage du soin
      */
	void cacherSoin();

    /**
      * \brief      Slot d'affichage de la furie
      * \details Affichage de la furie
      */
	void afficherFurie();

public:
    /**
      * \brief      Constructeur de la fenêtre de jeu
      * \details La fenêtre de jeu dispose d'une dimension fixe de 900x600 px
      * \param  parent
      * \param  lesOptions Toutes les options de jeu
      */
    GJeu(QWidget*, GOptions*);

    /**
      * \brief      Destructeur de la fenêtre de jeu
      * \details Le curseur est retire de la carte, avant la destruction de cette dernière
      */
	~GJeu();

    /**
      * \brief      Modificateur des attributs sonJoueur1, sonJoueur2, sonGeneral1, sonGeneral2, saCarte
      * \details Cette methode permet de mettre en place les generaux pour chaque joueur
      * \param  joueur1 Le joueur 1
      * \param  joueur2 Le joueur 2
      * \param  general1 Le general choisi par le joueur 1
      * \param  general2 Le general choisi par le joueur 2
      */
    void setJeu(Joueur*, Joueur*, General*, General*);

    /**
      * \brief      Methode d'affichage de menu
      * \details Cette methode permet d'effectuer l'animation de changement de menu
      */
	void affichageMenu();

    /**
      * \brief      Methode de gestion d'un tour de jeu
      * \details Cette methode permet de gerer
      */
	void tour();

    /**
      * \brief      Methode d'affichage du joueur
      * \details Cette methode permet de laisser affiche le joueur qui doit jouer pendant quelques secondes
      */
	void attenteAffichageJoueur();

    /**
      * \brief      Methode de changement de tour
      * \details Cette methode intervertit les deux joueurs, verifie que la limite de tour n'est pas atteinte, met a jour l'argent des joueurs et permet aux unites de reattaquer
      */
	void changerTour();

    /**
      * \brief      Methode d'affichage des informations sur une case
      * \details Cette methode affiche les informations sur l'unite se trouvant sur une case
      * \param  uneCase Case sur laquelle pointe le curseur
      */
	void informationsCase(Case*);

    /**
      * \brief      Methode d'affichage des possibilites de deplacement
      * \details Cette methode permet d'afficher les cases sur lesquelles peut se deplacer une unite
      * \param  uneCase Case de l'unite selectionnee
      */
	void choixDeplacement(Case*);

    /**
      * \brief      Methode d'annulation d'un deplacement
      */
	void majDeplacement();

    /**
      * \brief      Methode de deplacement d'une unite
      * \param  uneCase Case sur laquelle est deplacee l'unite
      * \param  uneUnite Unite a deplacer
      */
	void deplacerUnite(Case*, Unite*);

    /**
      * \brief      Methode de mise a jour du menu superieur
      * \details Cette methode permet de changer les informations affichees sur le menu superieur, selon la case sur laquelle pointe le curseur
      */
	void updateMenuHaut();

    /**
      * \brief      Methode de preparation du menu de recrutement
      * \details Cette methode prepare le contenu du menu, l'affiche ou le masque, et renvoie les messages d'impossibilites de recrutement
      */
	void menuRecrutement();

    /**
      * \brief      Methode de recrutement des unites
      * \param  uneUnite Unite a recruter (le nombre est celui de sa position dans l'enumeration TypeUnite)
      */
	void recruter(int);

    /**
      * \brief      Methode d'affichage de la portee d'attaque
      * \param  uneCase Case sur laquelle se trouve l'unite que l'on souhaite faire attaquer
      */
	void affichagePorteeAttaque(Case*);

    /**
      * \brief      Methode d'attaque d'une unite
      * \param  uneUnite Unite recevant les degats
      */
	void attaquer(Unite*);

    /**
      * \brief      Methode enlevant le visuel d'un combat
      */
	void majPortee();

    /**
      * \brief      Methode de capture d'un batiment
      * \param  uneCase Case (Batiment) a capturer
      */
	void capturer(Case*);

    /**
      * \brief      Methode de deplacement d'une unite par une unite de transport
      * \param uneCase Case de l'unite a transporter
      */
	void choixCaseTransport(Case*);

    /**
      * \brief      Methode d'annulation d'un deplacement
      * \details Attention : l'unite transportee est detruite !
      * \param nouvelleEtape
      */
	void arretTransport(int);

    /**
      * \brief      Modificateur de la valeur de l'attribut saFurie (de la classe General)
      * \details Cette methode permet d'activer ou non la furie du general et de l'afficher
      * \param joueur Joueur dont la furie du general va changer de valeur
      */
	void setFurie(int);

    /**
      * \brief      Methode de lancement d'une furie
      * \details La furie lancee est differente selon le general choisi par le joueur :
      * \details - Soin sur toutes les unites
      * \details - Ajout de 7 points de mouvement pour toutes les unites
      * \details - Ajout de 5 points de degats pour toutes les unites
      * \details - Les unites capturent les batiments 2 fois plus vite
      * \details - Ajout de 15000 d'argent
      * \param uneFurie
      */
	void lancerFurie();

    /**
      * \brief      Methode d'affichage de la fin de la partie
      * \details Cette methode affiche quel joueur a gagne, ou s'il y a egalite
      * \param unJoueur Joueur qui a gagne
      */
	void finJeu(int);

	// Accesseurs

    /**
      * \brief      Accesseur sur l'attribut etapeTour
      * \return Retourne la valeur de l'attribut etapeTour
      */
	int getEtapeTour();

    /**
      * \brief      Accesseur sur l'attribut saCarte
      * \return Retourne la valeur de l'attribut saCarte
      */
	Carte* getCarte();

    /**
      * \brief      Accesseur sur l'attribut sonCurseur
      * \return Retourne la valeur de l'attribut sonCurseur
      */
	QLabel* getCurseur();

    /**
      * \brief      Accesseur sur l'attribut joueurActuel
      * \return Retourne la valeur de l'attribut joueurActuel
      */
	int getJoueurActuel();
};

#endif // GJEU_H
