#include "EtatVivant.h"

namespace PatternEtat {
    bool EtatVivant::estVivant() const {
        return true; //retourne l'état vivant de la cellule
    }
    int EtatVivant::affichageCellule() const {
        return 1; //indique que la cellule est vivante lors de l'affichage console
    }
}