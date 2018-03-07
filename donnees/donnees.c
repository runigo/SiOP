/*
Copyright février 2018, Stephan Runigo
runigo@free.fr
SiOP est un simulateur d'ondes progressive en 2 dimensions. Ce 
logiciel est un programme informatique servant à simuler l'équation de 
propagation d'une onde en deux dimensions et à donner une représentation 
graphique de cette onde. 
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "donnees.h"

	//		Valeurs initiales des données physiques du simulateur,
	//						et création du système

	//		Valeur initiale et création du graphe

	//		Initialisation de la SDL


int donneesSysteme(systemeT * systeme, optionsT * options);
int donneesGraphe(grapheT * graphe, optionsT * options);

int donneesControleur(controleurT * controleur)
	{

	(*controleur).options.sortie = 0;	// Sortie de SiCP si > 0

		fprintf(stderr, " Initialisation du système\n");
	donneesSysteme(&(*controleur).systeme, &(*controleur).options);

		fprintf(stderr, " Initialisation du graphe\n");
	donneesGraphe(&(*controleur).graphe, &(*controleur).options);

		fprintf(stderr, " Initialisation SDL\n");
	interfaceInitialisation(&(*controleur).interface, (*controleur).options.fond);

	return 0;
	}

int donneesGraphe(grapheT * graphe, optionsT * options)
	{
	(*graphe).rouge=20;
	(*graphe).bleu=150;
	(*graphe).vert=200;
	(*graphe).fond=(*options).fond;	//	Couleur du fond
	return 0;
	}

int donneesoptionsT(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).fond=240;		// couleur du fond de l'affichage
	(*options).mode = 1;	// -1 : Wait, 1 : Poll
	(*options).pause=25;		// temps de pause SDL en ms

	(*options).duree = 100;	// 100 : temps réèl. Voir optionsT.c

	(*options).equation=3;	// 1 : pendule, 2 : linéarisation,
							//	 3 : corde, 4 : dioptre

	(*options).sensibilite=0.11;	// sensibilité des commandes
	(*options).augmente = 1+(*options).sensibilite;	// sensibilité des commandes
	(*options).diminue = 1/(*options).augmente;	// sensibilité des commandes

	(*options).dt=0.0006;	// discrétisation du temps
	(*options).moteur=3;	// État du moteur
							// 25 images par seconde, SDL_Delay(30);
							// dt*duree = 0.004

	(*options).dephasage=0*PI;

	(*options).frequence=11.1;	// Fréquence du générateur de signaux

	(*options).dissipation=0.0;	// Fréquence du générateur de signaux

	(*options).thread=0;		// 0 : un processus, 1 : deux threads

	return 0;
	}

int donneesSysteme(systemeT * systeme, optionsT * options)
	{

		// Initialisation du moteurs

	(*systeme).moteur.dt = (*options).dt;	// discrétisation du temps
	//(*systeme).moteur.horloge = 0.0;
	(*systeme).moteur.chrono = 0.0;

	(*systeme).moteur.courant=15.0;		// Mémoire courant Josephson si = 0
	(*systeme).moteur.josephson=0.0;

	(*systeme).moteur.generateur = (*options).moteur;	// éteint, sinus, carre, impulsion
	(*systeme).moteur.amplitude=0.57;		// Amplitude du générateur de signaux
	(*systeme).moteur.frequence=(*options).frequence;	// Fréquence du générateur de signaux
	(*systeme).moteur.phi=0;


		// Caractéristique de la chaîne
	(*systeme).libreFixe = 2;	// 0 periodique, 1 libre, 2 fixe
	(*systeme).equation = (*options).equation;	// 1 : pendule pesant
												// 2 : linéarisation
												// 3 : corde
												// 4 : dioptre

		// Paramètres physiques
	(*systeme).gravitation = 9.81;
	(*systeme).masseGauche = 1.0;
	(*systeme).masseDroite = 3.0;
	(*systeme).longueur = 9.81/4/PI/PI; // = 25 cm => période = 1 s
	(*systeme).dissipation = (*options).dissipation;
	(*systeme).couplage = 100321.1;
	(*systeme).dephasage = (*options).dephasage;




	//if((*systeme).equation == 3 || (*systeme).equation == 4)
	//	{		 // donneeCorde;
	//	(*systeme).couplage = (*systeme).couplage * 10.0;
	//	(*systeme).gravitation = 0.0;
	//	(*systeme).libreFixe = 2;
	//	(*systeme).moteur.josephson=0.0;
	//	}

	systemeInitialise(systeme);
	changeConditionsLimites(systeme, (*systeme).libreFixe);
	// fichier.c
	//
	//fichierLecture(systeme);

	return 0;
	}

//////////////////////////////////////////////////////////////////////////
