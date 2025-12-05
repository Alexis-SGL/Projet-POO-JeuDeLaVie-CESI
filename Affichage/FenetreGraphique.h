#pragma once
#include "Interface.h"
#include "../Principale/Grille.h"
#include <SFML/Graphics.hpp>

namespace Affichage {

    class FenetreGraphique : public Interface {
    private:
        sf::RenderWindow window; 
        int tailleCellule; 

    public:
        FenetreGraphique(int largeurGrille, int hauteurGrille, int tailleCellule); //créer la fênetre windows selon la taille de la grille
        ~FenetreGraphique();
        void afficher(const Principale::Grille& grille) override; //affichage des cellules vivantes sur la grille graphique
        void updateFenetre(); //Mettre à jour le fenêtre windows
        void gererEvenements(); //Gerer les cliques de l'utilisateur
        bool estOuverte() const; //savoir si la fênetre est toujours ouverte
    };
}