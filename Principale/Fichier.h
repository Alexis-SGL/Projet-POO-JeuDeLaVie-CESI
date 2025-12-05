#pragma once

#include <string>

namespace Principale {
    class Grille;

    class Fichier {
    private:
        std::string path;
    public:
        Fichier(std::string chemin);
        Grille* lecture(bool estTorique); //pointeur pour voir juste l'adresse et pas tout le temps copier la grille entièrement
        void ecriture(const Grille& grille, int iteration, bool estTorique); //Ecriture dans un dossier specifique en fonction du nom du fichier source a chaque itération
    };
}
