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


#include "interface.h"

int interfaceInitialisation(interfaceT * interface, int fond)
	{
	assert(SDL_Init(SDL_INIT_VIDEO) == 0);

	(*interface).continu = true;
	(*interface).fond = fond;


		// Création de la fenêtre
					//  SDL_WINDOW_SHOWN || SDL_WINDOW_RESIZABLE
	(*interface).fenetre = SDL_CreateWindow("Simulateur d'onde", SDL_WINDOWPOS_UNDEFINED, 
							SDL_WINDOWPOS_UNDEFINED, DIMENSION_X, DIMENSION_Y, 
							SDL_WINDOW_SHOWN);
	if(NULL == (*interface).fenetre)
		fprintf(stderr, "interfaceInitialisation : Erreur SDL_CreateWindow : %s.", SDL_GetError());


		// Création du rendu

	(*interface).rendu = SDL_CreateRenderer((*interface).fenetre, -1 , 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(NULL == (*interface).rendu)
		fprintf(stderr, "interfaceInitialisation : Erreur SDL_CreateRenderer : %s.", SDL_GetError());

	return 0;
	}

int interfaceNettoyage(interfaceT * interface)
	{
	int fond = (*interface).fond;
	SDL_SetRenderDrawColor((*interface).rendu, fond, fond, fond, 0);//SDL_ALPHA_OPAQUE
	SDL_RenderClear((*interface).rendu);
	SDL_SetRenderDrawColor((*interface).rendu, 255-fond, 255-fond, 255-fond, 0);//SDL_ALPHA_OPAQUE
	return 0;
	}

int interfaceMiseAJour(interfaceT * interface)
	{
	SDL_RenderPresent((*interface).rendu);
	return 0;
	}

int interfaceDestruction(interfaceT * interface)
	{
	SDL_DestroyRenderer((*interface).rendu);
	SDL_DestroyWindow((*interface).fenetre);
	SDL_Quit();
	return 0;
	}
