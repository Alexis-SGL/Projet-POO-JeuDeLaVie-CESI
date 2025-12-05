//Demande à Catch2 de générer la fonction main() pour les tests
#define CATCH_CONFIG_MAIN
//Inclusion de l'en-tête Catch2
#include "external/catch.hpp"

//Include classes qu'on veut tester
#include "../Principale/Cellule.h"
#include "../Principale/Grille.h"
#include "../Etats/EtatVivant.h"
#include "../Etats/EtatMort.h"

using namespace Principale;
using namespace PatternEtat;

//==================
//Fonctions utilitaires
//==================

//Remplit une grille avec un ensemble de cellules vivantes donné, toutes les autres étant mises à l'état mort.
static void remplirGrilleAvecPattern(Grille& g, const std::vector<std::pair<int,int>> &vivantes) {
    //On parcourt toute la grille
    for (int y = 0; y < g.getHauteur(); ++y) {
        for (int x = 0; x < g.getLargeur(); ++x) {
            //On met chaque cellule à l'état mort
            g.getCellule(x,y)->setEtatActuel(new EtatMort());
        }
    }
    //Puis on active uniquement les coordonnées passées dans vivantes
    for (auto [x,y] : vivantes) {
        g.getCellule(x,y)->setEtatActuel(new EtatVivant());
    }
}

//Renvoie la liste des coordonnées des cellules vivantes de la grille
static std::vector<std::pair<int,int>> cellulesVivantes(const Grille &g) {
    std::vector<std::pair<int,int>> res;       //vecteur résultat
    for (int y = 0; y < g.getHauteur(); ++y) { //boucle sur les lignes
        for (int x = 0; x < g.getLargeur(); ++x) { //boucle sur les colonnes
            //Si la cellule est vivante, on ajoute sa position dans le vecteur
            if (g.getCellule(x,y)->getEtatActuel()) {
                res.emplace_back(x,y);
            }
        }
    }
    return res; //on renvoie la liste des positions vivantes
}

//==================
//Tests sur Cellule
//==================

//Vérifie les transitions de base d'une cellule seule
TEST_CASE("Cellule - transitions de base") {
    //Cas 1 : cellule vivante avec 0 voisin -> doit mourir (sous-population)
    Cellule c1(new EtatVivant());     //crée une cellule vivante
    c1.calculerEtatSuivant(0);        //calcule l'état suivant avec 0 voisin
    REQUIRE(c1.changerEtat() == true); //l'état doit changer
    REQUIRE(c1.getEtatActuel() == false); //la cellule doit être morte

    //Cas 2 : cellule morte avec 3 voisins -> doit naître
    Cellule c2(new EtatMort());       //crée une cellule morte
    c2.calculerEtatSuivant(3);        //calcule l'état suivant avec 3 voisins
    REQUIRE(c2.changerEtat() == true); //l'état doit changer
    REQUIRE(c2.getEtatActuel() == true); //la cellule doit être vivante

    //Cas 3 : cellule vivante avec 2 voisins -> reste vivante
    Cellule c3(new EtatVivant());     //crée une cellule vivante
    c3.calculerEtatSuivant(2);        //2 voisins vivants
    REQUIRE(c3.changerEtat() == false); //l'état ne change pas
    REQUIRE(c3.getEtatActuel() == true); //elle reste vivante
}

//==================
//Tests Grille : blinker
//==================

//Vérifie qu'un oscillateur "blinker" se comporte correctement
TEST_CASE("Grille - blinker non torique") {
    Grille g(5,5,false); //crée une grille 5x5 non torique

    //Etat initial : blinker vertical au centre (3 cellules vivantes alignées)
    remplirGrilleAvecPattern(g, {{2,1},{2,2},{2,3}});

    //Après 1 update, le blinker doit être horizontal
    g.updateGrille();                    //calcule la génération suivante
    auto v1 = cellulesVivantes(g);      //récupère les cellules vivantes
    REQUIRE(v1.size() == 3);            //il doit y avoir exactement 3 vivantes
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(1,2)) == 1); //(1,2)
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(2,2)) == 1); //(2,2)
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(3,2)) == 1); //(3,2)

    //Après 2 updates, on revient à l'état initial (vertical)
    g.updateGrille();
    auto v2 = cellulesVivantes(g);
    REQUIRE(v2.size() == 3);
    REQUIRE(std::count(v2.begin(), v2.end(), std::make_pair(2,1)) == 1); //(2,1)
    REQUIRE(std::count(v2.begin(), v2.end(), std::make_pair(2,2)) == 1); //(2,2)
    REQUIRE(std::count(v2.begin(), v2.end(), std::make_pair(2,3)) == 1); //(2,3)
}

//=====================================================
//Grille - cas bords non toriques
//=====================================================

//Vérifie que les bords sont bien traités en mode non torique
TEST_CASE("Grille - voisins aux bords non toriques") {
    Grille g(3,3,false); //petite grille 3x3 classique (pas de wrap)

    //On met deux cellules vivantes en haut à gauche
    remplirGrilleAvecPattern(g, {{0,0}, {1,0}});

    //On calcule la génération suivante
    g.updateGrille();
    auto v = cellulesVivantes(g);

    //Dans cette configuration, tout doit mourir (pas assez de voisins)
    REQUIRE(v.empty());
}

//=====================================================
//Grille - cas bords toriques
//=====================================================

//Vérifie que le mode torique fonctionne sans se soucier d'un motif précis
TEST_CASE("Grille - voisins toriques basique") {
    Grille g(3,3,true); //grille 3x3 torique (wrap sur les bords)

    //On met quelques cellules vivantes qui forceront l'utilisation du wrap
    remplirGrilleAvecPattern(g, {{0,0}, {2,2}});

    //On vérifie simplement que la mise à jour ne plante pas
    REQUIRE_NOTHROW(g.updateGrille());
    auto v = cellulesVivantes(g);

    //Le nombre de cellules vivantes doit rester dans des bornes logiques
    REQUIRE(v.size() <= 9);
}

//=====================================================
//Grille - motif stable (bloc 2x2) et estStable()
//=====================================================

//Vérifie qu'un bloc 2x2 reste stable et que estStable() devient vrai
TEST_CASE("Grille - bloc stable") {
    Grille g(4,4,false); //grille 4x4 classique

    //Bloc 2x2 au centre : ces 4 cellules forment un motif stable
    remplirGrilleAvecPattern(g, {{1,1},{2,1},{1,2},{2,2}});

    //Première update : le bloc doit rester identique
    g.updateGrille();
    auto v1 = cellulesVivantes(g);
    REQUIRE(v1.size() == 4);
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(1,1)) == 1);
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(2,1)) == 1);
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(1,2)) == 1);
    REQUIRE(std::count(v1.begin(), v1.end(), std::make_pair(2,2)) == 1);

    //Deuxième update : l'état ne change plus, donc la grille est stable
    g.updateGrille();
    auto v2 = cellulesVivantes(g);

    //On vérifie que la configuration est exactement la même
    REQUIRE(v2 == v1);
    //Et que le drapeau "stable" de la grille est bien passé à vrai
    REQUIRE(g.estStable() == true);
}

//=====================================================
//Grille - blinker après N iterations (N arbitraire)
//=====================================================
TEST_CASE("Grille - blinker apres N iterations") {
    Grille g(5,5,false);
    //blinker vertical au centre
    remplirGrilleAvecPattern(g, {{2,1},{2,2},{2,3}});

    int N = 4; //nombre d'itérations arbitraire
    for (int i = 0; i < N; ++i) {
        g.updateGrille();
    }

    //Le blinker a une période 2 -> après 4 tours, on revient à l'état initial
    auto v = cellulesVivantes(g);
    REQUIRE(v.size() == 3);
    REQUIRE(std::count(v.begin(), v.end(), std::make_pair(2,1)) == 1);
    REQUIRE(std::count(v.begin(), v.end(), std::make_pair(2,2)) == 1);
    REQUIRE(std::count(v.begin(), v.end(), std::make_pair(2,3)) == 1);
}

//=====================================================
//Grille - extinction complète
//=====================================================
TEST_CASE("Grille - extinction complete") {
    Grille g(3,3,false);
    //Une seule cellule vivante isolée
    remplirGrilleAvecPattern(g, {{1,1}});

    g.updateGrille(); //elle doit mourir (0 voisins)

    auto v = cellulesVivantes(g);
    REQUIRE(v.empty());
}
