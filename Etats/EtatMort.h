#pragma once
#include "EtatCellule.h"

namespace PatternEtat {
    class EtatMort : public EtatCellule {
    public:
        bool estVivant() const override; //indique l'état de la cellule Morte
        int affichageCellule() const override; //retourne le symbole associé à son état de vie 
    };
}