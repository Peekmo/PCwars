#include "fenetre.h"

Fenetre::Fenetre()
{
    // Titre de la fenêtre
    this->setWindowTitle("PcWars");
	this->setFixedSize(700,500);

    // Création des fenêtes
    menuPrincipal = new GMenu(this);
    menuPrincipal->setVisible(false);

    optionsPrincipales = new GOptions(this);
    optionsPrincipales->setVisible(false);

    initJeu = new gInitJeu(this);
    initJeu->setVisible(false);

    chargement = new GChargement(this);
    chargement->setVisible(false);

    jeu = new GJeu(this, optionsPrincipales);
    jeu->setVisible(false);

    // Fenêtre affiché au lancement du programme
    afficherMenu();

    // Connexions Signaux/Slots
    QObject::connect(this, SIGNAL(fermetureFenetre()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(retourMenu()), this, SLOT(afficherMenu()));
    QObject::connect(this, SIGNAL(envoieOptions()), this, SLOT(afficherOptions()));
    QObject::connect(this, SIGNAL(envoieInit()), this, SLOT(afficherInit()));
    QObject::connect(chargement, SIGNAL(finChargement()), this, SLOT(afficherJeu()));
    QObject::connect(this, SIGNAL(envoieChargement()), this, SLOT(afficherChargement()));
	QObject::connect(this, SIGNAL(envoieFin()), this, SLOT(finJeu()));

}

// Slot d'affichage du menu
void Fenetre::afficherMenu()
{
    fermerFenetre();
    menuPrincipal->setVisible(true);
}

// Slot d'affichage des options de jeu
void Fenetre::afficherOptions()
{
    fermerFenetre();
    optionsPrincipales->setVisible(true);
}

// Slot d'affichage de l'init du jeu
void Fenetre::afficherInit()
{
    fermerFenetre();
    initJeu->setVisible(true);
}

// Slot d'affichage du chargement
void Fenetre::afficherChargement()
{
    fermerFenetre();
    chargement->startTimer();
    chargement->setVisible(true);
}

// Slot d'affichage du jeu
void Fenetre::afficherJeu()
{
    fermerFenetre();

	// On augmente la taille de la fenêtre pour l'affichage de la carte
	this->setFixedSize(900,600);

    Joueur *joueur1 = new Joueur(1, (*initJeu->getInitJeu())[0]->getChamp()->text(), optionsPrincipales->getArgentDepart());
    Joueur *joueur2 = new Joueur(2, (*initJeu->getInitJeu())[2]->getChamp()->text(), optionsPrincipales->getArgentDepart());

    General *general1 = new General(((*initJeu->getGeneraux())[(*initJeu->getInitJeu())[1]->getGeneral()])->getNom(), 1);
    General *general2 = new General(((*initJeu->getGeneraux())[(*initJeu->getInitJeu())[3]->getGeneral()])->getNom(), 2);

    jeu->setJeu(joueur1, joueur2, general1, general2);
	chargement->setVisible(false);
    jeu->setVisible(true);
}

// Après une partie, on détruit le jeu et on en reconstruit un :D
void Fenetre::finJeu()
{
	this->setFixedSize(700,500);

	delete jeu;
	delete menuPrincipal;
	delete initJeu;
	delete optionsPrincipales;
	delete chargement;

    // ReCréation des fenêtes
    menuPrincipal = new GMenu(this);
    menuPrincipal->setVisible(false);

    optionsPrincipales = new GOptions(this);
    optionsPrincipales->setVisible(false);

    initJeu = new gInitJeu(this);
    initJeu->setVisible(false);

    chargement = new GChargement(this);
    chargement->setVisible(false);

    jeu = new GJeu(this, optionsPrincipales);
    jeu->setVisible(false);

	afficherMenu();

    // Connexions Signaux/Slots
    QObject::connect(this, SIGNAL(fermetureFenetre()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(retourMenu()), this, SLOT(afficherMenu()));
    QObject::connect(this, SIGNAL(envoieOptions()), this, SLOT(afficherOptions()));
    QObject::connect(this, SIGNAL(envoieInit()), this, SLOT(afficherInit()));
    QObject::connect(chargement, SIGNAL(finChargement()), this, SLOT(afficherJeu()));
    QObject::connect(this, SIGNAL(envoieChargement()), this, SLOT(afficherChargement()));
	QObject::connect(this, SIGNAL(envoieFin()), this, SLOT(finJeu()));


}

// Méthode permettant de masquer la fenêtre en cours ( utilisée avant d'en afficher une nouvelle )
void Fenetre::fermerFenetre()
{
    if (menuPrincipal->isVisible() == true)
        menuPrincipal->setVisible(false);
    
    else if (optionsPrincipales->isVisible() == true)
        optionsPrincipales->setVisible(false);
    
    else if (initJeu->isVisible() == true)
        initJeu->setVisible(false);
    
    else if (jeu->isVisible() == true)
        initJeu->setVisible(false);
}

// Événements
void Fenetre::keyPressEvent(QKeyEvent *anEvent)
{

/* --------------------------------------------- Menu Principal --------------------------------------*/
    if (menuPrincipal->isVisible() == true)
    {
        // Flèche du bas
        if (anEvent->key() == Qt::Key_Down)
        {
            std::vector<Menu*>::iterator it;

            for (it = menuPrincipal->getMenu()->begin(); it != menuPrincipal->getMenu()->end(); it++)
            {
                // On ne peut pas plus descendre si on est au dernier menu
                if ((it+1) == menuPrincipal->getMenu()->end())
                    break;

                // Changement de séléction
                else if ((*it)->getSelection() == true)
                {
                    (*it)->setSelection(false);
                    (*(it+1))->setSelection(true);
                    break;
                }
            }
        }

        // Flèche du haut
        else if (anEvent->key() == Qt::Key_Up)
        {
            std::vector<Menu*>::reverse_iterator itr;

            for (itr = menuPrincipal->getMenu()->rbegin(); itr != menuPrincipal->getMenu()->rend(); itr++)
            {
                // On ne peut plus monter si on est au premier menu
                if ((itr+1) == menuPrincipal->getMenu()->rend())
                    break;

                // Changement de séléction
                else if ((*itr)->getSelection() == true)
                {
                    (*itr)->setSelection(false);
                    (*(itr+1))->setSelection(true);
                    break;
                }
            }
        }

        else if (anEvent->key() == Qt::Key_Return)
        {
            if ((*menuPrincipal->getMenu())[0]->getSelection() == true)
            {
                emit envoieInit();
            }
            else if ((*menuPrincipal->getMenu())[1]->getSelection() == true)
            {
                emit envoieOptions();
            }
            else if ((*menuPrincipal->getMenu())[2]->getSelection() == true)
            {
                emit fermetureFenetre();
            }
        }
    }

/* ------------------------------------------ Options du Jeu --------------------------------------------- */

    else if (optionsPrincipales->isVisible() == true)
    {
        // Flèche du bas
        if (anEvent->key() == Qt::Key_Down)
        {
            std::vector<Menu*>::iterator it;

            for (it = optionsPrincipales->getOptions()->begin(); it != optionsPrincipales->getOptions()->end(); it++)
            {
                // On ne peut pas plus descendre si on est au dernier Options
                if ((it+1) == optionsPrincipales->getOptions()->end())
                    break;

                // Changement de séléction
                else if ((*it)->getSelection() == true)
                {
                    (*it)->setSelection(false);
                    (*(it+1))->setSelection(true);
                    break;
                }
            }
        }

        // Flèche du haut
        else if (anEvent->key() == Qt::Key_Up)
        {
            std::vector<Menu*>::reverse_iterator itr;

            for (itr = optionsPrincipales->getOptions()->rbegin(); itr != optionsPrincipales->getOptions()->rend(); itr++)
            {
                // On ne peut plus monter si on est au premier Options
                if ((itr+1) == optionsPrincipales->getOptions()->rend())
                    break;

                // Changement de séléction
                else if ((*itr)->getSelection() == true)
                {
                    (*itr)->setSelection(false);
                    (*(itr+1))->setSelection(true);
                    break;
                }
            }
        }

        // Flèche de droite
        else if (anEvent->key() == Qt::Key_Right)
        {
            optionsPrincipales->setOptions(true);
        }

        // Flèche de droite
        else if (anEvent->key() == Qt::Key_Left)
        {
            optionsPrincipales->setOptions(false);
        }

        else if (anEvent->key() == Qt::Key_Return)
        {
            if ((*optionsPrincipales->getOptions())[1]->getSelection() == true)
            {
                emit envoieOptions();
            }
            else if ((*optionsPrincipales->getOptions())[4]->getSelection() == true)
            {
                emit retourMenu();
            }
        }
    }

    /* ------------------------------------------ Init du Jeu --------------------------------------------- */

	else if (initJeu->isVisible() == true)
	{
		// Flèche du bas
		if (anEvent->key() == Qt::Key_Down)
		{
			std::vector<Menu*>::iterator it;

			for (it = initJeu->getInitJeu()->begin(); it != initJeu->getInitJeu()->end(); it++)
			{
				// On ne peut pas plus descendre si on est au dernier Options
				if ((it+1) == initJeu->getInitJeu()->end())
					break;

				// Changement de séléction
				else if ((*it)->getSelection() == true)
				{                        
					(*it)->setSelection(false);
					(*(it+1))->setSelection(true);

					break;
				}
			}
		}

		// Flèche du haut
		else if (anEvent->key() == Qt::Key_Up)
		{
			std::vector<Menu*>::reverse_iterator itr;

			for (itr = initJeu->getInitJeu()->rbegin(); itr != initJeu->getInitJeu()->rend(); itr++)
			{
				// On ne peut plus monter si on est au premier Options
				if ((itr+1) == initJeu->getInitJeu()->rend())
					break;

				// Changement de séléction
				else if ((*itr)->getSelection() == true)
				{
					(*itr)->setSelection(false);
					(*(itr+1))->setSelection(true);

					break;
				}
			}
		}

		// Flèche de droite
		else if (anEvent->key() == Qt::Key_Right)
		{
			initJeu->setGeneral(true);
		}

		// Flèche de gauche
		else if (anEvent->key() == Qt::Key_Left)
		{
			initJeu->setGeneral(false);
		}

		else if (anEvent->key() == Qt::Key_Return)
		{
			// Evénement qui pour un appuis sur "Return" simule un "Tab" pour l'édition des champs qui se fait part Qt::TabFocus
			QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);

			if ((*initJeu->getInitJeu())[0]->getSelection() == true && (*initJeu->getInitJeu())[0]->getReadO() == true)
			{
				// Si le champ n'est pas en cours "d'édition", appuyer sur entrer permet d'écrire dedans
				QApplication::sendEvent(this, &event);

				(*initJeu->getInitJeu())[0]->setReadO(false);
			}

			else if ((*initJeu->getInitJeu())[2]->getSelection() == true && (*initJeu->getInitJeu())[2]->getReadO() == true)
			{
				// On fait l'équivalent de 2 "Tab" afin de se retrouver dans notre 2e champ
				QApplication::sendEvent(this, &event);
				QApplication::sendEvent(this, &event);

				(*initJeu->getInitJeu())[2]->setReadO(false);
			}

			else if ((*initJeu->getInitJeu())[4]->getSelection() == true)
			{
				emit(envoieChargement());
			}
		}
	}

	/* ------------------------------------------------------------- Jeu --------------------------------------------- */
	else if (jeu->isVisible() == true)
	{
		// Si on appuie sur n'importe quelle touche
		if (anEvent->key())
		{
			// Si on est �  la fin du jeu
			if (jeu->getEtapeTour() == 15)
				emit envoieFin();
		}

		// Si on appuie sur M, affichage du menu du haut
		if (anEvent->key() == Qt::Key_M)
			jeu->affichageMenu();

		// Si on appuie sur P, on passe le tour
		else if (anEvent->key() == Qt::Key_P)
		{
			if (jeu->getEtapeTour() == 2)
				jeu->changerTour();
		}

		// Si on appuie sur C
		else if (anEvent->key() == Qt::Key_C)
		{
			// Si on est bien �  l'étape 2
			if (jeu->getEtapeTour() == 2)
			{
				// On cherche le cuseur
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					// Si on est bien sur un bâtiment
					if (((*it)->getCurseur() == true) && ((*it)->getVisuel() == 'b' || (*it)->getVisuel() == 'v' || (*it)->getVisuel() == 'p' || (*it)->getVisuel() == 'q') && (*it)->getUnite() != 0)
					{
						//Si l'unité dessus peut faire des actions
						if ((*it)->getUnite()->getAttaque() == false && (*it)->getUnite()->getJoueur() == jeu->getJoueurActuel())
						{
							jeu->capturer(*it);
						}
					}
				}
			}
		}

		// Si on appuie sur D
		else if (anEvent->key() == Qt::Key_D)
		{
			// Si on est �  l'étape 2 ( déplacement du curseur )
			if (jeu->getEtapeTour() == 2 || jeu->getEtapeTour() == 8)
			{
				// On cherche où est le curseur
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						// On vérifie qu'il y a une unité sur cette case
						if ((*it)->getUnite() != 0)
						{
							// Si l'unité correspond au joueur actuel et qu'elle peut bouger
							if ((*it)->getUnite()->getJoueur() == jeu->getJoueurActuel() && (*it)->getUnite()->getAttaque() == false)
							{
								jeu->choixDeplacement(*it);
								(*it)->getUnite()->setDeplacement(true);
							}
						}
					}
				}
			}

			else if (jeu->getEtapeTour() == 3 || jeu->getEtapeTour() == 9)
			{
				Unite* uniteDeplacee = 0;

				// On recherche l'unité �  déplacer
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getUnite() != 0)
					{
						if ((*it)->getUnite()->getDeplacement() == true)
							uniteDeplacee = (*it)->getUnite();
					}
				}

				// On cherche où est le curseur
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						jeu->deplacerUnite((*it), uniteDeplacee);
					}
				}			
			}
		}

		// Si on appuie sur A
		else if (anEvent->key() == Qt::Key_A)
		{
			// Si on est �  l'étape 2 ( déplacement du curseur )
			if (jeu->getEtapeTour() == 2)
			{
				// On cherche où est le curseur
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						// On vérifie qu'il y a une unité sur cette case
						if ((*it)->getUnite() != 0)
						{
							// Si l'unité correspond au joueur actuel
							if ((*it)->getUnite()->getJoueur() == jeu->getJoueurActuel())
							{
								jeu->affichagePorteeAttaque(*it);
							}
						}
					}
				}
			}

			else if (jeu->getEtapeTour() == 5)
			{
				// On recherche l'unité �  attaquer
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						if ((*it)->getUnite() != 0)
						{
							if ((*it)->getUnite()->getJoueur() != jeu->getJoueurActuel())
								jeu->attaquer((*it)->getUnite());
						}

						else
						{
							jeu->majPortee();
						}
					}
				}
			}
		}


		// Si on appuie sur la touche R
		else if (anEvent->key() == Qt::Key_R)
		{
			if (jeu->getEtapeTour() == 2 || jeu->getEtapeTour() == 4)
				jeu->menuRecrutement();
		}

		// Si on appuie sur ECHAP
		else if (anEvent->key() == Qt::Key_Escape)
		{
			// Si on est en phase de déplacement
			if (jeu->getEtapeTour() == 3 || jeu->getEtapeTour() == 9)
				// On retour en mode déplacement du curseur simple
				jeu->majDeplacement();

			// Si on est en phase de recrutement
			else if (jeu->getEtapeTour() == 4)
				jeu->menuRecrutement();

			else if (jeu->getEtapeTour() == 5)
				jeu->majPortee();

			else if (jeu->getEtapeTour() == 7 || jeu->getEtapeTour() == 8)
				jeu->arretTransport(2);

			else if (jeu->getEtapeTour() == 10)
				jeu->arretTransport(8);
		}

		// Si on appuie sur F -- Mode furie
		else if (anEvent->key() == Qt::Key_F)
		{
			if (jeu->getEtapeTour() == 2)
			{
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						if ((*it)->getUnite() != 0)
						{
							if ((*it)->getUnite()->getType() == general && (*it)->getUnite()->getJoueur() == jeu->getJoueurActuel())
								jeu->lancerFurie();
						}
					}
				}
			}
		}

		// Si on appuie sur une touche F1 �  F6 en mode "recrutement"
		else if (anEvent->key() == Qt::Key_F1 || anEvent->key() == Qt::Key_F2 || anEvent->key() == Qt::Key_F3 || anEvent->key() == Qt::Key_F4 || anEvent->key() == Qt::Key_F5 || anEvent->key() == Qt::Key_F6)
		{
			if (jeu->getEtapeTour() == 4)
			{
				if (anEvent->key() == Qt::Key_F1)
					jeu->recruter(1);
				else if (anEvent->key() == Qt::Key_F2)
					jeu->recruter(2);
				else if (anEvent->key() == Qt::Key_F3)
					jeu->recruter(3);
				else if (anEvent->key() == Qt::Key_F4)
					jeu->recruter(4);
				else if (anEvent->key() == Qt::Key_F5)
					jeu->recruter(5);
				else if (anEvent->key() == Qt::Key_F6)
					jeu->recruter(6);
			}
		}

		// Si on appuie sur T = recrutement
		else if (anEvent->key() == Qt::Key_T)
		{
			// Si on est en mode déplacement
			if (jeu->getEtapeTour() == 2)
			{
				// On cherche le curseur
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{			
						if ((*it)->getUnite() != 0)
						{
							if (((*it)->getUnite()->getType() == croiseur || (*it)->getUnite()->getType() == camion) && (*it)->getUnite()->getJoueur() == jeu->getJoueurActuel())
								jeu->choixCaseTransport(*it);
						}
					}
				}
			}

		// Si on est en mode de choix de l'unité �  transporter 
		else if (jeu->getEtapeTour() == 7)
		{
			for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
			{
				if ((*it)->getCurseur() == true)
				{
					if ((*it)->getCibleTransport() == true)
						jeu->choixCaseTransport(*it);
				}
			}
		}

		// Si on est en mode de déplacement de l'unité transportante 
		else if (jeu->getEtapeTour() == 8)
		{
			for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
			{
				if ((*it)->getCurseur() == true)
				{
					if ((*it)->getUnite() != 0)
					{
						if ((*it)->getUnite()->getEnTransport() == true  && (*it)->getUnite()->getJoueur() == jeu->getJoueurActuel())
							jeu->choixCaseTransport(*it);
					}
				}
			}
		}

		else if (jeu->getEtapeTour() == 10)
		{
			for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
			{
				if ((*it)->getCurseur() == true)
				{
					if ((*it)->getCibleTransport() == true)
						jeu->choixCaseTransport(*it);
				}
			}
		}
	}

		// Si on appuie sur une des touches directionnelles
		else if (anEvent->key() == Qt::Key_Up || anEvent->key() == Qt::Key_Down || anEvent->key() == Qt::Key_Right || anEvent->key() == Qt::Key_Left)
		{
			// Si on est �  l'étape déplacement, choix d'une unité �  déplacer ou choix de l'endroit où placer une unité
			if (jeu->getEtapeTour() == 2 || jeu->getEtapeTour() == 7 || jeu->getEtapeTour() == 8 || jeu->getEtapeTour() == 10 || jeu->getEtapeTour() == 11)

			{
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						(*it)->setCurseur(false);
						jeu->getCarte()->removeWidget(jeu->getCurseur());

						// On regarde où on déplace le curseur
						if (anEvent->key() == Qt::Key_Up)
						{
							if ((*it)->getPosY() != 0)
							{
								(*(it-12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-12))->getPosY(), (*(it-12))->getPosX());
								jeu->informationsCase(*(it-12));
								jeu->updateMenuHaut();
								break;
							}
							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Down)
						{
							if ((*it)->getPosY() != 7)
							{
								(*(it+12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+12))->getPosY(), (*(it+12))->getPosX());
								jeu->informationsCase(*(it+12));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Right)
						{
							if ((*it)->getPosX() != 11)
							{
								(*(it+1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+1))->getPosY(), (*(it+1))->getPosX());
								jeu->informationsCase(*(it+1));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Left)
						{
							if ((*it)->getPosX() != 0)
							{
								(*(it-1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-1))->getPosY(), (*(it-1))->getPosX());
								jeu->informationsCase(*(it-1));
								jeu->updateMenuHaut();
								break;
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}
					}
				}
			}
			
			// Si on est �  l'étape 3 ou 8 du tour, même chose que l'étape 2 sauf qu'on prend que les cases où l'on peut se déplacer
			else if (jeu->getEtapeTour() == 3 || jeu->getEtapeTour() == 9)

			{
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						(*it)->setCurseur(false);
						jeu->getCarte()->removeWidget(jeu->getCurseur());

						// On regarde où on déplace le curseur
						if (anEvent->key() == Qt::Key_Up)
						{
							if ((*it)->getPosY() != 0 && (*(it-12))->getCibleDeplacement() == true)
							{
								(*(it-12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-12))->getPosY(), (*(it-12))->getPosX());
								jeu->informationsCase(*(it-12));
								jeu->updateMenuHaut();
								break;
							}
							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Down)
						{
							if ((*it)->getPosY() != 7 && (*(it+12))->getCibleDeplacement() == true)
							{
								(*(it+12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+12))->getPosY(), (*(it+12))->getPosX());
								jeu->informationsCase(*(it+12));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Right)
						{
							if ((*it)->getPosX() != 11 && (*(it+1))->getCibleDeplacement() == true)
							{
								(*(it+1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+1))->getPosY(), (*(it+1))->getPosX());
								jeu->informationsCase(*(it+1));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Left)
						{
							if ((*it)->getPosX() != 0 && (*(it-1))->getCibleDeplacement() == true)
							{
								(*(it-1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-1))->getPosY(), (*(it-1))->getPosX());
								jeu->informationsCase(*(it-1));
								jeu->updateMenuHaut();
								break;
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}
					}
				}
			}

			// Si on est �  l'étape 5 du tour, même chose que l'étape 2 sauf qu'on prend que les cases où l'on peut attaquer
			else if (jeu->getEtapeTour() == 5)

			{
				for (std::vector<Case*>::iterator it = jeu->getCarte()->getCases()->begin(); it != jeu->getCarte()->getCases()->end(); it++)
				{
					if ((*it)->getCurseur() == true)
					{
						(*it)->setCurseur(false);
						jeu->getCarte()->removeWidget(jeu->getCurseur());

						// On regarde où on déplace le curseur
						if (anEvent->key() == Qt::Key_Up)
						{
							if ((*it)->getPosY() != 0 && (*(it-12))->getCiblePortee() == true)
							{
								(*(it-12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-12))->getPosY(), (*(it-12))->getPosX());
								jeu->informationsCase(*(it-12));
								jeu->updateMenuHaut();
								break;
							}
							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Down)
						{
							if ((*it)->getPosY() != 7 && (*(it+12))->getCiblePortee() == true)
							{
								(*(it+12))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+12))->getPosY(), (*(it+12))->getPosX());
								jeu->informationsCase(*(it+12));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Right)
						{
							if ((*it)->getPosX() != 11 && (*(it+1))->getCiblePortee() == true)
							{
								(*(it+1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it+1))->getPosY(), (*(it+1))->getPosX());
								jeu->informationsCase(*(it+1));
								jeu->updateMenuHaut();
								break; // Break TRES important car sinon la boucle continue et le curseur est déplacé jusqu'�  la fin de la carte !
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}

						else if (anEvent->key() == Qt::Key_Left)
						{
							if ((*it)->getPosX() != 0 && (*(it-1))->getCiblePortee() == true)
							{
								(*(it-1))->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*(it-1))->getPosY(), (*(it-1))->getPosX());
								jeu->informationsCase(*(it-1));
								jeu->updateMenuHaut();
								break;
							}

							else
							{
								(*it)->setCurseur(true);
								jeu->getCarte()->addWidget(jeu->getCurseur(), (*it)->getPosY(), (*it)->getPosX());
							}
						}
					}
				}
			}
		}
	}
}

