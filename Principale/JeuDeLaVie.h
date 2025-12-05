#pragma once
#include <string>
#include "Grille.h"
#include "Fichier.h"

namespace Principale {
    class JeuDeLaVie {
    private:
        Grille* grille;
        int compteurIteration;
        int maxIteration;
        std::string cheminFichier;
        bool estTorique;
    public:
        JeuDeLaVie(std::string cheminFichier, int maxIter, bool estTorique); //Constructeur afin d'initialiser le jeu
        ~JeuDeLaVie(); //destructeur pour libérer la mémoire
        int getCompteurIteration() const; //getter pour le compteur d'iteration
        int getMaxIteration() const; //getter pour le nombre max d'iteration possible
        void jouerConsole(); //Pour lancer le jeu en mode console
        void jouerGraphique(); //Pour lancer le jeu en mode graphique
        void chargerFichier(std::string chemin); //charger la grille enregistrer dans un fichier dans le dossier /Data
    };
}