#include "menu.h"

Menu::Menu(bool uneSelection, int unY, QString unNewTexte, QWidget *parent): saSelection(uneSelection), sonY(unY), sonNewTexte(unNewTexte), sonChamp(0), sonGeneral(0)
{
    if (saSelection == true)
        this->setStyleSheet("color:black; background:url('images/menu-true.jpg');");
    else
        this->setStyleSheet("color:black; background:url('images/menu-false.jpg');");

    // Options du texte
    this->setText(sonNewTexte);
    this->setParent(parent);
    this->setAlignment(Qt::AlignCenter);
    this->setGeometry(250, sonY, 300, 40);
}

// Constructeur pour les champs de texte
Menu::Menu(bool uneSelection, int unY, QWidget *parent): saSelection(uneSelection), sonY(unY)
{
    sonChamp = new QLineEdit(parent);
    sonChamp->setGeometry(200,sonY,300,40);
    sonChamp->setFrame(false);
    sonChamp->setFocusPolicy(Qt::NoFocus);
    sonChamp->setReadOnly(true);

    if (saSelection == true)
        sonChamp->setStyleSheet("background:url('images/menu-true.jpg'); border:2px solid yellow; color:black;");
    else
        sonChamp->setStyleSheet("background:url('images/menu-false.jpg'); border:2px solid black; color:black; ");

    this->setParent(parent);
    this->setGeometry(200, sonY, 300, 40);
    this->setAlignment(Qt::AlignCenter);
}

bool Menu::getReadO()
{
    return sonChamp->isReadOnly();
}

void Menu::setReadO(bool valeur)
{
    sonChamp->setReadOnly(valeur);
}

QLineEdit* Menu::getChamp()
{
    return sonChamp;
}

void Menu::setSelection(bool uneSelection)
{
    saSelection = uneSelection;

    if (sonChamp == 0)
    {
        // Quel fond attribuer
        if (saSelection == true)
        {
            this->setStyleSheet("color:black; background:url('images/menu-true.jpg');");
            this->setFocus(); // Pour initjeu, sinon il y a un problème de choix du général en ayant cliqué sur "tab" ou "entrer"
        }
        else
            this->setStyleSheet("color:black; background:url('images/menu-false.jpg');");
    }

    else
    {
        if (saSelection == true)
        {
            sonChamp->setFocusPolicy(Qt::TabFocus);
            sonChamp->setStyleSheet("background:url('images/menu-true.jpg'); border:2px solid yellow; color:black; width:300px;");
        }

        else
        {
            sonChamp->setFocusPolicy(Qt::NoFocus);
            sonChamp->setReadOnly(true);
            sonChamp->setStyleSheet("background:url('images/menu-false.jpg'); border:2px solid black; color:black; width:300px;");
        }
    }
}

int Menu::getGeneral()
{
    return sonGeneral;
}

void Menu::setTextInit(QString leTexte, int unGeneral)
{
    this->setText(leTexte);
    sonGeneral = unGeneral;
}

bool Menu::getSelection()
{
    return saSelection;
}

int Menu::getY()
{
    return sonY;
}

Menu::~Menu()
{
}



