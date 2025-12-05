#include <SFML/Graphics.hpp> //permet de créer des fenêtres et de dessiner des formes
#include <vector> //pour utiliser des vecteurs dynamiques
#include <ctime> //pour générer des nombres aléatoires
#include <cstdlib> //pour générer des nombres aléatoires
#include "FenetreGraphique.h"
#include "../Principale/Cellule.h" //pour accéder à getEtatActuel()

namespace Affichage {
// ==============================================
// Constructeur 
// ==============================================

    FenetreGraphique::FenetreGraphique(int largeurGrille, int hauteurGrille, int tailleCellule) 
        : tailleCellule(tailleCellule) {
        int largeurPixel = largeurGrille * tailleCellule; //pixel de cellule * nb cellule en largeur
        int hauteurPixel = hauteurGrille * tailleCellule; //pixel de cellule * nb cellule en hauteur
        this->window.create(sf::VideoMode(largeurPixel, hauteurPixel), "Projet POO : Jeu de la Vie | Groupe 2"); //crée une fenêtre de taille : pixel de cellule * nb cellule
        this->window.setFramerateLimit(60);
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Destructeur 
// ==============================================

    FenetreGraphique::~FenetreGraphique() {
        if (this->window.isOpen()) { //si la fenetre est ouverte
            this->window.close(); //alors la fermé lors de la desctuction de l'objet
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : afficher() 
 // ==============================================

    void FenetreGraphique::afficher(const Principale::Grille& grille) {
        this->window.clear(sf::Color::White); //efface l’ancienne image
        sf::RectangleShape cell(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f)); //crée un carré représentant une cellule 
        cell.setFillColor(sf::Color::Black); //couleur de la cellule
        for (int y = 0; y < grille.getHauteur(); ++y) { //parcours la grille en hauteur
            for (int x = 0; x < grille.getLargeur(); ++x) { //parcours la grille en largeur
                Principale::Cellule* c = grille.getCellule(x, y); //recupère les infos sur la cellule en question
                if (c->getEtatActuel() == true) { //la cellule est vivante alors elle est dessinée.
                    cell.setPosition(x * tailleCellule, y * tailleCellule);  //place la cellule au bon endroit dans la fenêtre
                    this->window.draw(cell); //dessine la cellule
                }
            }
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : updateFenetre() 
// ==============================================

    void FenetreGraphique::updateFenetre() {
        this->window.display(); //affiche tout ce qui a été dessiné
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : gererEvenements() 
// ==============================================

    void FenetreGraphique::gererEvenements() {
        sf::Event event;
        while (this->window.pollEvent(event)) { //continue tant que la fenêtre est ouverte
            if (event.type == sf::Event::Closed) { //si l’utilisateur ferme la fenêtre
                this->window.close(); //ferme la fenêtre correctement
            }
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ==============================================
// Méthodes : estOuverte() 
// ==============================================

    bool FenetreGraphique::estOuverte() const {
        return this->window.isOpen(); //Pour savoir si la fenetre est encore ouverte
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}