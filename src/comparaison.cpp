#include "comparaison.h"
#include "jouer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void saisir_mot_dictionnaire(std::istream& is, char* mot) {
    char tmp[MAX_LETTRES];
    is >> setw(MAX_LETTRES) >> tmp;
	for (int lettre = 0; lettre < strlen(tmp); lettre++) {
		mot[lettre] = tmp[lettre];
	}
}

bool mot_existe_dans_dictionnaire(char *mot)
{
	ifstream dictionnaire("ods4.txt");
	bool trouve = false;
	if (!dictionnaire) {
		cerr << "Probleme lors de l'ouverture du fichier.";
		return trouve;
	}
	for (int lettre = 0; lettre < strlen(mot); lettre++) {
		mot[lettre] = toupper(mot[lettre]);
	}
	char mot_dictionnaire[MAX_LETTRES];
	while (dictionnaire.getline(mot_dictionnaire, MAX_LETTRES))
	{
		if (strcmp(mot_dictionnaire, mot) == 0) {
			trouve = true;
		}
	}
	return trouve;
}

unsigned int nb_mots_dictionnaire() {
	ifstream dictionnaire("ods4.txt");
	if (!dictionnaire) {
		cerr << "Probleme lors de l'ouverture du fichier." << endl;
		return 0;
	}
	char mot_dictionnaire[MAX_LETTRES];
	unsigned int nb_mots = 0;
	while (dictionnaire.getline(mot_dictionnaire, sizeof(dictionnaire))) {
		nb_mots++;
	}
	return nb_mots;
}

char** mot_coherent(char* debut_mot, unsigned int longueur_debut_mot, unsigned int* nb_mots_coherents, unsigned int nb_mots_dictionnaire) {
	const unsigned int MAX_MOTS = nb_mots_dictionnaire;
	char** mots_coherents = new char* [MAX_MOTS];
	ifstream dictionnaire("ods4.txt");
	char ligne[MAX_LETTRES];
	*nb_mots_coherents = 0;
	while (dictionnaire.getline(ligne, MAX_MOTS)) {
		ligne[strlen(ligne) - 1] = '\0';
		if (strncmp(ligne, debut_mot, longueur_debut_mot) == 0) {
			if (*nb_mots_coherents < MAX_MOTS) {
				mots_coherents[*nb_mots_coherents] = new char[MAX_LETTRES];
				strcpy(mots_coherents[*nb_mots_coherents], ligne);
				(*nb_mots_coherents)++;
			}
		}
	}
	dictionnaire.close();
	return mots_coherents;
}