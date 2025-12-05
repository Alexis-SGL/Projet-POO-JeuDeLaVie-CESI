#pragma once
#include "EtatCellule.h"

namespace PatternEtat {
    class EtatVivant : public EtatCellule {
    public:
        bool estVivant() const override; //indique l'état de la cellule Vivante
        int affichageCellule() const override; //retourne le symbole associé à son état de vie 
    };
}