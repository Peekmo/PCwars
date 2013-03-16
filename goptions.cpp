#include "goptions.h"

GOptions::GOptions(QWidget *parent)
    :sonArgentBatiments(1000), sonNombreTours(10), sonNombreUnites(5), sonArgentDepart(1000)
{
    // Définition du fond
    QLabel *sonFondAffiche = new QLabel(this);
    sonFondAffiche->setPixmap(QPixmap("images/titre.jpg"));
    sonFondAffiche->setGeometry(0,0,700,500);

    // On crée les Optionss
    sesOptions = new std::vector<Menu*>();

    this->setParent(parent);
    this->setFixedSize(700, 500);

    sesOptions->push_back(new Options(true, 75, "Argent par batiments : "+QString::number(sonArgentBatiments)+"", this));
    sesOptions->push_back(new Options(false, 150, "Tours maximum : "+QString::number(sonNombreTours)+"", this));
    sesOptions->push_back(new Options(false, 225, "Unites maximum : "+QString::number(sonNombreUnites)+"", this));
    sesOptions->push_back(new Options(false, 300, "Argent de depart : "+QString::number(sonArgentDepart)+"", this));
    sesOptions->push_back(new Menu(false, 375, "Retour au Options", this));

    std::vector<Menu*>::iterator it;

    // On place les Options
    for (it = sesOptions->begin(); it != sesOptions->end(); it++)
    {
        (*it)->setGeometry(200,(*it)->getY(), 300, 40);
    }
}

void GOptions::setOptions(bool modification)
{
    std::vector<Menu*>::iterator it;

    // Augmenter la valeur de l'option
    if (modification == true)
    {
        if ((*sesOptions)[0]->getSelection() == true)
        {
            // On vérifie qu'on est pas déjà au max
            if (sonArgentBatiments != 10000)
            {
                sonArgentBatiments += 1000;
                (*sesOptions)[0]->setText("Argent par batiments : "+QString::number(sonArgentBatiments)+"");
            }
        }

        else if ((*sesOptions)[1]->getSelection() == true)
        {
            if (sonNombreTours != 100)
            {
                sonNombreTours += 10;
                (*sesOptions)[1]->setText("Tours maximum : "+QString::number(sonNombreTours)+"");
            }
        }

        else if ((*sesOptions)[2]->getSelection() == true)
        {
            if (sonNombreUnites != 15)
            {
                sonNombreUnites += 5;
                (*sesOptions)[2]->setText("Unites maximum : "+QString::number(sonNombreUnites)+"");
            }
        }

        else if ((*sesOptions)[3]->getSelection() == true)
        {
            if (sonArgentDepart != 5000)
            {
                sonArgentDepart += 1000;
                (*sesOptions)[3]->setText("Argent de depart : "+QString::number(sonArgentDepart)+"");
            }
        }
    }

    // Diminuer la valeur de l'option
    else
    {
        if ((*sesOptions)[0]->getSelection() == true)
        {
            // On vérifie qu'on est pas déjà au max
            if (sonArgentBatiments != 1000)
            {
                sonArgentBatiments -= 1000;
                (*sesOptions)[0]->setText("Argent par batiments : "+QString::number(sonArgentBatiments)+"");
            }
        }

        else if ((*sesOptions)[1]->getSelection() == true)
        {
            if (sonNombreTours != 10)
            {
                sonNombreTours -= 10;
                (*sesOptions)[1]->setText("Tours maximum : "+QString::number(sonNombreTours)+"");
            }
        }

        else if ((*sesOptions)[2]->getSelection() == true)
        {
            if (sonNombreUnites != 5)
            {
                sonNombreUnites -= 5;
                (*sesOptions)[2]->setText("Unites maximum : "+QString::number(sonNombreUnites)+"");
            }
        }

        else if ((*sesOptions)[3]->getSelection() == true)
        {
            if (sonArgentDepart != 1000)
            {
                sonArgentDepart -= 1000;
                (*sesOptions)[3]->setText("Argent de depart : "+QString::number(sonArgentDepart)+"");
            }
        }
    }
}

std::vector<Menu*>* GOptions::getOptions()
{
    return sesOptions;
}

int GOptions::getArgentBatiments()
{
    return sonArgentBatiments;
}

int GOptions::getNbTours()
{
    return sonNombreTours;
}

int GOptions::getNbUnites()
{
    return sonNombreUnites;
}

int GOptions::getArgentDepart()
{
    return sonArgentDepart;
}
