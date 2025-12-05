#pragma once
namespace Principale { class Grille; }

namespace Affichage {
    class Interface {
    public:
        virtual ~Interface() = default; //Destructeur virtuel
        virtual void afficher(const Principale::Grille& grille)=0; //afficher la grille selon le mode choisit
    };
}