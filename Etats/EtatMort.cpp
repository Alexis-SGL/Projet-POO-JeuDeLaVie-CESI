#include "EtatMort.h"

namespace PatternEtat {
    bool EtatMort::estVivant() const {
        return false; //retourne l'état vivant de la cellule
    }
    int EtatMort::affichageCellule() const {
        return 0; //indique que la cellule est morte lors de l'affichage console
    }
}