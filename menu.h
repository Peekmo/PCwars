#ifndef MENU_H
#define MENU_H
/**
 * \file          menu.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres du menu
 */
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QLineEdit>


class Menu : public QLabel
{
protected:
    bool saSelection;
    int sonY;

    // Menu "normal"
    QString sonNewTexte;

    // Initialisation du jeu
    QLineEdit *sonChamp;
    int sonGeneral;

public:
    /**
      * \brief      Constructeur du menu
      * \param  uneSelection Nouvelle valeur de l'attribut saSelection
      * \param  unY Nouvelle valeur de l'attribut sonY
      * \param  unNewTexte Nouvelle valeur de l'attribut sonNewTexte
      * \param  parent
      */
    Menu(bool, int, QString, QWidget*);

    /**
      * \brief      Constructeur du menu d'initialisation du jeu
      * \param  uneSelection Nouvelle valeur de l'attribut saSelection
      * \param  unY Nouvelle valeur de l'attribut sonY
      * \param  parent
      */
    Menu(bool, int, QWidget*); // InitJeu

    /**
      * \brief      Destructeur du menu
      */
    ~Menu();

    // Modificateur
    /**
      * \brief      Modificateur de l'attribut saSelection
      * \details Cette methode permet de selectionner les choix dans les menus
      * \param uneSelection Nouvelle valeur de l'attribut saSelection
      */
    virtual void setSelection(bool); // Virtual pour les options

    /**
      * \brief      Modificateur de la valeur du texte du menu (par la methode setText)
      * \param  leTexte Nouveau texte a afficher
      * \param  unGeneral Nouvelle valeur de l'attribut sonGeneral
      */
    void setTextInit(QString, int);

    /**
      * \brief      Modificateur de la valeur de lecture seule de l'attribut sonChamp (par setReadOnly(bool))
      * \param  valeur Nouvelle valeur pour la lecture seule
      */
    void setReadO(bool);

    // Accesseurs
    /**
      * \brief      Accesseur sur l'attribut sonGeneral
      * \return Retourne la valeur de l'attribut sonGeneral
      */
    int getGeneral();

    /**
      * \brief      Accesseur sur la lecture seule de l'attribut sonChamp
      * \return Retourne un booleen selon si sonChamp est ou non en lecture seule
      */
    bool getReadO();

    /**
      * \brief      Accesseur sur l'attribut sonChamp
      * \return Retourne la valeur de l'attribut sonChamp
      */
    QLineEdit* getChamp();

    /**
      * \brief      Accesseur sur l'attribut saSelection
      * \return Retourne la valeur de l'attribut saSelection
      */
    bool getSelection();

    /**
      * \brief      Accesseur sur l'attribut sonY
      * \return Retoune la valeur de l'attribut sonY
      */
    int getY();
};

#endif // MENU_H
