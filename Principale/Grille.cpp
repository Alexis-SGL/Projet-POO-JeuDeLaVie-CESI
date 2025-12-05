#include "Grille.h"
#include "Cellule.h"
#include "../Etats/EtatMort.h"
#include "../Regles/RegleCelluleStandard.h"
#include <iostream>

namespace Principale {

// ==============================================
// Constructeur 
// ==============================================

    Grille::Grille(int l, int h, bool torique) : largeur(l), hauteur(h), matrice(h, std::vector<Cellule*>(l, nullptr)), jeuStable(false), estTorique(torique) {
        for (int y = 0; y < hauteur; y++) { //fait une boucle autant de ligne que doit avoir la grille
            for (int x = 0; x < largeur; x++) { //fait une boucle autant de colonne que doit la grille
                matrice[y][x] = new Cellule(new PatternEtat::EtatMort()); //créer pour chaque position une cellule avec un état mort par défault
            }
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Destructeur 
// ==============================================

    Grille::~Grille() { //détruit chaque cellule de la grille
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                delete matrice[y][x];
            }
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getlargeur() 
// ==============================================

    int Grille::getLargeur() const {
        return largeur; //retourne de l'attribut de la largeur de la grille
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getHauteur() 
// ==============================================

    int Grille::getHauteur() const {
        return hauteur; //retourne l'attribut de la hauteur de la grille
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getCellule() 
// ==============================================

    Cellule* Grille::getCellule(int x, int y) const {
        if (x<0 || x>=largeur || y<0 || y>=hauteur) { //si on cherche une cellule hors de la grille
            return nullptr; //alors retourne rien
        }
        return matrice[y][x]; //sinon on retourne le pointeur vers un objet cellule
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : calculTorique() 
// ==============================================

bool Grille::calculTorique(int& x, int& y) const {
    if (!estTorique) { //si le mode torique n'est pas activé
        return (x >= 0 && x < largeur && y >= 0 && y < hauteur); //on vérifie juste si on est dans les limites
    }

    //si le mode est activé, on applique la logique du Tore
    x= (x + largeur)%largeur; //si on sort trop à droite on passe à la premiere cellule de gauche, et inversement
    //Si x=-1 : (-1+10)%10 = 9

    y= (y + hauteur)%hauteur; //c'est la même logique mais en haut et en bas

    return true;
}

// ==============================================
// Méthodes : compterVoisins() 
// ==============================================

    int Grille::compterVoisins(int x, int y) const {
        int nbVoisin=0; //initialisation du compteur de voisins
        for (int dx= -1; dx<=1; dx++) { //on parcourt les _ voisins de la cellule
            for (int dy = -1; dy<=1; dy++) {
                if (dx==0 && dy==0) continue; //si c'est la cellule elle-même, on passe
                int nx=x+dx; //on recupere la position des voisins en largeur
                int ny=y+dy; //on recupere la position des voisins en hauteur
                if (calculTorique(nx, ny)) { //on regarde si on est en mode torique et si oui on modifie les valeurs et nx ny pour correspondre à la logique de Tore
                    if (matrice[ny][nx]->getEtatActuel()) { //Si la case est valide on regarde si elle est vivante
                        nbVoisin++; //Si oui alors on incrémente le compteur des voisins
                    }
                }
            }
        }
        return nbVoisin; //on retourne le nombre de voisins
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : updateGrille() 
// ==============================================

    void Grille::updateGrille() {
        //Calcul chaque état suivant de chaque cellule
        for (int y = 0; y < hauteur; y++) { //parcours la grille en hauteur
            for (int x = 0; x < largeur; x++) { //parcours la grille en largeur
                int voisins = compterVoisins(x, y); //appeler la fonction compterVoisins() pour obtenir le nombre de voisins de la cellule
                matrice[y][x]->calculerEtatSuivant(voisins); //selon le nombre de voisins, on regarde ce que la cellule devient, on calcule son prochain état
            }
        }
        this->jeuStable=true; //on part du principe que la grille est stable, c'est la même que avant

        //Faire la mutation des états de chaque cellule
        for (int y = 0; y < hauteur; y++) {//Parcours la grille en hauteur
            for (int x = 0; x < largeur; x++) { //parcours la grille en largeur
                if (matrice[y][x]->changerEtat() == true) { this->jeuStable=false; } //on fait le changement d'état de chaque cellule, et si il y a un changement, alors on passe la varible jeuStable à false
            }
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : estStable() 
// ==============================================

    bool Grille::estStable() const {
            return jeuStable; //retourne la valeur pour savoir si le jeu est stable
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}