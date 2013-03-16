#include "ginitjeu.h"

gInitJeu::gInitJeu(QWidget* parent)
{
    // Définition du fond
    QLabel *sonFondAffiche = new QLabel(this);
    sonFondAffiche->setPixmap(QPixmap("images/titre.jpg"));
    sonFondAffiche->setGeometry(0,0,700,500);

    this->setParent(parent);

    sonInitJeu = new std::vector<Menu*>;

    // Création des généraux
    sesGeneraux = new std::vector<General*>();
    sesGeneraux->push_back(new General("Infirmier Joel", 0));
    sesGeneraux->push_back(new General("Envy Debouger", 0));
    sesGeneraux->push_back(new General("Bjorn Tapefjord", 0));
    sesGeneraux->push_back(new General("Piksou Maggazyne", 0));
    sesGeneraux->push_back(new General("Tom Assyeger", 0));

	QLabel *joueur1 = new QLabel("Joueur 1", this);
	joueur1->setGeometry(200, 50, 300, 20);
	joueur1->setAlignment(Qt::AlignCenter);
	joueur1->setStyleSheet("color:black; font-size:16pt");
    sonInitJeu->push_back(new Menu(true, 75, this));
    sonInitJeu->push_back(new Options(false, 120, "General "+QString((*sesGeneraux)[0]->getNom())+"", this));


	QLabel *joueur2 = new QLabel("Joueur 2", this);
	joueur2->setGeometry(200, 185, 300, 20);
	joueur2->setAlignment(Qt::AlignCenter);
	joueur2->setStyleSheet("color:black; font-size:16pt");
    sonInitJeu->push_back(new Menu(false, 210, this));
    sonInitJeu->push_back(new Options(false, 255, "General "+QString((*sesGeneraux)[0]->getNom())+"", this));
    sonInitJeu->push_back(new Menu(false, 355, "Lancer le jeu", this));

    // Pour pouvoir avoir le focus
    (*sonInitJeu)[0]->setSelection(true);

    std::vector<Menu*>::iterator it;

    // On place les Optionss
    for (it = sonInitJeu->begin(); it != sonInitJeu->end(); it++)
    {
        (*it)->setGeometry(200,(*it)->getY(), 300, 40);
    }
}

void gInitJeu::setGeneral(bool modification)
{
    // Passer au général suivant
    if (modification == true)
    {
        std::vector<General*>::reverse_iterator itr;
        if ((*sonInitJeu)[1]->getSelection() == true)
        {
            if ((*sesGeneraux)[((*sonInitJeu)[1]->getGeneral())] == *(sesGeneraux->rbegin()))
                return;

            else
            {
                (*sonInitJeu)[1]->setTextInit("General "+QString((*sesGeneraux)[((*sonInitJeu)[1]->getGeneral())+1]->getNom())+"", ((*sonInitJeu)[1]->getGeneral())+1);
            }
        }

        else if ((*sonInitJeu)[3]->getSelection() == true)
        {
            if ((*sesGeneraux)[((*sonInitJeu)[3]->getGeneral())] == *(sesGeneraux->rbegin()))
                return;

            else
            {
                (*sonInitJeu)[3]->setTextInit("General "+QString((*sesGeneraux)[((*sonInitJeu)[3]->getGeneral())+1]->getNom())+"", ((*sonInitJeu)[3]->getGeneral())+1);
            }
        }
    }


    // Passer au général d'avant
    else
    {
        std::vector<General*>::iterator it;
        if ((*sonInitJeu)[1]->getSelection() == true)
        {
            if ((*sesGeneraux)[((*sonInitJeu)[1]->getGeneral())] == *(sesGeneraux->begin()))
                return;

            else
            {
                (*sonInitJeu)[1]->setTextInit("General "+QString((*sesGeneraux)[((*sonInitJeu)[1]->getGeneral())-1]->getNom())+"", ((*sonInitJeu)[1]->getGeneral())-1);
            }
        }

        else if ((*sonInitJeu)[3]->getSelection() == true)
        {
            if ((*sesGeneraux)[((*sonInitJeu)[3]->getGeneral())] == *(sesGeneraux->begin()))
                return;

            else
            {
                (*sonInitJeu)[3]->setTextInit("General "+QString((*sesGeneraux)[((*sonInitJeu)[3]->getGeneral())-1]->getNom())+"", ((*sonInitJeu)[3]->getGeneral())-1);
            }
        }
    }
}

std::vector<Menu*>* gInitJeu::getInitJeu()
{
    return sonInitJeu;
}

std::vector<General*>* gInitJeu::getGeneraux()
{
    return sesGeneraux;
}
