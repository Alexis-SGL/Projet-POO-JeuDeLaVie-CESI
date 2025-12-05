#pragma once
#include <vector>
#include <string>
#include "Cellule.h"

namespace Principale {
    class Grille {
    private:
        int largeur;
        int hauteur;
        std::vector<std::vector<Cellule*>> matrice;
        bool jeuStable;
        bool estTorique;
        bool calculTorique(int& x, int& y) const;
    public:
        Grille(int l, int h, bool estTorique);
        ~Grille();
        int getLargeur() const; //Getter pour la largeur de la grille
        int getHauteur() const; //Getter pour la hauteur de la grille
        void updateGrille(); //Fonction pour mettre à jour la grille
        Cellule* getCellule(int x, int y) const; //Obtenir les infos sur une cellule à un endroit précis
        int compterVoisins(int x, int y) const; //fonction pour compteur les voisins d'une cellule selon sa position
        bool estStable() const; //permet de savoir si la grille est stable, cela signifie que la grille entre 2 itérations est similaire
    };
}