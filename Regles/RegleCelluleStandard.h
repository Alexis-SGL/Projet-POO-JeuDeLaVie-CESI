#pragma once
#include "RegleCellule.h"

namespace PatternRegles {
    class RegleCelluleStandard : public RegleCellule {
    public:
        bool calculerEtatSuivant(bool estVivant, int nbVoisins) const override;
    };
}