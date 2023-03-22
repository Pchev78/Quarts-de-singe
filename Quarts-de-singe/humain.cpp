#include "jouer.h"

void humain(char* mot_a_completer, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche, char* mot_choisi) {
	char lettre;
	cin >> lettre;
	cin.ignore(MAX_LETTRES, '\n');
	lettre = toupper(lettre);
	if (lettre == '!') {
		cout << "le joueur " << joueur_courant->pos + 1 << joueur_courant->nature<< " abandonne la manche et prend un quart de singe" << endl;
		joueur_courant->qds += 0.25;
		*fin_manche = true;
		return;
	} else if (lettre == '?') {
		demander_mot_joueur_precedent(conteneur_joueurs, *joueur_courant, mot_choisi);
		*fin_manche = true;
		return;
	}
	mot_a_completer[longueur_mot] = lettre;
	return;
}