#pragma once

namespace PatternEtat {
    class EtatCellule {
    public:
        virtual ~EtatCellule()=default; //destructeur virtuel
        virtual bool estVivant() const=0; //indique l'état de la cellule 
        virtual int affichageCellule() const=0; //retourne le symbole associé à son état de vie 
    };
}