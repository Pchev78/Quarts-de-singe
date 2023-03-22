#include "jouer.h"


void initialiser_tab_joueurs(ConteneurTDE* conteneur_joueurs) {
	conteneur_joueurs->tab_joueurs = new Joueur[MAX_LETTRES];
}

void lancer_jeu() {
	ConteneurTDE conteneur_joueurs = saisir_joueurs();
	Joueur joueur_commence = conteneur_joueurs.tab_joueurs[0];
	while(!joueur_a_4_qds(conteneur_joueurs)) {
		joueur_commence = lancer_manche(&conteneur_joueurs, joueur_commence);
		afficher_qds(conteneur_joueurs);
	}
	cout << "La partie est finie" << endl;
}

Joueur lancer_manche(ConteneurTDE* conteneur_joueurs, Joueur premier_joueur) {
	char mot_joueurs[MAX_LETTRES], mot_choisi[MAX_LETTRES];
	// On initialise les tableaux de char
	for (int n = 0; n < MAX_LETTRES; n++) {
		mot_joueurs[n] = '\0';
		mot_choisi[n] = '\0';
	}
	bool fin_manche = false;
	unsigned int num_tour = 0;
	while (num_tour < MAX_LETTRES) {
		for (int i = 0; i < conteneur_joueurs->nb_joueurs; ++i) {
			int pos_joueur_courant = (premier_joueur.pos + i) % conteneur_joueurs->nb_joueurs;
			Joueur* joueur_courant = &conteneur_joueurs->tab_joueurs[pos_joueur_courant];
			afficher_joueur(*joueur_courant);
			cout << "(";
			for (unsigned int caractere = 0; caractere < num_tour; caractere++) {
				cout << mot_joueurs[caractere];
			}
			cout << ") > ";
			if (joueur_courant->nature == 'H') {
				humain(mot_joueurs, num_tour, conteneur_joueurs, joueur_courant, &fin_manche, mot_choisi);
			}
			else if (joueur_courant->nature == 'R') {
				strcpy(mot_choisi, mot_joueurs);
				robot(mot_joueurs, mot_choisi, num_tour, conteneur_joueurs, joueur_courant, &fin_manche);
			}
			if (num_tour > 1 && mot_existe_dans_dictionnaire(mot_joueurs)) {
				joueur_courant->qds += 0.25;
				cout << "le mot " << mot_joueurs << " existe, " << joueur_courant->pos + 1 << joueur_courant->nature << " prend un quart de singe" << endl;
				fin_manche = true;
			}
			if (fin_manche == true) {
				return *joueur_courant;
			}
			num_tour++;			
		}
	}
}

void ajouter_joueur(ConteneurTDE& conteneur_joueurs, unsigned int indice_joueur, const Joueur& joueur_a_ajouter) {
	if (indice_joueur >= conteneur_joueurs.nb_joueurs) {
		unsigned int newTaille = (indice_joueur + 1);
		Joueur* newT = new(nothrow) Joueur[newTaille];		
		for (int j = 0; j < conteneur_joueurs.nb_joueurs; ++j) { // On recopie les éléments déjà stockés
			newT[j] = conteneur_joueurs.tab_joueurs[indice_joueur];
		}
		delete[] conteneur_joueurs.tab_joueurs; // On désalloue l'ancien tableau
		conteneur_joueurs.tab_joueurs = newT;
		conteneur_joueurs.nb_joueurs= newTaille;
	}
	conteneur_joueurs.tab_joueurs[indice_joueur] = joueur_a_ajouter;
}

ConteneurTDE saisir_joueurs() {
	ConteneurTDE conteneur_joueurs;
	initialiser_tab_joueurs(&conteneur_joueurs);
	char entree_joueurs[MAX_LETTRES];
	cout << "Veuillez preciser les joueurs participant au jeu : H pour Humain ou R pour Robot" << endl;
	cin >> entree_joueurs;
	if (strlen(entree_joueurs) < MIN_JOUEURS) {
		cerr << "Probleme : Pas assez de joueurs" << endl;
		return conteneur_joueurs;
	}
	
	unsigned int compteur_joueurs = 0;
	
	for (unsigned int i = 0; i < strlen(entree_joueurs); i++)
	{
		entree_joueurs[i] = toupper(entree_joueurs[i]);
		Joueur joueur_courant;
		if (entree_joueurs[i] == 'H') {
			joueur_courant.nature = 'H';
			compteur_joueurs += 1;
		}
		else if (entree_joueurs[i] == 'R') {
			joueur_courant.nature = 'R';
			compteur_joueurs += 1;
		}
		joueur_courant.pos = i;
		ajouter_joueur(conteneur_joueurs, i, joueur_courant);
	}
	if (compteur_joueurs != strlen(entree_joueurs))
	{
		cerr << "Probleme : au moins une lettre saisie n'est pas correcte" << endl;
	}
	conteneur_joueurs.nb_joueurs = compteur_joueurs;
	return conteneur_joueurs;
}

void afficher_qds(ConteneurTDE conteneur_joueurs) {
	bool premier_joueur = true;
	for (int i = 0; i < conteneur_joueurs.nb_joueurs; i++) {
		Joueur joueur_courant = conteneur_joueurs.tab_joueurs[i];
		cout << joueur_courant.pos + 1 << joueur_courant.nature << " : " << joueur_courant.qds;
		if (joueur_courant.pos + 1 < conteneur_joueurs.nb_joueurs) {
			cout << "; ";
		}
	}
	cout << endl;
}

void afficher_joueur(Joueur joueur_courant) {
	cout << joueur_courant.pos + 1 << joueur_courant.nature << ", ";
}

void demander_mot_joueur_precedent(ConteneurTDE* conteneur_joueurs, Joueur joueur_courant, char* mot_choisi) {
	Joueur joueur_precedent;
	int pos_joueur_precedent = 0;
	if (joueur_courant.pos - 1 < 0) {
		pos_joueur_precedent = conteneur_joueurs->nb_joueurs - 1;
	} 
	else {
		pos_joueur_precedent = joueur_courant.pos - 1;
	}
	joueur_precedent = conteneur_joueurs->tab_joueurs[pos_joueur_precedent];
	
	char mot[MAX_LETTRES];
	afficher_joueur(joueur_precedent);
	cout << "saisir le mot > ";
	if (joueur_precedent.nature == 'H') {
		cin >> mot;
	}
	else if (joueur_precedent.nature == 'R') {
		strcpy(mot, mot_choisi);
	}
	if (!mot_existe_dans_dictionnaire(mot) || strlen(mot) <= MIN_LETTRES) {
		cout << "le mot " << mot << " n'existe pas, le joueur " << joueur_precedent.pos + 1 << joueur_precedent.nature << " prend un quart de singe" << endl;
		conteneur_joueurs->tab_joueurs[joueur_precedent.pos].qds += 0.25;
	}
	
	else {
		cout << "le mot " << mot << " existe, le joueur " << joueur_courant.pos + 1 << joueur_courant.nature << " prend un quart de singe" << endl;
		conteneur_joueurs->tab_joueurs[joueur_courant.pos].qds += 0.25;
	}
}

bool joueur_a_4_qds(const ConteneurTDE& conteneur_joueurs) {
	for (int pos_joueur = 0; pos_joueur < conteneur_joueurs.nb_joueurs; pos_joueur++) {
		Joueur joueur_courant = conteneur_joueurs.tab_joueurs[pos_joueur];
		if (joueur_courant.qds >= 1) {
			return true;
		}
	}
	return false;
}