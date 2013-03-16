#include "batiment.h"

int Batiment::joueurActuel(1);

Batiment::Batiment(int unePosX, int unePosY, TypeBatiment unTypeBatiment, int unArgent)
    :Case(batiment, unePosX, unePosY), sonTypeBatiment(unTypeBatiment), sonArgentBatiments(unArgent), sonJoueur(0), sesPointsCapture(10)
{
	sonJoueurAffichage = new QLabel(this);
	sonJoueurAffichage->hide();

    switch(unTypeBatiment)
    {
    case qg:
        sonVisuel = 'q';
        sonJoueur = joueurActuel;
		sonJoueurAffichage->setPixmap(QPixmap("images/terrains/drapeau"+QString::number(sonJoueur)+".png"));
		sonJoueurAffichage->show();
        joueurActuel++;
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case base:
        sonVisuel = 'b';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case ville:
        sonVisuel = 'v';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    default:
        sonVisuel = 'p';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
    }

    this->setPixmap(QPixmap("images/terrains/"+QString(sonVisuel)+".png"));
}

int Batiment::getJoueur()
{
    return sonJoueur;
}

int Batiment::getPointsCapture()
{
    return sesPointsCapture;
}

void Batiment::setPointsCapture(int newPts)
{
    sesPointsCapture = newPts;
}

void Batiment::setJoueur(int unJoueur)
{
    sonJoueur = unJoueur;

	sonJoueurAffichage->setPixmap(QPixmap("images/terrains/drapeau"+QString::number(sonJoueur)+".png"));
	sonJoueurAffichage->show();
}

Unite* Batiment::getUnite()
{
    return sonUnite;
}

void Batiment::setUnite(Unite *uneUnite)
{
    sonUnite = uneUnite;
}

char Batiment::getVisuel()
{
    return sonVisuel;
}
