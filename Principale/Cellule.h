#pragma once
#include "../Etats/EtatCellule.h"
#include "../Regles/RegleCellule.h"

namespace Principale {
    class Cellule {
    private:
        PatternEtat::EtatCellule* etatActuel;
        PatternEtat::EtatCellule* etatSuivant;
        PatternRegles::RegleCellule* regle;
    public:
        Cellule(PatternEtat::EtatCellule* etatInitial); //constructeur pour chaque cellule avec son état inital
        ~Cellule(); //desctructeur de cellule pour libérer de la mémoire
        void setEtatActuel(PatternEtat::EtatCellule* nouvelEtat); //Définir l'état actuel de la cellule
        bool getEtatActuel() const;//voir l'état actuel de la cellule
        void calculerEtatSuivant(int nbVoisins); //calculer l'état suivant avec le nombre de voisins autour de la cellule
        bool changerEtat(); //faire la mutation de l'état de la cellule pour la modifier
        int recupererAffichage() const; //recuperer le symbole de la cellule pour afficher lors de l'affichage console 
    };
}