#include "unite.h"

Unite::Unite(QString unNom, TypeUnite unType, int unJoueur)
    :sonNom(unNom), sesPointsDeVie(10), sonType(unType), sonJoueur(unJoueur), enDeplacement(false), sonAttaque(false)
{
    sesPointsDefense = new std::vector<int>();

	switch (unType)
	{
		case general:
			sesPointsDeMouvement = 5;
			saPortee = 3;
			sesPointsDegats = 10;
			sesPointsDefense->push_back(9);
			sesPointsDefense->push_back(9);
			sesPointsDefense->push_back(8);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(8);
			sesPointsDefense->push_back(9);
			sesPointsDefense->push_back(9);
			sesPointsDefense->push_back(8);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case infanterie:
			sesPointsDeMouvement = 3;
			saPortee = 1;
			sesPointsDegats = 6;
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(1);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case bazooka:
			sesPointsDeMouvement = 2;
			saPortee = 2;
			sesPointsDegats = 8;
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(4);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(1);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case camion:
			sesPointsDeMouvement = 5;
			saPortee = 0;
			sesPointsDegats = 1;
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(1);
			sonTransport = true;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case tank:
			sesPointsDeMouvement = 4;
			saPortee = 3;
			sesPointsDegats = 8;
			sesPointsDefense->push_back(4);
			sesPointsDefense->push_back(7);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(7);
			sesPointsDefense->push_back(2);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case croiseur:
			sesPointsDeMouvement = 4;
			saPortee = 4;
			sesPointsDegats = 7;
			sesPointsDefense->push_back(3);
			sesPointsDefense->push_back(8);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(7);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(4);
			sesPointsDefense->push_back(2);
			sonTransport = true;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case chasseur:
			sesPointsDeMouvement = 6;
			saPortee = 4;
			sesPointsDegats = 7;
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(5);
			sesPointsDefense->push_back(7);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(7);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(4);
			sesPointsDefense->push_back(9);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;

		case bombardier:
			sesPointsDeMouvement = 5;
			saPortee = 1;
			sesPointsDegats = 10;
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(0);
			sesPointsDefense->push_back(6);
			sesPointsDefense->push_back(2);
			sesPointsDefense->push_back(1);
			sesPointsDefense->push_back(5);
			sonTransport = false;
			enTransport = false;
			sonUniteTransportee = 0;
			break;
	}

        this->setPixmap(QPixmap("images/unite"+QString::number(sonJoueur)+"/"+QString::number(sonType)+".png"));
		this->setAlignment(Qt::AlignCenter);
}

QString Unite::getNom()
{
    return sonNom;
}

void Unite::setJoueur(int unJoueur)
{
    sonJoueur = unJoueur;

    if (sonJoueur != 0)
        this->setPixmap(QPixmap("images/unite"+QString::number(sonJoueur)+"/"+QString::number(sonType)+".png"));
}


int Unite::getJoueur()
{
    return sonJoueur;
}

TypeUnite Unite::getType()
{
	return sonType;
}

Unite::~Unite()
{
    delete sesPointsDefense;
}

int Unite::getVie()
{
	return sesPointsDeVie;
}

void Unite::setVie(int uneVie)
{
	sesPointsDeVie = uneVie;
}

int Unite::getDegats()
{
	return sesPointsDegats;
}

void Unite::setDegats(int unDegat)
{
	sesPointsDegats = unDegat;
}

std::vector<int>* Unite::getDefense()
{
	return sesPointsDefense;
}

int Unite::getMouvements()
{
	return sesPointsDeMouvement;
}

void Unite::setMouvements(int desPointsMouvement)
{
	sesPointsDeMouvement = desPointsMouvement;
}

bool Unite::getDeplacement()
{
	return enDeplacement;
}

void Unite::setDeplacement(bool unDeplacement)
{
	enDeplacement = unDeplacement;
}

int Unite::getPortee()
{
	return saPortee;
}

bool Unite::getAttaque()
{
	return sonAttaque;
}

void Unite::setAttaque(bool uneAttaque)
{
	sonAttaque = uneAttaque;
}

bool Unite::getSonTransport()
{
	return sonTransport;
}

bool Unite::getEnTransport()
{
	return enTransport;
}

void Unite::setEnTransport(bool leEnTransport)
{
	enTransport = leEnTransport;
}

Unite* Unite::getUniteTransportee()
{
	return sonUniteTransportee;
}

void Unite::setUniteTransportee(Unite* uneUnite)
{
	sonUniteTransportee = uneUnite;

	if (sonUniteTransportee != 0)
		// Pour cacher l'affichage de l'unité
		sonUniteTransportee->hide();
}
