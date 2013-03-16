#include "carte.h"
#include "listeCartes.cpp"

Carte::Carte(int unArgentBatiment)
    :sonNom("Carte de Test"), saTailleX(12), saTailleY(8), enCours(false), sonJoueur1(0), sonJoueur2(0)
{
    TypeBatiment unBatiment;
    TypeCase uneCase;

    // Pour qu'il n'y ai pas d'espaces entre les cases et de marge sur les côtés de la fenêtre
    this->setSpacing(0);
    this->setMargin(0);

    sesCases = new std::vector<Case*>();
    int leId(0);

    for (int i(0); i < saTailleY; i++)
    {
        for (int i2(0); i2 < saTailleX; i2++)
        {
            char laCase = maMap1(i2, i);

            switch(laCase)
            {
            case 'l':
                uneCase = plaine;
                break;

            case 'f':
                uneCase = foret;
                break;

            case 'r':
                uneCase = route;
                break;

            case 'm':
                uneCase = montagne;
                break;

            case 'e':
                uneCase = mer;
                break;

            case 'q':
                uneCase = batiment;
                unBatiment = qg;
                break;

            case 'b':
                uneCase = batiment;
                unBatiment = base;
                break;

            case 'p':
                uneCase = batiment;
                unBatiment = port;
                break;

            case 'v':
                uneCase = batiment;
                unBatiment = ville;
                break;
            }

            if (uneCase == batiment)
                sesCases->push_back(new Batiment(i2, i, unBatiment, unArgentBatiment));
            else
                sesCases->push_back(new Case(uneCase, i2, i));

            this->addWidget((*sesCases)[leId], i, i2);
            leId++;
        }
    }
}

Carte::~Carte()
{
	for (std::vector<Case*>::iterator it = sesCases->begin(); it != sesCases->end(); it++)
	{
		delete (*it);
	}
}

std::vector<Case*>* Carte::getCases()
{
	return sesCases;
}

void Carte::setJeu(General* general1, General* general2)
{
    std::vector<Case*>::iterator it;

    for (it = sesCases->begin(); it != sesCases->end(); it++)
    {
        if ((*it)->getVisuel() == 'q')
        {
            if ((*it)->getJoueur() == 1)
                (*it)->setUnite(general1);

            else if ((*it)->getJoueur() == 2)
                (*it)->setUnite(general2);
        }
    }
}

