#include <iostream>
#include <string>
#include <limits>
#include "Principale/JeuDeLaVie.h"
#include <filesystem>

int main(int argc, char* argv[]) {
    const std::string RESET = "\033[0m"; 
    std::cout << "" << std::endl;
    const std::string BLEU = "\033[34m";
    std::cout << BLEU << "       ░▒▓█▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓███████▓▒░░▒▓████████▓▒░      ░▒▓█▓▒░       ░▒▓██████▓▒░       ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓████████▓▒░ " << std::endl;
    std::cout << BLEU << "       ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░        " << std::endl;
    std::cout << BLEU << "       ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░       ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        " << std::endl;
    std::cout << BLEU << "       ░▒▓█▓▒░▒▓██████▓▒░ ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░        ░▒▓█▓▒░      ░▒▓████████▓▒░       ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░   " << std::endl;
    std::cout << BLEU << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░        " << std::endl;
    std::cout << BLEU << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░        " << std::endl;
    std::cout << BLEU << " ░▒▓██████▓▒░░▒▓████████▓▒░░▒▓██████▓▒░       ░▒▓███████▓▒░░▒▓████████▓▒░      ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░         ░▒▓██▓▒░  ░▒▓█▓▒░▒▓████████▓▒░ " << std::endl;
    std::cout << RESET << std::endl;

    //Choix du fichier source
    std::string cheminFichier;

    if (argc > 1) {
        cheminFichier = argv[1];
        if (!std::filesystem::exists(cheminFichier)) {
            std::cerr << "!! Le fichier passé en argument n'existe pas !" << std::endl;
            cheminFichier = ""; 
        }
    }
    if (cheminFichier.empty()) {
        std::cout << " !! Aucun fichier valide trouvé !" << std::endl;
        bool fichierTrouve = false;
        while (!fichierTrouve) {
            std::cout << "\nVeuillez entrer le chemin du fichier : ";
            std::cin >> cheminFichier;

            if (std::filesystem::exists(cheminFichier)) {
                std::cout << "Fichier trouvé avec succes !" << std::endl;
                fichierTrouve = true; 
            } else {
                std::cerr << "!! Le fichier '" << cheminFichier << "' est introuvable" << std::endl;
            }
        }
    }



    //Choix du nombre d'itérations
    int maxIterations=0;
    std::cout << "\nEntrez le nombre maximum d'iterations : ";
    while (!(std::cin >> maxIterations) || maxIterations<=0) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << "!! Entree invalide. Entrez un entier positif : ";
    }

    //Choix du mode torique (ponit technique supplémentaire)
    char choixTorique;
    bool estTorique=false;
    std::cout << "\nVoulez-vous activer le mode torique ? (o/n) : ";  std::cin >> choixTorique;
    while (choixTorique != 'o' && choixTorique != 'O' && choixTorique != 'n' && choixTorique != 'N') {
        std::cout << "\n!! Entrée invalide. Repondez par 'o' (oui) ou 'n' (non) : ";
        std::cin >> choixTorique;
    }
    if (choixTorique=='o' || choixTorique == 'O') {
        estTorique=true;
        std::cout << "Mode Torique activé" << std::endl;
    } else {
        std::cout << "Mode Classique" << std::endl;
    }

    Principale::JeuDeLaVie jeu(cheminFichier, maxIterations, estTorique); //Initialisation du jeu

    //Choix du mode d'affichage
    int choixMode = 0;
    std::cout << "\nChoisissez le mode d'affichage :" << std::endl;
    std::cout << "[1] -> Mode Console" << std::endl;
    std::cout << "[2] -> Mode Fênetre Graphique" << std::endl;
    std::cout << "Votre choix : ";
    std::cin >> choixMode;

    while (std::cin.fail() || (choixMode != 1 && choixMode != 2)) {
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        std::cout << "!! Choix inconnu. Veuillez taper 1 ou 2 : ";
        std::cin >> choixMode;
    }


    //Lancement du jeu
    if (choixMode==1) {
        jeu.jouerConsole();
        std::cout << "\nSimulation terminée. Verifiez le dossier de sortie (Data/..)" << std::endl;
    } 
    else if (choixMode == 2) {
        std::cout << "\nLancement de la fenetre graphique... " << std::endl;
        std::cout << "Fermez la fenetre pour quitter" << std::endl;
        jeu.jouerGraphique();
        std::cout << "\nFenetre fermée -> Fin du programme !" << std::endl;
    } 
    else {
        std::cerr << "Choix invalide -> Abandon !" << std::endl;
        return 1;
    }

    return 0;
}
