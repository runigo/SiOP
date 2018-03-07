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

#include "projection.h"

void projectionSystemeGraphe(systemeT * systeme, grapheT * graphe)
	{
	//		Projette le système sur le graphe 
	int i, j;
	double max, min;

	// Recherche du maximum et du minimum

	max = (*systeme).pendule[0][0].nouveau;
	min = (*systeme).pendule[0][0].nouveau;

	for(i=0;i<DIMENSION_X;i++)
		{
		for(j=0;j<DIMENSION_X;j++)
			{
			if((*systeme).pendule[i].nouveau > max)
				{
				max = (*systeme).pendule[i][j].nouveau;
				}
			if((*systeme).pendule[i].nouveau < min)
				{
				min = (*systeme).pendule[i][j].nouveau;
				}
			}
		}

	// Amplitude des valeurs à dessiner
	amplitude = max-min;

	// Projection de la fonction
	for(i=0;i<DIMENSION_X;i++)
		{
		for(j=0;j<DIMENSION_Y;j++)
			{
			(*graphe).amplitude[i][j] = (int)(((*systeme).pendule[i][j].nouveau - min )*255/amplitude);
			}
		}
	return;
	}

////////////////////////////////////////////////////////////////////////////////////
