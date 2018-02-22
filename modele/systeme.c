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

#include "systeme.h"

void systemeInitialisePendule(systemeT * systeme);
void systemeCouplage(systemeT * systeme);
void systemeInertie(systemeT * systeme);
void systemeIncremente(systemeT * systeme);
//void systemeInitialiseLimiteInfini(systemeT * systeme);
//void systemeChangeLimite(systemeT * systeme);
//void systemeFormeDioptre(systemeT * systeme, float facteur);
float systemeMoteur(systemeT * systeme);

// normalise le premier pendule
void systemeJaugeZero(systemeT * systeme);
// normalise la moyenne du système à zéro
void systemeJauge(systemeT * systeme);
double systemeMoyenne(systemeT * systeme);



/*----------------JAUGE ET NORMALISATION-------------------*/

// normalise le premier pendule
void systemeJaugeZero(systemeT * systeme)
	{
	float position = (*systeme).pendul[0][0].nouveau;
	float jauge;

	//fprintf(stderr, "\nEntrée systemeJaugeZero, position = %f\n", position);
	//fprintf(stderr, "\nEntrée systemeJaugeZero, position/DEUXPI = %f\n", position/DEUXPI);

	jauge = -DEUXPI*(int)(position/DEUXPI);
	if(jauge>PI || jauge<PI)
		{
		int i, j;
		for(i=1;i<DIMENSION_X;i++)
			{
			for(j=0;i<DIMENSION_Y;j++)
				{
				penduleJauge(&(*systeme).pendul[i][j], jauge);
				}
			}
		for(j=1;i<DIMENSION_Y;j++)
			{
			penduleJauge(&(*systeme).pendul[0][j], jauge);
			}
		}


	//fprintf(stderr, "Moyenne = %f\n", systemeMoyenne(systeme));
	//fprintf(stderr, "systemeJaugeZero, sortie\n\n");
	return;
	}


// normalise la moyenne du système à zéro
void systemeJauge(systemeT * systeme)
	{
	double moyenne = systemeMoyenne(systeme);
	if(moyenne>(MOYENNE_MAX))
		{
		int i, j;
		for(i=0;i<DIMENSION_X;i++)
			{
			for(j=0;i<DIMENSION_Y;j++)
				{
				penduleJauge(&(*systeme).pendul[i][j], -MOYENNE_MAX);
				}
			}
		fprintf(stderr, "Moyenne = %f\n", moyenne);
		}
	if(moyenne<(-MOYENNE_MAX))
		{
		int i, j;
		for(i=0;i<DIMENSION_X;i++)
			{
			for(j=0;i<DIMENSION_Y;j++)
				{
				penduleJauge(&(*systeme).pendul[i][j], MOYENNE_MAX);
				}
			}
		fprintf(stderr, "Moyenne = %f\n", moyenne);
		}
	return;
	}

double systemeMoyenne(systemeT * systeme)
	{
	double moyenne = 0.0;

	int i, j;
	for(i=0;i<DIMENSION_X;i++)
		{
		for(j=0;i<DIMENSION_Y;j++)
			{
			moyenne = moyenne + (*systeme).pendul[i][j].nouveau;
			}
		}

	return ( moyenne / ( DIMENSION_X * DIMENSION_Y ) );
	}

void systemeInitialise(systemeT * systeme)
	{
	// Initialisation des pendules
	systemeInitialisePendule(systeme);

	// Initialise les conditions aux limites
	//systemeChangeLimite(systeme);

	// Extrémité absorbante
	//systemeInitialiseLimiteInfini(systeme);
/*
	// Dissipation initiale Corde
	if((*systeme).equation == 3 || (*systeme).equation == 4)
		{
		changeFormeDissipation(systeme, 2);
		}
*/

	// Masse initiale Dioptre
/*	if((*systeme).equation == 4)
		{
	int i;
			for(i=N/2;i<N;i++)
				{
				penduleReinitialiseMasse(&(*systeme).pendul[i], (*systeme).masseDroite, (*systeme).moteur.dt);
				}
		}
	//printf("Systeme initialisé\n");
*/
	return;
	}

void systemeEvolution(systemeT * systeme, int duree)
	{//	Fait évoluer le système pendant duree * dt
	int i;
	for(i=0;i<duree;i++)
		{
		systemeCouplage(systeme);
		systemeInertie(systeme);
		systemeIncremente(systeme);
		}
	systemeJaugeZero(systeme);
	return;
	}

void systemeInitialisePendule(systemeT * systeme)
	{
	float m=(*systeme).masseGauche;
	float l=(*systeme).longueur;
	float d=(*systeme).dissipation;
	float c=(*systeme).couplage;
	float g=(*systeme).gravitation;
	float t=(*systeme).moteur.dt;

	int i, j;

	for(i=0;i<N;i++)
		{
		for(j=0;i<DIMENSION_Y;j++)
			{
			penduleInitialiseParametre(&(*systeme).pendul[i][j], m, l, d);
			penduleInitialiseExterieur(&(*systeme).pendul[i][j], c, g, t);
			penduleInitialisePosition(&(*systeme).pendul[i][j], 0.0, 0.0);
			penduleInitialiseDephasage(&(*systeme).pendul[i][j], 0.0);
			}
		}

	penduleInitialiseDephasage(&(*systeme).pendul[0][0], (*systeme).dephasage);

	return;
	}
/*
void systemeInitialiseLimiteInfini(systemeT * systeme)
	{
	int i;

	for(i=0;i<N;i++)
		{
		(*systeme).pendul[i].dissipation = 0.0;
		}

	for(i=1;i<N/6;i++)
		{
		(*systeme).pendul[N-i].dissipation = 10*(1.0-i/(float)(N/6));
		}


	return;
	}
*/
void systemeCouplage(systemeT * systeme)
	{//	Calcul des forces de couplage

	int libreFixe = (*systeme).libreFixe;

	int i, j;
	for(i=1;i<(N-1);i++)
		{
		penduleCouplage(&(*systeme).pendul[i-1], &(*systeme).pendul[i], &(*systeme).pendul[i+1]);
		}

	if(libreFixe!=0) // Limites non périodique
		{
		penduleCouplage(&(*systeme).pendul[0], &(*systeme).pendul[0], &(*systeme).pendul[1]);
		penduleCouplage(&(*systeme).pendul[N-2], &(*systeme).pendul[N-1], &(*systeme).pendul[N-1]);
		}
	else // Limites périodiques
		{
		penduleCouplage(&(*systeme).pendul[N-1], &(*systeme).pendul[0], &(*systeme).pendul[1]);
		penduleCouplage(&(*systeme).pendul[N-2], &(*systeme).pendul[N-1], &(*systeme).pendul[0]);
		}

	return;
	}

void systemeInertie(systemeT * systeme)
	{//	Principe d'inertie applique au système

  // Version SiCF-1.0, extrémité moteur fixe.

	//int equation = (*systeme).equation;
	//int libreFixe = (*systeme).libreFixe;
	//int etatMoteur = (*systeme).moteur.generateur;
	float courantJosephson = (*systeme).moteur.josephson;

	//float moteur = moteursGenerateur(&(*systeme).moteur);

				// Cas du premier et du dernier pendule

			//  0 : periodiques 1 : libres, 2 : fixes, 3 libre-fixe, 4 fixe-libre

/*	if (libreFixe==0 || libreFixe==1 || libreFixe==3)
		{
		penduleInertie(&(*systeme).pendul[0], equation, courantJosephson);
		}
	else
		{
		penduleInitialisePosition(&(*systeme).pendul[0], 0.0, 0.0);
		}
	if (libreFixe==0 || libreFixe==1 || libreFixe==4)
		{
		penduleInertie(&(*systeme).pendul[N-1], equation, courantJosephson);
		}
	else
		{
		penduleInitialisePosition(&(*systeme).pendul[N-1], (*systeme).pendul[N-1].dephasage, (*systeme).pendul[N-1].dephasage);
		}

	if(etatMoteur!=0) // moteur allumé
		{
		penduleInitialisePosition(&(*systeme).pendul[0], moteur, moteur);
		}
*/	/*else // SiCF-1.0 : extrémité moteur fixe
		{
		penduleInitialisePosition(&(*systeme).pendul[0], 0, 0);
		}*/

						// Cas des autres pendules
	int i, j;
	for(i=1;i<(DIMENSION_X-1);i++)
		{
		for(j=1;i<(DIMENSION_Y-1);j++)
			{
			penduleInertie(&((*systeme).pendul[i][j]), (*systeme).equation, courantJosephson);
			}
		}
	return;
	}

void systemeIncremente(systemeT * systeme)
	{//	incremente l'horloge, l'ancien et l'actuel etat du système

	//(*systeme).moteur.horloge = (*systeme).moteur.horloge + (*systeme).moteur.dt;
	(*systeme).moteur.chrono = (*systeme).moteur.chrono + (*systeme).moteur.dt;

	int i, j;
	for(i=1;i<(DIMENSION_X-1);i++)
		{
		for(j=1;i<(DIMENSION_Y-1);j++)
			{
			penduleIncremente(&((*systeme).pendul[i][j]));
			}
		}

	return;
	}

void systemeAffiche(systemeT * systeme)
	{// Affichage de la position et des parametres
	printf("\nParamètres système\n");
	printf("	Couplage entre les pendules	%4.3f\n", (*systeme).couplage);
	printf("	Longueur des pendules		%4.3f\n",(*systeme).longueur);
	printf("	Intensité de la gravitation	%4.3f\n",(*systeme).gravitation);
	printf("	Masse des pendules à droite : %4.3f, à gauche : %4.3f\n",(*systeme).masseDroite,(*systeme).masseGauche);
	printf("	Masse des pendules \n");
	/*	int equation;		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4
		float dephasage;	//	déphasage entre les limites
		int libreFixe;		// 0 : périodiques 1 : libres, 2 : fixes, 
	*/					//		3 libre-fixe, 4 fixe-libre
	return;
	}

//////////////////////////////////////////////////////////////////////
