#include <iostream>
#include "Console.h"
#include "../Principale/Cellule.h" //recupererAffichage()

namespace Affichage {
// ==============================================
// Méthodes : afficher() 
// ==============================================

    void Console::afficher(const Principale::Grille& grille) {
        std::cout << "\033[2J\033[1;1H"; //nettoyage du terminal (\033[2J efface tout le contenu du terminal) (\033[1;1H replace le curseur tout en haut à gauche)
        std::cout << "=== JEU DE LA VIE (Mode Console) ===" << std::endl;
        std::cout << "Largeur: " << grille.getLargeur() << " | Hauteur: " << grille.getHauteur() << std::endl;
        std::cout << "------------------------------------" << std::endl;
        for (int y = 0; y < grille.getHauteur(); ++y) { //parcours la grille en hauteur
            for (int x = 0; x < grille.getLargeur(); ++x) { //parcours la grille en largeur
                Principale::Cellule* c = grille.getCellule(x, y);
                //if (c) {
                //    std::cout << c->recupererAffichage(); //récupère le symbole selon l'état de la cellule
                //} else {
                //   std::cout << "? "; //sécurité visuelle si la case est vide
                //}
                int val = (c ? c->recupererAffichage() : 0); //récupère le symbole selon l'état de la cellule
                if (val == 1) { 
                    std::cout << "██"; //deux blocs pleins pour faire un carré blanc
                } else {
                    std::cout << "  "; //deux espaces pour faire du vide
                }
            }
            std::cout << std::endl; //Pour sauter de ligne à chaque fin de rangée
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}