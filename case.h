#ifndef CASE_HPP
#define CASE_H
/**
 * \file          case.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres des cases
 */
#include <algorithm>
#include <vector>
#include <QLabel>
#include <QPixmap>
#include "general.h"


enum TypeCase
{
    route,
    plaine,
    montagne,
    foret,
    mer,
    batiment
};

enum TypeBatiment
{
    qg,
    base,
    ville,
    port
};

class Case : public QLabel
{
protected:
    TypeCase sonTypeCase;
    char sonVisuel;
    int saPosX;
    int saPosY;
    int saCouverture;
    std::vector <int> *sesPointsDeMouvements;
    bool estOccupe;
    Unite* sonUnite;

    // Deplacement
	bool sonCurseur;
	bool saCibleDeplacement;
	int sonCalculDeplacement;
	QLabel *imageDeplacement;

	// Attaque
	bool saCiblePortee;
	int sonCalculPortee;
	QLabel *imagePortee;

	// Transport
	bool saCibleTransport;
	QLabel *imageTransport;

	// Soin
	QLabel *affichageSoin;

public:
    /**
      * \brief      Constructeur de la Case
      * \param  unTypeCase Type de la case (route, plaine, montagne, foret, mer, batiment)
      * \param  unePosX Position en abcisse de la case
      * \param  unePosY Position en ordonnee de la case
      */
    Case(TypeCase, int, int);

    /**
      * \brief      Destructeur de la Case
      * \details Lors de la destruction de la case, ses points de mouvement et son unite sont prealablement detruits
      */
    ~Case();

    /**
      * \brief      Accesseur sur l'attribut sonVisuel
      * \return Retourne la valeur de l'attribut sonVisuel
      */
    virtual char getVisuel();

    /**
      * \brief      Accesseur sur l'attribut saCouverture
      * \return Retourne la valeur de l'attribut saCouverture
      */
	int getCouverture();

    /**
      * \brief      Accesseur sur l'attribut sonUnite
      * \return Retourne la valeur de l'attribut sonUnite
      */
    Unite* getUnite();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonUnite
      * \param  uneUnite Nouvelle valeur de l'attribut sonUnite
      */
    void setUnite(Unite*);

    /**
      * \brief      Accesseur sur l'attribut sonJoueur (classe fille Batiment)
      * \details La methode revoie zero s'il ne s'agit pas d'un batiment
      * \return Retourne la valeur de l'attribut sonJoueur
      */
    virtual int getJoueur();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonJoueur (classe fille Batiment)
      * \details Voir dans la classe Batiment
      */
    virtual void setJoueur(int) {}

    /**
      * \brief      Accesseur sur l'attribut sesPointsCapture (classe fille Batiment)
      * \details La methode renvoie zero s'il ne s'agit pas d'un batiment
      * \return Retourne la valeur de l'attribut sesPointsCapture
      */
	virtual int getPointsCapture() {return 0;}

    /**
      * \brief      Modificateur de la valeur de l'attribut sesPointsCapture (classe fille Batiment)
      * \details Voir dans la classe Batiment
      */
	virtual void setPointsCapture(int) {}

    /**
      * \brief      Accesseur sur l'attribut saPosX
      * \return Retourne la valeur de l'attribut saPosX
      */
	int getPosX();

    /**
      * \brief      Accesseur sur l'attribut saPosY
      * \return Retourne la valeur de l'attribut saPosY
      */
	int getPosY();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonCurseur
      * \details Cette methode permet de savoir si le curseur se situe sur la case
      * \param unCurseur Nouvelle valeur de l'attribut sonCurseur
      */
	void setCurseur(bool);

    /**
      * \brief      Accesseur sur l'attribut sonCurseur
      * \return Retourne la valeur de l'attribut sonCurseur
      */
	bool getCurseur();

    /**
      * \brief      Accesseur sur l'attribut sesPointsDeMouvement
      * \return Retourne la valeur de l'attribut sesPointsDeMouvement
      */
	std::vector<int>* getMouvements();

    // Deplacements
    /**
      * \brief      Accesseur sur l'attribut saCibleDeplacement
      * \return Retourne la valeur de l'attribut saCibleDeplacement
      */
	bool getCibleDeplacement();

    /**
      * \brief      Modificateur de la valeur de l'attribut saCibleDeplacement
      * \details Si la cible de deplacement existe (true), alors on affiche l'image de deplacement (imageDeplacement)
      * \param uneCibleDeplacement Nouvelle valeur de l'attribut saCibleDeplacement
      */
	void setCibleDeplacement(bool);

    /**
      * \brief      Accesseur sur l'attribut sonCalculDeplacement
      * \return Retourne la valeur de l'attribut sonCalculDeplacement
      */
	int getCalculDeplacement();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonCalculDeplacement
      * \param  unCalculeDeplacement Nouvelle valeur de l'attribut sonCalculDeplacement
      */
	void setCalculDeplacement(int);

	// Attaque
    /**
      * \brief      Accesseur sur l'attribut saCiblePortee
      * \return Retourne la valeur de l'attribut saCiblePortee
      */
	bool getCiblePortee();

    /**
      * \brief      Modificateur de la valeur de l'attribut saCiblePortee
      * \details Si la cible de portee existe (true), alors on affiche l'image de portee (imagePortee)
      * \param uneCiblePortee Nouvelle valeur de l'attribut saCiblePortee
      */
	void setCiblePortee(bool);

    /**
      * \brief      Accesseur sur l'attribut sonCalculPortee
      * \return Retourne la valeur de l'attribut sonCalculPortee
      */
	int getCalculPortee();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonCalculPortee
      * \param  unCalculPortee Nouvelle valeur de l'attribut sonCalculPortee
      */
	void setCalculPortee(int);
	
	// Transport
    /**
      * \brief      Accesseur sur l'attribut saCibleTransport
      * \return Retourne la valeur de l'attribut saCibleTransport
      */
	bool getCibleTransport();

    /**
      * \brief      Modificateur de la valeur de l'attribut saCibleTransport
      * \details Si la cible de transport existe (true), alors on affiche l'image de transport (imageTransport)
      * \param uneCibleTransport Nouvelle valeur de l'attribut saCibleTransport
      */
	void setCibleTransport(bool);

	// Affichage soin
    /**
      * \brief      Methode d'affichage des soins
      * \details S'il y a un soin, on affiche le texte "Soin !" de l'attribut affichageSoin
      * \param unSoin Valeur indiquant s'il y a ou non un soin
      */
	void setAffichageSoin(bool);
};

#endif // CASE_HPP
