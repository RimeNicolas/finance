#include "random1.h"
#include "simpleMC1.h"
#include "gaussNumerical.h"
#include "analyticalFormulas.h"
#include <iostream>

int main()
{
    double expiry(1.0), strike(50.0), spot(50.0), vol(0.1), r(0.01);
	unsigned long nbPaths(1000000);
	std::cout << simpleMC1(expiry, strike, spot, vol, r, nbPaths) << std::endl;
	
	std::cout << priceCall(expiry, strike, spot, vol, r, nbPaths) << std::endl;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
