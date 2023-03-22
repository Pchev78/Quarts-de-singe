#include "jouer.h"


char lettre_aleatoire() {
	char ch = 'A' + rand() % LONGUEUR_ALPHABET; // On prend A et on lui ajoute un nombre aléatoire entre 0 (correspondant à A) et LONGUEUR_ALPHABET (correspondant à Z)
	return ch;
}

char lettre_coherente(char* mot, char* mot_choisi, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche) {
	unsigned int nb_mots_coherents = 0, nb_mots_dico = nb_mots_dictionnaire();
	char** mots_coherents = mot_coherent(mot, longueur_mot, &nb_mots_coherents, nb_mots_dico);
	if (nb_mots_coherents == 0) { // Si le robot n'a pas aucun mot possible à saisir, il demande au joueur précédent à quel mot il pense
		cout << '?' << endl;
		demander_mot_joueur_precedent(conteneur_joueurs, *joueur_courant, mot_choisi);
		*fin_manche = true;
	}
	else {
		unsigned int nb_aleatoire = rand() % nb_mots_coherents;
		char* mot_renvoye = mots_coherents[nb_aleatoire]; // Le robot pioche aléatoirement un mot parmi la liste des mots cohérents
		strcpy(mot_choisi, mot_renvoye);
		return mot_renvoye[longueur_mot];
	}
	return '!'; // S'il y a eu un problème, le robot abandonne
}

void robot(char* mot_a_completer, char* mot_choisi, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche) {
	srand(time(NULL));
	if (longueur_mot  == 0) { // Si le robot doit saisir la première lettre du mot
		mot_a_completer[longueur_mot] = lettre_aleatoire();
	}
	else {
		mot_a_completer[longueur_mot] = lettre_coherente(mot_a_completer, mot_choisi, longueur_mot, conteneur_joueurs, joueur_courant, fin_manche);
	}
	cout << endl;
}
