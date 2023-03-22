#ifndef jouer
#define jouer
#pragma once

#include <iostream>
#include "comparaison.h"
#include <ctime>
#include <cassert>
using namespace std;

enum {
	MIN_JOUEURS = 2,			// Nombre minimal de joueurs pouvant participer au jeu
	LONGUEUR_ALPHABET = 26,		// Longueur de l'alphabet
	MAX_QUARTS_SINGE = 1		// Verifier si marche pour les float. Si marche pas, remplacer par 4
};

/**
 * @brief Structure de donn�es de type Joueur
 */
struct Joueur {
	char nature;				// Nature du joueur : H (Humain), R (Robot) ou N (Non sp�cifi�)
	int pos;					// Position par rapport aux autres joueurs
	float qds = 0;				// Nombre de quarts de singe en possession du Joueur : augmente au fur et � mesure que le joueur perd
};

/** @brief Conteneur de joueurs allou�s en  
 *  m�moire	dynamique de capacit� nb_joueurs
 */
struct ConteneurTDE {
	unsigned int nb_joueurs;	// capacit� du conteneur (>0)
	Joueur* tab_joueurs;		// tableau allou� en m�moire dynamique
};

/**
 * @brief Initialise un tableau de joueurs
 * @param [in,out] conteneur_joueurs : conteneur qui doit �tre initialis�
 */
void initialiser_tab_joueurs(ConteneurTDE* conteneur_joueurs);

/**
 * @brief Lance une manche tant qu'aucun joueur n'a 4 quarts de singe.
 */
void lancer_jeu();

/**
 * @brief Demande un mot � chaque joueur jusqu'� ce qu'un joueur abandonne.
 * @param [in,out] conteneur_joueurs : le conteneur de joueurs
 * @param [in] premier_joueur : joueur qui commencera la manche
 * @return le joueur ayant perdu la manche
 */
Joueur lancer_manche(ConteneurTDE* joueurs, Joueur premier_joueur);

/**
 * @brief Ajoute un joueur � un conteneur.
 * @param [in,out] conteneur_joueurs : le conteneur de joueurs.
 * @param [in] indice_joueur : position du joueur par rapport aux autres.
 * @param [in] joueur_a_ajouter : le joueur � ajouter au conteneur.
 */
void ajouter_joueur(ConteneurTDE& conteneur_joueurs, unsigned int indice_joueur, const Joueur& joueur_a_ajouter);

/**
 * @brief Demande � l'utilisateur de saisir tous les joueurs participant au jeu.
 * @see initialiser_tab_joueurs pour l'initialisation du conteneur.
 * @return le conteneur de joueurs
 * @pre strlen(entree_joueurs) < MIN_JOUEURS
 */
ConteneurTDE saisir_joueurs();

/**
 * @brief Affiche le nombre de quarts de singe de chaque joueur.
 * @param[in] conteneur_joueurs : conteneur des joueurs participant au jeu
 */
void afficher_qds(ConteneurTDE conteneur_joueurs);

/**
 * @brief Affiche la position et la nature d'un joueur.
 * @param[in] joueur_courant : joueur � afficher
 */
void afficher_joueur(Joueur joueur_courant);

/**
 * @brief Demande au joueur pr�c�dent (� celui qui a appel� la fonction)
 * le mot auquel il pensait lorsqu'il a saisi son dernier caract�re.
 * @param[in,out] conteneur_joueurs : conteneur des joueurs participant au jeu.
 * @param[in] joueur_courant : joueur ayant fait appel � la fonction.
 * @param[in] mot_choisi : mot auquel pense le robot.
 */
void demander_mot_joueur_precedent(ConteneurTDE* conteneur_joueurs, Joueur joueur_courant, char* mot_choisi);

/**
 * @brief Indique si un joueur a 4 quarts de singe
 * @param[in] conteneur_joueurs : conteneur des joueurs participant au jeu
 * @return true si un joueur a 4 quarts de singe, false sinon
 */
bool joueur_a_4_qds(const ConteneurTDE& conteneur_joueurs);

/**
 * @brief Donne une lettre majuscule al�atoire comprise entre A et Z.
 * @return une lettre majuscule al�atoire.
 */
char lettre_aleatoire();

/**
 * @brief Donne une lettre possible pour compl�ter le mot.
 * S'il n'existe aucune lettre possible, on ajoute '!' pour signifier un abandon.
 * @param[in,out] mot_a_completer : mot que le robot va compl�ter.
 * param[in,out] mot_choisi : mot auquel le robot pense.
 * @param[in,out] fin_manche : indique si la manche est finie ou non.
 * @param[in] conteneur_joueurs : conteneur des joueurs partcipant.
 * @param[in] joueur_courant : joueur dont c'est le tour.
 * @param[in] longueur_mot : longueur du mot � compl�ter.
 */
char lettre_coherente(char* mot, char* mot_choisi, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche);

/**
 * @brief R�alise le tour du robot en appelant la fonction lettre_aleatoire ou lettre_coherente.
 * @see lettre_aleatoire dans le cas o� le robot doit saisir le premier caract�re du mot.
 * @see lettre_coherente dans le cas o� le robot doit saisir un autre caract�re.
 * @param[in,out] mot_a_completer : mot que le robot va compl�ter.
 * param[in,out] mot_choisi : mot auquel le robot pense.
 * @param[in,out] fin_manche : indique si la manche est finie ou non.
 * @param[in] conteneur_joueurs : conteneur des joueurs partcipant.
 * @param[in] joueur_courant : joueur dont c'est le tour.
 * @param[in] longueur_mot : longueur du mot � compl�ter.
 */
void robot(char* mot_a_completer, char* mot_choisi, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche);

/**
 * @brief Joue le tour d'un humain.
 * @param[in,out] mot_a_completer : mot devant �tre compl�t� par le joueur.
 * param[in,out] conteneur_joueurs : conteneur des joueurs participant au jeu.
 * param[in,out] joueur_courant : joueur humain dont c'est le tour.
 * param[in,out] fin_manche : indique si la manche est finie ou non.
 * param[in] mot_choisi : mot auquel pense le robot.
 */
void humain(char* mot_a_completer, unsigned int longueur_mot, ConteneurTDE* conteneur_joueurs, Joueur* joueur_courant, bool* fin_manche, char* mot_choisi);
#endif