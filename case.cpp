#include "case.h"

Case::Case(TypeCase unTypeCase, int unePosX, int unePosY)
    :sonTypeCase(unTypeCase), saPosX(unePosX), saPosY(unePosY), sonUnite(0), sonCurseur(false), saCibleDeplacement(false), sonCalculDeplacement(0), saCiblePortee(false), sonCalculPortee(0), saCibleTransport(false)
{

    sesPointsDeMouvements = new std::vector <int>();

    // De base, une case n'a pas d'unit� sur elle
	sonUnite = 0;

    switch(unTypeCase)
    {

    case plaine:
        saCouverture = 1;
        sonVisuel = 'l';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case route:
        saCouverture = 1;
        sonVisuel = 'r';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case foret:
        saCouverture = 2;
        sonVisuel = 'f';
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case montagne:
        saCouverture = 4;
        sonVisuel = 'm';
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(3);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(2);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    case mer:
        saCouverture = 1;
        sonVisuel = 'e';
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(0);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        sesPointsDeMouvements->push_back(1);
        break;

    default:
        saCouverture = 3;
        sonVisuel = 'b';
    }

    this->setPixmap(QPixmap("images/terrains/"+QString(sonVisuel)+".png"));

	imageDeplacement = new QLabel(this);
	imageDeplacement->setPixmap(QPixmap("images/deplacement.png"));
	imageDeplacement->hide();

	imagePortee = new QLabel(this);
	imagePortee->setPixmap(QPixmap("images/portee.png"));
	imagePortee->hide();

	imageTransport = new QLabel(this);
	imageTransport->setPixmap(QPixmap("images/transport.png"));
	imageTransport->hide();

	affichageSoin = new QLabel(this);
	affichageSoin->setGeometry(0, 0, 75, 75);
	affichageSoin->setStyleSheet("padding:5px; color:green; font-size:17pt; background:url('images/fondAction.png');");
	affichageSoin->setAlignment(Qt::AlignCenter);
	affichageSoin->setText("Soin !");
	affichageSoin->hide();
}

Case::~Case()
{
    delete sesPointsDeMouvements;
	delete sonUnite;
}

char Case::getVisuel()
{
    return sonVisuel;
}

int Case::getCouverture()
{
	return saCouverture;
}

Unite* Case::getUnite()
{
    return sonUnite;
}

void Case::setUnite(Unite *uneUnite)
{
    sonUnite = uneUnite;

	// Si on a bien ajouté une unité
	if (sonUnite != 0)
	{
		sonUnite->setParent(this);
		sonUnite->show();
	}
}

int Case::getJoueur()
{
    return 0;
}

int Case::getPosX()
{
	return saPosX;
}

int Case::getPosY()
{
	return saPosY;
}

void Case::setCurseur(bool unCurseur)
{
	sonCurseur = unCurseur;
}

bool Case::getCurseur()
{
	return sonCurseur;
}

std::vector<int>* Case::getMouvements()
{
	return sesPointsDeMouvements;
}

bool Case::getCibleDeplacement()
{
	return saCibleDeplacement;
}

void Case::setCibleDeplacement(bool uneCibleDeplacement)
{
	saCibleDeplacement = uneCibleDeplacement;

	if (saCibleDeplacement == true)
		imageDeplacement->show();
	else
		imageDeplacement->hide();
}

int Case::getCalculDeplacement()
{
	return sonCalculDeplacement;
}

void Case::setCalculDeplacement(int unCalculDeplacement)
{
	sonCalculDeplacement = unCalculDeplacement;
}

bool Case::getCiblePortee()
{
	return saCiblePortee;
}

void Case::setCiblePortee(bool uneCiblePortee)
{
	saCiblePortee = uneCiblePortee;

	if (saCiblePortee == true)
		imagePortee->show();
	else
		imagePortee->hide();
}

int Case::getCalculPortee()
{
	return sonCalculPortee;
}

void Case::setCalculPortee(int unCalculPortee)
{
	sonCalculPortee = unCalculPortee;
}

bool Case::getCibleTransport()
{
	return saCibleTransport;
}

void Case::setCibleTransport(bool uneCibleTransport)
{
	saCibleTransport = uneCibleTransport;

	if (saCibleTransport == true)
		imageTransport->show();
	else
		imageTransport->hide();
}

void Case::setAffichageSoin(bool unSoin)
{
	if (unSoin == true)
		affichageSoin->show();
	else
		affichageSoin->hide();
}
