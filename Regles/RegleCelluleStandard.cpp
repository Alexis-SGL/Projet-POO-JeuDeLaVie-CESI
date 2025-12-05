#include "RegleCelluleStandard.h"

namespace PatternRegles {
    //Règles Standard du jeu :
    //une cellule morte possédant exactement trois voisines vivantes devient vivante
    //Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt
    bool RegleCelluleStandard::calculerEtatSuivant(bool estVivant, int nbVoisins) const {
        if (estVivant) {
            return (nbVoisins==2 || nbVoisins==3);
        } else {
            return (nbVoisins==3);
        }
    }
}