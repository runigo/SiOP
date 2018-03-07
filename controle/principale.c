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

#include "principale.h"

int main(int nb, char *opt[])
	{
	controleurT controleur;

	fprintf(stderr, "\nInitialisations des options\n");
	if(donneesOptions(&controleur.options)==0)
		{
		fprintf(stderr, "Traitement des options de la ligne de commande\n");
		optionsTraitement(&controleur.options, nb, opt);
		}

	fprintf(stderr, "Initialisations\n");
	if(donneesControleur(&controleur)==0)
		{
		fprintf(stderr, "Simulation graphique du système, \n");
		controleurSimulationGraphique(&controleur);
		}
	else
		{
		fprintf(stderr, "Problème lors de l'initialisation\n");
		}

	//fprintf(stderr, "Calcul énergétique\n");
	//observableAfficheEnergie(&controleur.system);

	fprintf(stderr, "\nSortie de SiOP\n");

	return 0;
	}

//////////////////////////////////////////////////////////////////
/*
SiCF 1.1
		fprintf(stderr, "Simulation graphique du système, \n");
		if(control.option.thread==1)
			{
			//fprintf(stderr, "deux threads\n");
			processusSimulationGraphique(&control);
			}
		else
			{
			//fprintf(stderr, "processus unique\n");
			controleurSimulationGraphique(&control);
			}
*/
