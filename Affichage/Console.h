#pragma once
#include "Interface.h"
#include "../Principale/Grille.h"

namespace Affichage {
    class Console : public Interface {
    public:
        void afficher(const Principale::Grille& grille) override;
    };
}