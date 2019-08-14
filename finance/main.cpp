#include "random1.h"
#include "simpleMC1.h"
#include "gaussNumerical.h"
#include "analyticalFormulas.h"
#include <iostream>
#include <array>

using namespace std;

int main()
{
	const unsigned int N = 10;
	array<double, N> v = {};
	array<double, N> s = v;
	for (size_t i = 0; i < v.size() - 1; i++)
	{
		v[i + 1] = getZBoxMuller();
		s[i + 1] = s[i] + v[i+1];
	}

	for (auto it = v.begin(); it != v.end(); ++it)
		cout << *it << endl;

	for (auto it = s.begin(); it != s.end(); ++it)
		cout << *it << endl;

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
