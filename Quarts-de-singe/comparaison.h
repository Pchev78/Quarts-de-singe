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
 * @param [in,out] mot : mot qui va être copié à partir du dictionnaire.
 * @param [in] is : dictionnaire.
 */
void saisir_mot_dictionnaire(std::istream& is, char* mot);

/**
 * @brief Compare les mots du dictionnaire avec celui donné en paramètre.
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
 * @brief Donne une liste de mots cohérents avec le debut du mot passé en paramètre.
 * @param[in,out] nb_mots_coherents : nombre de mots cohérents.
 * @param[in] debut_mot : début du mot.
 * @param[in] longueur_debut_mot : longueur du début du mot.
 * @param[in] nb_mots_dictionnaire : nombre de mots présents dans le dictionnaire.
 */
char** mot_coherent(char* debut_mot, unsigned int longueur_debut_mot, unsigned int* nb_mots_coherents, unsigned int nb_mots_dictionnaire);

#endif