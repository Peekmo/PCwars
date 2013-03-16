#ifndef UNITE_H
#define UNITE_H
#include <QString>
#include <QLabel>
#include <vector>
#include <QWidget>
/**
 * \file          unite.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de l'unite
 */
enum TypeUnite
{
    general,
    infanterie,
	bazooka,
    camion,
    tank,
    croiseur,
    chasseur,
	bombardier
};

class Unite : public QLabel
{
protected:
    QString sonNom;
    int sesPointsDeVie;
    int sesPointsDeMouvement;
    int saPortee;
    TypeUnite sonType;
    int sesPointsDegats;
    std::vector <int> *sesPointsDefense;
    int sonJoueur;
	bool enDeplacement;
    bool sonAttaque; // Si le joueur a deja  attaquee avec ou non
    bool sonTransport; // Si une unite peut transporter ou non d'autres unites
    bool enTransport; // Si l'unite est en train de transporter une unite
	Unite *sonUniteTransportee;

public:
    /**
      * \brief      Constructeur de l'unite
      * \param unNom Nom de l'unite
      * \param unType Type de l'unite (tous ses autres attributs en decouleront)
      * \param unJoueur Joueur auquel appartient l'unite
      */
    Unite(QString, TypeUnite, int);

    /**
      * \brief      Destructeur de l'unite
      * \details Lors de la destruction de l'unite, ses points de defense sont prealablement detruits
      */
    ~Unite();

    /**
      * \brief      Accesseur sur l'attribut sonNom
      * \return Retourne la valeur de l'attribut sonNom
      */
    QString getNom();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonJoueur
      * \details Cette methode permet en outre d'afficher l'image d'unite correspondante
      * \param unJoueur Nouvelle valeur de l'attribut sonJoueur
      */
    virtual void setJoueur(int);

    /**
      * \brief      Accesseur sur l'attribut sonJoueur
      * \return Retourne la valeur de l'attribut sonJoueur
      */
    virtual int getJoueur();

    /**
      * \brief      Accesseur sur l'attribut sonType
      * \return Retourne la valeur de l'attribut sonType
      */
	TypeUnite getType();

    /**
      * \brief      Accesseur sur l'attribut sesPointsDeVie
      * \return Retourne la valeur de l'atribut sesPointsDeVie
      */
	int getVie();

    /**
      * \brief      Modificateur de la valeur de l'attribut sesPointsDeVie
      * \param  uneVie Nouvelle valeur de l'attribut sesPointsDeVie
      */
	void setVie(int);

    /**
      * \brief      Accesseur sur l'attribut sesPointsDegats
      * \return Retourne la valeur de l'attribut sesPointsDegats
      */
	int getDegats();

    /**
      * \brief      Modificateur de la valeur de l'attribut sesPointsDegats
      * \param  unDegat Nouvelle valeur de l'attribut sesPointsDegats
      */
	void setDegats(int);

    /**
      * \brief      Accesseur sur l'attribut sesPointsDefense
      * \return Retourne la valeur de l'attribut sesPointsDefense
      */
	std::vector<int>* getDefense();

    /**
      * \brief      Accesseur sur l'attribut sesPointsDeMouvement
      * \return Retourne la valeur de l'attribut sesPointsDeMouvement
      */
    int getMouvements();

    /**
      * \brief      Modificateur de la valeur de l'attribut sesPointsDeMouvement
      * \param  desPointsMouvement Nouvelle valeur de l'attribut sesPointsDeMouvement
      */
	void setMouvements(int);

    /**
      * \brief      Accesseur sur l'attribut enDeplacement
      * \return Retourne la valeur de l'attribut enDeplacement
      */
	bool getDeplacement();

    /**
      * \brief      Modificateur de la baleur de l'attribut enDeplacement
      * \param  unDeplacement Nouvelle valeur de l'attribut enDeplacement
      */
	void setDeplacement(bool);

    /**
      * \brief      Accesseur sur l'attribut saPortee
      * \return Retourne la valeur de l'attribut saPortee
      */
	int getPortee();

    /**
      * \brief      Accesseur sur l'attribut sonAttaque
      * \return Retourne la valeur de l'attribut sonAttaque
      */
	bool getAttaque();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonAttaque
      * \param  uneAttaque Nouvelle valeur de l'attribut sonAttaque
      */
	void setAttaque(bool);

    /**
      * \brief      Accesseur sur l'attribut sonTransport
      * \return Retourne la valeur de l'attribut sonTransport
      */
	bool getSonTransport();

    /**
      * \brief      Accesseur sur l'attribut enTransport
      * \return Retourne la valeur de l'attribut enTransport
      */
	bool getEnTransport();

    /**
      * \brief      Modificateur de la valeur de l'attribut enTransport
      * \param  leEnTransport Nouvelle valeur de l'attribut enTransport
      */
	void setEnTransport(bool);

    /**
      * \brief      Accesseur sur l'attribut sonUniteTransportee
      * \return Retourne la valeur de l'attribut sonUniteTransportee
      */
	Unite* getUniteTransportee();

    /**
      * \brief      Modificateur de la valeur de l'attribut sonUniteTransportee
      * \details Cette methode masque l'unite alors transportee
      * \param  uneUnite Nouvelle valeur de l'attribut sonUniteTransportee
      */
	void setUniteTransportee(Unite*);
};

#endif // UNITE_H
