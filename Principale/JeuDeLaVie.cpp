#include "JeuDeLaVie.h"
#include "Fichier.h"
#include "Grille.h"
#include "../Affichage/Console.h"
#include "../Affichage/FenetreGraphique.h"
#include <iostream>
#include <SFML/System.hpp>

namespace Principale {

// ==============================================
// Constructeur 
// ==============================================

    JeuDeLaVie::JeuDeLaVie(std::string chemin, int maxIter, bool estTorique) 
    : grille(nullptr), //initialisation d'une grille vide
      compteurIteration(0), //Initialisation du compteur d'itération à 0
      maxIteration(maxIter), //Nombre max d'itération à atteindre
      cheminFichier(chemin), //le chemin où est stocker le fichier source
      estTorique(estTorique)  //savoir si on utilise l'extension mode torique ou pas
    {
        chargerFichier(this->cheminFichier); //dès le debut, charger le fichier source
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Destructeur 
// ==============================================

    JeuDeLaVie::~JeuDeLaVie() {
        delete grille; //si une grille prend de la mémoire, alors libérer la mémoire allouée
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getCompteurIteration() 
// ==============================================

    int JeuDeLaVie::getCompteurIteration() const {
        return compteurIteration; //Getter pour savoir le nombre itération en cours
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getMaxIteration() 
// ==============================================

    int JeuDeLaVie::getMaxIteration() const {
        return maxIteration; //retourner le nombre max d'itération de la partie
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : chargerFichier() 
// ==============================================

    void JeuDeLaVie::chargerFichier(std::string chemin) {
        if(grille) delete grille; //nettoyage de l'ancienne grille si elle existe déjà
        Fichier f(chemin);   //création de l'objet Fichier pour gérer la lecture
        grille = f.lecture(this->estTorique); //lire le fichier et créer une nouvelle grille
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : jouerConsole() 
// ==============================================

    void JeuDeLaVie::jouerConsole() {
        if (!grille) return; //si grille est vide alors retourner
        Fichier fichier(cheminFichier);
        Affichage::Console console; //instancier l'affichage dans le terminal
        console.afficher(*grille); //Affichage de l'état initial
        fichier.ecriture(*grille, compteurIteration, estTorique);//Sauvegarder l'iteration 0
        while (compteurIteration<maxIteration && !grille->estStable()) { //boucle tant que le nombre max d'itérations n'est pas atteint et que la grille n'est pas stable
            grille->updateGrille();//Calcul de la génération suivante
            compteurIteration++; //incrémentation du compteur
            fichier.ecriture(*grille, compteurIteration, estTorique); //sauvegarde de la grille dans un fichier txt
            console.afficher(*grille); //affichage de la nouvelle grille dans la console
            sf::sleep(sf::milliseconds(200));
        }
        if (grille->estStable()) { std::cout << "\nLe jeu s'est stabilise a l'iteration " << compteurIteration << " !" << std::endl;
        } else {std::cout << "\nNombre maximum d'iterations atteint !" << std::endl; }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : jouerGraphique() 
// ==============================================

    void JeuDeLaVie::jouerGraphique() {
        if (!grille) return; //si pas de grille, on lance pas le jeu
        Fichier fichier(cheminFichier);
        Affichage::FenetreGraphique fenetre(grille->getLargeur(), grille->getHauteur(), (1000/grille->getLargeur())); //création de la fênetre graphique
        fichier.ecriture(*grille, compteurIteration, estTorique); //Sauvegarde l'iteration 0
        while (fenetre.estOuverte()) { //tant que la fênetre est ouverte, le jeu peut continuer
            fenetre.gererEvenements(); //gestion des cliques comme la fermeture de la fênetre
            if (compteurIteration<maxIteration  && !grille->estStable()) {//boucle tant que le nombre max d'itérations n'est pas atteint et que la grille n'est pas stable
                grille->updateGrille();//Calcul de la génération suivante
                compteurIteration++; //incrémentation du compteur
                fichier.ecriture(*grille, compteurIteration, estTorique); //sauvegarde de la grille dans un fichier txt
            }
            fenetre.afficher(*grille); //mettre à jour les cellules sur l'affichage graphique
            fenetre.updateFenetre();//Mettre à jour la fênetre avec un Windows.display()
            sf::sleep(sf::milliseconds(200)); //Delay de 200ms secondes pour voir l'évolution
        }
        if (grille->estStable()) { std::cout << "\nLe jeu s'est stabilise a l'iteration " << compteurIteration << " !" << std::endl;
        } else if(compteurIteration>=maxIteration) {std::cout << "\nNombre maximum d'iterations atteint !" << std::endl; }
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}