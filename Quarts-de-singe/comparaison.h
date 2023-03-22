#ifndef comparaison
#define comparaison
#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum {
	MIN_LETTRES = 2,			// Nombre minimal de lettres pour un mot dans le dictionnaire
	MAX_LETTRES = 26			// Nombre maximal de lettres pour un mot dans le dictionnaire
};

/**
 * @brief Prend un mot du dictionnaire et le copie dans la variable mot.
 * @param [in,out] mot : mot qui va �tre copi� � partir du dictionnaire.
 * @param [in] is : dictionnaire.
 */
void saisir_mot_dictionnaire(std::istream& is, char* mot);

/**
 * @brief Compare les mots du dictionnaire avec celui donn� en param�tre.
 * @param[in] mot : mot que l'utilisateur a voulu comparer.
 * @return true si le mot existe dans le dictionnaire.
 * @return false si le mot n'existe pas dans le dictionnaire.
 */
bool mot_existe_dans_dictionnaire(char *mot);

/**
 * @brief Compte le nombre de mots du dictionnaire.
 * @return le nombre de mots du dictionnaire.
 */
unsigned int nb_mots_dictionnaire();

/**
 * @brief Donne une liste de mots coh�rents avec le debut du mot pass� en param�tre.
 * @param[in,out] nb_mots_coherents : nombre de mots coh�rents.
 * @param[in] debut_mot : d�but du mot.
 * @param[in] longueur_debut_mot : longueur du d�but du mot.
 * @param[in] nb_mots_dictionnaire : nombre de mots pr�sents dans le dictionnaire.
 */
char** mot_coherent(char* debut_mot, unsigned int longueur_debut_mot, unsigned int* nb_mots_coherents, unsigned int nb_mots_dictionnaire);

#endif