#include "gjeu.h"

GJeu::GJeu(QWidget* parent, GOptions* lesOptions)
    : sesOptions(lesOptions), sonMenuAffiche(false), sonNbTours(1), joueurActuel(1),  sonJoueur1(0), sonJoueur2(0), sonGeneralJ1(0), sonGeneralJ2(0)
{
    this->setParent(parent);
	this->setFixedSize(900,600);
	QLabel *sonLabel = new QLabel(this);
	sonLabel->setPixmap(QPixmap("images/titre.jpg"));
	sonLabel->setGeometry(0,0,700,500);
	
	// Timer pour l'affichage de l'animation du menu du haut
	sonTimerMenuHaut = new QTimer(this);
	QObject::connect(sonTimerMenuHaut, SIGNAL(timeout()), this, SLOT(changerImage()));

    saCarte = new Carte(sesOptions->getArgentBatiments());
    this->setLayout(saCarte);
	
	// Menu du haut
	sonMenuHaut = new QLabel(this);
	sonMenuHaut->setStyleSheet("color:white; background:url('images/menu-jeu.png')");
	sonMenuHaut->setAlignment(Qt::AlignCenter);
	sonMenuHaut->setGeometry(0,-90,900,100);
	sonMenuPosition = -90;

	// Montrer Menu
	montrerMenu = new QLabel(this);
	montrerMenu->setGeometry(5, 5, 100, 20);
	montrerMenu->setText("M : Menu");

	// Menu du bas
	sonMenuBas = new QLabel(this);
	sonMenuBas->setStyleSheet("background:url('images/menu-bas.png'); color:black;");
	sonMenuBas->setGeometry(0, 500, 900, 100);
	sonMenuBas->setAlignment(Qt::AlignCenter);
	sonMenuBas->hide();

	// Affichage du joueur qui doit jouer
	tourJoueur = new QLabel(this);
	affichageJoueurX = 605;
	sonJoueurAffiche = false;
	tourJoueur->setGeometry(0, affichageJoueurX, 900, 100);

	affichageJoueur = new QTimer(this);
	QObject::connect(affichageJoueur, SIGNAL(timeout()), this, SLOT(afficherJoueur()));

	// Objets nécessaires au curseur
	sonCurseur = new QLabel();
	sonCurseur->setPixmap(QPixmap("images/curseur.png"));

	ancienneUnite = 0; // Par défaut, on n'a pas séléctionné d'unité

	// Menu de recrutement
	sonRecrutement = new QLabel(this);
	sonRecrutement->setGeometry(900, 0, 900, 600);
	sonRecrutement->setAlignment(Qt::AlignCenter);
	sonRecrutement->setStyleSheet("font-size:13pt; color:white; background:url('images/recrutement.png');");

	affichageRecrutement = new QTimer(this);
	QObject::connect(affichageRecrutement, SIGNAL(timeout()), this, SLOT(afficherRecrutement()));

	// Pour savoir, quand on bouge l'affichage, si on cherche à montrer ou cacher le menu
	montrerRecrutement = false;

	// Affichage des dégâts infligés
	sesDegatsJoueur1 = new QLabel();
	sesDegatsJoueur1->setStyleSheet("color:red; font-size:17pt; padding:5px; background:url('images/fondAction.png');");
	sesDegatsJoueur1->hide();
	
	sesDegatsJoueur2 = new QLabel();
	sesDegatsJoueur2->setStyleSheet("color:red; font-size:17pt; padding:5px; background:url('images/fondAction.png');");
	sesDegatsJoueur2->hide();

	attaquante = 0;
	defendante = 0;

	affichageDegats = new QTimer(this);
	QObject::connect(affichageDegats, SIGNAL(timeout()), this, SLOT(effacerDegats()));

	// Affichage capture de bâtiment
	afficherCapturer = new QLabel();
	afficherCapturer->setStyleSheet("color:red; font-size:13pt; padding:1px; background:url('images/fondAction.png');");
	afficherCapturer->hide();

	affichageCapturer = new QTimer(this);
	QObject::connect(affichageCapturer, SIGNAL(timeout()), this, SLOT(effacerCapture()));

	// Affichage transport d'unité raté
	afficherTransportRate = new QLabel(this);
	afficherTransportRate->setStyleSheet("background:url('images/uniteTransport.png');");
	afficherTransportRate->setGeometry(0, 0, 900, 600);
	afficherTransportRate->hide();

	affichageTransportRate = new QTimer(this);
	
	QObject::connect(affichageTransportRate, SIGNAL(timeout()), this, SLOT(finAffichageTransportRate()));

	// Soin
	affichageSoin = new QTimer(this);
	QObject::connect(affichageSoin, SIGNAL(timeout()), this, SLOT(cacherSoin()));

	// Affichage de la furie
	saFurieJ1 = new QLabel(this);
	saFurieJ1->setStyleSheet("color:red; font-size:15pt");
	saFurieJ1->setText("[F] : Furie");
	saFurieJ1->setVisible(false);
	saFurieJ1->setGeometry(800, 5, 100, 30);

	saFurieJ2 = new QLabel(this);
	saFurieJ2->setStyleSheet("color:red; font-size:15pt");
	saFurieJ2->setText("[F] : Furie");
	saFurieJ2->setVisible(false);
	saFurieJ2->setGeometry(800, 5, 100, 30);

	infoFurie = new QLabel(this);
	infoFurie->setStyleSheet("background:url('images/furie.png'); color:white; font-size:15pt");
	infoFurie->setText("<center>Furie Activee !<br /><br />");
	infoFurie->setGeometry(0, -70, 900, 700);
	infoFurie->hide();

	affichageFurie = new QTimer(this);
	QObject::connect(affichageFurie, SIGNAL(timeout()), this, SLOT(afficherFurie()));

	// Fin du jeu
	saFinJeu = new QLabel(this);
	saFinJeu->setGeometry(0, -600, 900, 600);
	saFinJeu->setStyleSheet("color:white; background-color:black; font-size:30pt;");

	affichageFinJeu = new QTimer(this);
	QObject::connect(affichageFinJeu, SIGNAL(timeout()), this, SLOT(fin()));
}

void GJeu::setJeu(Joueur* joueur1, Joueur* joueur2, General* general1, General* general2)
{
    sonJoueur1 = joueur1;
    sonJoueur2 = joueur2;
	sonGeneralJ1 = general1;
	sonGeneralJ2 = general2;

    saCarte->setJeu(general1, general2);

	// Début de tour
	etapeTour = 1;
	tour();

}

// Méthode permettant de mettre à jour les informations affichées dans le menu du haut
void GJeu::updateMenuHaut()
{
	// Variables d'affichage
	QString nomJoueur;
	int argentJoueur(0);

	// Si c'est le tour du joueur 1
	if (joueurActuel == 1)
	{
		nomJoueur = sonJoueur1->getNom();
		argentJoueur = sonJoueur1->getArgent();
	}

	else
	{
		nomJoueur = sonJoueur2->getNom();
		argentJoueur = sonJoueur2->getArgent();
	}
	
	sonMenuHaut->setText("<center>Joueur : "+nomJoueur+" | Argent : "+QString::number(argentJoueur)+" | Tour : "+QString::number(sonNbTours));
	sonMenuHaut->setText(sonMenuHaut->text()+"<table>");

	if (etapeTour == 2)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ P ] </center></td><td> Passer le tour</td></tr>");

		// On cherche où est le curseur pour savoir les actions possibles
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getCurseur() == true)
			{
				// Si on est sur un bâtiment où l'on peut recruter, nous appartenant et qui est vide
				if (((*it)->getVisuel() == 'q' || (*it)->getVisuel() == 'p' || (*it)->getVisuel() == 'b') && (*it)->getUnite() == 0 && (*it)->getJoueur() == joueurActuel) 
					sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ R ] </center></td><td> Recruter</td></tr>");

				// Si on est sur une unité qui nous appartient
				if ((*it)->getUnite() != 0 && (*it)->getUnite()->getJoueur() == joueurActuel && (*it)->getUnite()->getAttaque() == false)
				{
					sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ D ] </center></td><td> Deplacement</td></tr>");

					// Si c'est pas un camion
					if ((*it)->getUnite()->getType() != camion)
						sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ A ] </center></td><td> Attaquer</td></tr>");

					// Si c'est une unité de transport
					if ((*it)->getUnite()->getSonTransport() == true)
						sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ T ] </center></td><td> Transporter une unite</td></tr>");
				}

				// Si on est sur un bâtiment avec une unité dessus
				if (((*it)->getVisuel() == 'q' || (*it)->getVisuel() == 'p' || (*it)->getVisuel() == 'b') && (*it)->getUnite() != 0 && (*it)->getUnite()->getAttaque() == false)
				{
					// Si c'est notre unité sur un bâtiment ennemi
					if ((*it)->getUnite()->getJoueur() == joueurActuel && (*it)->getJoueur() != joueurActuel)
						sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ C ] </center></td><td> Capturer</td></tr>");

					// Si c'est notre unité sur notre bâtiment et que celui-ci est abimé
					else if ((*it)->getUnite()->getJoueur() == joueurActuel && (*it)->getJoueur() == joueurActuel && (*it)->getPointsCapture() != 10)
						sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ C ] </center></td><td> Reparer</td></tr>");
				}
			}
		}
	}

	else if (etapeTour == 3 || etapeTour == 9)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ D ] </center></td><td> Deplacement</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler</td></tr>");
	}

	else if (etapeTour == 4)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Fx ] </center></td><td> Recruter une unite</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler</td></tr>");
	}

	else if (etapeTour == 5)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ A ] </center></td><td> Attaquer</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler</td></tr>");
	}

	else if (etapeTour == 7)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ T ] </center></td><td> Selectionner l'unite</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler</td></tr>");
	}

	else if (etapeTour == 8)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ D ] </center></td><td> Deplacement</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ T ] </center></td><td> Deposer unite</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler ( attention, l'unite transportee disparaitra )</td></tr>");
	}

	else if (etapeTour == 10)
	{
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ T ] </center></td><td> Deposer l'unite</td></tr>");
		sonMenuHaut->setText(sonMenuHaut->text()+"<tr><td><center>[ Esc ] </center></td><td> Annuler</td></tr>");

	}
}

// Méthode qui permet d'effectuer l'animation de changement de menu
void GJeu::affichageMenu()
{
	sonTimerMenuHaut->start(30); // Temps entre deux images
}

// Méthode qui gère un tour de jeu
void GJeu::tour()
{
	// Si on est au début du tour
	if (etapeTour == 1)
	{
		tourJoueur->setStyleSheet("background:url('images/jeu-joueur"+QString::number(joueurActuel)+".png')");
		affichageJoueur->start(5);
	}

	// Etape de choix de l'unité à séléctionner
	else if (etapeTour == 2)
	{
		// Savoir si il y a une unité à soigner
		bool lancerTimer(false);

		// On gère les soins de début de tour
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			// Si on est sur un bâtiment
			if (((*it)->getVisuel() == 'p' || (*it)->getVisuel() == 'q' || (*it)->getVisuel() == 'v' || (*it)->getVisuel() == 'b') && (*it)->getJoueur() == joueurActuel)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getVie() < 10 && (*it)->getUnite()->getJoueur() == joueurActuel)
					{
						(*it)->getUnite()->setVie((*it)->getUnite()->getVie() + 3);

						// On vérifie qu'on a pas dépassé le max
						if ((*it)->getUnite()->getVie() > 10)
							(*it)->getUnite()->setVie(10);

						(*it)->setAffichageSoin(true);

						lancerTimer = true;
					}
				}
			}
		}

		if (lancerTimer == true)
		{
			etapeTour = 100;
			affichageSoin->start(700);
		}

		// On place le curseur sur notre général par défaut
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			sonCurseur->show();
			if ((*it)->getUnite() != 0)
			{
				if ((*it)->getUnite()->getType() == 0 && (*it)->getUnite()->getJoueur() == joueurActuel)
				{
					saCarte->addWidget(sonCurseur, (*it)->getPosY(), (*it)->getPosX());
					(*it)->setCurseur(true);
					this->informationsCase(*it);
				}
			}
		}

		// Si on a une furie
		if (sonGeneralJ1->getFurieActivee() == true)
			sonGeneralJ1->setFurieActivee(false);
		else if (sonGeneralJ2->getFurieActivee() == true)
			sonGeneralJ2->setFurieActivee(false);

		// Si on peut faire une furie
		if (joueurActuel == 1)
		{
			saFurieJ2->setVisible(false);

			if (sonGeneralJ1->getIsFurie() == true)
				saFurieJ1->setVisible(true);
		}

		else
		{
			saFurieJ1->setVisible(false);

			if (sonGeneralJ2->getIsFurie() == true)
				saFurieJ2->setVisible(true);
		}

		this->updateMenuHaut();
	}
}

// Méthode ( slot ) permettant de faire le changement d'image
void GJeu::changerImage()
{
	// Si on veut enlever le menu
	if (sonMenuAffiche == false && sonMenuPosition != 0)
	{
		sonMenuPosition += 5;
		sonMenuHaut->move(0, sonMenuPosition);
	}

	// Si on veut afficher le menu
	else if (sonMenuAffiche == true && sonMenuPosition != -90)
	{
		sonMenuPosition -= 5;
		sonMenuHaut->move(0, sonMenuPosition);
	}

	// Exécuté qu'une fois toute les images affichées
	else
	{
		sonTimerMenuHaut->stop();
		
		if (sonMenuAffiche == false)
		{
			montrerMenu->setText("M : Cacher");
			sonMenuAffiche = true;
		}

		else
		{
			sonMenuAffiche = false;
			montrerMenu->setText("M : Menu");
		}
	}
}

// Animation d'affichage du tour de jeu
void GJeu::afficherJoueur()
{
	affichageJoueur->stop();
	affichageJoueur->start(5);

	if (sonJoueurAffiche == false && affichageJoueurX != 250)
	{
		affichageJoueurX -= 5;
		tourJoueur->move(0, affichageJoueurX);
	}

	else if (sonJoueurAffiche == true && affichageJoueurX != 650)
	{
		affichageJoueurX += 5;
		tourJoueur->move(0, affichageJoueurX);
	}

	else
	{
		affichageJoueur->stop();

		if (sonJoueurAffiche == false)
		{
			sonJoueurAffiche = true;
			attenteAffichageJoueur();
		}

		else
		{
			sonJoueurAffiche = false;
			etapeTour++;
			tour();
		}
	}
}

// Méthode permettant de laisser afficher le joueur qui doit jouer durant quelques secondes
void GJeu::attenteAffichageJoueur()
{
	affichageJoueur->start(2000);
}

// Changement de tour
void GJeu::changerTour()
{
	updateMenuHaut();

	if (joueurActuel == 1)
	{
		joueurActuel = 2;
	}

	else
	{
		joueurActuel = 1;
		sonNbTours++;

		// On vérifie qu'on a pas dépassé le nombre de tout maximum
		if (sonNbTours > sesOptions->getNbTours())
		{
			this->finJeu(3);
			return;
		}

		// On met à jour les sous des joueurs
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getJoueur() == 2)
			{
				sonJoueur2->setArgent(sonJoueur2->getArgent() + sesOptions->getArgentBatiments());
			}

			else if ((*it)->getJoueur() == 1)
			{
				sonJoueur1->setArgent(sonJoueur1->getArgent() + sesOptions->getArgentBatiments());
			}

			// On permet aux unités de réattaquer
			if ((*it)->getUnite() != 0)
				(*it)->getUnite()->setAttaque(false);
		}
	}

	saCarte->removeWidget(sonCurseur);
	sonCurseur->hide();

	// On remet le curseur à 0
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		if ((*it)->getCurseur() == true)
			(*it)->setCurseur(false);
	}

	// On remet tout les PM au max et on remet les points de dégâts de base
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{ 
		if ((*it)->getUnite() != 0)
		{
			int mouvements;
			int degats;

			switch((*it)->getUnite()->getType())
			{
				case general:
					mouvements = 5;
					degats = 10;
					break;
				case infanterie:
					mouvements = 3;
					degats = 6;
					break;
				case bazooka:
					mouvements = 2;
					degats = 8;
					break;
				case camion:
					mouvements = 5;
					degats = 1;
					break;
				case tank:
					mouvements = 4;
					degats = 8;
					break;
				case croiseur:
					mouvements = 4;
					degats = 7;
					break;
				case chasseur:
					mouvements = 6;
					degats = 7;
					break;
				case bombardier:
					mouvements = 5;
					degats = 10;
					break;
			}

			(*it)->getUnite()->setMouvements(mouvements);
			(*it)->getUnite()->setDegats(degats);
		}
	}

	etapeTour = 1;
	tour();
}

// Affichage des informations d'une case contenant une unité ( en bas de l'écran )
void GJeu::informationsCase(Case* uneCase)
{
	if (uneCase->getUnite() != 0)
	{
		QString sonType;
		
		switch(uneCase->getUnite()->getType())
		{
			case general:
				sonType = "General";
				break;
			case infanterie:
				sonType = "Infanterie";
				break;
			case bazooka:
				sonType = "Bazooka";
				break;
			case camion:
				sonType = "Camion";
				break;
			case tank:
				sonType = "Tank";
				break;
			case croiseur:
				sonType = "Croiseur";
				break;
			case chasseur:
				sonType = "Chasseur";
				break;
			case bombardier:
				sonType = "Bombardier";
				break;
		}

		sonMenuBas->show();
		sonMenuBas->setText("<center><table><tr><td rowspan=\"4\"><img src=\"images/unite"+QString::number(uneCase->getUnite()->getJoueur())+"/"+QString::number(uneCase->getUnite()->getType())+".png\"/></td><td>Joueur "+QString::number(uneCase->getUnite()->getJoueur())+"</td></tr><tr><td>"+sonType+"</td></tr><tr><td>Points de vie : "+QString::number(uneCase->getUnite()->getVie())+"</td></tr><tr><td>Mouvements : "+QString::number(uneCase->getUnite()->getMouvements())+"</tr></table></center>");
	}

	else
	{
		sonMenuBas->hide();
	}
}

// Affichage des possibilités de déplacement
void GJeu::choixDeplacement(Case *uneCase)
{
	// On place la case où se trouve l'unité en mode déplacement
	uneCase->setCibleDeplacement(true);

	// On passe à l'étape déplacement d'unité ( étape 3 )
	if (etapeTour == 2)
		etapeTour = 3;
	else if (etapeTour == 8)
		etapeTour = 9;

	// On va devoir faire autant de tours que le nombre max de déplacement de chaque unité
	for (int i(0); i < uneCase->getUnite()->getMouvements(); i++)
	{
		// On fait une boucle qui va calculer le nombre de PM mini nécessaire pour les cases adjacentes
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			// On fait ce calcul pour toute les cases autour d'une case de deplacement
			if ((*it)->getCibleDeplacement() == true)
			{
				// On calcul le nombre de PM nécessaire pour arriver à la case suivante
				int deplacementNecessaire = (*it)->getCalculDeplacement() + (*(*it)->getMouvements())[uneCase->getUnite()->getType()];

				// Si on a assez de PM
				if (deplacementNecessaire <= uneCase->getUnite()->getMouvements())
				{
					// Case de gauche
					if ((*it)->getPosX() != 0)
					{
						// Si on peut s'y déplacer
						if ((*(*(it-1))->getMouvements())[uneCase->getUnite()->getType()] != 0 && (*(it-1))->getUnite() == 0)
						{
							// Si le nombre de PM est plus petit en passant par cette case
							if ((*(it-1))->getCalculDeplacement() > deplacementNecessaire || (*(it-1))->getCalculDeplacement() == 0)
							{
								(*(it-1))->setCalculDeplacement(deplacementNecessaire);
							}
						}
					}

					// Case de droite
					if ((*it)->getPosX() != 11)
					{
						// Si on peut s'y déplacer
						if ((*(*(it+1))->getMouvements())[uneCase->getUnite()->getType()] != 0 && (*(it+1))->getUnite() == 0)
						{
							// Si le nombre de PM est plus petit en passant par cette case
							if ((*(it+1))->getCalculDeplacement() > deplacementNecessaire || (*(it+1))->getCalculDeplacement() == 0)
							{
								(*(it+1))->setCalculDeplacement(deplacementNecessaire);
							}
						}
					}

					// Case du bas
					if ((*it)->getPosY() != 7)
					{
						// Si on peut s'y déplacer
						if ((*(*(it+12))->getMouvements())[uneCase->getUnite()->getType()] != 0 && (*(it+12))->getUnite() == 0)
						{
							// Si le nombre de PM est plus petit en passant par cette case
							if ((*(it+12))->getCalculDeplacement() > deplacementNecessaire || (*(it+12))->getCalculDeplacement() == 0)
							{
								(*(it+12))->setCalculDeplacement(deplacementNecessaire);
							}
						}
					}

					// Case du haut
					if ((*it)->getPosY() != 0)
					{
						// Si on peut s'y déplacer
						if ((*(*(it-12))->getMouvements())[uneCase->getUnite()->getType()] != 0 && (*(it-12))->getUnite() == 0)
						{
							// Si le nombre de PM est plus petit en passant par cette case
							if ((*(it-12))->getCalculDeplacement() > deplacementNecessaire || (*(it-12))->getCalculDeplacement() == 0)
							{
								(*(it-12))->setCalculDeplacement(deplacementNecessaire);
							}
						}
					}
				}
			}
		}

		// On rend déplaçable les cases qui le sont
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			// Si il a une valeur de calcul différente de 0, c'est qu'elle est accessible
			if ((*it)->getCalculDeplacement() != 0 && (*it)->getCibleDeplacement() == false)
			{
				(*it)->setCibleDeplacement(true);
			}
		}
	}

	this->updateMenuHaut();
}

// Annulation de la phase de déplacement
void GJeu::majDeplacement()
{
	if (etapeTour == 3)
		etapeTour = 2;
	else if (etapeTour == 9)
		etapeTour = 8;

	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		if ((*it)->getCibleDeplacement() == true)
		{
			(*it)->setCibleDeplacement(false);
			(*it)->setCalculDeplacement(0);
			
			if ((*it)->getUnite() != 0)
			{
				// Si on est sur l'unité on la sort du mouvement
				if ((*it)->getUnite()->getDeplacement() == true)
					(*it)->getUnite()->setDeplacement(false);
			}
		}
	}

	this->updateMenuHaut();
}

// Déplacement de l'unité
void GJeu::deplacerUnite(Case* uneCase, Unite* uneUnite)
{
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		if ((*it)->getUnite() == uneUnite)
		{
			// Si on a pas voulu se déplacer sur la même case que celle où on est
			if ((*it) != uneCase)
				(*it)->setUnite(0);
			else
				break;
		}

		else if ((*it) == uneCase)
		{
			(*it)->setUnite(uneUnite);
			uneUnite->setMouvements(uneUnite->getMouvements()-(*it)->getCalculDeplacement());
		}
	}

	majDeplacement();
	this->updateMenuHaut();
}

// Prépare le menu de recrutement, et l'affiche / le désaffiche
void GJeu::menuRecrutement()
{
	// Selon l'étape à laquelle on est, on entre ou en sort en étape de recrutement
	if (etapeTour == 2)
	{
		// On vérifie qu'on est sur une case bâtiment vide
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getCurseur() == true)
			{
				// Si on est pas sur un batiment, il se passe rien
				if ((*it)->getVisuel() != 'b' && (*it)->getVisuel() != 'q' && (*it)->getVisuel() != 'v' && (*it)->getVisuel() != 'p')
					return;

				// Si on est pas sur un bâtiment à nous
				else if ((*it)->getJoueur() != joueurActuel)
				{
					sonRecrutement->setText("<center>Desole, ce batiment ne vous appartient pas !</center>");
					etapeTour = 100; // On peut rien faire pendant ce temps
					break;
				}

				// Si il y a une unité dessus
				else if ((*it)->getUnite() != 0)
				{
					sonRecrutement->setText("<center>Une unite se trouve actuellement sur le batiment.<br/> Veuillez la bouger avant de recruter</center>");
					etapeTour = 100;
					break;
				}

				else
				{
					// Sinon, c'est que le bâtiment est à nous, affichage des infos de recrutement
					// On veut stocker l'argent disponible du joueur
					int argentDisponible(0);

					etapeTour = 100;

					// On vérifie qu'on peut encore recruter, qu'on a pas atteint le max d'unité possible
					int nbUnite(0);

					for (std::vector<Case*>::iterator it2 = saCarte->getCases()->begin(); it2 != saCarte->getCases()->end(); it2++)
					{
						if ((*it2)->getUnite() != 0)
						{
							if ((*it2)->getUnite()->getJoueur() == joueurActuel)
								nbUnite++;
						}
					}

					if (nbUnite == sesOptions->getNbUnites())
					{
						sonRecrutement->setText("<center>Vous ne pouvez plus recruter !<br/>Vous avez atteint le maximum.</center>");
						break;
					}

					else
					{
						if (joueurActuel == 1)
							argentDisponible = sonJoueur1->getArgent();
						else
							argentDisponible = sonJoueur2->getArgent();

						// Affichage des unités achetable
						// Création du tableau
						sonRecrutement->setText("<center><table>");

						// Si on est ruiné
						if (argentDisponible == 0)
							sonRecrutement->setText(sonRecrutement->text()+"<tr><td>Vous n'avez pas assez de sous pour recruter.</td></tr>");

						/* ---------------- Unités recrutables sur tous les bâtiments ------- */
						// Si on a Au moins 1000
						if (argentDisponible >= 1000)
						{
							sonRecrutement->setText(sonRecrutement->text()+"<tr><strong><td><center>- Touche -  </center></td><td><center> - Unite - </center></td><td><center> - Cout - </center></td></tr>");
							sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F1</td><td>Infanterie</td><td>1000</td></tr>");
						}

						// 3000
						if (argentDisponible >= 3000)
						{
							sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F2</td><td>Bazooka</td><td>3000</td></tr>");
						}

						// Si on est sur un port, on ne peut recruter que des bateaux en plus
						if ((*it)->getVisuel() == 'p') 
						{
							// 5500
							if (argentDisponible >= 5500)
							{
								sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F3</td><td>Croiseur</td><td>5500</td></tr>");
							}					
						}

						// Si on est sur une ville, on peut pas recruter
						else if ((*it)->getVisuel() == 'v')
							sonRecrutement->setText("<center>Vous ne pouvez pas recruter sur une ville.</center>");

						// Unités recrutables sur les autres bâtiments 
						else
						{
							// 1500
							if (argentDisponible >= 1500)
							{
								sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F3</td><td>Camion</td><td>1500</td></tr>");
							}

							// 4500
							if (argentDisponible >= 4500)
							{
								sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F4</td><td>Tank</td><td>4500</td></tr>");
							}

							// 6000
							if (argentDisponible >= 6000)
							{
								sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F5</td><td>Chasseur</td><td>6000</td></tr>");
							}

							// 7000
							if (argentDisponible >= 7000)
							{
								sonRecrutement->setText(sonRecrutement->text()+"<tr><td>F6</td><td>Bombardier</td><td>7000</td></tr>");
							}
							sonRecrutement->setText(sonRecrutement->text()+"</table></center>");
							this->updateMenuHaut();
						}
					}					
					
					break;
				}
			}
		}
	}

	affichageRecrutement->start(5);
}

void GJeu::afficherRecrutement()
{
	// Si le menu est caché à la base
	if (montrerRecrutement == false)
	{
		// Si on a pas fini de l'afficher
		if (sonRecrutement->geometry().x() != 0)
			sonRecrutement->setGeometry(sonRecrutement->geometry().x() - 5, 0, 900, 600);

		// Sinon, on arrête le timer et on change l'état du menu
		else
		{
			montrerRecrutement = true;
			affichageRecrutement->stop();
			etapeTour=4;
			this->updateMenuHaut();
		}
	}
	
	else 
	{
		// Si on a pas fini de le cacher
		if (sonRecrutement->geometry().x() != 900)
			sonRecrutement->setGeometry(sonRecrutement->geometry().x() + 5, 0, 900, 600);

		// Sinon, on arrête le timer et on change l'état du menu
		else
		{
			montrerRecrutement = false;
			affichageRecrutement->stop();
			etapeTour = 2;
			this->updateMenuHaut();
		}
	}
}

// Fonction appelée lors du recrutement d'une unité
void GJeu::recruter(int uneUnite)
{
	// Informations sur l'argent dispo ( pour éviter les fraudes !! )
	int argentDisponible(0);

	if (joueurActuel == 1)
		argentDisponible = sonJoueur1->getArgent();
	else
		argentDisponible = sonJoueur2->getArgent();

	// On recompte le nombre d'unité
	int nbUnite(0);

	for (std::vector<Case*>::iterator it2 = saCarte->getCases()->begin(); it2 != saCarte->getCases()->end(); it2++)
	{
		if ((*it2)->getUnite() != 0)
		{
			if ((*it2)->getUnite()->getJoueur() == joueurActuel)
				nbUnite++;
		}
	}

	// Unité qu'on veut recruter
	TypeUnite laUnite;

	// On fait recherche la case sur laquelle on va recruter
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		// Une fois qu'on l'a trouvée
		if ((*it)->getCurseur() == true)
		{
			// On doit refaire toute les vérifications
			if ((*it)->getJoueur() == joueurActuel && (*it)->getUnite() == 0 && nbUnite < sesOptions->getNbUnites())
			{
				// Si on est sur un port
				if ((*it)->getVisuel() == 'p')
				{
					// On vérifie qu'on a bien appuyé sur une touche entre F1 et F3
					if (uneUnite == 1 || uneUnite == 2 || uneUnite == 3)
					{
						// Si on veut recruter une infanterie
						if (uneUnite == 1 && argentDisponible >= 1000)
						{
							argentDisponible -= 1000;
							laUnite = infanterie;
						}

						// Bazooka
						else if (uneUnite == 2 && argentDisponible >= 3000)
						{
							argentDisponible -= 3000;
							laUnite = bazooka;
						}

						// Croiseur
						else if (uneUnite == 3 && argentDisponible >= 5500)
						{
							argentDisponible -= 5500;
							laUnite = croiseur;
						}

						else
						{
							sonRecrutement->setText("<center>Erreur ! Vous n'avez pas assez de sous");
							break;
						}
					}

					// Sinon, message d'erreur
					else
					{
						sonRecrutement->setText("<center>Erreur, cette touche ne fonctionne pas.</center>");
						break;
					}
				}

				// Sinon, si on est sur un QG ou sur une base
				else if ((*it)->getVisuel() != 'v')
				{
					// Si on veut recruter une infanterie
					if (uneUnite == 1 && argentDisponible >= 1000)
					{
						argentDisponible -= 1000;
						laUnite = infanterie;
					}

					// Bazooka
					else if (uneUnite == 2 && argentDisponible >= 3000)
					{
						argentDisponible -= 3000;
						laUnite = bazooka;
					}

					// Camion
					else if (uneUnite == 3 && argentDisponible >= 1500)
					{
						argentDisponible -= 1500;
						laUnite = camion;
					}

					// Tank
					else if (uneUnite == 4 && argentDisponible >= 4500)
					{
						argentDisponible -= 4500;
						laUnite = tank;
					}

					// Chasseur
					else if (uneUnite == 5 && argentDisponible >= 6000)
					{
						argentDisponible -= 6000;
						laUnite = chasseur;
					}

					// Bombardier 
					else if (uneUnite == 6 && argentDisponible >= 7000)
					{
						argentDisponible -= 7000;
						laUnite = bombardier;
					}

					else
					{
						sonRecrutement->setText("<center>Erreur ! Vous n'avez pas assez de sous");
						break;
					}				
				}
				
				// Si on est sur une ville, on peut pas recruter
				else if ((*it)->getVisuel() == 'v')
					break;

				// Mise à jour de la case
				(*it)->setUnite(new Unite("NomBidon", laUnite, joueurActuel));
				this->menuRecrutement();
				
				// On met à jour l'argent ! :D
				if (joueurActuel == 1)
					sonJoueur1->setArgent(argentDisponible);
				else
					sonJoueur2->setArgent(argentDisponible);

				this->updateMenuHaut();
			}
		}
	}
}

void GJeu::affichagePorteeAttaque(Case* uneCase)
{
	// Si l'unité peut attaquer ce tour
	if (uneCase->getUnite()->getAttaque() == false)
	{

		// On place la case où se trouve l'unité en mode portée
		uneCase->setCiblePortee(true);

		// On défini l'unité qui lance l'attaque
		attaquante = uneCase->getUnite();

		// On passe à l'étape d'attaque d'unité ( étape 5 )
		etapeTour = 5;

		// On va devoir faire autant de tours que le nombre max de portée de chaque unité
		for (int i(1); i <= uneCase->getUnite()->getPortee(); i++)
		{
			// On fait une boucle qui va voir quelles sont les cases qu'il à qui il va falloir donner l'état "portée"
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				// On fait ce calcul pour toute les cases autour d'une case de deplacement
				if ((*it)->getCiblePortee() == true)
				{
					// Case de gauche
					if ((*it)->getPosX() != 0)
					{
						(*(it-1))->setCalculPortee(i);
					}

					// Case de droite
					if ((*it)->getPosX() != 11)
					{
						(*(it+1))->setCalculPortee(i);
					}

					// Case du bas
					if ((*it)->getPosY() != 7)
					{
						(*(it+12))->setCalculPortee(i);
					}

					// Case du haut
					if ((*it)->getPosY() != 0)
					{
						(*(it-12))->setCalculPortee(i);
					}
				}
			}

			// On gère l'affichage et l'état
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				// Si on a une portée supérieur à 0, c'est qu'on est accessible
				if ((*it)->getCalculPortee() != 0)
					(*it)->setCiblePortee(true);
			}
		}
	}

	this->updateMenuHaut();
}


void GJeu::attaquer(Unite* uneUnite)
{
	defendante = uneUnite;

	// Pour contenir le résultat des dégats
	double degatsJ1(0);
	double degatsJ2(0);

	// Pour la conversion en entier
	int degatsJoueur1(0);
	int degatsJoueur2(0);

	// On enregistre le fait que l'unité a déjà attaqué
	attaquante->setAttaque(true);

	// On calcul les dégats du joueur attaquant
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		// On récupère la couverture défensive du joueur attaqué
		if ((*it)->getUnite() == defendante)
		{
			degatsJ1 = (double(attaquante->getVie())/double(defendante->getVie()))*(double((attaquante->getDegats()))/(double((*(defendante->getDefense()))[attaquante->getType()]) * double((*it)->getCouverture())))*3;			
			degatsJoueur1 = degatsJ1;
			break;
		}
	}

	// On inflige les dégâts
	defendante->setVie(defendante->getVie() - degatsJoueur1);

	// On vérifie que le joueur attaqué est encore en vie
	if (defendante->getVie() > 0)
	{
		// On calcul les dégats du joueur défendant
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			// On récupère la couverture défensive du joueur attaquant
			if ((*it)->getUnite() == attaquante)
			{
				degatsJ2 = (double(defendante->getVie())/double(attaquante->getVie()))*(double((defendante->getDegats()))/(double((*(attaquante->getDefense()))[defendante->getType()]) * double((*it)->getCouverture())))*3;			
				degatsJoueur2 = degatsJ2;
				break;
			}
		}

		// On inflige les dégâts
		attaquante->setVie(attaquante->getVie() - degatsJoueur2);
	}

	// On enregistre les coordonnées pour l'affichage
	QPoint *posDefense = 0;
	QPoint *posAttaque = 0;

	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getUnite() == defendante)
				posDefense = new QPoint((*it)->getPosX(), (*it)->getPosY());
			else if ((*it)->getUnite() == attaquante)
				posAttaque = new QPoint((*it)->getPosX(), (*it)->getPosY());
		}

	// On applique tout les changements
	if (defendante->getVie() > 0)
		sesDegatsJoueur1->setText("- "+QString::number(degatsJoueur1));
	else
	{
		// On le supprime de la case
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getUnite() == defendante)
			{
				(*it)->setUnite(0);
				break;
			}
		}
		
		if (defendante == sonGeneralJ1)
		{
			this->finJeu(2);
			return;
		}

		else if (defendante == sonGeneralJ2)
		{
			this->finJeu(1);
			return;
		}

		else
		{
			delete defendante;
			sesDegatsJoueur1->setText("Mort");

			// Augmentation de la furie
			if (joueurActuel == 1)
				this->setFurie(1);	
			else
				this->setFurie(2);	
		}
	}

	if (attaquante->getVie() > 0)
		sesDegatsJoueur2->setText("- "+QString::number(degatsJoueur2));
	else
	{
		// On le supprime de la case
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getUnite() == attaquante)
			{
				(*it)->setUnite(0);
				break;
			}
		}

		if (attaquante == sonGeneralJ1)
		{
			this->finJeu(2);
			return;
		}

		else if (attaquante == sonGeneralJ2)
		{
			this->finJeu(1);
			return;
		}

		else
		{
			delete attaquante;
			sesDegatsJoueur2->setText("Mort");

			// Augmentation de la furie
			if (joueurActuel == 2)
				this->setFurie(1);	
			else
				this->setFurie(2);	
		}
	}

	// On met en place les affichages
	sesDegatsJoueur1->show();
	sesDegatsJoueur2->show();

	saCarte->addWidget(sesDegatsJoueur1, posDefense->y(), posDefense->x());
	saCarte->addWidget(sesDegatsJoueur2, posAttaque->y(), posAttaque->x());

	affichageDegats->start(1000);
}

// Réinitialisation de l'affichage
void GJeu::effacerDegats()
{
	affichageDegats->stop();

	sesDegatsJoueur1->hide();
	sesDegatsJoueur2->hide();

	saCarte->removeWidget(sesDegatsJoueur1);
	saCarte->removeWidget(sesDegatsJoueur2);

	this->majPortee();
	this->updateMenuHaut();
}

// Annulation des données concernant un combat
void GJeu::majPortee()
{
	attaquante = 0;
	defendante = 0;
	etapeTour = 2;

	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		// Si on a une portée supérieur à 0, c'est qu'on est accessible
		if ((*it)->getCiblePortee() == true)
		{
			(*it)->setCiblePortee(false);
			(*it)->setCalculPortee(0);
		}
	}

	this->updateMenuHaut();
}

// Capture d'un batiment
void GJeu::capturer(Case* uneCase)
{
	// Etape capture
	etapeTour = 6;

	// On passe l'attaque de l'unité qui capture à à true pour qu'il ne puisse pas effectuer d'autres actions
	uneCase->getUnite()->setAttaque(true);

	// Si la case n'appartient pas au joueur qui joue, on tente de capturer
	if (uneCase->getJoueur() != joueurActuel)
	{
		bool bonusFacture(false);

		// On vérifie qu'on est pas sous furie
		if ((joueurActuel == 1 && sonGeneralJ1->getFurieActivee() == true && sonGeneralJ1->getNom() == "Tom Assyeger") || (joueurActuel == 2 && sonGeneralJ2->getFurieActivee() == true && sonGeneralJ2->getNom() == "Tom Assyeger"))
			bonusFacture = true;

		// Si c'est un QG, on réduit seulement de 1
		if (uneCase->getVisuel() == 'q')
		{
			if (bonusFacture == true)
				uneCase->setPointsCapture(uneCase->getPointsCapture() - 2);
			else
				uneCase->setPointsCapture(uneCase->getPointsCapture() - 1);

			// Si ses points se retrouvent à 0, fin du jeu
			if (uneCase->getPointsCapture() <= 0)
				this->finJeu(joueurActuel);
		}

		else
		{
			if (bonusFacture == true)
				uneCase->setPointsCapture(uneCase->getPointsCapture() - 10);
			else
				uneCase->setPointsCapture(uneCase->getPointsCapture() - 5);
		}

		if (uneCase->getPointsCapture() != 0)
			afficherCapturer->setText("En cours...");

		else
		{
			afficherCapturer->setText("Bravo !");
			uneCase->setJoueur(joueurActuel);
			uneCase->setPointsCapture(10);
		}
	}

	// Sinon, si le bâtiment nous appartient, on le répare
	else
	{
		// On vérifie qu'on est pas déjà au max
		if (uneCase->getPointsCapture() != 10)
		{
			// Si c'est un QG, on augmente seulement de 1
			if (uneCase->getVisuel() == 'q')
			{
				uneCase->setPointsCapture(uneCase->getPointsCapture() + 1);

				// Si ses points se retrouvent à 0, fin du jeu
				if (uneCase->getPointsCapture() == 0)
					this->finJeu(joueurActuel);
			}

			else
				uneCase->setPointsCapture(uneCase->getPointsCapture() + 5);

			if (uneCase->getPointsCapture() != 10)
				afficherCapturer->setText("Reparation...");

			else
				afficherCapturer->setText("Fini !");
		}

		// Sinon, on affiche un message et on permet à l'unité de faire d'autres actions
		else
		{
			afficherCapturer->setText("Maximum !");
			uneCase->getUnite()->setAttaque(false);
		}
	}

	afficherCapturer->show();

	// On cherche la case sur laquelle on veut afficher le message
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		if ((*it) == uneCase)
		{
			saCarte->addWidget(afficherCapturer, (*it)->getPosY(), (*it)->getPosX());
			break;
		}
	}

	affichageCapturer->start(1000);
	this->updateMenuHaut();
}

// Fin de la capture
void GJeu::effacerCapture()
{
	affichageCapturer->stop();

	// On remet à 2
	etapeTour = 2;

	afficherCapturer->hide();

	saCarte->removeWidget(afficherCapturer);
	this->updateMenuHaut();
}

// Déplacement d'une unité par une unité de transport
void GJeu::choixCaseTransport(Case *uneCase)
{
	// Si on était en déplacement, on doit afficher les unités transportables
	if (etapeTour == 2)
	{
		// On vérifie que notre unité de transport peut encore faire une action
		if (uneCase->getUnite()->getAttaque() == false)
		{
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				// On cherche notre case
				if ((*it) == uneCase)
				{
					// Permet de savoir si une case est accessible
					bool accessible(false);

					// Case de gauche
					if ((*it)->getPosX() != 0)
					{
						// Si il a une unité transportable
						if ((*(it-1))->getUnite() != 0)
						{
							if ((*(it-1))->getUnite()->getType() != croiseur && (*(it-1))->getUnite()->getJoueur() == joueurActuel)
							{
								(*(it-1))->setCibleTransport(true);
								accessible = true;
							}
						}
					}

					// Case de droite
					if ((*it)->getPosX() != 11)
					{
						// Si il a une unité transportable
						if ((*(it+1))->getUnite() != 0)
						{
							if ((*(it+1))->getUnite()->getType() != croiseur && (*(it+1))->getUnite()->getJoueur() == joueurActuel)
							{
								(*(it+1))->setCibleTransport(true);
								accessible = true;
							}
						}
					}

					// Case du bas
					if ((*it)->getPosY() != 7)
					{
						// Si il a une unité transportable
						if ((*(it+12))->getUnite() != 0)
						{
							if ((*(it+12))->getUnite()->getType() != croiseur && (*(it+12))->getUnite()->getJoueur() == joueurActuel)
							{
								(*(it+12))->setCibleTransport(true);
								accessible = true;
							}
						}
					}

					// Case du haut
					if ((*it)->getPosY() != 0)
					{
						// Si il a une unité transportable
						if ((*(it-12))->getUnite() != 0)
						{
							if ((*(it-12))->getUnite()->getType() != croiseur && (*(it-12))->getUnite()->getJoueur() == joueurActuel)
							{
								(*(it-12))->setCibleTransport(true);
								accessible = true;
							}
						}
					}				
					
					if (accessible == true)
					{
						uneCase->getUnite()->setEnTransport(true);

						// Étape séléction de l'unité à déplacer
						etapeTour = 7;
					}

					break;
				}
			}
		}
	}

	// Si on est à l'étape de choix de l'unité à transporter
	else if (etapeTour == 7)
	{
		// Etape de déplacement d'une unité
		etapeTour = 8;

		// On ajoute l'unité dans l'unité qui la transport
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getUnite() != 0)
			{
				if ((*it)->getUnite()->getEnTransport() == true)
				{
					(*it)->getUnite()->setUniteTransportee(uneCase->getUnite());
					uneCase->setUnite(0);
					break;
				}
			}
		}

		// On cache l'image du choix de l'unité
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getCibleTransport() == true)
			{
				(*it)->setCibleTransport(false);
			}
		}
	}

	// Si on est à l'étape de déplacement d'une unité
	else if (etapeTour == 8)
	{
		// Etape de choix du dépôt de l'unité
		etapeTour = 10;

		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			// On cherche notre case
			if ((*it) == uneCase)
			{
				// Case de gauche
				if ((*it)->getPosX() != 0)
				{
					// Si il n'y a pas encore d'unité dessus
					if ((*(it-1))->getUnite() == 0)
					{
						// Si c'est pas une case de mer ( on ne peut pas déposer d'unité sur la mer ! )
						if ((*(it-1))->getVisuel() != 'e')
							(*(it-1))->setCibleTransport(true);
					}
				}

				// Case de droite
				if ((*it)->getPosX() != 11)
				{
					// Si il n'y a pas encore d'unité dessus
					if ((*(it+1))->getUnite() == 0)
					{
						// Si c'est pas une case de mer ( on ne peut pas déposer d'unité sur la mer ! )
						if ((*(it+1))->getVisuel() != 'e')
							(*(it+1))->setCibleTransport(true);
					}
				}

				// Case du bas
				if ((*it)->getPosY() != 7)
				{
					// Si il n'y a pas encore d'unité dessus
					if ((*(it+12))->getUnite() == 0)
					{
						// Si c'est pas une case de mer ( on ne peut pas déposer d'unité sur la mer ! )
						if ((*(it+12))->getVisuel() != 'e')
							(*(it+12))->setCibleTransport(true);
					}
				}

				// Case du haut
				if ((*it)->getPosY() != 0)
				{
					// Si il n'y a pas encore d'unité dessus
					if ((*(it-12))->getUnite() == 0)
					{
						// Si c'est pas une case de mer ( on ne peut pas déposer d'unité sur la mer ! )
						if ((*(it-12))->getVisuel() != 'e')
							(*(it-12))->setCibleTransport(true);
					}
				}				

				break;
			}
		}
	}

	// Si on est à l'étape de choix du déplacement
	else if (etapeTour == 10)
	{
		etapeTour = 2;

		// On cherche l'unité qui transporte
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getUnite() != 0)
			{
				if ((*it)->getUnite()->getEnTransport() == true)
				{
					(*it)->getUnite()->setEnTransport(false);
					uneCase->setUnite((*it)->getUnite()->getUniteTransportee());
					(*it)->getUnite()->setUniteTransportee(0);
					break;
				}
			}
		}

		// On réinitialise l'affichage
		for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
		{
			if ((*it)->getCibleTransport() == true)
			{
				(*it)->setCibleTransport(false);
			}
		}
	}

	this->updateMenuHaut();
}

// Méthode permettant d'annuler un transport d'unité
void GJeu::arretTransport(int nouvelleEtape)
{
	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		if ((*it)->getCibleTransport() == true)
		{
			(*it)->setCibleTransport(false);
		}

		if ((*it)->getUnite() != 0)
		{

			if (etapeTour == 8)
			{
				// On quitte l'état de transport si on y était
				if ((*it)->getUnite()->getEnTransport() == true)
					(*it)->getUnite()->setEnTransport(false);

				// On détruit l'unité transportée si il y en a
				if ((*it)->getUnite()->getUniteTransportee() != 0)
				{
					// On peut rien faire
					etapeTour = 100;

					// On vérifie que c'est pas un général
					if ((*it)->getUnite()->getUniteTransportee() == sonGeneralJ1)
						this->finJeu(2);
					else if ((*it)->getUnite()->getUniteTransportee() == sonGeneralJ2)
						this->finJeu(1);

					afficherTransportRate->show();
					affichageTransportRate->start(2000);

					delete (*it)->getUnite()->getUniteTransportee();
					(*it)->getUnite()->setUniteTransportee(0);
				}
			}
		}
	}
	
	etapeTour = nouvelleEtape;
	this->updateMenuHaut();
}

// Fin de l'affichage du message de destruction de l'unité lors d'un transport arrêté
void GJeu::finAffichageTransportRate()
{
	affichageTransportRate->stop();
	afficherTransportRate->hide();
}

// Cacher l'affichage du soin
void GJeu::cacherSoin()
{
	affichageSoin->stop();

	etapeTour = 2;

	for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
	{
		(*it)->setAffichageSoin(false);
	}
}

// Changer la furie du général
void GJeu::setFurie(int joueur)
{
	if (joueur == 1)
	{
		if (saFurieJ1->isVisible() == false)
		{
			sonGeneralJ1->setFurie(sonGeneralJ1->getFurie()+1);

			if (sonGeneralJ1->getIsFurie() == true)
				saFurieJ1->setVisible(true);	
		}

		else
		{
			sonGeneralJ1->setFurie(0);
			saFurieJ1->setVisible(false);
		}
	}

	else
	{
		if (saFurieJ2->isVisible() == false)
		{
			sonGeneralJ2->setFurie(sonGeneralJ2->getFurie()+1);

			if (sonGeneralJ2->getIsFurie() == true)
				saFurieJ2->setVisible(true);	
		}

		else
		{
			sonGeneralJ2->setFurie(0);
			saFurieJ2->setVisible(false);
		}
	}
}

// Lancer furie
void GJeu::lancerFurie()
{
	if (joueurActuel == 1 && sonGeneralJ1->getIsFurie() == true)
	{
		// Soin de toute les unités
		if (sonGeneralJ1->getNom() == "Infirmier Joel")
		{
			// On recherche toute les unités
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setVie(10);
				}
			}

			infoFurie->setText(infoFurie->text()+"Vos unites sont en pleine forme !</center>");
		}

		// Active le mode furie pour bouger
		else if (sonGeneralJ1->getNom() == "Envy Debouger")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites sont plus rapides !");

			// On recherche toute les unités pour augmenter leur PM
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setMouvements((*it)->getUnite()->getMouvements() + 7);
				}
			}
		}

		// Mode furie pour l'attaque
		else if (sonGeneralJ1->getNom() == "Bjorn Tapefjord")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites sont plus fortes !");

			// On recherche toute les unités
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setDegats((*it)->getUnite()->getDegats() + 5);
				}
			}
		}

		else if (sonGeneralJ1->getNom() == "Tom Assyeger")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites capturent plus vite !");
			sonGeneralJ1->setFurieActivee(true);
		}

		// Augmenter les sous
		else if (sonGeneralJ1->getNom() == "Piksou Maggazyne")
		{
			sonJoueur1->setArgent(sonJoueur1->getArgent()+15000);

			infoFurie->setText(infoFurie->text()+"Vous avez gagne 15 000 d'argent !</center>");
		}
		
		this->setFurie(1);
		infoFurie->show();
		affichageFurie->start(1000);
	}

	else if (joueurActuel == 2 && sonGeneralJ2->getIsFurie() == true)
	{
		// Soin de toute les unités
		if (sonGeneralJ2->getNom() == "Infirmier Joel")
		{
			// On recherche toute les unités
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setVie(10);
				}
			}

			infoFurie->setText(infoFurie->text()+"Vos unites sont en pleine forme !</center>");
		}

		// Active le mode furie pour bouger
		else if (sonGeneralJ2->getNom() == "Envy Debouger")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites sont plus rapides !");

			// On recherche toute les unités pour augmenter leur PM
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setMouvements((*it)->getUnite()->getMouvements() + 7);
				}
			}
		}

		// Mode furie pour l'attaque
		else if (sonGeneralJ2->getNom() == "Bjorn Tapefjord")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites sont plus fortes !");

			// On recherche toute les unités
			for (std::vector<Case*>::iterator it = saCarte->getCases()->begin(); it != saCarte->getCases()->end(); it++)
			{
				if ((*it)->getUnite() != 0)
				{
					if ((*it)->getUnite()->getJoueur() == joueurActuel)
						(*it)->getUnite()->setDegats((*it)->getUnite()->getDegats() + 5);
				}
			}
		}

		else if (sonGeneralJ2->getNom() == "Tom Assyeger")
		{
			infoFurie->setText(infoFurie->text()+"Vos unites capturent plus vite !");
			sonGeneralJ2->setFurieActivee(true);
		}

		// Augmenter les sous
		else if (sonGeneralJ2->getNom() == "Piksou Maggazyne")
		{
			sonJoueur2->setArgent(sonJoueur1->getArgent()+15000);

			infoFurie->setText(infoFurie->text()+"Vous avez gagne 15 000 d'argent !</center>");
		}

		this->setFurie(2);
		infoFurie->show();
		affichageFurie->start(1000);
	}
}

// Définition des affichages de fin de jeu
void GJeu::finJeu(int unJoueur)
{
	etapeTour = 15;

	if (unJoueur == 1)
		saFinJeu->setText("<center>"+sonJoueur1->getNom()+" a gagne la partie !</center>");
	else if (unJoueur == 2)
		saFinJeu->setText("<center>"+sonJoueur2->getNom()+" a gagne la partie !</center>");
	else if (unJoueur == 3)
		saFinJeu->setText("<center>Egalite ! Nombre de tour maximum atteint</center>");

	affichageFinJeu->start(5);
}

// Affichage de la furie
void GJeu::afficherFurie()
{
	affichageFurie->stop();

	infoFurie->setText("<center>Furie Activee !<br /><br />");
	infoFurie->hide();
}

// Affichage de la fin
void GJeu::fin()
{
	if (saFinJeu->geometry().y() != 0)
		saFinJeu->move(0, saFinJeu->geometry().y() + 5);
	else
		affichageFinJeu->stop();
}

int GJeu::getEtapeTour()
{
	return etapeTour;
}

Carte* GJeu::getCarte()
{
	return saCarte;
}

QLabel* GJeu::getCurseur()
{
	return sonCurseur;
}

int GJeu::getJoueurActuel()
{
	return joueurActuel;
}

GJeu::~GJeu()
{
	saCarte->removeWidget(sonCurseur);	
	delete saCarte;
}
