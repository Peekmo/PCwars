#include "joueur.h"

Joueur::Joueur(int unId, QString unNom, int unArgent)
    :sonId(unId), sonNom(unNom), sonArgent(unArgent)
{
}

QString Joueur::getNom()
{
    return sonNom;
}

int Joueur::getArgent()
{
    return sonArgent;
}

int Joueur::getId()
{
	return sonId;
}

void Joueur::setArgent(int unArgent)
{
	sonArgent = unArgent;
}
