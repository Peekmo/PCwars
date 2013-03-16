#include "general.h"
General::General(QString unNom, int unJoueur)
    :Unite(unNom, general, unJoueur), saFurie(0), saFurieActivee(false) 
{
}

void General::setFurie(int uneFurie)
{
	// Si on est pas déjà au max
	if (uneFurie <= 10)
		saFurie = uneFurie;
}

int General::getFurie()
{
	return saFurie;
}

// Permet de savoir si le général est en mode furie ou pas
bool General::getIsFurie()
{
	if (saFurie == 10)
		return true;
	else
		return false;
}

void General::setFurieActivee(bool uneFurieActivee)
{
	saFurieActivee = uneFurieActivee;
}

bool General::getFurieActivee()
{
	return saFurieActivee;
}

