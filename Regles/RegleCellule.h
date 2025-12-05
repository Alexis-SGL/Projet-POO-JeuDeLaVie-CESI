#pragma once

namespace PatternRegles {
    class RegleCellule {
    public:
        virtual ~RegleCellule()=default;
        virtual bool calculerEtatSuivant(bool estVivant, int nbVoisins) const =0;
    };
}