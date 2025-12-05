#include "Fichier.h"
#include "Grille.h"
#include "../Etats/EtatVivant.h"
#include "../Etats/EtatMort.h"
#include <fstream>
#include <filesystem>
#include <sstream>

namespace Principale {
// ==============================================
// Constructeur 
// ==============================================

Fichier::Fichier(std::string chemin): path(std::move(chemin)) {} //On enregistre le chemin du fichier source
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : lecture() 
// ==============================================

    Grille* Fichier::lecture(bool estTorique) {
        std::ifstream file(path); //on ouvre le fichier en mode lecture
        if (!file.is_open()) { return nullptr; } //on ne continu pas le programme si le fichier ne s'ouvre pas
        int largeurFichier=0; //variable pour stocker la largeur de la grille enregistré dans le fichier
        int hauteurFichier=0; //variable pour stocker la hauteur de la grille enregistré dans le fichier
        file >> hauteurFichier >> largeurFichier; //lecture de la taille de la grille dans le fichier
        if (!file) { return nullptr; } //on ne continu pas si la lecture à échoué

        auto* grille = new Grille(largeurFichier, hauteurFichier, estTorique); //Création de la grille avec les dimenses lues et le mode choisi
        
        for (int y=0; y<hauteurFichier; ++y) { //parcours la grille en hauteur
            for (int x=0; x<largeurFichier; ++x) { //Parcours la grille en largeur
                int valeur=0; //initialisation d'une valeur qui définira l'état de la cellule (par défault la cellule est morte)
                file >> valeur; //lecture de la valeur dans le fichier texte
                auto* cell = grille->getCellule(x, y); //création d'un objet pour la cellule avec sa position
                if (!cell) continue; //Si la cellule n'existe pas, on passe à la suite
                if (valeur==1) { //si la valeur est 1, cela veut dire que la cellule est vivante
                    cell->setEtatActuel(new PatternEtat::EtatVivant()); //on met l'état actuel à EtatVivant()
                } else { //sinon
                    cell->setEtatActuel(new PatternEtat::EtatMort()); //l'état de la cellule est alors EtatMort()
                }
            }
        }
        return grille; //on retourne la grille sous forme de pointeur
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : ecriture() 
// ==============================================

    void Fichier::ecriture(const Grille& grille, int iteration, bool estTorique) {
        std::string strTorique=(estTorique ? "Torique" : "Classique"); //Co nversion du booléen en string pour l'écrire dans le nom du dossier
        std::filesystem::path p(path); //récuperer le nom du fichier source
        std::string base = p.stem().string(); //enlever l'extension du fichier
        std::string outDirName = "Data/" + base + "_" + strTorique + "_out"; //Création du nom du dossier où sera stocker les grilles
        std::filesystem::create_directories(outDirName); //Création du dossier pour stocker chaque itération

        std::ostringstream oss;
        oss << outDirName << "/iteration_" << iteration << ".txt"; //création du chemin complet du fichier de sortie
        std::ofstream out(oss.str()); //ouvrir le fichier en mode écriture
        if (!out.is_open()) { return; } //On ne continu pas si on a pas réussi à ouvrir le fichier

        int hauteurGrille = grille.getHauteur(); //récupére la hauteur de la grille
        int largeurGrille = grille.getLargeur(); //récupere la largeur de la grille

        out << hauteurGrille << " " << largeurGrille << "\n"; //écrit l'en-tête du fichier avec les dimensions
        for (int y=0; y<hauteurGrille; ++y) { //Parcours la grille en hauteur
            for (int x=0; x < largeurGrille; ++x) { //Parcours la grille en largeur
                auto* cell = grille.getCellule(x, y); //recherche les données sur chaque cellule selon la position 
                int v = cell ? cell->recupererAffichage() : 0; //recupere le symbole à afficher selon l'état de la cellule
                out << v; //l'écrire dans le fichier
                if (x < largeurGrille-1) { //si on est pas encore arriver à la fin de la ligne
                    out << " "; //on met un espace pour laisser de la place entre 2 symboles
                }
            }
            out << "\n"; //à la fin d'une largeur on saute une ligne
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
